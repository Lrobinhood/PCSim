#include <stdio.h>
#include <stdlib.h>

#include "test_filter_wrapper.h"
#include "test_filter_scan.h"
#include "test_m7_scan.h"
#include "autotest_main.h"

extern void test_autotest_interface_request();

#ifdef _DEBUG
	#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
	#define DEBUG_CLIENTBLOCK
#endif
 
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
 
	#define new DEBUG_CLIENTBLOCK
#endif

extern void autotest_interface_reginterface(); 

void Integration_TsLoop();

static int i = 0;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define CALL_TEST(a) do { \
        printf("\n\n[%d: %s] \n\n\n", ++i, #a); \
        a(); \
    }while (0);

int main(int argc, char* argv[]) {

    int ret = 0;

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

#if 1
    if (argc > 1)
    {
        ret = autotest_main(argc, argv);
    }
    else
    {
        //CALL_TEST(Test_Wrapper_FilterNIT);

        //CALL_TEST(Test_Wrapper_FilterSGT);

        //CALL_TEST(Test_CERT_ManageChannelSearch);

        //CALL_TEST(Test_ACTL_StartServiceSearch);

        //CALL_TEST(Test_ACTL_StartManualSearch_dvbt);

        //CALL_TEST(Test_ACTL_StartServiceSearch_dvbt_autoscan);

        //CALL_TEST(Test_Wrapper_SecFilter);

        //CALL_TEST(Test_CERT_M7_Scan_Start)
        //CALL_TEST(Test_CERT_M7_SCAN_ACTION);
    
        //printf("Input any key to continue:\n");
        //getch();
        
        //CALL_TEST(Test_CERT_M7_Scan_Stop)
        //CALL_TEST(autotest_interface_reginterface);
        //..\AUTOTEST-M7Scan\m7-fast-scan-Test_22_1.ini

        CALL_TEST(test_autotest_interface_request);
    }
#else
    CALL_TEST(Integration_TsLoop);

#endif
    return ret;
}