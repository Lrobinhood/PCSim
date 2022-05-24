#include <techtype.h>
#include <dbgfuncs.h>

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>

#include "stbhwc.h"
#include "stbheap.h"
#include "stbuni.h"

#include "stbsiflt.h"

#include "stbdpc.h"

#include "stbsitab.h"
#include "stbsic.h"
#include  "stberc.h"

#include "ap_dbacc.h"
#include "ap_dbdef.h"

#include "ap_cntrl.h"

#include "ap_si.h"

#include "ap_cfg.h"


#include "cert_sitbl.h"


#include "FilterForDtvkitWrapper.h"

#include "test_filter_scan.h"


#include "cert_log.h"

#include "cert_scan_common.h"
#include "cert_apctrl.h"
#include "cert_apctrl_scan_common.h"
#include "cert_apctrl_m7_scan.h"
#include "cert_apctrl_m7_scan_common.h"

#include "cert_misc.h"
#include "cert_dbg.h"

#include "autotest_cfg.h"
#include "autotest_result.h"
#include "autotest_main.h"
#include "autotest_scan.h"
#include "autotest_interface.h"


#define TAG "AUTOTEST-SCAN"


// B: Local Variable Define


// E: Local Variable Define

// B: Local function declare
static void m7_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size);

static int autotest_scan_m7_fti(const char *TestIniFile);
static int autotest_scan_m7_standby(const char *TestIniFile);
static int autotest_scan_m7_poweron(const char *TestIniFile);

// E: Local function declare



int autotest_m7_fast(const char *TestIniFile)
{
    int ret = 0;

    char* scan_type_str = AUTOTEST_M7_GetScanType(TestIniFile);

    autotest_interface_reginterface();

    if (0 == strcmp(scan_type_str, "standby"))
    {
        ret = autotest_scan_m7_standby(TestIniFile);
    }
    else if (0 == strcmp(scan_type_str, "poweron"))
    {
        ret = autotest_scan_m7_poweron(TestIniFile);
    }
    else
    {
        ret = autotest_scan_m7_fti(TestIniFile);
    }

    return ret;
}



/*
Get Operator List:          cmd 0x00010002
    Request("Dvbs.scanControl", "[65538]");
Get Get Sub Operator List:  cmd 0x00010003
    Request("Dvbs.scanControl", "[65539]");
Set Operator:               cmd 0x00010004
    Request("Dvbs.scanControl", "[65540, "oper name"]")
Set Set SubOperator:        cmd 0x00010005
    Request("Dvbs.scanControl", "[65541, "suboper name"]")
*/

void M7_UI_Handle_OPELIST_SELECT_NOTIFY()
{
    char cmd[128];

    // 1. Get Operator List:          cmd 0x00010002
    sprintf(cmd, "[%d]", 0x00010002);
    autotest_interface_request("Dvbs.scanControl", cmd);

    // 2. Set Operator:               cmd 0x00010004
    sprintf(cmd, "[%d, \"%s\"]", 0x00010004, AUTOTEST_GetSelectedOperName());
    autotest_interface_request("Dvbs.scanControl", cmd);

    // 3. Get Sub Operator List:  cmd 0x00010003
    sprintf(cmd, "[%d]", 0x00010003);
    autotest_interface_request("Dvbs.scanControl", cmd);

    // 4. Set Set SubOperator:        cmd 0x00010005
    sprintf(cmd, "[%d, \"%s\"]", 0x00010005, AUTOTEST_GetSelectedOperSubName());
    autotest_interface_request("Dvbs.scanControl", cmd);
}

void M7_UI_Handle_DISEQC_CONFIRM_NOTIFY()
{
    char cmd[128];

    sprintf(cmd, "[%d]", 0x00010001);
    autotest_interface_request("Dvbs.scanControl", cmd);
}

void M7_UI_Handle_REGION_SELECT_NOTIFY()
{
    char cmd[1024];
    char item[128];

    // Set Region
    sprintf(cmd, "[%d]", 0x00010006);
    autotest_interface_request("Dvbs.scanControl", cmd);

    // Get Region
    sprintf(cmd, "[%d, [", 0x00010007);

    // Set Region
    unsigned int region_num = AUTOTEST_GetRegionNumber();
    for (unsigned int loop = 0; loop < region_num; loop++)
    {
        sprintf(item,"{\"RegionName\":\"%s\", \"SetRegion\":\"%s\"}",
                    AUTOTEST_GetRegionNameByIdx(loop + 1),
                    AUTOTEST_GetRegionSerByIdx(loop + 1));

        strcat(cmd, item);

        if (loop + 1 < region_num)
        {
            strcat(cmd, ", ");
        }
    }

    sprintf(item, "]]");

    strcat(cmd, item);

    //printf("%s\n", cmd);

    autotest_interface_request("Dvbs.scanControl", cmd);
}



// B: Local function define
static int autotest_scan_m7_fti(const char *TestIniFile)
{
    U32BIT count = 0;

    U32BIT country_code = 0;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    // This line maybe delete
    AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);

    if (AUTOTEST_isMulMod(TestIniFile))
    {
        count = AUTOTEST_GetModNumber(TestIniFile);
        AUTOTEST_GetAllModulatorCfg(TestIniFile, count);
    }

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, m7_DVB_EVENT_HANDLER);
    Init_Test_Filter_Wrapper();

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);
    ADB_SetAcitveServiceList(SIGNAL_QPSK);
    ACFG_SetOperatorsType(SIGNAL_QPSK, GERMANY_DVBS_OPERATORS_OTHER);

    autotest_set_signal_type(AUTOTEST_Get_CurCfg_TuneSig());

    // Init For Special Country
    Init_Test_for_Country(country_code, autotest_get_signal_type(), TestIniFile);

    autotest_scan_clear_all_records();

    // Call Start M7
    BOOLEAN skipauto = AUTOTEST_M7_isSkipAutoDiseqc(TestIniFile);

    cert_apctrl_scan_Init();
    CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_FTI, skipauto);

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != autotest_get_exit_flag())
        {
            goto LOOP;
        }
    }

    autotest_set_exit_flag(0);

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}

static int autotest_scan_m7_standby(const char *TestIniFile)
{
    U32BIT count = 0;

    U32BIT country_code = 0;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    // This line maybe delete
    AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);

    if (AUTOTEST_isMulMod(TestIniFile))
    {
        count = AUTOTEST_GetModNumber(TestIniFile);
        AUTOTEST_GetAllModulatorCfg(TestIniFile, count);
    }

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, m7_DVB_EVENT_HANDLER);
    Init_Test_Filter_Wrapper();

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);
    ADB_SetAcitveServiceList(SIGNAL_QPSK);
    ACFG_SetOperatorsType(SIGNAL_QPSK, GERMANY_DVBS_OPERATORS_OTHER);

    autotest_set_signal_type(AUTOTEST_Get_CurCfg_TuneSig());

    // Init For Special Country
    Init_Test_for_Country(country_code, autotest_get_signal_type(), TestIniFile);


    // Call Start M7
    cert_apctrl_scan_Init();
    CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_STANDBY, FALSE);

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != autotest_get_exit_flag())
        {
            goto LOOP;
        }
    }

    autotest_set_exit_flag(0);

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}

static int autotest_scan_m7_poweron(const char *TestIniFile)
{
    U32BIT count = 0;

    U32BIT country_code = 0;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    // This line maybe delete
    AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);

    if (AUTOTEST_isMulMod(TestIniFile))
    {
        count = AUTOTEST_GetModNumber(TestIniFile);
        AUTOTEST_GetAllModulatorCfg(TestIniFile, count);
    }

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, m7_DVB_EVENT_HANDLER);
    Init_Test_Filter_Wrapper();

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);
    ADB_SetAcitveServiceList(SIGNAL_QPSK);
    ACFG_SetOperatorsType(SIGNAL_QPSK, GERMANY_DVBS_OPERATORS_OTHER);

    autotest_set_signal_type(AUTOTEST_Get_CurCfg_TuneSig());

    // Init For Special Country
    Init_Test_for_Country(country_code, autotest_get_signal_type(), TestIniFile);


    // Call Start M7
    cert_apctrl_scan_Init();
    CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_POWERON, FALSE);

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != autotest_get_exit_flag())
        {
            goto LOOP;
        }
    }

    autotest_set_exit_flag(0);

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}



static void m7_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:0x%x, event_data:0x%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    if (0)
    {
        Wrapper_DisableTsLoop();

        autotest_set_exit_flag(1);
    }
    else if (STB_EVENT_SEARCH_M7_DISEQC_CONFIRM_NOTIFY == event)
    {
#if 1
        // B: Notify to UI & User Selected
        autotest_interface_notify(event, event_data, data_size);
        // E: Notify to UI & User Selected
#else
        cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_DISEQC_CONFIRM, NULL, NULL);
#endif
    }
    else if (STB_EVENT_SEARCH_M7_OPELIST_SELECT_NOTIFY == event)
    {
#if 1
        // B: Notify to UI & User Selected
        autotest_interface_notify(event, event_data, data_size);
        // E: Notify to UI & User Selected
#else

        {
            U32BIT *oper_list_id_ptr = (U32BIT *)malloc(sizeof(U32BIT));
            U32BIT *oper_sublist_id_ptr = (U32BIT *)malloc(sizeof(U32BIT));

            *oper_list_id_ptr = AUTOTEST_GetSelectedOperId();
            *oper_sublist_id_ptr = AUTOTEST_GetSelectedOperSubListId();

            cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_OPERLIST_CONFIRM, oper_list_id_ptr, oper_sublist_id_ptr);
        }
#endif
    }
    else if (STB_EVENT_SEARCH_M7_REGION_SELECT_NOTIFY == event)
    {
    #if 1
        autotest_interface_notify(event, event_data, data_size);
    #else
        cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_REGION_CONFIRM, NULL, NULL);
    #endif
    }
    else if (STB_EVENT_SEARCH_M7_SEARCH_FINISHED_NOTIFY == event)
    {
        // B: Notify to UI & User Selected
        autotest_interface_notify(event, event_data, data_size);
        // E: Notify to UI & User Selected

        Wrapper_DisableTsLoop();
        autotest_set_exit_flag(1);
    }

}

// E: Local function define


