#include <techtype.h>
#include <dbgfuncs.h>

#include <stdio.h>
#include <string.h>
#include <memory.h>


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
    cert_apctrl_scan_Init();
    cert_apctrl_scan_M7_ScanStart(EN_M7_SCAN_FTI);

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
    cert_apctrl_scan_M7_ScanStart(EN_M7_SCAN_STANDBY);

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
    cert_apctrl_scan_M7_ScanStart(EN_M7_SCAN_POWERON);

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
        cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_DISEQC_CONFIRM, NULL, NULL);
    }
    else if (STB_EVENT_SEARCH_M7_OPELIST_SELECT_NOTIFY == event)
    {
        U32BIT *oper_list_id_ptr = (U32BIT *)malloc(sizeof(U32BIT));
        U32BIT *oper_sublist_id_ptr = (U32BIT *)malloc(sizeof(U32BIT));

        *oper_list_id_ptr = AUTOTEST_GetSelectedOperId();
        *oper_sublist_id_ptr = AUTOTEST_GetSelectedOperSubListId();

        cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_OPERLIST_CONFIRM, oper_list_id_ptr, oper_sublist_id_ptr);
    }
    else if (STB_EVENT_SEARCH_M7_REGION_SELECT_NOTIFY == event)
    {
        cert_apctrl_scan_SendMsg(INVALID_RES_ID, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_REGION_CONFIRM, NULL, NULL);
    }
    else if (STB_EVENT_SEARCH_M7_SEARCH_FINISHED_NOTIFY == event)
    {
        Wrapper_DisableTsLoop();
        autotest_set_exit_flag(1);
    }
}


// E: Local function define


