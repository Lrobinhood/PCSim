
//---includes for this file----------------------------------------------------
// compiler library header files
#include <string.h>
#include <stdlib.h>

// third party header files

// Ocean Blue Software header files

#include <techtype.h>
#include <dbgfuncs.h>


#include "stbpvr.h"

#include "cert_log.h"

#define TAG "STBPVR_STUB"

U8BIT STB_PVRGetPathForRecordingIndex(U8BIT rec_index)
{
    U8BIT path = 0;

    CERT_LOG_DEBG(TAG, "[%s] return: %u ", __FUNCTION__, path);

    return(path);
}

void STB_PVRPlaybackNotifyTime(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


BOOLEAN STB_PVRIsInitialised(void)
{
    BOOLEAN ret = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] Empty Func, return:%u", __FUNCTION__, ret);

    return ret;
}

BOOLEAN STB_PVRStartRecording(U8BIT path, U32BIT handle)
{
    BOOLEAN ret = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] Empty Func, return:%u", __FUNCTION__, ret);

    return ret;
}

void STB_PVRStopRecording(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

BOOLEAN STB_PVRIsRecording(U8BIT path, U32BIT *handle)
{
    BOOLEAN ret = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] Empty Func, return:%u", __FUNCTION__, ret);

    return ret;
}

void STB_PVRStoreRecordingLen(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}

void STB_PVRSetStandbyState(BOOLEAN state)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}












