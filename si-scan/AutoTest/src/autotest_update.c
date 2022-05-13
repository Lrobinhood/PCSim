#include <techtype.h>
#include <dbgfuncs.h>


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

#include "cert_misc.h"
#include "cert_dbg.h"


#include "autotest_assistant.h"
#include "autotest_cfg.h"
#include "autotest_result.h"
#include "autotest_main.h"
#include "autotest_scan.h"


#define TAG "AUTOTEST-UPDATE"



// B: Type define


// E: Type Define

// B: Local Variable Define
static U8BIT sg_exit_flag = 0;
static E_STB_DP_SIGNAL_TYPE sg_signal_type = SIGNAL_COFDM;

// E: Local Variable Define

// B: Local function declare
static void autotest_update_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size);

// E: Local function declare

bool is_update_test(unsigned int test_type)
{
    bool ret = false;

    switch (test_type)
    {
        case EN_TESTTYE_UPDATE_BASIC:
            ret = true;

            break;

        default:
            ret = false;

            break;
    }

    return ret;
}



int autotest_update(int argc, char* argv[], unsigned int test_type)
{
    U32BIT loglevel = ANDROID_LOG_DEBUG;

    int ret = 1;

    if (argc > 2)
    {
        loglevel = autotest_setloglevel(argv[2]);
    }

    CERT_LOG_DEBG(TAG, "[%s] TestIni:%s", __FUNCTION__, argv[1]);

    AUTOTEST_SetCfgIniFile(argv[1]);
    switch (test_type)
    {

        case EN_TESTTYE_UPDATE_BASIC:
            ret = autotest_update_basic(argv[1]);

            break;

        default:
            CERT_LOG_ERROR(TAG, "[%s] unsupport test type:%u", __FUNCTION__, test_type);
            AutoTest_Result_Write_Case(M_FAILEDCASES_FILENAME, argc, argv);

            break;
    }


    CERT_LOG_FATAL(TAG, "[%s] TestIni:%s, Result:%s", __FUNCTION__, argv[1], ret == 0 ? "Passed!" : "Failed!");

    return ret;
}



int autotest_update_basic(const char *TestIniFile)
{
    U8BIT path = 0;

    U32BIT country_code = 0;
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Get_One_CH_Cfg(TestIniFile, "CH 1");

    AUTOTEST_Init_DVB(autotest_update_DVB_EVENT_HANDLER);
    AUTOTEST_Init_Filter_Wrapper();

    if (!Init_Manual_Tunning_Params(AUTOTEST_Get_CurCfg_TuneSys(), &s_manual_tuning_para))
    {
        return -1;
    }

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(AUTOTEST_Get_CountryCode(TestIniFile));
    ACFG_SetAutomaticOrderingEnabled(TRUE);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);


    path = STB_DPAcquireTunerPath(sg_signal_type, NULL, NULL, RES_OWNER_DVB, DP_PRIORITY_LOW,
                                    FALSE, FALSE, TRUE);

    pc_set_si_required(path, APP_SI_MODE_UPDATE);

    U16BIT onet_id  = 0;
    U16BIT trans_id = 0;
    U16BIT serv_id  = 0;

    AUTOTEST_Get_ServiceTripleId(&onet_id, &trans_id, &serv_id);
    void *s_ptr = ADB_FindServiceByIds(onet_id, trans_id, serv_id);


    CERT_LOG_DEBG(TAG, "[%s] tripleID: %u, %u, %u, s_ptr:%p", __FUNCTION__,
                   onet_id, trans_id, serv_id, s_ptr);

    ADB_SetTunedService(path, s_ptr);
    STB_DPSetTuneStatus(path, TUNE_LOCKED);

    unsigned int duration = AUTOTEST_Get_Duration();
    unsigned int loop_times = AUTOTEST_Get_LoopTimes();

    long filesize = AUTOTEST_Get_FileLen(AUTOTEST_Get_CurCfg_StreamFile());

    unsigned int sleep_ms = Wrapper_CalcTsLoopDelay(filesize, duration);




    CERT_LOG_DEBG(TAG, "[%s] filesize:%lu, duration:%u, sleep_ms:%u, loop_times:%u", __FUNCTION__,
                   filesize, duration, sleep_ms, loop_times);

    if (0 != duration && 0 != filesize)
    {
        Wrapper_SetTsLoopDelayMS(sleep_ms);
    }

    pc_StartSiProcess(path);

    unsigned int times = 0;

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (0 != loop_times && ++times == loop_times)
            sg_exit_flag = 1;


        if (1 != sg_exit_flag)
            goto LOOP;
    }

    sg_exit_flag = 0;

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}

// B: Local Function Define
static void autotest_update_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:0x%x, event_data:0x%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    // To be done ...
}


// E: Local Function Define
