#ifndef __AUTOTEST_CFG_H__
#define __AUTOTEST_CFG_H__

#define M_STREAMFILE_PATHNANME_LEN 256

typedef enum tag_TestType {
    EN_TESTTYPE_NONE,
    EN_TESTTYPE_MANUALSCAN,
    EN_TESTTYPE_MANUALSCAN_DVBT_NEW,
    EN_TESTTYPE_,
    EN_TESTTYPE_AUTOSCAN,
    EN_TESTTYPE_SATSCAN,
    EN_TESTTYPE_ASTRA_TP_SCAN,
    EN_TESTTYPE_ASTRA_SAT_SCAN,
    EN_TESTTYPE_M7_FAST,

    EN_TESTTYE_UPDATE_BASIC,

    EN_TESTTYE_FREE_RUN,
    EN_TESTTYPE_COUNT
} EN_TESTTYE;

typedef struct tag_TestCH_Cfg {
    BOOLEAN valid;
    char streamfile[M_STREAMFILE_PATHNANME_LEN];
    E_STB_TUNE_SYSTEM_TYPE tune_system_type;
    E_STB_TUNE_SIGNAL_TYPE tune_sig_type;
    U8BIT sig_strength;
    U8BIT sig_quality;
    U32BIT freq;
    U8BIT  plpid;

    E_STB_DP_POLARITY pol;
    U16BIT srate;
    E_STB_DP_FEC fec;
    E_STB_DP_MODULATION modu;
    U32BIT lofreq;

    // for update
    U32BIT ts_duration_ms;
    U32BIT loop_times;
    U16BIT onid;
    U16BIT tsid;
    U16BIT serid;
    char channel[16];
}S_TEST_CH_CFG;

//
void AUTOTEST_SetCfgIniFile(const char *TestIniFile);

// BASE config
EN_TESTTYE AUTOTEST_Get_Scan_Type(const char *TestIniFile);
U32BIT AUTOTEST_Get_CountryCode(const char *TestIniFile);
U16BIT AUTOTEST_Get_PreferNetid(const char *TestIniFile);
BOOLEAN AUTOTEST_Get_ClearDB(const char *TestIniFile);
U32BIT AUTOTEST_Get_ScanCount(const char *TestIniFile);
BOOLEAN AUTOTEST_Get_AutoOrder(const char *TestIniFile);
BOOLEAN AUTOTEST_Get_NetScan();
BOOLEAN AUTOTEST_Get_QuickScan();
BOOLEAN AUTOTEST_Is_AllTunerLocked();




// SHOWINFO config
E_STB_TUNE_SIGNAL_TYPE AUTOTEST_Get_ShowInfo_Sigtype(const char *TestIniFile);
BOOLEAN AUTOTEST_Get_ShowInfo_Servlist(const char *TestIniFile);

// CONFLICT SERVICE config
void AUTOTEST_Get_ConflictService_List(const char *TestIniFile, U32BIT *number_ptr, char ***name_list);

// SELECT SERVICE config
void AUTOTEST_Get_SelectService_List(const char *TestIniFile, U32BIT *number_ptr, char ***name_list);

// SEL-SGT-SRV-LIST
void AUTOTEST_Get_SelSGT_SerList(U32BIT *number_ptr, char **list_name);

// B: CHANNEL config
void AUTOTEST_Update_Autoscan_CH_Cfg(BOOLEAN isFirstCh, const char *TestIniFile);

BOOLEAN AUTOTEST_Update_Netscan_Cfg(E_STB_TUNE_SYSTEM_TYPE system_type, E_STB_TUNE_SIGNAL_TYPE sig_type,
                                                        U32BIT freq, E_STB_DP_POLARITY polarity);





void AUTOTEST_Set_One_CH_Cfg_Invalid();
BOOLEAN AUTOTEST_Is_CH_Cfg_Valid();


char *AUTOTEST_Get_CurCfg_StreamFile();
U32BIT AUTOTEST_Get_Duration();
U32BIT AUTOTEST_Get_LoopTimes();
void AUTOTEST_Get_ServiceTripleId(U16BIT *onid_ptr, U16BIT *tsid_ptr, U16BIT *serid_ptr);



E_STB_TUNE_SYSTEM_TYPE AUTOTEST_Get_CurCfg_TuneSys();
E_STB_TUNE_SIGNAL_TYPE AUTOTEST_Get_CurCfg_TuneSig();
U8BIT AUTOTEST_Get_CurCfg_SigStrength();
U8BIT AUTOTEST_Get_CurCfg_SigQuality();

U32BIT AUTOTEST_Get_CurCfg_Freq();
U8BIT AUTOTEST_Get_CurCfg_Plpid();



// CHANNEL config: for DVBS
E_STB_DP_POLARITY AUTOTEST_Get_CurCfg_Polairty();
U16BIT AUTOTEST_Get_CurCfg_Srate();
E_STB_DP_FEC AUTOTEST_Get_CurCfg_Fec();
E_STB_DP_MODULATION AUTOTEST_Get_CurCfg_Modulation();
U32BIT AUTOTEST_Get_CurCfg_LoFreq();

// E: CHANNEL config


// B: 2022-05-07 for Multi Modulators simulation
BOOLEAN AUTOTEST_isMulMod(const char *TestIniFile);
BOOLEAN AUTOTEST_isGoMulMod();

U32BIT AUTOTEST_GetModNumber(const char  *TestIniFile);
void AUTOTEST_GetAllModulatorCfg(const char *TestIniFile, U32BIT modulator_numbers);
void AUTOTEST_UpdateCurMod(U32BIT curmod_index);
// E: 2022-05-07 for Multi Modulators simulation

// B: 2022-05-07 for Result Check
BOOLEAN AUTOTEST_isOnlyCheckTotalServiceNumber(const char  *TestIniFile);
U32BIT AUTOTEST_GetTotalServiceNumber(const char  *TestIniFile);
// E: 2022-05-07 for Result Check

// B: 2022-05-07 for M7
U32BIT AUTOTEST_GetSelectedOperId();
U32BIT AUTOTEST_GetSelectedOperSubListId();

char* AUTOTEST_M7_GetScanType(const char  *TestIniFile);
// E: 2022-05-07 for M7



// E: 2022-05-07 for Result Check

#define INVALID_MODULATOR_INDEX 0xFFFFFFFF
U32BIT AUTOTEST_GetMatchModulatorIndex_Dvbs(U32BIT freq, U32BIT freqoffset, U32BIT lofreq, U32BIT pol);
#endif
