#include <stdlib.h>
#include <string.h>

#include <json/json.h>

#include "EventManager.h"
#include "DvbsInterface.h"

#include "autotest_interface.h"

#define TAG "AUTOTEST-INTERFACE"


static std::string Request(const std::string& resource, const std::string& json);
static bool ParseResource(const std::string& resource, std::string* interface, std::string* invokable);

extern "C" void M7_UI_Handle_OPELIST_SELECT_NOTIFY();
extern "C" void M7_UI_Handle_DISEQC_CONFIRM_NOTIFY();
extern "C" void M7_UI_Handle_REGION_SELECT_NOTIFY();

extern "C"
{
#include "stberc.h"
#include "cert_log.h"

    void autotest_interface_notify(unsigned int event, void *event_data, unsigned int data_size)
    {
        EventManager::event(event, event_data, data_size);

        if (STB_EVENT_SEARCH_M7_OPELIST_SELECT_NOTIFY == event)
        {
            M7_UI_Handle_OPELIST_SELECT_NOTIFY();
        }
        else if (STB_EVENT_SEARCH_M7_DISEQC_CONFIRM_NOTIFY == event)
        {
            M7_UI_Handle_DISEQC_CONFIRM_NOTIFY();
        }
        else if (STB_EVENT_SEARCH_M7_REGION_SELECT_NOTIFY == event)
        {
            M7_UI_Handle_REGION_SELECT_NOTIFY();
        }
    }

    void autotest_interface_reginterface()
    {
        //static DvbsInterface& instance = DvbsInterface::instance();

        Glue::addInterface<DvbsInterface>("Dvbs");
    }

    void autotest_interface_request(char *resource, char *json)
    {
        std::string res_string = resource;
        std::string json_string = json;

        Request(res_string, json_string);
    }

}

static bool ParseResource(const std::string &resource, std::string *interface, std::string *invokable)
{
   std::istringstream iss(resource);

   if (interface && invokable)
   {
      std::getline(iss, *interface, '.');
      std::getline(iss, *invokable, '.');

      return (*interface != "" && *invokable != "");
   }

   return false;
}

std::string Request(const std::string& resource, const std::string& json)
{
    Json::Value response(Json::objectValue);
    Json::Value request;

    response["accepted"] = false;
    response["data"] = "Bad request";

    std::string interface;
    std::string invokable;
    if (ParseResource(resource, &interface, &invokable)) {
        Json::Reader reader;
        if (reader.parse(json, request) && request.isArray()) {
            RequestDataJSON request_data(request);
            ResponseDataJSON response_data(&response["data"]);
            response["accepted"] = Glue::invoke(interface, invokable, &request_data, &response_data);
            response_data.finish();
        }
    }

    Json::FastWriter writer;
    std::string reply(writer.write(response));

    CERT_LOG_INFO(TAG, "request : %s json:%s", resource.c_str(), json.c_str());
    CERT_LOG_INFO(TAG, "reply : %s", reply.c_str());

    return reply;
}




