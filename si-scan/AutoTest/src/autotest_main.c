#include <techtype.h>
#include <dbgfuncs.h>


#include "stbhwtun.h"
#include "stbdpc.h"

#include "cert_log.h"

#include "cert_apctrl.h"

#include "autotest_cfg.h"
#include "autotest_main.h"
#include "autotest_scan.h"

#define TAG "AUTOTEST-MAIN"

// B: Local Variable Define
// E: Local Variable Define



// B: Local function declare
// E: Local function declare

int autotest_main(int argc, char* argv[])
{
    int ret = 0;

    EN_TESTTYE test_type = AUTOTEST_Get_Scan_Type(argv[1]);

    if (is_scan_test(test_type))
    {
        ret = autotest_scan(argc, argv, test_type);
    }
    else if (is_update_test(test_type))
    {
        ret = autotest_update(argc, argv, test_type);
    }
    else
    {
        // free run
        //ret = autotest_free_run(argc, argv, test_type);
    }


    return ret;
}



unsigned int autotest_setloglevel(char *loglevel)
{
    U32BIT level = ANDROID_LOG_DEBUG;

    if (0 == strcmp(loglevel, "ANDROID_LOG_CLOSE"))
    {
        level = ANDROID_LOG_CLOSE;
    }
    else if (0 == strcmp(loglevel, "ANDROID_LOG_FATAL"))
    {
        level = ANDROID_LOG_FATAL;
    }
    else if (0 == strcmp(loglevel, "ANDROID_LOG_ERROR"))
    {
        level = ANDROID_LOG_ERROR;
    }
    else if (0 == strcmp(loglevel, "ANDROID_LOG_WARN"))
    {
        level = ANDROID_LOG_WARN;
    }
    else if (0 == strcmp(loglevel, "ANDROID_LOG_INFO"))
    {
        level = ANDROID_LOG_INFO;
    }
    else
    {
        level = ANDROID_LOG_DEBUG;
    }

    return CERT_Common_SetLogLevel(level);
}



