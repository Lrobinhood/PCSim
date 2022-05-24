#ifndef GLUE_GLUE_H
#define GLUE_GLUE_H

#include "RequestData.h"
#include "ResponseData.h"
#include "RequestDataStub.h"
#include "ResponseDataStub.h"
#include "RequestDataJSON.h"
#include "ResponseDataJSON.h"

#include <string>
#include <map>
#include <list>
#include <algorithm>

#ifndef _WIN32
#include <utils/Log.h>
#define LOG_TAG "Glue"
#endif
/*
  stl iterator is not thread safe,
  introduced more restrictions on this const-like list.
  define USE_ARRAY bellow to use array for simplicity.
*/
#define USE_ARRAY

/*check before use*/
#define MAX_INVOKABLE_PER_INTERFACE 128
#define MAX_INTERFACE 32
#define MAX_SIGNAL_HANDLER 32

/**
 * @defgroup metaapi Meta-API
 * The Meta-API is the API that clients of glue services use.
 */

class Glue
{
   public:
   class Interface
   {
      public:
      typedef bool (Interface::*Invokable)(RequestData*, ResponseData*);

      void setname(const std::string &name) {m_name = name;}
      std::string& getname() { return m_name;}

      /**
       * @brief Invoke an invokable function.
       * @param name Invokable name.
       * @param request Request data.
       * @param response Response data.
       */
      bool invoke(const std::string& invokable, RequestData* request, ResponseData* response)
      {
         return invoke(invokable, request, response, true);
      }

      bool invoke(const std::string& invokable, RequestData* request, ResponseData* response, bool decorator)
      {
#ifdef USE_ARRAY
         for (int i = 0; i < m_invcnt; i++) {
             if (invokable.compare(m_inv[i].name) == 0) {
                 if (m_inv[i].inv != nullptr) {
                    bool ret;
                    InvokableInDecorator();
                    ret = (this->*(m_inv[i].inv))(request, response);
                    InvokableOutDecorator();
                    return ret;
                 }
             }
         }
         return false;
#else
         std::map<std::string, Invokable>::iterator it = m_invokable.find(invokable);
         return (it == m_invokable.end()) ? false : (this->*(it->second))(request, response);
#endif
      }
      /**
       * @brief Invoke an invokable function without request or response data (default arguments).
       * @param name Invokable name.
       * @param request Request data.
       * @param response Response data.
       */
      bool invoke(const std::string& invokable)
      {
         return invoke(invokable, true);
      }

      bool invoke(const std::string& invokable, bool decorator)
      {
         RequestDataStub request;
         ResponseDataStub response;
#ifdef USE_ARRAY
         for (int i = 0; i < m_invcnt; i++) {
             if (invokable.compare(m_inv[i].name) == 0) {
                 if (m_inv[i].inv != nullptr) {
                    bool ret;
                    InvokableInDecorator();
                    ret = (this->*(m_inv[i].inv))(&request, &response);
                    InvokableOutDecorator();
                    return ret;
                 }
             }
         }
         return false;
#else
         std::map<std::string, Invokable>::iterator it = m_invokable.find(invokable);
         return (it == m_invokable.end()) ? false : (this->*(it->second))(&request, &response);
#endif
      }

      protected:
      Interface(){
#ifdef USE_ARRAY
         m_inv = new inv_t[MAX_INVOKABLE_PER_INTERFACE];
         for (int i = 0; i < MAX_INVOKABLE_PER_INTERFACE; i++) {
             m_inv[i].name = "";
             m_inv[i].inv = nullptr;
         }
         m_invcnt = 0;
#endif
      };
      virtual ~Interface(){delete []m_inv;};

      /**
       * @brief Add an invokable function to this interface.
       * @param name Invokable name.
       * @param invokable Function pointer.
       */
      template <class T>
      void addInvokable(const std::string& name, bool (T::*invokable)(RequestData*, ResponseData*))
      {
#ifdef USE_ARRAY
         m_inv[m_invcnt].name = name;
         m_inv[m_invcnt].inv = static_cast<Invokable>(invokable);
         m_invcnt++;
#else
         m_invokable[name] = static_cast<Invokable>(invokable);
#endif
      }

      /**
       * @brief Send signal to each signal handler added to the glue instance.
       * @param signal Signal name.
       * @param invokable Pointer to an invokable function that populates ResponseData for the signal.
       */
      void signal(const std::string &signal)
      {
         Glue::signal(signal, 0, 0, NULL, 0);
      }

      void signal(const std::string &signal, int id)
      {
         Glue::signal(signal, 0, 0, NULL, id);
      }

      /**
       * @brief Send signal to each signal handler added to the glue instance.
       * @param signal Signal name.
       * @param invokable Pointer to an invokable function that populates ResponseData for the signal.
       */
      template <class T>
      void signal(const std::string &signal, bool (T::*invokable)(RequestData*, ResponseData*), RequestData* request)
      {
         Glue::signal(signal, static_cast<Interface::Invokable>(invokable), static_cast<Interface *>(&T::instance()), request, 0);
      }

      template <class T>
      void signal(const std::string &signal, bool (T::*invokable)(RequestData*, ResponseData*), RequestData* request, int id)
      {
         Glue::signal(signal, static_cast<Interface::Invokable>(invokable), static_cast<Interface *>(&T::instance()), request, id);
      }

      template <class T>
      void signal(const std::string &signal, bool (T::*invokable)(RequestData*, ResponseData*), int id)
      {
         Json::Value v;
         v[0] = id;
         RequestDataJSON request(v);
         Glue::signal(signal, static_cast<Interface::Invokable>(invokable), static_cast<Interface *>(&T::instance()), &request, id);
      }

      virtual void InvokableInDecorator(void) {};
      virtual void InvokableOutDecorator(void) {};

      private:
      Interface(Interface const&);
      Interface& operator=(Interface const&);
      std::map<std::string, Invokable> m_invokable;
#ifdef USE_ARRAY
      typedef struct {
          std::string name;
          Invokable inv;
      } inv_t;

      inv_t *m_inv;
      int m_invcnt;
#endif

        std::string m_name;

   };

   typedef void (*SignalHandler)(const std::string &signal, Interface::Invokable invokable, Glue::Interface *invokable_object, RequestData* request, int id);

   /**
    * @brief Add an interface to the glue.
    * @param name Interface name.
    */
   template <class T>
   static void addInterface(const std::string &name)
   {
      Glue& glue = instance();
      T& interface = T::instance();

      interface.setname(name);

#ifdef USE_ARRAY
      glue.m_intfs[glue.m_intfcnt].name = name;
      glue.m_intfs[glue.m_intfcnt].intf = &interface;
      glue.m_intfcnt++;
#else
      glue.m_interfaces[name] = &interface;
#endif
   }

   /**
    * @brief Add a signal handler to the glue that is called for each signal.
    * @param handler Pointer to a signal handler function.
    */
   static void addSignalHandler(SignalHandler handler)
   {
      Glue& glue = instance();
#ifdef USE_ARRAY
      for(int i = 0; i < glue.m_sigcnt; i++) {
          if (glue.m_sigs[i] == handler)
              return;
      }
      glue.m_sigs[glue.m_sigcnt] = handler;
      glue.m_sigcnt++;
#else
      if (std::find(glue.m_signalhandlers.begin(), glue.m_signalhandlers.end(), handler) == glue.m_signalhandlers.end())
      {
         glue.m_signalhandlers.push_back(handler);
      }
#endif
   }

   /**
    * @brief Invoke an invokable function.
    * @param name Interface name.
    * @param name Invokable name.
    * @param request Request data.
    * @param response Response data.
    */
   static bool invoke(const std::string &interface, const std::string& invokable, RequestData* request, ResponseData* response)
   {
      Glue& glue = instance();
#ifdef USE_ARRAY
      for (int i = 0; i < glue.m_intfcnt; i++) {
          if ((interface.compare(glue.m_intfs[i].name) == 0)) {
              if (glue.m_intfs[i].intf != nullptr) {
                  return glue.m_intfs[i].intf->invoke(invokable, request, response);
              }
          }
      }
#else
      std::map<std::string, Interface*>::iterator it = glue.m_interfaces.find(interface);
      if (it != glue.m_interfaces.end())
      {
         return it->second->invoke(invokable, request, response);
      }
#endif

      return false;
   }

   /**
    * @brief Send signal to each signal handler.
    * @param signal Signal name.
    * @param invokable Pointer to an invokable function that populates ResponseData for the signal.
    * @param invokable_object An object that invokable is a member of.
    */
   static void signal(const std::string &signal, Interface::Invokable invokable, Interface *invokable_object, RequestData* request, int id)
   {
      Glue& glue = instance();
#ifdef USE_ARRAY
      for (int i = 0; i < glue.m_sigcnt; i++) {
         if (glue.m_sigs[i])
          glue.m_sigs[i](signal, invokable, invokable_object, request, id);
      }
#else
      for (std::list<SignalHandler>::iterator it = glue.m_signalhandlers.begin(); it != glue.m_signalhandlers.end(); ++it)
      {
         (*it)(signal, invokable, invokable_object, request, id);
      }
#endif
   }

   private:
   static Glue& instance()
   {
      static Glue instance;
      return instance;
   }

	Glue() {
#ifdef USE_ARRAY
        m_intfs = new intf_t[MAX_INTERFACE];
        for (int i = 0; i < MAX_INTERFACE; i++) {
            m_intfs[i].name = "";
            m_intfs[i].intf = nullptr;
        }
        m_intfcnt = 0;

        memset(m_sigs, 0, sizeof(m_sigs));
        m_sigcnt = 0;
#endif
   }
   Glue(Glue const&);
   Glue& operator=(Glue const&);

    ~Glue() {
#ifdef USE_ARRAY
     delete []m_intfs;
#endif
      }


#ifdef USE_ARRAY
   typedef struct _s_m {
       std::string name;
       Interface *intf;
   } intf_t;

   intf_t *m_intfs;
   int m_intfcnt;

   SignalHandler m_sigs[MAX_SIGNAL_HANDLER];
   int m_sigcnt;
#else
   std::map<std::string, Interface*> m_interfaces;
   std::list<SignalHandler> m_signalhandlers;
#endif
};

#endif

