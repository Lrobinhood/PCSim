#ifndef EventManager_H
#define EventManager_H

#include <map>

#ifndef _WIN32
#include "utils/Log.h"
#define LOG_TAG "XXX"
#endif

/*
  stl iterator is not thread safe,
  introduced more restrictions on this const-like list.
  define USE_ARRAY bellow to use array for simplicity.
*/
#define USE_ARRAY

/*check before use*/
#define MAX_EVT_HANDLER 32

class EventManager
{
   public:
   typedef void (*EventHandler)(unsigned int code, const void *data, unsigned int data_size);

   /**
    * @brief Add an event handler to the manager that is called for each event.
    * @param handler Pointer to an event handler function.
    */
   static void addEventHandler(EventHandler handler)
   {
      EventManager& manager = instance();
#ifdef USE_ARRAY
      for (int i = 0; i < manager.m_handlercnt; i++) {
          if (manager.m_handlers[i] == handler)
              return;
      }
      manager.m_handlers[manager.m_handlercnt] = handler;
      manager.m_handlercnt++;
#else
      if (std::find(manager.m_eventhandlers.begin(), manager.m_eventhandlers.end(), handler) == manager.m_eventhandlers.end())
      {
         manager.m_eventhandlers.push_back(handler);
      }
#endif
   }

   /**
    * @brief Send event to each event handler.
    */
   static void event(unsigned int code, void *data, unsigned int data_size)
   {
      EventManager& manager = instance();
#ifdef USE_ARRAY
      for (int i = 0; i < manager.m_handlercnt; i++) {
          manager.m_handlers[i](code, data, data_size);
      }
#else
      for (std::list<EventHandler>::iterator it = manager.m_eventhandlers.begin(); it != manager.m_eventhandlers.end(); ++it)
      {
         (*it)(code, data, data_size);
      }
#endif
   }

   private:
	EventManager() {
#ifdef USE_ARRAY
        memset(m_handlers, 0, sizeof(m_handlers));
        m_handlercnt = 0;
#endif
    };
   EventManager(EventManager const&);
   EventManager& operator=(EventManager const&);

   static EventManager& instance()
   {
      static EventManager instance;
      return instance;
   }

#ifdef USE_ARRAY
   EventHandler m_handlers[MAX_EVT_HANDLER];
   int m_handlercnt;
#else
   std::list<EventHandler> m_eventhandlers;
#endif
};

#endif // EventManager_H

