#include <stdlib.h>
#include <string.h>

#include <json/json.h>
#include <iostream>

#include "Glue.h"
#include "RequestData.h"
#include "ResponseData.h"



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

static void parse_region_setting_para(Json::Value root)
{
    unsigned int num = 0;
     
    num = root.size();

    for (unsigned int loop = 0; loop < num; loop++)
    {
        std::string a = root[loop]["RegionName"].asString();
        std::string b = root[loop]["SetRegion"].asString();

        std::cout << "a:" << a << " b:" << b << std::endl;
    }
}
static bool invoke_test(RequestData* request, ResponseData* response)
{
    RequestDataJSON* request_json = dynamic_cast<RequestDataJSON*>(request);

    unsigned int cmd = request_json->shiftUInt32(0);

#if 1
    Json::Value root = request_json->shiftJsonValue();

    if (!root.isNull())
    {
        parse_region_setting_para(root);
    }
#endif

    return true;
}
static std::string Request(const std::string& resource, const std::string& json)
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
            
            response["accepted"] = invoke_test(&request_data, &response_data);
            
            response_data.finish();
        }
    }

    Json::FastWriter writer;
    std::string reply(writer.write(response));

    return reply;
}

void autotest_interface_request(char *resource, char *json)
{
    std::string res_string = resource;
    std::string json_string = json;

    Request(res_string, json_string);
}

extern "C" void test_autotest_interface_request()
{
    char cmd[1024];
    char item[128];

    // Get Region
    sprintf(cmd, "[%d, [", 0x00010007);

    sprintf(item,"{\"RegionName\":\"%s\", \"SetRegion\":\"%s\"}", "A", "B");

    strcat(cmd, item);

    strcat(cmd, ", ");

    sprintf(item,"{\"RegionName\":\"%s\", \"SetRegion\":\"%s\"}", "C", "D");
    
    strcat(cmd, item);

    sprintf(item, "]]");

    strcat(cmd, item);

    printf("%s\n", cmd);

    // Set Region
    autotest_interface_request((char *)"Dvbs.scanControl", cmd);
}
