#ifndef __AUTOTEST_SCAN_H__
#define __AUTOTEST_SCAN_H__

// B: Type define
typedef enum tag_Simlulate_Type
{
    EN_SIMU_MANUAL_SCAN,
    EN_SIMU_AUTO_SCAN,
    EN_SIMU_NUMBER
}E_SIMU_TYPE;

// E: Type Define

typedef void (*DVB_EVENT_HANDLER)(U32BIT event, void *event_data, U32BIT data_size);

int autotest_get_exit_flag();
void autotest_set_exit_flag(int exit_flag);

int autotest_get_signal_type();
void autotest_set_signal_type(int signal_type);


void Init_Test_DVB(E_SIMU_TYPE eSimuType, DVB_EVENT_HANDLER dvb_event_handle_func);
void Init_Test_Filter_Wrapper();
void Init_Test_for_Country(U32BIT CountryCode, E_STB_DP_SIGNAL_TYPE SigType, const char *TestIniFile);

bool is_scan_test(unsigned int test_type);

int autotest_scan(int argc, char* argv[], unsigned int test_type);

int autotest_manualscan(const char *TestIniFile);

int autotest_dvbt_new_manualscan(const char *TestIniFile);

int autotest_manualscan_twice(const char *TestIniFile);

int autotest_autoscan(const char *TestIniFile);

int autotest_astra_transponder_scan(const char *TestIniFile);

int autotest_astra_sat_scan(const char *TestIniFile);

int autotest_m7_fast(const char *TestIniFile);

void autotest_scan_clear_all_records();




#endif
