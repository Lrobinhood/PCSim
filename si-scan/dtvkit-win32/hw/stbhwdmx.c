/**
 * @brief   Set Top Box - Hardware Layer, STB Demux Functions for PC Simulator on Win32
 * @file    stbhwdmx.c
 * @date    2021-01-29
 */




#include "techtype.h"
#include "dbgfuncs.h"

#include "stbhwdmx.h"
#include "FilterForDtvkitWrapper.h"

#include "cert_log.h"

#define TAG "stbhwdmx"

/*---global function definitions---------------------------------------------*/


/**
 * @brief   Initialises the demux / programmable transport interface
 * @param   paths Number of demux paths to be initialised
 * @param   inc_pes_collection Not used
 */
void STB_DMXInitialise(U8BIT paths, BOOLEAN inc_pes_collection)
{
    Wrapper_DMXInitialise(paths, inc_pes_collection);
}

/**
 * @brief   Returns the capability flags of the given demux
 * @param   path - demux
 * @return  Capability flags
 */
U16BIT STB_DMXGetCapabilities(U8BIT path)
{
   U16BIT caps = DMX_CAPS_LIVE|DMX_CAPS_PIP|DMX_CAPS_RECORDING|DMX_CAPS_PLAYBACK|DMX_CAPS_MONITOR_SI;

   CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

   return(caps);
}

/**
 * @brief   Changes the packet IDs for the PCR Video, Audio, Text and Data
 * @param   path The demux path to be configured
 * @param   pcr_pid The PID to use for the Program Clock Reference
 * @param   video_pid The PID to use for the Video PES
 * @param   audio_pid The PID to use for the Audio PES
 * @param   text_pid The PID to use for the Teletext data
 * @param   data_pid The PID to use for the data
 */
void STB_DMXChangeDecodePIDs(U8BIT path, U16BIT pcr_pid, U16BIT video_pid, U16BIT audio_pid,
   U16BIT text_pid, U16BIT data_pid, U16BIT ad_pid)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);
}

/**
 * @brief   Changes just the teletext PID
 * @param   path The demux path to configure
 * @param   text_pid The PID to use for the teletext data
 */
void STB_DMXChangeTextPID(U8BIT path, U16BIT text_pid)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);
}

/**
 * @brief   Get a New PID Filter & Setup Associated Buffer and Callback
 *          Function Address.
 * @param   path Required Decode Path Number.
 * @param   pid Required PID to Demux.
 * @param   func_ptr User's Interrupt Procedure Function Address.
 * @return  New PID filter identifier or invalid id.
 */
U16BIT  STB_DMXGrabPIDFilter(U8BIT path, U16BIT pid, FILTER_CALLBACK func_ptr)
{
    return Wrapper_DMXGrabPIDFilter(path, pid, func_ptr);
}

/**
 * @brief   Releases a previously allocated PID filter
 * @param   path the demux path of the filter
 * @param   pfilt_id the handle of the filter
 */
void STB_DMXReleasePIDFilter(U8BIT path, U16BIT pfilt_id)
{
    Wrapper_DMXReleasePIDFilter(path, pfilt_id);
}

/**
 * @brief   Allocated a new section filter on the specified PID filter
 * @param   path the demux path to use
 * @param   pfilt_id the PID filter to assign the section filter to
 * @return  The section filter handle
 */
U16BIT STB_DMXGrabSectFilter(U8BIT path, U16BIT pfilt_id)
{
    return Wrapper_DMXGrabSectFilter(path, pfilt_id);
}

/**
 * @brief   Releases a previously allocated section filter
 * @param   path the demux path of the filter
 * @param   sfilt_id the handle of the section filter
 */
void STB_DMXReleaseSectFilter(U8BIT path, U16BIT sfilt_id)
{
    Wrapper_DMXReleaseSectFilter(path, sfilt_id);
}

/**
 * @brief   Configures a match and mask for a specified section filter
 * @param   path the demux path of the section filter
 * @param   sfilt_id the handle of the section filter
 * @param   match_ptr pointer to the match bytes
 * @param   mask_ptr pointer to the mask bytes
 * @param   not_equal_byte_index the byte position for a not equal compare
 * @param   crc TRUE to use CRC checking FALSE to ignore
 */
void STB_DMXSetupSectFilter(U8BIT path, U16BIT sfilt_id, U8BIT *match_ptr, U8BIT *mask_ptr,
   U8BIT not_equal_byte_index, BOOLEAN crc)
{
    Wrapper_DMXSetupSectFilter(path, sfilt_id, match_ptr, mask_ptr, not_equal_byte_index, crc);
}

/**
 * @brief   Start Specified PID Filter Collecting Data.
 * @param   path Required Decode Path Number.
 * @param   pfilter_id Required PID Filter Identifier.
 */
void  STB_DMXStartPIDFilter(U8BIT path, U16BIT pfilt_id)
{
    Wrapper_DMXStartPIDFilter(path, pfilt_id);
}

/**
 * @brief   Stop Specified PID Filter Collecting Data.
 * @param   path Required Decode Path Number.
 * @param   pfilter_id Required PID Filter Identifier.
 */
void  STB_DMXStopPIDFilter(U8BIT path, U16BIT pfilt_id)
{
    Wrapper_DMXStopPIDFilter(path, pfilt_id);
}

/**
 * @brief   Copies a filtered section to caller's buffer
 * @param   path the demux path to use
 * @param   buffer the caller's buffer
 * @param   size the size of the caller's buffer
 * @param   pfilt_id the handle of the PID filter to read from
 * @return  TRUE copied ok
 * @return  FALSE no data to copy
 */
BOOLEAN STB_DMXCopyPIDFilterSect(U8BIT path, U8BIT *buffer, U16BIT size, U16BIT pfilt_id)
{
    return Wrapper_DMXCopyPIDFilterSect(path, buffer, size, pfilt_id);
}

/**
 * @brief   Flushes (emDMXes) the buffer of a speficied PID filter
 * @param   path the demux path of the filter
 * @param   pfilt_id the handle of the PID filter
 */
void STB_DMXFlushPIDFilterBuffer(U8BIT path, U16BIT pfilt_id)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);
}

/**
 * @brief   Skips (discards) a section in the PID filter buffer
 * @param   path the demux path of the filter
 * @param   pfilt_id the PID filter handle
 */
void STB_DMXSkipPIDFilterSect(U8BIT path, U16BIT pfilt_id)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);
}

/**
 * @brief   Returns the maximum number of section filters available on this hw
 * @return  The number of filters
 */
U8BIT STB_DMXGetMaxSectionFilters(void)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return 96;
}



/**
 * @brief   Configures the source of the demux
 * @param   path the demux path to configure
 * @param   source the source to use
 * @param   param source specific parameters (e.g. tuner number)
 */
void STB_DMXSetDemuxSource(U8BIT path, E_STB_DMX_DEMUX_SOURCE source, U8BIT param)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

}

/**
 * @brief   Gets the current source of a given demux
 * @param   path the demux path to query
 * @param   source the source of the demux
 * @param   param the source specific parameter (e.g. tuner number)
 */
void STB_DMXGetDemuxSource(U8BIT path, E_STB_DMX_DEMUX_SOURCE *source, U8BIT *param)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

}


/**
 * @brief   change the source of the demux when cam card plug or unplug
 *          we need check "is_set_tssource" is 0 or not,if it value is 0,
 *          we do nothing now.
 * @param   slot  cam card slot
 * @param   plug 0:cam card unplug, 1：camc card plug
 */
void STB_DMXChangeAllDemuxSource(U8BIT slot, U8BIT plug)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);
}

/**
 * @brief   set the tsout source when ts route is "tsin->tsout->tsin"
 * get ts out source from cfg
 */


/**
 * @brief   Reads Teletext PES data from the demux
 * @param   path the demux path to read
 * @param   buffer pointer to PES data
 * @param   num_bytes the number of bytes of data
 */
void STB_DMXReadTextPES(U8BIT path, U8BIT **buffer, U32BIT *num_bytes)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

}

/**
 * @brief   Writes data to the demux from memory
 * @param   path the demux path to be written
 * @param   data the data to be written
 * @param   size the number of bytes to be written
 */
void STB_DMXWriteDemux(U8BIT path, U8BIT *data, U32BIT size)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

}

/**
 * @brief   Acquires a descrambler for the specified track on this path
 * @param   path the demux path for which the descrambler is acquired
 * @param   track enum representing audio, video or subtitles PES
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXGetDescramblerKey(U8BIT path, E_STB_DMX_DESC_TRACK track)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}

/**
 * @brief   Frees the descrambler for the specified track on this path
 * @param   path the demux path for which the descrambler is freed
 * @param   track enum representing audio, video or subtitles PES
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXFreeDescramblerKey(U8BIT path, E_STB_DMX_DESC_TRACK track)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}


/**
 * @brief   Set the descrambler key data for the specified track on this path
 * @param   path the demux path for which the descrambler key data is set
 * @param   track enum representing audio, video or subtitles PES
 * @param   parity even or odd
 * @param   data pointer to the key data, its length depends on the descrambler
 *          type (see STB_DMXSetDescramblerType)
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXSetDescramblerKeyData(U8BIT path, E_STB_DMX_DESC_TRACK track,
   E_STB_DMX_DESC_KEY_PARITY parity, U8BIT *data)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}


/**
 * @brief   Get the descrambler key usage for the specified track on this path as set by
 *          STB_DMXSetKeyUsage
 * @param   path the demux path that the descrambler key usage refers to
 * @param   track enum representing audio, video or subtitles PES
 * @param   key_usage whether the descrambler has been set to operate at PES level, transport
 *          level or all.
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXGetKeyUsage(U8BIT path, E_STB_DMX_DESC_TRACK track, E_STB_DMX_KEY_USAGE *key_usage)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}


/**
 * @brief   Set the descrambler key usage for the specified track on this path
 * @param   path the demux path that the descrambler key usage refers to
 * @param   track enum representing audio, video or subtitles PES
 * @param   key_usage whether the descrambler operates at PES level, transport
 *          level or all.
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXSetKeyUsage(U8BIT path, E_STB_DMX_DESC_TRACK track, E_STB_DMX_KEY_USAGE key_usage)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}


/**
 * @brief   Get the descrambler type for the specified track on this path, as set by
 *          STB_DMXSetDescramblerType
 * @param   path the demux path that the descrambler type refers to
 * @param   type descrambler type (DES, AES, etc...)
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXGetDescramblerType(U8BIT path, E_STB_DMX_DESC_TRACK track, E_STB_DMX_DESC_TYPE *type)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}


/**
 * @brief   Set the descrambler type for the specified track on this path
 * @param   path the demux path that the descrambler type refers to
 * @param   type descrambler type (DES, AES, etc...)
 * @return  TRUE on success, FALSE otherwise
 */
BOOLEAN STB_DMXSetDescramblerType(U8BIT path, E_STB_DMX_DESC_TRACK track, E_STB_DMX_DESC_TYPE type)
{
    CERT_LOG_WARN(TAG, "[%s] not implemented yet", __FUNCTION__);

    return TRUE;
}




