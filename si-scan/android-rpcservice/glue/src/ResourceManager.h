#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//#include "common.h"
#include <map>

#define TAG "ResouceManager"

class ResourceManager
{
   public:
   enum Resource
   {
      InitialiseDvb,
      ActivePath
   };
   enum ResourcePriority
   {
      ResourcePriorityHighest = 300,
      ResourcePriorityDelete = 200,
      ResourcePriorityScan = 100,
      ResourcePriorityTune = 90,
      ResourcePriorityBgScan = 80,
      ResourcePriorityPlay = 50
   };

   typedef void (*ReleaseResource)(Resource resource);

   /**
    * @brief Acquire resource.
    * @param resource The resource to acquire.
    * @param acquirer A pointer that uniquely identifies the acquirer.
    * @param release_callback A function that when called must release the resource before returning.
    */
   static bool acquire(Resource resource, const void *acquirer, ReleaseResource release_callback, int priority = 50)
   {
      assert(acquirer);

      ResourceManager& manager = instance();

      bool acquired = true;

     CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> mutex lock - acquire resource:%d", GetAcquirerName(acquirer).c_str(), resource);
      STB_OSMutexLock(manager.mutex);

      std::map<Resource, Acquisition>::iterator it = manager.m_resources.find(resource);
      if (it != manager.m_resources.end())
      {
         if (it->second.acquirer != acquirer)
         {
            if (it->second.priority < priority)
            {
               if (it->second.release_callback)
               {
                 CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> call release_callback - resource:%d",
                        GetAcquirerName(it->second.acquirer).c_str(), resource);
                  it->second.release_callback(resource);
               }
            }
            else
            {
               acquired = false;
            }
         }
         else
         {
             if (priority == ResourcePriorityScan)
             {
                if (it->second.release_callback)
                {
                    CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> scan call release_callback - resource:%d",
                           GetAcquirerName(it->second.acquirer).c_str(), resource);
                     it->second.release_callback(resource);
                }
             }
         }
      }

      if (acquired)
      {
         manager.m_resources[resource] = Acquisition(acquirer, release_callback, priority);
        CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> aquire resouce: %d", GetAcquirerName(acquirer).c_str(), resource);
      }

     CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> mutex unlock - acquire resource:%d", GetAcquirerName(acquirer).c_str(), resource);
      STB_OSMutexUnlock(manager.mutex);

      return acquired;
   }

   /**
    * @brief Once the resource is released, this method must be called.
    * @param resource The resource that was released.
    * @param acquirer The pointer that was used to uniquely identify the acquirer.
    */
   static void released(Resource resource, const void *acquirer)
   {
      assert(acquirer);

      ResourceManager& manager = instance();

     CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> mutex lock - release resource:%d", GetAcquirerName(acquirer).c_str(), resource);
      STB_OSMutexLock(manager.mutex);

      std::map<Resource, Acquisition>::iterator it = manager.m_resources.find(resource);
      if (it != manager.m_resources.end())
      {
         if (it->second.acquirer == acquirer)
         {
           CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> relsease resouce: %d", GetAcquirerName(acquirer).c_str(), resource);
            manager.m_resources.erase(it);
         }
      }

     CERT_LOG_DEBG(TAG, "[ResourceManager] <%s> mutex unlock - release resource:%d", GetAcquirerName(acquirer).c_str(), resource);
      STB_OSMutexUnlock(manager.mutex);

   }

   private:
   struct Acquisition
   {
      Acquisition() :
         acquirer(0), release_callback(0), priority(0) {}
      Acquisition(const void *acquirer, ReleaseResource release_callback, int priority) :
         acquirer(acquirer), release_callback(release_callback), priority(priority) {}
      const void *acquirer;
      ReleaseResource release_callback;
      int priority;
   };

   ResourceManager()
   {
      if (!mutex)
      {
        CERT_LOG_DEBG(TAG, "[ResourceManager] create mutex");
         mutex = STB_OSCreateMutex();
      }
   };
   ~ResourceManager()
   {
      if (mutex)
      {
        CERT_LOG_DEBG(TAG, "[ResourceManager] delete mutex");
         STB_OSDeleteMutex(mutex);
         mutex = NULL;
      }
   };
   ResourceManager(ResourceManager const&);
   ResourceManager& operator=(ResourceManager const&);

   static ResourceManager& instance()
   {
      static ResourceManager instance;
      return instance;
   }

   static std::string GetAcquirerName(const void *acquirer)
   {
      const std::string& acquirer_name = ((Glue::Interface *)acquirer)->getname();
      if (acquirer_name.empty()) {
         return "unknown";
      }

      return acquirer_name;
   }

   std::map<Resource, Acquisition> m_resources;
   void *mutex = NULL;
};

#endif // RESOURCEMANAGER_H

