#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <techtype.h>
#include <dbgfuncs.h>

#include "stbhwtun.h"
#include "stbdpc.h"

#include "cert_log.h"

#include "minIni.h"

#include "autotest_cfg.h"

#define TAG "AUTOTEST_CFG"

// B: Local variable define
static char sg_config_ini_file[512] = { "\0" };

// E: Local variable define

// B: Local function declare
static E_STB_TUNE_SYSTEM_TYPE get_tune_sys_tpye(char *type_str);
static E_STB_TUNE_SIGNAL_TYPE get_tune_sig_type(char *type_str);

static E_STB_DP_POLARITY get_tune_polarity(char *type_str);
static E_STB_DP_FEC get_tune_fec(char *type_str);
static E_STB_DP_MODULATION get_tune_modulation(char *type_str);

static void get_servicename_List(const char *TestIniFile, const char *ListName, U32BIT *number_ptr, char ***name_list);

static void get_test_ch_cfg(const char *TestIniFile, const char *CH, S_TEST_CH_CFG *ch_cfg);
static void show_test_ch_cfg(const S_TEST_CH_CFG *ch_cfg);
// E: Local function declare

volatile static S_TEST_CH_CFG sg_TestCh_Cfg = {
    .valid              = FALSE,
    .streamfile         = "",
    .tune_system_type   = TUNE_SYSTEM_TYPE_UNKNOWN,
    .tune_sig_type      = TUNE_SIGNAL_NONE,
    .sig_strength       = 80,
    .sig_quality        = 80,
    .freq               = 0,
    .plpid              = 0,
    // B: For DVBS
    .pol                = POLARITY_HORIZONTAL,
    .srate              = 24500000,
    .fec                = FEC_7_8_,
    .modu               = MOD_QPSK,
    .lofreq             = 9750,
    // E: For DVBS
    // B: For Update
    .ts_duration_ms     = 0,
    .loop_times         = 1,
    .onid               = 0,
    .tsid               = 0,
    .serid              = 0,
    .channel            =""
    // E: For Update
};


void AUTOTEST_SetCfgIniFile(const char *TestIniFile)
{
    strcpy(sg_config_ini_file, TestIniFile);
}

EN_TESTTYE AUTOTEST_Get_Scan_Type(const char *TestIniFile)
{
    EN_TESTTYE type = EN_TESTTYPE_NONE;

    char str[100];
    long n;

    n = ini_gets("BASE", "SCANTYPE", "dummy", str, sizearray(str), TestIniFile);

    if (0 == strcmp(str, "Manual"))
    {
        type = EN_TESTTYPE_MANUALSCAN;
    }
    else if (0 == strcmp(str, "DVBT-New-Manual"))
    {
        type  = EN_TESTTYPE_MANUALSCAN_DVBT_NEW;
    }
    else if (0 == strcmp(str, "Auto"))
    {
        type = EN_TESTTYPE_AUTOSCAN;
    }
    else if (0 == strcmp(str, "Sat"))
    {
        type = EN_TESTTYPE_SATSCAN;
    }
    else if (0 == strcmp(str, "AstraTP"))
    {
        type = EN_TESTTYPE_ASTRA_TP_SCAN;
    }
    else if (0 == strcmp(str, "AstraSat"))
    {
        type = EN_TESTTYPE_ASTRA_SAT_SCAN;
    }
    else if (0 == strcmp(str, "Update"))
    {
        type = EN_TESTTYE_UPDATE_BASIC;
    }
    else if (0 == strcmp(str, "M7Fast"))
    {
        type = EN_TESTTYPE_M7_FAST;
    }
    else
    {
        type = EN_TESTTYE_FREE_RUN;
    }

    return type;
}

U32BIT AUTOTEST_Get_CountryCode(const char *TestIniFile)
{
    U32BIT code = 0;

    char str[10];
    long n;

    n = ini_gets("BASE", "COUNTRY", "dummy", str, sizearray(str), TestIniFile);
    assert(3==n);

    code =  (U32BIT)(str[0] << 16 | str[1] << 8 | str[2]);

    return code;
}


U32BIT AUTOTEST_Get_ScanCount(const char *TestIniFile)
{
    U32BIT count = 1;

    char str[10];
    long n;

    n = ini_getl("BASE", "SCANCOUNT", 1, TestIniFile);
    count = (U32BIT)n;

    return count;
}



U16BIT AUTOTEST_Get_PreferNetid(const char *TestIniFile)
{
    U16BIT code = -1;

    char str[10];
    long n;

    n = ini_getl("BASE", "NETID", -1, TestIniFile);
    if (-1 != n)
    {
        code = (U16BIT)n;
    }

    return code;
}



E_STB_TUNE_SIGNAL_TYPE AUTOTEST_Get_ShowInfo_Sigtype(const char *TestIniFile)
{
    E_STB_TUNE_SIGNAL_TYPE sig_type = TUNE_SIGNAL_NONE;

    char str[M_STREAMFILE_PATHNANME_LEN];
    long n;

    n = ini_gets("SHOWINFO", "SIGTYPE", "dummy", str, sizearray(str), TestIniFile);
    sig_type = get_tune_sig_type(str);

    return sig_type;
}

BOOLEAN AUTOTEST_Get_ShowInfo_Servlist(const char *TestIniFile)
{
    BOOLEAN ret = FALSE;
    char str[M_STREAMFILE_PATHNANME_LEN];
    long n;

    n = ini_gets("SHOWINFO", "SERVLIST", "FALSE", str, sizearray(str), TestIniFile);
    if (0 == strcmp(str, "true"))
    {
        ret = TRUE;
    }

    return ret;
}

// CONFLICT SERVICE config
void AUTOTEST_Get_ConflictService_List(const char *TestIniFile, U32BIT *number_ptr, char ***name_list)
{
    get_servicename_List(TestIniFile, "CONFLICT SERVICE", number_ptr, name_list);
}


// SELECT SERVICE config
void AUTOTEST_Get_SelectService_List(const char *TestIniFile, U32BIT *number_ptr, char ***name_list)
{
    get_servicename_List(TestIniFile, "SELECT SERVICE", number_ptr, name_list);
}


// SEL-SGT-SRV-LIST
void AUTOTEST_Get_SelSGT_SerList(U32BIT *number_ptr, char **list_name)
{
    BOOLEAN ret = FALSE;
    char name[256];
    long n;
    char *tmp = NULL;

    n = ini_getl("SEL-SGT-SRV-LIST", "LISTID", 0, sg_config_ini_file);
    *number_ptr = n;


    n = ini_gets("SEL-SGT-SRV-LIST", "LISTNAME", "dummy", name, sizearray(name), sg_config_ini_file);
    *list_name = malloc(n + 1);
    strcpy(*list_name, name);
}



BOOLEAN AUTOTEST_Get_ClearDB(const char *TestIniFile)
{
    BOOLEAN is_clear_db = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "CLEARDB", "false", str, sizearray(str), TestIniFile);

    if (0 == strcmp(str, "true"))
    {
        is_clear_db = TRUE;
    }

    return is_clear_db;
}

BOOLEAN AUTOTEST_Get_AutoOrder(const char *TestIniFile)
{
    BOOLEAN ret = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "AUTOORDER", "false", str, sizearray(str), TestIniFile);

    if (0 == strcmp(str, "true"))
    {
        ret = TRUE;
    }

    return ret;
}

BOOLEAN AUTOTEST_Get_NetScan()
{
    BOOLEAN ret = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "NETSCAN", "false", str, sizearray(str), sg_config_ini_file);

    if (0 == strcmp(str, "true"))
    {
        ret = TRUE;
    }

    return ret;
}

BOOLEAN AUTOTEST_Get_QuickScan()
{
    BOOLEAN ret = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "QUICKSCAN", "false", str, sizearray(str), sg_config_ini_file);

    if (0 == strcmp(str, "true"))
    {
        ret = TRUE;
    }

    return ret;
}

BOOLEAN AUTOTEST_Is_AllTunerLocked()
{
    BOOLEAN ret = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "ALLLOCKED", "false", str, sizearray(str), sg_config_ini_file);

    if (0 == strcmp(str, "true"))
    {
        ret = TRUE;
    }

    return ret;
}




BOOLEAN AUTOTEST_Get_One_CH_Cfg(const char *TestIniFile, const char *CH)
{
    char str[M_STREAMFILE_PATHNANME_LEN];
    long n;

    n = ini_gets(CH, "STREAM", "dummy", str, sizearray(str), TestIniFile);
    if (0 == strcmp(str, "dummy"))
    {
        //sg_TestCh_Cfg.valid = FALSE;

        return FALSE;
    }

    strcpy(sg_TestCh_Cfg.streamfile, str);

    n = ini_gets(CH, "SYSTYPE", "dummy", str, sizearray(str), TestIniFile);
    sg_TestCh_Cfg.tune_system_type = get_tune_sys_tpye(str);

    n = ini_gets(CH, "SIGTYPE", "dummy", str, sizearray(str), TestIniFile);
    sg_TestCh_Cfg.tune_sig_type = get_tune_sig_type(str);

    n = ini_getl(CH, "STRENGTH", 80, TestIniFile);
    sg_TestCh_Cfg.sig_strength = (U8BIT)n;

    n = ini_getl(CH, "QULITY", 80, TestIniFile);
    sg_TestCh_Cfg.sig_quality = (U8BIT)n;

    n = ini_getl(CH, "FREQ", -1, TestIniFile);
    sg_TestCh_Cfg.freq = (U32BIT)n;

    n = ini_getl(CH, "PLPID", -1, TestIniFile);
    sg_TestCh_Cfg.plpid = (U8BIT)n;

    n = ini_getl(CH, "DURATION", 0, TestIniFile);
    sg_TestCh_Cfg.ts_duration_ms = n;

    n = ini_getl(CH, "LOOP", 1, TestIniFile);
    sg_TestCh_Cfg.loop_times = n;

    n = ini_getl(CH, "ONID", 0, TestIniFile);
    sg_TestCh_Cfg.onid = n;

    n = ini_getl(CH, "TSID", 0, TestIniFile);
    sg_TestCh_Cfg.tsid = n;

    n = ini_getl(CH, "SERID", 0, TestIniFile);
    sg_TestCh_Cfg.serid = n;

    // B: For DVBS

    n = ini_gets(CH, "POLAR", "dummy", str, sizearray(str), TestIniFile);
    sg_TestCh_Cfg.pol = get_tune_polarity(str);

    n = ini_getl(CH, "SRATE", -1, TestIniFile);
    sg_TestCh_Cfg.srate = (U32BIT)n;

    n = ini_gets(CH, "FEC", "dummy", str, sizearray(str), TestIniFile);
    sg_TestCh_Cfg.fec = get_tune_fec(str);

    n = ini_gets(CH, "MODU", "dummy", str, sizearray(str), TestIniFile);
    sg_TestCh_Cfg.modu = get_tune_modulation(str);

     n = ini_getl(CH, "LOFREQ", 9750, TestIniFile);
     sg_TestCh_Cfg.lofreq = (U32BIT)n;

    // E: For DVBS

    sg_TestCh_Cfg.valid = TRUE;

    return TRUE;
}


void AUTOTEST_Set_One_CH_Cfg_Invalid()
{
    sg_TestCh_Cfg.valid = FALSE;
}

BOOLEAN AUTOTEST_Is_CH_Cfg_Valid()
{
    return sg_TestCh_Cfg.valid;
}


char *AUTOTEST_Get_CurCfg_StreamFile()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return NULL;
    }

    return sg_TestCh_Cfg.streamfile;
}


U32BIT AUTOTEST_Get_Duration()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return 0;
    }

    return sg_TestCh_Cfg.ts_duration_ms;
}


U32BIT AUTOTEST_Get_LoopTimes()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return 0;
    }

    return sg_TestCh_Cfg.loop_times;
}


void AUTOTEST_Get_ServiceTripleId(U16BIT *onid_ptr, U16BIT *tsid_ptr, U16BIT *serid_ptr)
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return 0;
    }

    *onid_ptr = sg_TestCh_Cfg.onid;
    *tsid_ptr = sg_TestCh_Cfg.tsid;
    *serid_ptr = sg_TestCh_Cfg.serid;
}



E_STB_TUNE_SYSTEM_TYPE AUTOTEST_Get_CurCfg_TuneSys()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return TUNE_SYSTEM_TYPE_UNKNOWN;
    }

    return sg_TestCh_Cfg.tune_system_type;
}

E_STB_TUNE_SIGNAL_TYPE AUTOTEST_Get_CurCfg_TuneSig()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return TUNE_SIGNAL_NONE;
    }

    return sg_TestCh_Cfg.tune_sig_type;
}

U8BIT AUTOTEST_Get_CurCfg_SigStrength()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return 50;
    }

    return sg_TestCh_Cfg.sig_strength;
}

U8BIT AUTOTEST_Get_CurCfg_SigQuality()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return 50;
    }

    return sg_TestCh_Cfg.sig_quality;
}


U32BIT AUTOTEST_Get_CurCfg_Freq()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return -1;
    }

    return sg_TestCh_Cfg.freq;
}

U8BIT AUTOTEST_Get_CurCfg_Plpid()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return -1;
    }

    return sg_TestCh_Cfg.plpid;
}

E_STB_DP_POLARITY AUTOTEST_Get_CurCfg_Polairty()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return POLARITY_RIGHT;
    }

    return sg_TestCh_Cfg.pol;
}

U16BIT AUTOTEST_Get_CurCfg_Srate()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return -1;
    }

    return sg_TestCh_Cfg.srate;
}

E_STB_DP_FEC AUTOTEST_Get_CurCfg_Fec()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return FEC_AUTOMATIC;
    }

    return sg_TestCh_Cfg.fec;
}

E_STB_DP_MODULATION AUTOTEST_Get_CurCfg_Modulation()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return MOD_AUTO;
    }

    return sg_TestCh_Cfg.modu;
}

U32BIT AUTOTEST_Get_CurCfg_LoFreq()
{
    if (!sg_TestCh_Cfg.valid)
    {
        CERT_LOG_ERROR(TAG, "[%s] Err", __FUNCTION__);

        return -1;
    }

    return sg_TestCh_Cfg.lofreq;
}



void AUTOTEST_Update_Autoscan_CH_Cfg(BOOLEAN isFirstCh, const char *TestIniFile)
{
    static U32BIT autoscan_ch = 0;
    static char ini_file[256];
    char channel[32];

    if (isFirstCh)      // The first Ch
    {
        autoscan_ch = 1;
        strcpy(ini_file, TestIniFile);
    }
    else
    {
        autoscan_ch++;
    }

    sprintf(channel, "CH %u", autoscan_ch);

    AUTOTEST_Get_One_CH_Cfg(ini_file, channel);
}


BOOLEAN AUTOTEST_Update_Netscan_Cfg(E_STB_TUNE_SYSTEM_TYPE system_type, E_STB_TUNE_SIGNAL_TYPE sig_type,
                                                        U32BIT freq, E_STB_DP_POLARITY polarity)
{
    BOOLEAN ret = FALSE;
    U32BIT chno = 1;
    char channel[32];

    sprintf(channel, "CH %u", chno);
    while (AUTOTEST_Get_One_CH_Cfg(sg_config_ini_file, channel))
    {
        if (TUNE_SIGNAL_QPSK == sig_type)
        {
            if ((system_type == AUTOTEST_Get_CurCfg_TuneSys() ||  TUNE_SYSTEM_TYPE_UNKNOWN == system_type) &&
                sig_type    == AUTOTEST_Get_CurCfg_TuneSig() &&
                (polarity    == AUTOTEST_Get_CurCfg_Polairty() || POLARITY_RIGHT == AUTOTEST_Get_CurCfg_Polairty()) &&
                (freq >= AUTOTEST_Get_CurCfg_Freq() - 2&& freq <= AUTOTEST_Get_CurCfg_Freq() + 2))
            {
                ret = TRUE;

                break;
            }
        }
        else
        {
            if ((system_type == AUTOTEST_Get_CurCfg_TuneSys() ||  TUNE_SYSTEM_TYPE_UNKNOWN == system_type) &&
                sig_type    == AUTOTEST_Get_CurCfg_TuneSig() &&
                (freq >= AUTOTEST_Get_CurCfg_Freq() - 2000000 && freq <= AUTOTEST_Get_CurCfg_Freq() + 2000000))
            {
                ret = TRUE;

                break;
            }
        }

        chno++;
        sprintf(channel, "CH %u", chno);
    }

    return ret;
}

// B: 2022-05-07 for Multi Modulators simulation
static S_TEST_CH_CFG *sg_Modulator_Cfg_array = NULL;
static int sg_Modulator_Number = 0;
static BOOLEAN sg_bGoMulMod = FALSE;

BOOLEAN AUTOTEST_isMulMod(const char *TestIniFile)
{
    BOOLEAN is_multimod_simulation = FALSE;

    char str[100];
    long n;

    n = ini_gets("BASE", "MULMOD", "false", str, sizearray(str), TestIniFile);
    if (0 == strcmp(str, "true"))
    {
        is_multimod_simulation = TRUE;
    }

    sg_bGoMulMod = is_multimod_simulation;

    return is_multimod_simulation;
}

BOOLEAN AUTOTEST_isGoMulMod()
{
    return sg_bGoMulMod;
}


U32BIT AUTOTEST_GetModNumber(const char  *TestIniFile)
{
    U32BIT count = 1;

    long n;

    n = ini_getl("BASE", "MODNUM", 0, TestIniFile);
    count = (U32BIT)n;

    return count;
}

void AUTOTEST_GetAllModulatorCfg(const char *TestIniFile, U32BIT modulator_numbers)
{
    int i;
    char channel[32];

    if (NULL != sg_Modulator_Cfg_array)
    {
        free(sg_Modulator_Cfg_array);
    }

    sg_Modulator_Cfg_array  = malloc(modulator_numbers * sizeof(S_TEST_CH_CFG));
    sg_Modulator_Number     = modulator_numbers;

    for (i = 0; i < modulator_numbers; i++)
    {
        sprintf(channel, "CH %u", (i + 1));

        get_test_ch_cfg(TestIniFile, channel, &(sg_Modulator_Cfg_array[i]));

        show_test_ch_cfg(&(sg_Modulator_Cfg_array[i]));
    }
}


void AUTOTEST_UpdateCurMod(U32BIT curmod_index)
{
    extern void Wrapper_DisableTsLoop();

    memcpy(&sg_TestCh_Cfg, &(sg_Modulator_Cfg_array[curmod_index]), sizeof(S_TEST_CH_CFG));
    Wrapper_DisableTsLoop();
}

U32BIT AUTOTEST_GetMatchModulatorIndex_Dvbs(U32BIT freq, U32BIT freqoffset, U32BIT lofreq, U32BIT pol)
{
    U32BIT match_idx = INVALID_MODULATOR_INDEX;

    for (int i = 0; i < sg_Modulator_Number; i++)
    {
        if ((freq > sg_Modulator_Cfg_array[i].freq - freqoffset && freq < sg_Modulator_Cfg_array[i].freq + freqoffset)
            /*&& (lofreq == sg_Modulator_Cfg_array[i].lofreq)*/
            && (pol == sg_Modulator_Cfg_array[i].pol || POLARITY_END == sg_Modulator_Cfg_array[i].pol))
        {
            match_idx = i;
            break;
        }
    }

    return match_idx;
}

// E: 2022-05-07 for Multi Modulators simulation



// B: 2022-05-07 for Result Check
BOOLEAN AUTOTEST_isOnlyCheckTotalServiceNumber(const char  *TestIniFile)
{
    BOOLEAN is_only_check_total_service = FALSE;

    char str[100];
    long n;

    n = ini_gets("TOTAL SERVISES", "ONLYCHKNUM", "false", str, sizearray(str), TestIniFile);
    if (0 == strcmp(str, "true"))
    {
        is_only_check_total_service = TRUE;
    }

    return is_only_check_total_service;
}


U32BIT AUTOTEST_GetTotalServiceNumber(const char  *TestIniFile)
{
    U32BIT count = 0;

    long n;

    n = ini_getl("TOTAL SERVISES", "ALLSERNUM", 0, TestIniFile);
    count = (U32BIT)n;

    return count;
}
// E: 2022-05-07 for Result Check



// B: 2022-05-07 for M7
U32BIT AUTOTEST_GetSelectedOperId()
{
    U32BIT count = 0;

    long n;

    n = ini_getl("M7FAST", "OPERLISTID", 0xFFFFFFFF, sg_config_ini_file);
    count = (U32BIT)n;

    return count;
}

U32BIT AUTOTEST_GetSelectedOperSubListId()
{
    U32BIT count = 0;

    long n;

    n = ini_getl("M7FAST", "OPERSUBID", 0xFFFFFFFF, sg_config_ini_file);
    count = (U32BIT)n;

    return count;
}

char* AUTOTEST_M7_GetScanType(const char  *TestIniFile)
{
    char str[100];
    long n;

    n = ini_gets("M7FAST", "SCANTYPE", "fti", str, sizearray(str), TestIniFile);
    if (0 == strcmp(str, "standby"))
    {
        return "standby";
    }
    else if (0 == strcmp(str, "poweron"))
    {
        return "poweron";
    }

    return "fti";
}


// E: 2022-05-07 for M7



// B: Local function define
static E_STB_TUNE_SYSTEM_TYPE get_tune_sys_tpye(char *type_str)
{
    E_STB_TUNE_SYSTEM_TYPE type = TUNE_SYSTEM_TYPE_UNKNOWN;

    if (0 == strcmp(type_str, "DVBT"))
    {
        type = TUNE_SYSTEM_TYPE_DVBT;
    }
    else if (0 == strcmp(type_str, "DVBT2"))
    {
        type = TUNE_SYSTEM_TYPE_DVBT2;
    }
    else if (0 == strcmp(type_str, "DVBS"))
    {
        type = TUNE_SYSTEM_TYPE_DVBS;
    }
    else if (0 == strcmp(type_str, "DVBS2"))
    {
        type = TUNE_SYSTEM_TYPE_DVBS2;
    }
    else if (0 == strcmp(type_str, "DVBC"))
    {
        type = TUNE_SYSTEM_TYPE_DVBC;
    }
    else if (0 == strcmp(type_str, "ISDBT"))
    {
        type = TUNE_SYSTEM_TYPE_ISDBT;
    }
    else if (0 == strcmp(type_str, "ANALOG"))
    {
        type = TUNE_SYSTEM_TYPE_ANALOG;
    }

    return type;
}

static E_STB_TUNE_SIGNAL_TYPE get_tune_sig_type(char *type_str)
{
    E_STB_TUNE_SIGNAL_TYPE type = TUNE_SIGNAL_NONE;

    if (0 == strcmp(type_str, "COFDM"))
    {
        type = TUNE_SIGNAL_COFDM;
    }
    else if (0 == strcmp(type_str, "QPSK"))
    {
        type = TUNE_SIGNAL_QPSK;
    }
    else if (0 == strcmp(type_str, "QAM"))
    {
        type = TUNE_SIGNAL_QAM;
    }
    else if (0 == strcmp(type_str, "ISDBT"))
    {
        type = TUNE_SIGNAL_ISDBT;
    }
    else if (0 == strcmp(type_str, "ANALOG"))
    {
        type = TUNE_SIGNAL_ANALOG;
    }

    return type;
}

static E_STB_DP_POLARITY get_tune_polarity(char *type_str)
{
    E_STB_DP_POLARITY pol = POLARITY_HORIZONTAL;

    if (0 == strcmp(type_str, "HOR"))
    {
        pol = POLARITY_HORIZONTAL;
    }
    else if (0 == strcmp(type_str, "VER"))
    {
        pol = POLARITY_VERTICAL;
    }
    else if (0 == strcmp(type_str, "ALL"))
    {
        pol = POLARITY_END;
    }
    else if (0 == strcmp(type_str, "LEFT"))
    {
        pol = POLARITY_LEFT;
    }
    else
    {
        pol = POLARITY_RIGHT;
    }

    return pol;
}

static E_STB_DP_FEC get_tune_fec(char *type_str)
{
    E_STB_DP_FEC fec = FEC_AUTOMATIC;

    if (0 == strcmp(type_str, "FEC_1_2"))
    {
        fec = FEC_1_2_;
    }
    else if (0 == strcmp(type_str, "FEC_2_3"))
    {
        fec = FEC_2_3_;
    }
    else if (0 == strcmp(type_str, "FEC_3_4"))
    {
        fec = FEC_3_4_;
    }
    else if (0 == strcmp(type_str, "FEC_5_6"))
    {
        fec = FEC_5_6_;
    }
    else if (0 == strcmp(type_str, "FEC_7_8"))
    {
        fec = FEC_7_8_;
    }
     else if (0 == strcmp(type_str, "FEC_1_4"))
    {
        fec = FEC_1_4_;
    }
    else if (0 == strcmp(type_str, "FEC_1_3"))
    {
        fec = FEC_1_3_;
    }
     else if (0 == strcmp(type_str, "FEC_2_5"))
    {
        fec = FEC_2_5_;
    }
    else if (0 == strcmp(type_str, "FEC_8_9"))
    {
        fec = FEC_8_9_;
    }
     else if (0 == strcmp(type_str, "FEC_9_10"))
    {
        fec = FEC_9_10_;
    }
    else if (0 == strcmp(type_str, "FEC_3_5"))
    {
        fec = FEC_3_5_;
    }
    else if (0 == strcmp(type_str, "FEC_4_5"))
    {
        fec = FEC_4_5_;
    }
    else
    {
        fec = FEC_AUTOMATIC;
    }

    return fec;
}

static E_STB_DP_MODULATION get_tune_modulation(char *type_str)
{
    E_STB_DP_MODULATION mod = MOD_AUTO;

    if (0 == strcmp(type_str, "MOD_QPSK"))
    {
        mod = MOD_QPSK;
    }
    else if (0 == strcmp(type_str, "MOD_8PSK"))
    {
        mod = MOD_8PSK;
    }
    else if (0 == strcmp(type_str, "MOD_16QAM"))
    {
        mod = MOD_16QAM;
    }
    else
    {
        mod = MOD_AUTO;
    }

    return mod;
}

static void get_servicename_List(const char *TestIniFile, const char *ListName, U32BIT *number_ptr, char ***name_list)
{

    BOOLEAN ret = FALSE;
    char service_idx[6];
    char str[M_STREAMFILE_PATHNANME_LEN];
    long n;
    U32BIT i = 0;
    char *tmp = NULL;

    do
    {
        sprintf(service_idx, "SER%d", i + 1);
        n = ini_gets(ListName, service_idx, "dummy", str, sizearray(str), TestIniFile);
        if (0 == strcmp(str, "dummy"))
        {
            break;
        }

        i++;
    } while (1);

    *number_ptr = i;
    *name_list = malloc(sizeof(char *) * i);

    for (i = 0; i < *number_ptr; i++)
    {
        sprintf(service_idx, "SER%d", i + 1);
        n = ini_gets(ListName, service_idx, "dummy", str, sizearray(str), TestIniFile);

        (*name_list)[i] = malloc(n + 1);
        strcpy((*name_list)[i], str);
    }
}


static void get_test_ch_cfg(const char *TestIniFile, const char *CH, S_TEST_CH_CFG *ch_cfg)
{
    char str[M_STREAMFILE_PATHNANME_LEN];
    long n;

    n = ini_gets(CH, "STREAM", "dummy", str, sizearray(str), TestIniFile);
    strcpy(ch_cfg->streamfile, str);

    n = ini_gets(CH, "SYSTYPE", "dummy", str, sizearray(str), TestIniFile);
    ch_cfg->tune_system_type = get_tune_sys_tpye(str);

    n = ini_gets(CH, "SIGTYPE", "dummy", str, sizearray(str), TestIniFile);
    ch_cfg->tune_sig_type = get_tune_sig_type(str);

    n = ini_getl(CH, "STRENGTH", 80, TestIniFile);
    ch_cfg->sig_strength = (U8BIT)n;

    n = ini_getl(CH, "QULITY", 80, TestIniFile);
    ch_cfg->sig_quality = (U8BIT)n;

    n = ini_getl(CH, "FREQ", -1, TestIniFile);
    ch_cfg->freq = (U32BIT)n;

    n = ini_getl(CH, "PLPID", -1, TestIniFile);
    ch_cfg->plpid = (U8BIT)n;

    n = ini_getl(CH, "DURATION", 0, TestIniFile);
    ch_cfg->ts_duration_ms = n;

    n = ini_getl(CH, "LOOP", 1, TestIniFile);
    ch_cfg->loop_times = n;

    n = ini_getl(CH, "ONID", 0, TestIniFile);
    ch_cfg->onid = n;

    n = ini_getl(CH, "TSID", 0, TestIniFile);
    ch_cfg->tsid = n;

    n = ini_getl(CH, "SERID", 0, TestIniFile);
    ch_cfg->serid = n;

    // B: For DVBS

    n = ini_gets(CH, "POLAR", "dummy", str, sizearray(str), TestIniFile);
    ch_cfg->pol = get_tune_polarity(str);

    n = ini_getl(CH, "SRATE", -1, TestIniFile);
    ch_cfg->srate = (U32BIT)n;

    n = ini_gets(CH, "FEC", "dummy", str, sizearray(str), TestIniFile);
    ch_cfg->fec = get_tune_fec(str);

    n = ini_gets(CH, "MODU", "dummy", str, sizearray(str), TestIniFile);
    ch_cfg->modu = get_tune_modulation(str);

     n = ini_getl(CH, "LOFREQ", 9750, TestIniFile);
     ch_cfg->lofreq = (U32BIT)n;

    // E: For DVBS

    ch_cfg->valid = TRUE;

    strcpy(ch_cfg->channel, CH);

    return TRUE;
}

static void show_test_ch_cfg(const S_TEST_CH_CFG *ch_cfg)
{
    CERT_LOG_DEBG(TAG, "");
    CERT_LOG_DEBG(TAG, "[%s] B: ===>", __FUNCTION__);

    CERT_LOG_DEBG(TAG, "\t ch:%s, stream:%s", ch_cfg->channel, ch_cfg->streamfile);

    CERT_LOG_DEBG(TAG, "\t systype:%d, freq:%d", ch_cfg->tune_system_type, ch_cfg->freq);
    CERT_LOG_DEBG(TAG, "\t plpid:%d", ch_cfg->plpid);
    CERT_LOG_DEBG(TAG, "\t pol:%d", ch_cfg->pol);
    CERT_LOG_DEBG(TAG, "\t lofreq:%d", ch_cfg->lofreq);

    CERT_LOG_DEBG(TAG, "[%s] E: <===", __FUNCTION__);
    CERT_LOG_DEBG(TAG, "");

}



// E: Local function define
