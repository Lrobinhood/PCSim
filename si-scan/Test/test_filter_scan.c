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

#include "ap_cntrl.h"
#include "ap_si.h"
#include "ap_cfg.h"


#include "cert_sitbl.h"


#include "FilterForDtvkitWrapper.h"

#include "test_filter_scan.h"


#include "cert_log.h"
#include "cert_scan_common.h"

#define TAG "TEST-FILTER-SCAN"


// B: Type define
typedef enum tag_Simlulate_Type
{
    EN_SIMU_MANUAL_SCAN,
    EN_SIMU_AUTO_SCAN,
    EN_SIMU_NUMBER
}E_SIMU_TYPE;

// E: Type Define

// B: Local Variable Define

static U8BIT sg_exit_flag = 0;
static E_STB_DP_SIGNAL_TYPE sg_signal_type = SIGNAL_COFDM;

// E: Local Variable Define

// B: Local function declare
static void Init_Test_Filter_Wrapper();
static void Init_Test_DVB(E_SIMU_TYPE eSimuType);

static BOOLEAN test_STBEventHandler(BOOLEAN latched, BOOLEAN repeat, U16BIT class, U16BIT type,
                                      void *data, U32BIT data_size);

static void test_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size);
//static void test_DVB_EVENT_HANDLER_for_autoscan(U32BIT event, void *event_data, U32BIT data_size);


// E: Local function declare


void Test_CERT_ManageChannelSearch()
{
    {
        // AEV_Initialise --> STB_ERRegisterHandler
        STB_ERRegisterHandler(test_STBEventHandler);
        
        // APP_InitialiseDVB -->  STB_Initialise --> STB_DPInitialise
        STB_RESInitialise();
        STB_DPInitialise();

        ADB_Initialise();
        ASI_InitialiseAppSi();
        ACTL_InitialiseAppControl();
    }

    // ACTL_StartManualSearch --> STB_DPAcquireTunerPath
    STB_DPAcquireTunerPath(SIGNAL_QPSK, NULL, NULL, RES_OWNER_DVB, DP_PRIORITY_LOW, FALSE, FALSE, TRUE);


    Init_Test_Filter_Wrapper();

    APP_NvmSave(COUNTRY_CODE_NVM, COUNTRY_CODE_SWEDEN, TRUE);

    STB_DPSetSignalType(0, SIGNAL_QPSK);

    ASI_SetAppSiMode(0, APP_SI_MODE_CHANNEL_SEARCH);

    STB_SITerrSendEvent(0, SI_EVENT_SEARCH);

LOOP:
    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-730\\HD_muxB_010.trp");
    Wrapper_EnableTsLoop();
    Wrapper_StartTsLoop(0);
    Wrapper_DisableTsLoop();

    if (1 != sg_exit_flag)
        goto LOOP;

    sg_exit_flag = 0;


}



void Test_ACTL_StartServiceSearch()
{
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN);
    Init_Test_Filter_Wrapper();

    // Test
    s_manual_tuning_para.freq = 997000000;
    s_manual_tuning_para.u.sat.dvb_s2   = 0;
    s_manual_tuning_para.u.sat.fec      = 1;
    s_manual_tuning_para.u.sat.freq_ex  = 1;
    s_manual_tuning_para.u.sat.modulation   = 1;
    s_manual_tuning_para.u.sat.polarity     = 1;
    s_manual_tuning_para.u.sat.satellite    = 0;
    s_manual_tuning_para.u.sat.symbol_rate  = 2800000;
    
    ACTL_CreatSatelliteInfo(&s_manual_tuning_para, 1);

    APP_NvmSave(COUNTRY_CODE_NVM, COUNTRY_CODE_SWEDEN, TRUE);

    sg_signal_type = SIGNAL_QPSK;
    ACTL_StartServiceSearch(sg_signal_type, ACTL_FREQ_SEARCH);
    
    LOOP:
        Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-730\\HD_muxB_010.trp");
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();
    
        if (1 != sg_exit_flag)
            goto LOOP;
    
        sg_exit_flag = 0;
}



void Test_ACTL_StartManualSearch_dvbt()
{
    S_MANUAL_TUNING_PARAMS s_manual_tuning_para;

    Init_Test_DVB(EN_SIMU_MANUAL_SCAN);
    Init_Test_Filter_Wrapper();

    // Test
    s_manual_tuning_para.freq = 858000000;
    s_manual_tuning_para.u.terr.bwidth  = TBWIDTH_8MHZ;
    s_manual_tuning_para.u.terr.mode    = MODE_COFDM_16K;
    s_manual_tuning_para.u.terr.plp_id  = 0;
    s_manual_tuning_para.u.terr.type    = TERR_TYPE_DVBT;

    ACFG_SetCountry(COUNTRY_CODE_SWEDEN);

    sg_signal_type = SIGNAL_COFDM;

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                 TRUE, TRUE, s_manual_tuning_para.freq, POLARITY_END);
    ACTL_StartManualSearch(sg_signal_type, &s_manual_tuning_para, ACTL_FREQ_SEARCH);
    
    LOOP:
        Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-86\\Task8_16_mux1.trp");
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();
    
        if (1 != sg_exit_flag)
            goto LOOP;
    
        sg_exit_flag = 0;

}


void Test_ACTL_StartServiceSearch_dvbt_autoscan()
{
    Init_Test_DVB(EN_SIMU_AUTO_SCAN);
    Init_Test_Filter_Wrapper();

    // Test

    ACFG_SetCountry(COUNTRY_CODE_SWEDEN);

    sg_signal_type = SIGNAL_COFDM;

    /* void ADB_PrepareDatabaseForSearch(E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite, BOOLEAN clear_new_flag,
                                  BOOLEAN retune, BOOLEAN manual_search, U32BIT frequency, E_STB_DP_POLARITY pol)*/
    ADB_PrepareDatabaseForSearch(sg_signal_type, NULL, TRUE,
                                 TRUE, FALSE, 0, POLARITY_END);
    ACTL_StartServiceSearch(sg_signal_type, ACTL_FREQ_SEARCH);

    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-86\\Task8_16_mux1.trp");
    LOOP:
        Wrapper_EnableTsLoop();
        Wrapper_StartTsLoop(0);
        Wrapper_DisableTsLoop();
    
        if (1 != sg_exit_flag)
            goto LOOP;
    
        sg_exit_flag = 0;

}





// B: Local function define
static void Init_Test_Filter_Wrapper()
{
    static U8BIT init_flag = 0;

    if (0 == init_flag)
    {
        STB_SITerrInitialise();

        Wrapper_DMXInitialise(0, 1);

    }
}

static void Init_Test_DVB(E_SIMU_TYPE eSimuType)
{
    static U8BIT init_dvb_flag = 0;

    if (0 == init_dvb_flag)
    {
        STB_ERInitialise();

        #if 0
        if (EN_SIMU_AUTO_SCAN == eSimuType)
        {
            AEV_Initialise(test_DVB_EVENT_HANDLER_for_autoscan);
        }
        else
        {
            AEV_Initialise(test_DVB_EVENT_HANDLER);
        }
        #endif
        AEV_Initialise(test_DVB_EVENT_HANDLER);

        // APP_InitialiseDVB -->  STB_Initialise --> STB_DPInitialise
        STB_RESInitialise();
        STB_DPInitialise();

        ADB_Initialise();
        ASI_InitialiseAppSi();
        ACTL_InitialiseAppControl();
    }
}



static BOOLEAN test_STBEventHandler(BOOLEAN latched, BOOLEAN repeat, U16BIT class, U16BIT type,
                                      void *data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] latched:%u, repeat:%u, class:%u, type:%u, data:%p, data_size:%u", __FUNCTION__,
                       latched, repeat, class, type, data, data_size);

    if (EV_CLASS_SEARCH == class && EV_TYPE_SUCCESS == type)
    {
        //ADB_AllocateLcns(SIGNAL_QPSK);
        //ADB_SaveDatabase();

        /*
        void ADB_FinaliseDatabaseAfterSearch(BOOLEAN save_changes, E_STB_DP_SIGNAL_TYPE tuner_type, void *satellite,
        BOOLEAN search_completed, BOOLEAN clear_new_flags, BOOLEAN manual_search)
        */

        ADB_FinaliseDatabaseAfterSearch(TRUE, SIGNAL_QPSK, NULL, TRUE, TRUE, TRUE);


        Wrapper_DisableTsLoop();
        sg_exit_flag = 1;
    }

    return TRUE;
}

static void test_DVB_EVENT_HANDLER(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:%u, event_data:%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    if (STB_EVENT_SEARCH_SUCCESS == event && ACTL_IsSearchComplete())
    {
        ADB_FinaliseDatabaseAfterSearch(TRUE, sg_signal_type, NULL, TRUE, TRUE, TRUE);

        Wrapper_DisableTsLoop();
        
        sg_exit_flag = 1;
    }
    else if(STB_EVENT_SEARCH_SUCCESS == event)
    {
        Wrapper_DisableTsLoop();
        Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-86\\Task8_16_mux2.trp");
    }
}

/*
static void test_DVB_EVENT_HANDLER_for_autoscan(U32BIT event, void *event_data, U32BIT data_size)
{
    CERT_LOG_INFO(TAG, "[%s] event:%u, event_data:%p, data_size:%u", __FUNCTION__,
                        event, event_data, data_size);

    if (STB_EVENT_SEARCH_SUCCESS == event && ACTL_IsSearchComplete())
    {

        ADB_FinaliseDatabaseAfterSearch(TRUE, sg_signal_type, NULL, TRUE, TRUE, TRUE);

        Wrapper_DisableTsLoop();
        sg_exit_flag = 1;
    }
}
*/

// E: Local function define

