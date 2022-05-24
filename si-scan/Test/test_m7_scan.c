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



#include "cert_log.h"
#include "cert_scan_common.h"

#include "cert_apctrl.h"
#include "cert_apctrl_scan_common.h"
#include "cert_apctrl_m7_scan_common.h"
#include "cert_apctrl_m7_scan.h"


#include "test_m7_scan.h"

#define TAG "TEST-M7-SCAN"



void Test_CERT_M7_Scan_Start()
{
    cert_apctrl_scan_Init();
    CERT_APCTRL_SCAN_M7_ScanStart(EN_M7_SCAN_FTI, FALSE);
}

void Test_CERT_M7_Scan_Stop()
{
    CERT_APCTRL_SCAN_M7_ScanStop(0);
}

void Test_CERT_M7_SCAN_ACTION()
{
    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_SELF_MSG, EN_M7_SCAN_SELF_EVENT_SEARCHCOMPLETED, NULL, NULL);

    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_DISEQC_CONFIRM, NULL, NULL);

    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_STACK_MSG, EN_M7_SCAN_STACK_EVENT_SEARCHSUCCESS, NULL, NULL);

    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_STACK_MSG, EN_M7_SCAN_STACK_EVENT_SEARCHSUCCESS, NULL, NULL);

    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_UI_MSG, EN_M7_SCAN_UI_EVENT_OPERLIST_CONFIRM, NULL, NULL);

    cert_apctrl_scan_SendMsg(0, EN_M7_SCAN_STACK_MSG, EN_M7_SCAN_STACK_EVENT_SEARCHSUCCESS, NULL, NULL);
}

