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


extern U32BIT CERT_Common_SetLogLevel(U32BIT loglevel);
extern void AutoTest_STBHWTUN_ResetTunerStartTuner();



// B: Local Variable Define

static U8BIT sg_exit_flag = 0;
static E_STB_DP_SIGNAL_TYPE sg_signal_type = SIGNAL_COFDM;

static BOOLEAN sg_manual_search = TRUE;

int autotest_get_exit_flag()
{
    return sg_exit_flag;
}

void autotest_set_exit_flag(int exit_flag)
{
    sg_exit_flag = exit_flag;
}

int autotest_get_signal_type()
{
    return sg_signal_type;
}
void autotest_set_signal_type(int signal_type)
{
    sg_signal_type = signal_type;
}


// E: Local Variable Define

// B: Local function declare
void Init_Test_Filter_Wrapper();

void Init_Test_for_Country(U32BIT CountryCode, E_STB_DP_SIGNAL_TYPE SigType);

BOOLEAN Init_Manual_Tunning_Params(E_STB_TUNE_SYSTEM_TYPE tune_sys_type, S_MANUAL_TUNING_PARAMS *tuning_params_ptr);

static void test_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size);
static void m7_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size);

static void autoscan_posthandle(const char *TestIniFile);
static void autoscan_posthandle_italy(const char *TestIniFile);

static void autotest_get_servicelist_from_name(U32BIT number, char **name_list, ADB_SERVICE_REC ***s_ptr_list);
static BOOLEAN find_match_name_from_conflict_slist(char *name, ADB_SERVICE_REC **slist, U16BIT list_len);

static BOOLEAN autotest_create_satelite_info(const char *TestIniFile);

// E: Local function declare

bool is_scan_test(unsigned int test_type)
{
    bool ret = false;

    switch (test_type)
    {
        case EN_TESTTYPE_MANUALSCAN:
        case EN_TESTTYPE_MANUALSCAN_DVBT_NEW:
        case EN_TESTTYPE_AUTOSCAN:
        case EN_TESTTYPE_SATSCAN:
        case EN_TESTTYPE_ASTRA_TP_SCAN:
        case EN_TESTTYPE_ASTRA_SAT_SCAN:
        case EN_TESTTYPE_M7_FAST:
            ret = true;

            break;

        default:
            ret = false;

            break;
    }

    return ret;
}

int autotest_scan(int argc, char* argv[], unsigned int test_type)
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
        case EN_TESTTYPE_MANUALSCAN:
            sg_manual_search = TRUE;

            if (AUTOTEST_Get_ScanCount(argv[1]) <= 1)
            {
                ret = autotest_manualscan(argv[1]);
            }
            else
            {
                ret = autotest_manualscan_twice(argv[1]);
            }

            break;

       case EN_TESTTYPE_MANUALSCAN_DVBT_NEW:
            sg_manual_search = TRUE;
            ret = autotest_dvbt_new_manualscan(argv[1]);

            break;

        case EN_TESTTYPE_ASTRA_TP_SCAN:
            sg_manual_search = TRUE;
            ret = autotest_astra_transponder_scan(argv[1]);

            break;

        case EN_TESTTYPE_AUTOSCAN:
            sg_manual_search = FALSE;
            ret = autotest_autoscan(argv[1]);

            break;

        case EN_TESTTYPE_SATSCAN:
            sg_manual_search = FALSE;
            autotest_create_satelite_info(argv[1]);
            ret = autotest_autoscan(argv[1]);

            break;

        case EN_TESTTYPE_ASTRA_SAT_SCAN:
            sg_manual_search = FALSE;
            autotest_create_satelite_info(argv[1]);
            ret = autotest_astra_sat_scan(argv[1]);

            break;

        case EN_TESTTYPE_M7_FAST:
            sg_manual_search = FALSE;
            ret = autotest_m7_fast(argv[1]);

            break;

        default:
            CERT_LOG_ERROR(TAG, "[%s] unsupport test type:%u", __FUNCTION__, test_type);
            AutoTest_Result_Write_Case(M_FAILEDCASES_FILENAME, argc, argv);

            break;
    }

    ADB_FinaliseDatabaseAfterSearch(TRUE, sg_signal_type, NULL, TRUE, TRUE, sg_manual_search);

    autoscan_posthandle(argv[1]);

    loglevel = CERT_Common_SetLogLevel(loglevel);


    if (AUTOTEST_Get_ShowInfo_Servlist(argv[1]))
    {
        CERT_DBG_Show_Service_List(AUTOTEST_Get_ShowInfo_Sigtype(argv[1]));

        CERT_DBG_Show_Transponder_Rec_List(AUTOTEST_Get_ShowInfo_Sigtype(argv[1]));

        CERT_DBG_Show_Network_Rec_List();

        CERT_DBG_Show_Sat_Rec_List();

        CERT_DBG_Show_Lnb_Rec_List();
    }

    if (0 == ret)
    {
        ret = AutoTest_Result_check_service(argc, argv);
    }


    CERT_LOG_FATAL(TAG, "[%s] TestIni:%s, Result:%s", __FUNCTION__, argv[1], ret == 0 ? "Passed!" : "Failed!");


    return ret;
}


int autotest_manualscan(const char *TestIniFile)
{
    U16BIT netid = 0;
    U32BIT country_code = 0;
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Get_One_CH_Cfg(TestIniFile, "CH 1");

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

    if (!Init_Manual_Tunning_Params(AUTOTEST_Get_CurCfg_TuneSys(), &s_manual_tuning_para))
    {
        return -1;
    }

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();

    ADB_SetAcitveServiceList(sg_signal_type);

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);

    netid = AUTOTEST_Get_PreferNetid(TestIniFile);
    ACTL_SetScanNetworkID(netid);

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                   BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    if (AUTOTEST_Get_ClearDB(TestIniFile))
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, FALSE, 0, POLARITY_END);
    }
    else
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, TRUE, s_manual_tuning_para.freq, POLARITY_END);
    }

    if (AUTOTEST_Get_QuickScan())
    {
        U16BIT netid = AUTOTEST_Get_PreferNetid(TestIniFile);
        ACTL_SetQuickScan(TRUE);
        ACTL_SetScanNetworkID(netid);
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_NETWORK_SEARCH);
    }
    else if (AUTOTEST_Get_NetScan())
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
            goto LOOP;
    }

    sg_exit_flag = 0;

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}

int autotest_dvbt_new_manualscan(const char *TestIniFile)
{
    U32BIT country_code = 0;
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Get_One_CH_Cfg(TestIniFile, "CH 1");

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

    if (!Init_Manual_Tunning_Params(AUTOTEST_Get_CurCfg_TuneSys(), &s_manual_tuning_para))
    {
        return -1;
    }

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(AUTOTEST_Get_CountryCode(TestIniFile));
    ACFG_SetAutomaticOrderingEnabled(TRUE);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();
    ADB_SetAcitveServiceList(sg_signal_type);

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);

    // void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency)
    if (AUTOTEST_Get_ClearDB(TestIniFile))
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, FALSE, 0, POLARITY_END);
    }
    else
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, TRUE, s_manual_tuning_para.freq, POLARITY_END);
    }

    ACTL_PrepareServiceSearch(SIGNAL_COFDM, EN_ACTL_SEARCH_TYPE_MANUAL, &s_manual_tuning_para);

    if (AUTOTEST_Get_NetScan())
    {
        ACTL_StartServiceSearch(SIGNAL_COFDM, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartServiceSearch(SIGNAL_COFDM, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
            goto LOOP;
    }

    sg_exit_flag = 0;

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}



int autotest_manualscan_twice(const char *TestIniFile)
{
    static int count = 1;

    U32BIT country_code = 0;
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Get_One_CH_Cfg(TestIniFile, "CH 1");

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

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

    TWICE:

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    if (AUTOTEST_Get_ClearDB(TestIniFile))
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, FALSE, 0, POLARITY_END);
    }
    else
    {
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                     TRUE, TRUE, s_manual_tuning_para.freq, POLARITY_END);
    }

    if (AUTOTEST_Get_NetScan())
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
            goto LOOP;
    }

    sg_exit_flag = 0;

    if (count < 2)
    {
        count++;
        goto TWICE;
    }

    AUTOTEST_Set_One_CH_Cfg_Invalid();


    return 0;
}


int autotest_astra_transponder_scan(const char *TestIniFile)
{
    static int count = 1;

    U32BIT country_code = 0;
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Get_One_CH_Cfg(TestIniFile, "CH 1");

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

    if (!Init_Manual_Tunning_Params(AUTOTEST_Get_CurCfg_TuneSys(), &s_manual_tuning_para))
    {
        return -1;
    }

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(AUTOTEST_Get_CountryCode(TestIniFile));
    ACFG_SetAutomaticOrderingEnabled(TRUE);
    ACFG_SetOperatorsType(TUNE_SIGNAL_QPSK, GERMANY_DVBS_OPERATORS_HDPLUS);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);

    TWICE:

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    if (1 == count)
    {
        if (AUTOTEST_Get_ClearDB(TestIniFile))
        {
            ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                         TRUE, FALSE, 0, POLARITY_END);
        }
        else
        {
            ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                        TRUE, TRUE, s_manual_tuning_para.freq, POLARITY_END);
        }
    }
    else
    {
        CERT_APCTRL_Set_Astra_Search_Stage(1);
    }

    if (AUTOTEST_Get_NetScan())
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
            goto LOOP;
    }

    sg_exit_flag = 0;

    if (count < 2)
    {
        count++;
        goto TWICE;
    }

    AUTOTEST_Set_One_CH_Cfg_Invalid();


    return 0;
}


int autotest_astra_sat_scan(const char *TestIniFile)
{
    static int count = 1;

    char channel[32];
    U32BIT country_code = 0;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);

    TWICE:

    if (1 == count)
    {
        /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
        ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                    TRUE, FALSE, 0, POLARITY_END);
    }
    else
    {
        CERT_APCTRL_Set_Astra_Search_Stage(1);
        AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);
        AutoTest_STBHWTUN_ResetTunerStartTuner();
    }

    if (AUTOTEST_Get_NetScan())
    {
       ACTL_StartServiceSearch(sg_signal_type, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartServiceSearch(sg_signal_type, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
        {
            goto LOOP;
        }
    }

    sg_exit_flag = 0;

    if (count < 2)
    {
        count++;
        goto TWICE;
    }

    //autoscan_posthandle(TestIniFile);

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}



int autotest_autoscan(const char *TestIniFile)
{
    char channel[32];
    U32BIT country_code = 0;

    CERT_LOG_DEBG(TAG, "[%s] ", __FUNCTION__);

    AUTOTEST_Update_Autoscan_CH_Cfg(TRUE, TestIniFile);

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN, NULL);
    Init_Test_Filter_Wrapper();

    country_code = AUTOTEST_Get_CountryCode(TestIniFile);
    ACFG_SetCountry(country_code);
    ACFG_SetAutomaticOrderingEnabled(TRUE);

    sg_signal_type = AUTOTEST_Get_CurCfg_TuneSig();
    ADB_SetAcitveServiceList(sg_signal_type);

    // Init For Special Country
    Init_Test_for_Country(country_code, sg_signal_type, TestIniFile);

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                 TRUE, FALSE, 0, POLARITY_END);

    ACTL_PrepareServiceSearch(SIGNAL_COFDM, EN_ACTL_SEARCH_TYPE_FULL, NULL);

    if (AUTOTEST_Get_QuickScan())
    {
        ACTL_SetQuickScan(TRUE);
        ACTL_StartServiceSearch(sg_signal_type, ACTL_NETWORK_SEARCH);
    }
    else if (AUTOTEST_Get_NetScan())
    {
       ACTL_StartServiceSearch(sg_signal_type, ACTL_NETWORK_SEARCH);
    }
    else
    {
        ACTL_StartServiceSearch(sg_signal_type, ACTL_FREQ_SEARCH);
    }

    LOOP:
    {
        Wrapper_SetTsSource(0, AUTOTEST_Get_CurCfg_StreamFile());
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();

        if (1 != sg_exit_flag)
        {
            goto LOOP;
        }
    }

    sg_exit_flag = 0;

    //autoscan_posthandle(TestIniFile);

    AUTOTEST_Set_One_CH_Cfg_Invalid();

    return 0;
}

void autotest_scan_clear_all_records()
{
    DBDEF_RequestAccess();
    DBA_LockDatabase();
    DBDEF_DeleteAllRecords();
    //DBA_ClearDatabase();
    DBA_UnlockDatabase();
    DBDEF_ReleaseAccess();
}


// B: Local function define
void Init_Test_Filter_Wrapper()
{
    static U8BIT init_flag = 0;

    if (0 == init_flag)
    {
        STB_SITerrInitialise();

        Wrapper_DMXInitialise(0, 1);

    }
}

void Init_Test_DVB(E_SIMU_TYPE eSimuType, DVB_EVENT_HANDLER dvb_event_handle_func)
{
    static U8BIT init_dvb_flag = 0;

    if (0 == init_dvb_flag)
    {
        STB_ERInitialise();

        if (NULL == dvb_event_handle_func)
        {
            AEV_Initialise(test_DVB_EVENT_HANDLER);
        }
        else
        {
            AEV_Initialise(dvb_event_handle_func);
        }

        // APP_InitialiseDVB -->  STB_Initialise --> STB_DPInitialise
        STB_RESInitialise();
        STB_DPInitialise();

        // APP_NvmInitialise(); // "APP_NvmInitialise" will be called in ADB_Initialise
        ADB_Initialise();
        ASI_InitialiseAppSi();
        ACTL_InitialiseAppControl();
    }
}


void Init_Test_for_Country(U32BIT CountryCode, E_STB_DP_SIGNAL_TYPE SigType, const char *TestIniFile)
{
    if (COUNTRY_CODE_ITALY == CountryCode)
    {
        BOOLEAN auto_order = AUTOTEST_Get_AutoOrder(TestIniFile);
        ACFG_SetAutomaticOrderingEnabled(auto_order);

        CERT_LOG_DEBG(TAG, "[%s] Italy AutoOrder:%u", __FUNCTION__, auto_order);
    }

}



BOOLEAN Init_Manual_Tunning_Params(E_STB_TUNE_SYSTEM_TYPE tune_sys_type, S_MANUAL_TUNING_PARAMS *tuning_params_ptr)
{
    BOOLEAN ret = TRUE;

    switch (tune_sys_type)
    {
        case TUNE_SYSTEM_TYPE_DVBT:
        case TUNE_SYSTEM_TYPE_DVBT2:
        case TUNE_SYSTEM_TYPE_UNKNOWN:
        {
            tuning_params_ptr->freq             = AUTOTEST_Get_CurCfg_Freq();
            tuning_params_ptr->u.terr.bwidth    = TBWIDTH_8MHZ;
            tuning_params_ptr->u.terr.mode      = MODE_COFDM_16K;
            tuning_params_ptr->u.terr.plp_id   = AUTOTEST_Get_CurCfg_Plpid();
            tuning_params_ptr->u.terr.type     = AUTOTEST_Get_CurCfg_TuneSys();

            break;
        }

        case TUNE_SYSTEM_TYPE_DVBS:
        case TUNE_SYSTEM_TYPE_DVBS2:
        {
            static ADB_SATELLITE_REC sat_rec;

            tuning_params_ptr->freq                 = AUTOTEST_Get_CurCfg_Freq() + AUTOTEST_Get_CurCfg_LoFreq();
            tuning_params_ptr->u.sat.satellite      = &sat_rec;
            tuning_params_ptr->u.sat.polarity       = AUTOTEST_Get_CurCfg_Polairty();
            tuning_params_ptr->u.sat.symbol_rate    = AUTOTEST_Get_CurCfg_Srate();
            tuning_params_ptr->u.sat.fec            = AUTOTEST_Get_CurCfg_Fec();
            tuning_params_ptr->u.sat.dvb_s2         = FALSE;
            tuning_params_ptr->u.sat.freq_ex        = 0;
            tuning_params_ptr->u.sat.modulation     = AUTOTEST_Get_CurCfg_Modulation();

            break;
        }

        case TUNE_SYSTEM_TYPE_DVBC:
        {
            tuning_params_ptr->freq                 = AUTOTEST_Get_CurCfg_Freq();
            tuning_params_ptr->u.cab.mode           = MODE_QAM_64;
            tuning_params_ptr->u.cab.symbol_rate    = AUTOTEST_Get_CurCfg_Srate();
        }

        break;

        default:
        {
            CERT_LOG_ERROR(TAG, "[%s] Unsupport tune_sys_type:%u", __FUNCTION__, tune_sys_type);

            ret = FALSE;

            break;
        }
    }

    return ret;
}


static void test_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:0x%x, event_data:0x%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    if ((STB_EVENT_SEARCH_SUCCESS == event || STB_EVENT_TUNE_NOTLOCKED == event ||  STB_EVENT_SEARCH_FAIL == event)
        && ACTL_IsSearchComplete())
    {
        //ADB_FinaliseDatabaseAfterSearch(TRUE, sg_signal_type, NULL, TRUE, TRUE, sg_manual_search);

        Wrapper_DisableTsLoop();

        sg_exit_flag = 1;
    }
    else if(STB_EVENT_SEARCH_SUCCESS == event || STB_EVENT_SEARCH_FAIL == event)
    {
        // Update progress ... ...
        Wrapper_DisableTsLoop();
    }
    else if (STB_EVENT_SEARCH_SEL_SERLIST == event)
    {
        U32BIT no = 0;
        U8BIT *name = NULL;

        CERT_LOG_INFO(TAG, "[%s] event: STB_EVENT_SEARCH_SEL_SERLIST", __FUNCTION__);

        AUTOTEST_Get_SelSGT_SerList(&no, &name);

        CERT_APCTRL_SetSelect_SGT_SrvListId(no, name);

        if (NULL != name)
            free(name);

        CERT_APCTRL_SendEvent_Select_While_Search(*((U8BIT*)event_data));
    }
}

#if 0
static void m7_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:0x%x, event_data:0x%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    if (0)
    {
        Wrapper_DisableTsLoop();

        sg_exit_flag = 1;
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
        sg_exit_flag = 1;
    }
}
#endif

static void autoscan_posthandle(const char *TestIniFile)
{
    U16BIT netid = AUTOTEST_Get_PreferNetid(TestIniFile);
    U32BIT country_code = AUTOTEST_Get_CountryCode(TestIniFile);

    if (COUNTRY_CODE_NORWAY == country_code &&
        -1 != netid)
    {
        ADB_SetNetworkPreferedOfRegion(netid);
    }
    else if (COUNTRY_CODE_ITALY  == country_code)
    {
        autoscan_posthandle_italy(TestIniFile);
    }
}



static void autoscan_posthandle_italy(const char *TestIniFile)
{
    BOOLEAN check_result_ok = TRUE;

    // 1. Check_Conflict_Lcn_Service
    {
        ADB_SERVICE_REC **s_ptr_list = NULL;
        U16BIT length = 0;
        U16BIT diff_lcn = 0;

        ADB_GetConflictLcnServiceList(&s_ptr_list, &length, &diff_lcn);

        char **name_list = NULL;
        U32BIT number = 0;

        AUTOTEST_Get_ConflictService_List(TestIniFile, &number, &name_list);

        if (number != length)
        {
            CERT_LOG_ERROR(TAG, "[%s] number:%u, length:%u ERR!", __FUNCTION__, number, length);

            return;
        }

        for (U32BIT i = 0; i < number; i++)
        {
        #if 1 // Only for debug
            CERT_LOG_DEBG(TAG, "[%s] conflict cfgser %d:%s", __FUNCTION__,
                           i, name_list[i]);

            if (NULL != s_ptr_list[i])
                CERT_LOG_DEBG(TAG, "[%s] conflict s_ptr(%d):%s", __FUNCTION__,
                               i, s_ptr_list[i]->name_str->str_ptr);
        #endif

            if (!find_match_name_from_conflict_slist(name_list[i], s_ptr_list, length))
            {
                check_result_ok = FALSE;
            }

            free(name_list[i]);
        }

        free(name_list);
        free(s_ptr_list);
    }

    if (!check_result_ok)
    {
        CERT_LOG_ERROR(TAG, "[%s] check_result Failed!", __FUNCTION__);

        return;
    }

    // 2. Set_Keep_Lcn_Servcie
    {
        char **name_list = NULL;
        U32BIT number = 0;

        ADB_SERVICE_REC **s_ptr_list = NULL;

        AUTOTEST_Get_SelectService_List(TestIniFile, &number, &name_list);
        autotest_get_servicelist_from_name(number, name_list, &s_ptr_list);

        for (U32BIT i = 0; i < number; i++)
        {
        #if 0 // Only for debug
            CERT_LOG_DEBG(TAG, "[%s] ser %d:%s", __FUNCTION__,
                           i, name_list[i]);

            if (NULL != s_ptr_list[i])
                CERT_LOG_DEBG(TAG, "[%s] s_ptr(%d):%s", __FUNCTION__,
                               i, s_ptr_list[i]->name_str->str_ptr);
        #endif

            if (NULL != s_ptr_list[i])
                ADB_SelectServiceKeepConflictLcn(s_ptr_list[i], sg_signal_type);

            free(name_list[i]);
        }

        free(name_list);
        free(s_ptr_list);
    }
}



static void autotest_get_servicelist_from_name(U32BIT number, char **name_list, ADB_SERVICE_REC ***s_ptr_list)
{
    ADB_SERVICE_REC *s1_ptr = NULL;

    *s_ptr_list = malloc(sizeof(ADB_SERVICE_REC *) * number);

    for (U32BIT i = 0; i < number; i++)
    {
        (*s_ptr_list)[i] = NULL;

        s1_ptr = DBDEF_GetNextServiceRec(NULL);
        while (s1_ptr != NULL)
        {
            if (NULL != s1_ptr->name_str && NULL != s1_ptr->name_str->str_ptr)
            {
                U16BIT nchar = 0;
                U8BIT *utf8_name_ptr = STB_ConvertStringToUTF8(s1_ptr->name_str->str_ptr,
                                                               &nchar, FALSE, s1_ptr->name_str->lang_code);
                if (NULL != utf8_name_ptr && 0 == strcmp(name_list[i], utf8_name_ptr+1))
                {
                    (*s_ptr_list)[i] = s1_ptr;

                    STB_FreeMemory(utf8_name_ptr);

                    break;
                }
                else
                {
                    STB_FreeMemory(utf8_name_ptr);
                }
            }
            s1_ptr = DBDEF_GetNextServiceRec(s1_ptr);
        }
    }
}


static BOOLEAN find_match_name_from_conflict_slist(char *name, ADB_SERVICE_REC **slist, U16BIT list_len)
{
    BOOLEAN ret = FALSE;

    for (int i = 0; i < list_len; i++)
    {
        U16BIT nchar = 0;
        U8BIT *utf8_name_ptr = STB_ConvertStringToUTF8(slist[i]->name_str->str_ptr,
                                                       &nchar, FALSE, slist[i]->name_str->lang_code);

        if (0 == strcmp(name, utf8_name_ptr + 1))
        {
            ret = TRUE;

            break;
        }

        STB_FreeMemory(utf8_name_ptr);
    }

    return ret;
}


static BOOLEAN autotest_create_satelite_info(const char *TestIniFile)
{
    int i = 0;
    char channel[32];

    S_MANUAL_TUNING_PARAMS params[1000];

    do
    {
        sprintf(channel, "CH %d", i + 1);

        if (!AUTOTEST_Get_One_CH_Cfg(TestIniFile, channel))
            break;

        if (!Init_Manual_Tunning_Params(AUTOTEST_Get_CurCfg_TuneSys(), &params[i]))
        {
            break;
        }

        i++;
    } while (i < 1000);

    ACTL_CreatSatelliteInfo(params, i);
    CERT_LOG_INFO(TAG, "[%s] total para:%d", __FUNCTION__, i);

    return TRUE;
}


// E: Local function define


