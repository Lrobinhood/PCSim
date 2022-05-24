#include "DvbsInterface.h"
#include "EventManager.h"

extern "C" {
#include "stbhwos.h"
#include "techtype.h"
#include "stbheap.h"
#include "stberc.h"

#include "cert_apctrl.h"
#include "cert_log.h"
}
#include "ResourceManager.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>

#include <json/json.h>





#define LOG_TAG "DvbsInterface"

static BOOLEAN g_started    = FALSE;
static U8BIT g_frontendid   = -1;
static S8BIT g_progress     = 0;

static void ReleaseSearchActivePath(ResourceManager::Resource resource);

static void ReleaseSearchActivePath(ResourceManager::Resource resource)
{

}


// E: Scan Control Command Define
DvbsInterface::DvbsInterface()
{
    EventManager::addEventHandler(DvbsInterface::eventHandler);

    addInvokable("scanControl", &DvbsInterface::scanControl);
    //addInvokable("getStatus", &DvbsInterface::getStatus);
}

bool DvbsInterface::getStatus(RequestData* request, ResponseData* response)
{
    ResponseData::Object* object = response->setObject(3);

    object->insertBool("started", g_started);
    object->insertInt32("frontendpath", g_frontendid);
    object->insertInt32("progress", g_progress);

    object->finish();

    CERT_LOG_DEBG(LOG_TAG, "[%s] g_start:%u, frontendpath:%u, g_progress:%u", __FUNCTION__,
        g_started, g_frontendid, g_progress);

    return true;
}

bool DvbsInterface::scanControl(RequestData* request, ResponseData* response)
{
    bool ret = true;
    U32BIT cmd = M_SCANCONTROL_CMD_INVALID;

    cmd = request->shiftUInt32(M_SCANCONTROL_CMD_INVALID); // arg1: cmd
    if (CMD_OPERATOR_M7 == GET_CMD_OPERATOR(cmd))
    {
        request->resetDataIdx();
        ret = scanControl_M7(request, response);
    }
    else
    {
        response->setString("Operator unsupport");
        ret = false;
    }

    return ret;
}

bool DvbsInterface::scanControl_M7(RequestData* request, ResponseData* response)
{
    bool ret = true;
    U32BIT loop = 0;

    U32BIT cmd          = request->shiftUInt32(M_SCANCONTROL_CMD_INVALID); // arg1: cmd

    if (CMD_ACTION_GETOPERATOR == GET_CMD_ACTION(cmd))
    {
        U8BIT** operator_list    = NULL;
        U32BIT operator_num     = 0;
        U32BIT countrycode      = request->shiftUInt32(-1); // arg2: countrycode

        operator_num = CERT_APCTRL_SCAN_M7_GetOperatorList(countrycode, &operator_list);

        ResponseData::Array* array = response->setArray(operator_num);

        for (loop = 0; loop < operator_num; loop++)
        {
            std::string str((char *)operator_list[loop]);
            array->appendString(str);
        }

        array->finish();

        if (NULL != operator_list)
        {
            STB_FreeMemory(operator_list);
        }
    }
    else if (CMD_ACTION_GETSUBOPERATOR == GET_CMD_ACTION(cmd))
    {
        U8BIT** sub_list    = NULL;
        U32BIT sub_num      = 0;
        U32BIT countrycode  = request->shiftUInt32(-1); // arg2: countrycode
        U8BIT* opername     = CERT_APCTRL_SCAN_M7_GetSelectedOperatorName();

        sub_num = CERT_APCTRL_SCAN_M7_GetOperSubList(countrycode, opername, &sub_list);

        ResponseData::Array* array = response->setArray(sub_num);

        for (loop = 0; loop < sub_num; loop++)
        {
            std::string str((char *)sub_list[loop]);
            array->appendString(str);
        }

        array->finish();

        if (NULL != sub_list)
        {
            STB_FreeMemory(sub_list);
        }
    }
    else if (CMD_ACTION_SETOPERATOR == GET_CMD_ACTION(cmd))
    {
        std::string opername = request->shiftString("");
        CERT_APCTRL_SCAN_M7_SetSelectedOperatorName((U8BIT *)opername.c_str());

        response->setString(opername);
    }
    else if (CMD_ACTION_SETSUBOPERATOR == GET_CMD_ACTION(cmd))
    {
        std::string subname = request->shiftString("");
        CERT_APCTRL_SCAN_M7_SetSelectedOperSubName((U8BIT *)subname.c_str());

        CERT_APCTRL_SCAN_M7_OnOperAndSubListConfirm();

        response->setString(subname);
    }
    else if (CMD_ACTION_DISEQCCONFIRM == GET_CMD_ACTION(cmd))
    {
        CERT_APCTRL_SCAN_M7_OnManualDiseqcConfirm();

        response->setString("OK");
    }
    else if (CMD_ACTION_GETREGION == GET_CMD_ACTION(cmd))
    {
        STRU_CERT_M7_REGION_REC *region_array = NULL;
        U32BIT region_number = 0;

        region_number = CERT_APCTRL_SCAN_M7_GetRegionArray(&region_array);

        ResponseData::Array* array = response->setArray(region_number);

        for (loop = 0; loop < region_number; loop++)
        {
            ResponseData::Object *object    = array->appendObject(2);
            ResponseData::Array* srvarray   = NULL;

            object->insertString("RegionName", (char *)region_array[loop].region_name);
            srvarray = object->insertArray("RegionSrvList", region_array[loop].region_srv_number);

            for (U32BIT idx = 0; idx < region_array[loop].region_srv_number; idx++)
            {
                srvarray->appendString((char *)region_array[loop].region_srv_name_array[idx]);
            }

            srvarray->finish();

            object->finish();
        }

        array->finish();

        CERT_APCTRL_SCAN_M7_ReleaseRegionArray(region_array, region_number);
    }
    else if (CMD_ACTION_SETREGION == GET_CMD_ACTION(cmd))
    {
        RequestDataJSON* request_json = dynamic_cast<RequestDataJSON*>(request);

        Json::Value root = request_json->shiftJsonValue();

        if (!root.isNull())
        {
            unsigned int num = 0;

            num = root.size();

            for (unsigned int loop = 0; loop < num; loop++)
            {
                std::string a = root[loop]["RegionName"].asString();
                std::string b = root[loop]["SetRegion"].asString();

                if (!a.empty() && !b.empty())
                {
                    CERT_LOG_DEBG(TAG, "[%s] RegionName:%s, SetRegion:%s", __FUNCTION__,
                                        a.c_str(), b.c_str());
                    CERT_APCTRL_SCAN_M7_SetRegionSelection((U8BIT *)a.c_str(), (U8BIT *)b.c_str());
                }
            }

        }

        CERT_APCTRL_SCAN_M7_OnSelectRegionConfirm();

        response->setString("Ok");
    }
    else
    {
        response->setString("Cmd not support");
        ret = false;
    }

    return ret;
}


bool DvbsInterface::startSearch_M7(RequestData* request, ResponseData* response)
{
    std::string scan_mode;
    std::string scan_type;

    BOOLEAN is_skipauto = FALSE;
    BOOLEAN ret         = TRUE;

    request->resetDataIdx();

    scan_mode       = request->shiftString("m7fast");   // arg1: scan_mode
    is_skipauto     = request->shiftBool(false);        // arg2: is skip autodiseqc
    scan_type       = request->shiftString("fti");

    g_frontendid = INVALID_RES_ID;
    g_progress = 0;
    g_started = TRUE;

    if (ResourceManager::acquire(
            ResourceManager::ActivePath, this, ReleaseSearchActivePath, ResourceManager::ResourcePriorityScan))
    {

        if (0 == scan_type.compare("fti"))
        {
            if (is_skipauto)
            {
                ret = CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_FTI, TRUE);
            }
            else
            {
                ret = CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_FTI, FALSE);
            }
        }
        else if (0 == scan_type.compare("standby"))
        {
            ret = CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_STANDBY, FALSE);
        }
        else if (0 == scan_type.compare("poweron"))
        {
            ret = CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_POWERON, FALSE);
        }
        else if (0 == scan_type.compare("manual"))
        {
            // To be done ...
        }
        else if (0 == scan_type.compare(""))
        {
            // To be done ...
        }
        else
        {
            ret = FALSE;
        }

        if (ret)
        {
            response->setString("start success");
        }
        else
        {
            response->setString("unknow scan type");
        }
    }
    else
    {
        response->setString("Conflict");
    }


    return ret;
}

bool DvbsInterface::finishSearch_M7(RequestData* request, ResponseData* response)
{
    BOOLEAN ret = TRUE;

    request->resetDataIdx();

    ret = CERT_APCTRL_SCAN_M7_ScanStop();
    if (ret)
    {
        response->setString("stop success");
    }
    else
    {
        response->setString("stop failed");
    }

    return ret;
}


void DvbsInterface::eventHandler(unsigned int code,
                                 const void* data,
                                 unsigned int data_size)
{
    CERT_LOG_INFO(LOG_TAG, "[%s] event:0x%x", __FUNCTION__, code);
    DvbsInterface::eventHandler_M7(code, data, data_size);
}


void DvbsInterface::eventHandler_M7(unsigned int code,
                                const void* data,
                                unsigned int data_size)
{
    static DvbsInterface& instance = DvbsInterface::instance();
    RequestDataJSON request_data(Json::arrayValue);

    if (EV_TYPE_M7_DISEQC_CONFIRM_NOTIFY == code)
    {
        instance.signal("M7NeedDiseqcConfirm");
    }
    else if (EV_TYPE_M7_OPELIST_SELECT_NOTIFY == code)
    {
        instance.signal("M7NeedSelectOperator");
    }
    else if (EV_TYPE_M7_SUBLIST_SELECT_NOTIFY == code)
    {
        instance.signal("M7NeedSelectSublist");
    }
    else if (EV_TYPE_M7_REGION_SELECT_NOTIFY == code)
    {
        instance.signal("M7NeedSelectRegion");
    }
    else if (EV_TYPE_M7_SEARCH_FINISHED_NOTIFY == code)
    {
        g_progress = 100;
        instance.signal("SearchStatusUpdate", &DvbsInterface::getStatus, &request_data);
    }

    CERT_LOG_DEBG(LOG_TAG, "[%s] code:0x%x", __FUNCTION__, code);


}



