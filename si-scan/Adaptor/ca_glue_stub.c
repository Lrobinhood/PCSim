//#define CA_DEBUG

/*---Includes for this file---------------------------------------------------*/
/* compiler library header files */
#include <unistd.h>

/* Third party header files */

/* Ocean Blue Software header files */
#include <techtype.h>
#include <dbgfuncs.h>
#include <stbhwc.h>
#include "stbhwos.h"
#include "stbheap.h"

#include "ca_glue.h"


#include "cert_log.h"

#define TAG "CA_GLUE_STUB"

void STB_CAReportPMT(U32BIT handle, U8BIT *pmt_data, U16BIT data_len)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CAReportCAT(U8BIT path, U8BIT *cat_data, U16BIT data_len)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CAReportBAT(U32BIT handle, U8BIT *bat_data, U16BIT data_len)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CAReportNIT(U32BIT handle, U8BIT *nit_data, U16BIT data_len)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_CADescramblerRequiredForPlayback(U16BIT *ca_ids, U16BIT num_ca_ids)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_CANotifyRunningStatus(U32BIT handle, U8BIT status)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_CAReleaseDescrambler(U32BIT handle)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN STB_CAAcquireDescrambler(U8BIT path, U16BIT serv_id, U16BIT *ca_ids, U16BIT num_ca_ids,
   U32BIT *handle)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_CADescrambleServiceStart(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CADescrambleServiceStop(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CADecodeVideoStatus(U32BIT handle, E_CA_DECODE_STATUS decode_status)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CADecodeAudioStatus(U32BIT handle, E_CA_DECODE_STATUS decode_status)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CADecodeADStatus(U32BIT handle, E_CA_DECODE_STATUS decode_status)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_CADescramblerRequiredForRecording(U16BIT *ca_ids, U16BIT num_ca_ids)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_CiKeysClear(U8BIT path, U8BIT slot_id)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_CiHandlePinEvent(U8BIT slot_id, U8BIT rating, BOOLEAN is_fta_program)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN STB_CiCcIsSlotReady(U8BIT slot_id)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN STB_CiCaSystemSupported(U8BIT slot_id, U8BIT* pmt_data)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

typedef enum
{
    DRM_NONE,
    DRM_SECURE_INPUT_BUFFER,
    DRM_NORMAL_INPUT_BUFFER
} E_STB_DRM_TYPE;
void STB_AVSetDrmMode(U8BIT path, E_STB_DRM_TYPE mode)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void MDCI_SHUN_SDTTableProcess(U8BIT path, void *pSDTData)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN MDCI_OP_IsInOpEnv(void)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN APVR_IsTimeshiftRecordingInProgress(void)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

U8BIT ACI_FindCISlotForService(void *serv_ptr)
{
    U8BIT retval = 0;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}


E_CAS_TYPE STB_CAGetCASType()
{
    return CAS_TYPE_NONE;
}

/******************************************************************************
** End of file
******************************************************************************/
