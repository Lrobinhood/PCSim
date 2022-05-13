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


#include "autotest_cfg.h"
#include "autotest_init.h"

#define TAG "AUTOTEST-MAIN"




// B: Type define


// E: Type Define

// B: Local Variable Define

// E: Local Variable Define

// B: Local function declare

// E: Local function declare


void AUTOTEST_Init_DVB(DVB_EVENT_HANDLE_FUNC dvb_event_handle_func)
{
    static U8BIT init_dvb_flag = 0;

    if (0 == init_dvb_flag)
    {
        STB_ERInitialise();

        AEV_Initialise(dvb_event_handle_func);

        // APP_InitialiseDVB -->  STB_Initialise --> STB_DPInitialise
        STB_RESInitialise();
        STB_DPInitialise();

        ADB_Initialise();
        ASI_InitialiseAppSi();
        ACTL_InitialiseAppControl();
    }
}


void AUTOTEST_Init_Filter_Wrapper()
{
    static U8BIT init_flag = 0;

    if (0 == init_flag)
    {
        STB_SITerrInitialise();

        Wrapper_DMXInitialise(0, 1);

    }
}




