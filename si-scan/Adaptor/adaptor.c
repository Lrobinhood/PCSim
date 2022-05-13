#include <stdlib.h>
#include <stdio.h>

#include "techtype.h"

#include "stbhwini.h"
#include "stbdpc.h"
#include "stbvtc.h"
#include "stbhwcfg.h"
#include "stbgc.h"

#include "cert_log.h"

#define TAG "ADAPTER"


BOOLEAN APVR_IsStopped(U8BIT path)
{
    BOOLEAN retval = TRUE;

    //CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}


BOOLEAN ACA_AcquireCADescrambler(U8BIT path, void *s_ptr)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}


BOOLEAN STB_IMGConvertPNG(U8BIT *image_data, U32BIT image_data_size, U8BIT **output_data,
    U32BIT *output_data_size, U16BIT *pixel_width, U16BIT *pixel_height)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN STB_IMGConvertJPEG(U8BIT *image_data, U32BIT image_data_size, U8BIT **output_data,
    U32BIT *output_data_size, U16BIT *pixel_width, U16BIT *pixel_height)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}



void *APVR_GetPlaybackService(U8BIT path)
{
    void *srv_ptr = NULL;

    CERT_LOG_DEBG(TAG, "[%s] return: %p ", __FUNCTION__, srv_ptr);

    return(srv_ptr);
}

BOOLEAN APVR_IsRecordingInProgress(void)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void APVR_PausePlay(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


BOOLEAN APVR_StopRecording(U32BIT handle)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN APVR_GetRecordingHandle(U8BIT path, U32BIT *recording_handle_ptr)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_VTSetVideoAlignmentPref(U8BIT path, E_VIDEO_ASPECT_MODE alignment)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


U32BIT AM_FileEcho(const char *name, const char *cmd)
{
    U32BIT retval = 0;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return retval;
}

BOOLEAN AML_DMX_FileEcho(const char *name, const char *cmd)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_VTSetVideoAfd(U8BIT path, U8BIT afd)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}




void STB_VTSetVideoOutput(U8BIT path, S_RECTANGLE *output)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


BOOLEAN STB_HWSetStandbyState(E_HW_STANDBY_STATE state)
{
    BOOLEAN retval = FALSE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_HWSetWakeUpTime(U16BIT mjd, U16BIT year, U8BIT month, U8BIT day, U8BIT hours,
   U8BIT minutes, U32BIT time_in_mins)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBEnable(U8BIT path, BOOLEAN enable)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBStart(U8BIT path, U16BIT pid, U16BIT composition_id, U16BIT ancillary_id)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBStop(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBSetStream(U8BIT path, U16BIT pid, U16BIT composition_id, U16BIT ancillary_id)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBStatus(BOOLEAN *started, BOOLEAN *shown)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


void STB_SUBReadSettings(BOOLEAN *running, U16BIT *pid, U16BIT *comp_id, U16BIT *anc_id, BOOLEAN *enabled)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

U16BIT STB_PVRRecordingGetDiskId(U32BIT handle)
{
    return 0;
}

BOOLEAN APVR_StopRecordingByPath(U8BIT path)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void APVR_EitUpdated(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void APVR_ChangeRecordingDesMode(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void APVR_PidsUpdated(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN APVR_HandlePrivateTimer(U32BIT timer_handle)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void STB_PVRUpdateRecordings(BOOLEAN force_load)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

#if 0
BOOLEAN ADB_GetServiceVirtualFlag(void *s_ptr)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}
#endif

void STB_EnterCICamChannel(U32BIT module)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

U32BIT STB_GetDefaultAiModule()
{
    U32BIT retval = 0;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return (retval);
}

void ACI_TuneReply(U8BIT path, U32BIT module, U32BIT status)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN ACI_FindOperatorProfileModule(U32BIT cicam_id, U32BIT *module)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN STB_CISendOperatorExit(U32BIT module)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

BOOLEAN ACI_OperatorExit(void)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}

void * DBDEF_FindVirtualServiceRecByCamId(U32BIT camid)
{
    void *retval = NULL;

    CERT_LOG_DEBG(TAG, "[%s] return: 0x%p ", __FUNCTION__, retval);

    return(retval);
}

int STB_Cam_Is_CIPlus_Mode()
{
    int retval = 0;

    CERT_LOG_DEBG(TAG, "[%s] return: %d ", __FUNCTION__, retval);

    return (retval);
}

void STB_AVSetVideoColor(U8BIT path, BOOLEAN blank, BOOLEAN is_black_color)
{
     CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_CADescrambleIoctl(U32BIT handle, const char* inJson, char* outJson, U32BIT outLen)
{
     CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_GetDemoCapabilityByType(E_STB_TUNE_SIGNAL_TYPE eType, U_STB_DEMO_CAPABILITY* pCap)
{
    BOOLEAN retval = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, retval);

    return(retval);
}


E_TUNER_EVENT STB_TuneGetLockStatus(U8BIT path)
{
    E_TUNER_EVENT tuner_event = TUNER_STATE_UNKNOW;

    CERT_LOG_DEBG(TAG, "[%s] tuner_event: %u ", __FUNCTION__, tuner_event);

    return tuner_event;
}


E_STB_TUNE_MODULATION STB_TuneGetModulation(U8BIT path)
{
    E_STB_TUNE_MODULATION mod = TUNE_MOD_AUTO;

    CERT_LOG_DEBG(TAG, "[%s] mod: %u ", __FUNCTION__, mod);

    return mod;
}

int settimeofday ( const struct timeval *tv,const struct timezone *tz)
{
    return 0;
}

void STB_CADescrambleSessionIoctl(U32BIT session, const char* inJson, char* outJson, U32BIT outLen)
{
    CERT_LOG_DEBG(TAG, "[%s] dummy ", __FUNCTION__);
}

void APVR_NormalPlay(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] dummy ", __FUNCTION__);
}
