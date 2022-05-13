#include <stdio.h>
#include <stdlib.h>

#include "test_filter_wrapper.h"
#include "test_filter_scan.h"
#include "test_m7_scan.h"
#include "autotest_main.h"



void Integration_TsLoop();

static int i = 0;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define CALL_TEST(a) do { \
        printf("\n\n[%d: %s] \n\n\n", ++i, #a); \
        a(); \
    }while (0);

int main(int argc, char* argv[]) {

    int ret = 0;

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

        CALL_TEST(Test_CERT_M7_Scan_Start)
        CALL_TEST(Test_CERT_M7_SCAN_ACTION);
    
        printf("Input any key to continue:\n");
        getch();
        
        CALL_TEST(Test_CERT_M7_Scan_Stop)
    }
#else
    CALL_TEST(Integration_TsLoop);

#endif
    return ret;
}