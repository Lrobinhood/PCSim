/*******************************************************************************
 * Copyright (c) 2018 The DTVKit Open Software Foundation Ltd (www.dtvkit.org)
 *
 * This file is part of a DTVKit Software Component
 * You are permitted to copy, modify or distribute this file subject to the terms
 * of the DTVKit 1.0 Licence which can be found in licence.txt or at www.dtvkit.org
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * If you or your organisation is not a member of DTVKit then you have access
 * to this source code outside of the terms of the licence agreement
 * and you are expected to delete this and any associated files immediately.
 * Further information on DTVKit, membership and terms can be found at www.dtvkit.org
 *******************************************************************************/
/**
 * @brief   Set Top Box - Hardware Layer, AV Control and decoding
 * @file    stbhwav.c
 * @date    October 2018
 */

/*---includes for this file--------------------------------------------------*/
/* compiler library header files */
#include <stdio.h>
#include <string.h>

/* third party header files */


/* STB header files */
#include "techtype.h"

#include "stbhwdef.h"
//#define DEBUG_FUNCTIONS
#include "dbgfuncs.h"
#include "stbhwos.h"
#include "stbhwmem.h"
#include "stbhwav.h"
//#include "stbhwosd.h"
#include "stbpvrpr.h"
//#include "internal.h"
#include "stbhwdef.h"


#include "cert_log.h"

#define TAG "STBHWAV_STUB"

/*---macro definitions for this file-----------------------------------------*/


/*---constant definitions for this file--------------------------------------*/

/*---local typedef structs for this file-------------------------------------*/


/*---local function prototypes for this file---------------------------------*/



/*---global function definitions----------------------------------------------*/

/**
 * @brief   Initialises the AV components
 * @param   audio_paths The number of audio paths
 * @param   video_paths The number of video paths
 */
void STB_AVInitialise(U8BIT audio_paths, U8BIT video_paths)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the aspect ratio of the connected television
 * @param   path The video path to be set
 * @param   ratio The aspect ratio of the tv
 * @param   format The signal format of the tv
 */
void STB_AVSetTVType(U8BIT path, E_STB_AV_ASPECT_RATIO ratio, E_STB_AV_VIDEO_FORMAT format)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Set the aspect ratio setting of the tv
 * @param   path the video path
 * @param   ratio The requested aspect ratio setting of the tv
 * @return  Valid aspect ratio setting, only different from the parameter if that was invalid
 */
E_STB_AV_ASPECT_RATIO STB_TVSetAspectRatio(E_STB_AV_ASPECT_RATIO ratio)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return ASPECT_RATIO_16_9;;
}



/**
 * @brief   Register callback for updated video information
 * @param   path video decoder path
 * @param   callback - the callback to call when video information is updated
 * @param   vtc_user_data - user data to pass to the callback
 */
void STB_AVSetVideoCallback(U8BIT path, void (*callback)(S_STB_AV_VIDEO_INFO *, void *), void *user_data)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Apply video transformation
 * @param   input - input video rectangle
 * @param   output - output video rectangle
 */
void STB_AVApplyVideoTransformation(U8BIT path, S_RECTANGLE* src, S_RECTANGLE* dest)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Blanks or unblanks the video display
 * @param   path the video path to be configured
 * @param   blank TRUE to blank, FALSE to unblank
 */
void STB_AVBlankVideo(U8BIT path, BOOLEAN blank)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Routes a specified AV source to a specified AV output
 * @param   output The output to be connected
 * @param   source The source signal to be connected
 * @param   param parameter associated with the source
 */
void STB_AVSetAVOutputSource(E_STB_AV_OUTPUTS output, E_STB_AV_SOURCES source, U32BIT param)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Turns on/off all AV outputs (e.g. for standby mode)
 */
void STB_AVSetAVOutput(BOOLEAN av_on)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the output channel of the RF Modulator
 * @param   chan the UHF channel number
 */
void STB_AVSetUhfModulatorChannel(U8BIT chan)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Gets the current RF modulator channel
 * @return  The RF frequency as a UHF channel number
 */
U8BIT STB_AVGetUhfModulatorChannel(void)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return 0;
}

/**
 * @brief   Sets the volume of the audio output
 * @param   path the audio path to be configured
 * @param   vol the audio volume (0-100%)(the value of vol is from 0 to 100)
 */
void STB_AVSetAudioVolume(U8BIT path, U8BIT vol)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Gets the current volume of the audio output
 * @param   path The audio path to query
 * @return  audio volume (0-100%)
 */
U8BIT STB_AVGetAudioVolume(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return 5;
}

/**
 * @brief   Mutes or unmutes the audio output
 * @param   path The audio path to be configured
 * @param   mute TRUE to mute, FALSE to unmute
 */
void STB_AVSetAudioMute(U8BIT path, BOOLEAN mute)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Gets the current muting status of the audio output
 * @param   path the audio path to be queried
 * @return  TRUE audio is muted, FALSE otherwise
 */
BOOLEAN STB_AVGetAudioMute(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return FALSE;
}


/**
 * @brief   Configures the audio channel mode (stereo/left/right)
 * @param   path the audio path to be configured
 * @param   mode the audio mode to use
 */
void STB_AVChangeAudioMode(U8BIT path, E_STB_AV_AUDIO_MODE mode)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Starts the Audio decoder
 * @param   path the audio decoder path to be started
 */
void STB_AVStartAudioDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}



/**
 * @brief   Starts the video decoder
 * @param   path the video decode path to be started
 */
void STB_AVStartVideoDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Pause video decoding
 * @param   path Required Decode Path Number.
 */
void  STB_AVPauseVideoDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Resume video decoding
 * @param   path Required Decode Path Number.
 */
void  STB_AVResumeVideoDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Stops the video decoder
 * @param   path the video decoder path to be stopped
 */
void STB_AVStopVideoDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Stops the audio decoder
 * @param   path the audio decoder path to be stopped
 */
void STB_AVStopAudioDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the current 33-bit System Time Clock from the PCR PES.
 *          On some systems, this information may need to be obtained from the associated demux,
 *          which will be contained in the 'param' value when STB_AVSetVideoSource is called.
 * @param   path video path
 * @param   stc an array in which the STC will be returned, ordered such that
 *                stc[0] contains the MS bit (33) of the STC value and stc[4]
 *                contains the LS bits (0-7).
 */
void STB_AVGetSTC(U8BIT path, U8BIT stc[5])
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the source of the video decoder
 * @param   path video path to configure
 * @param   source the source device to use
 * @param   param tuner or demux number
 */
void STB_AVSetVideoSource(U8BIT path, E_STB_AV_DECODE_SOURCE source, U32BIT param)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the source of the audio decoder
 * @param   path audio path to configure
 * @param   source the source device to use
 * @param   param tuner or demux number
 */
void STB_AVSetAudioSource(U8BIT path, E_STB_AV_DECODE_SOURCE source, U32BIT param)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}



/**
 * @brief   Sets the video surface  with the given video decoder path
 * @param   path video path
 * @param   video surface point
 * @return  TRUE if the codec is supported and is set correctly, FALSE otherwise
 */
BOOLEAN STB_AVSetSurface(U8BIT path, void *surface)
{
    BOOLEAN success = TRUE;
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return success;
}

/**
 * @brief   Gets the video surface  with the given video decoder path
 * @param   path video path
 * @return  surface poniter
 */
void * STB_AVGetSurface(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}



/**
 * @brief   Sets the video codec to be used when decoding video with the given video decoder path
 * @param   path video path
 * @param   codec codec to be used
 * @return  TRUE if the codec is supported and is set correctly, FALSE otherwise
 */
BOOLEAN STB_AVSetVideoCodec(U8BIT path, E_STB_AV_VIDEO_CODEC codec)
{
    BOOLEAN success = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return success;
}

/**
 * @brief   Sets the audio codec to be used when decoding audio with the given audio decoder path
 * @param   path audio path
 * @param   codec codec to be used
 * @return  TRUE if the codec is supported and is set correctly, FALSE otherwise
 */
BOOLEAN STB_AVSetAudioCodec(U8BIT path, E_STB_AV_AUDIO_CODEC codec)
{
    BOOLEAN success = TRUE;

    FUNCTION_START(STB_AVSetAudioCodec);

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return success;
}

/**
 * @brief   Loads an audio sample for subsequent playback
 * @param   path the decoder path to use for playback
 * @param   data the audio sample data to be loaded
 * @param   size the size of the audio sample in bytes
 * @return  E_HW_STATUS code
 */
E_HW_STATUS STB_AVLoadAudioSample(U8BIT path, U8BIT *data, U32BIT size)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return HW_OK;
}

/**
 * @brief   Plays back a previously loaded audio sample
 * @param   path the audio path to use for playback
 * @param   loop_count the number of times to play the sample, 0=forever
 * @return  E_HW_STATUS code
 */
E_HW_STATUS STB_AVPlayAudioSample(U8BIT path, U32BIT loop_count)
{
    E_HW_STATUS success = HW_GEN_ERROR;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return success;
}

/**
 * @brief   Pauses playback of an audio sample
 * @param   path Audio path on which to pause
 * @return  E_HW_STATUS code
 */
E_HW_STATUS STB_AVPauseAudioSample(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }


   return HW_GEN_ERROR;
}

/**
 * @brief   Resumes playback of an audio sample
 * @param   path Audio path on which to resume
 * @return  E_HW_STATUS code
 */
E_HW_STATUS STB_AVResumeAudioSample(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }


   return HW_GEN_ERROR;
}

/**
 * @brief   Stops playback of an audio sample
 * @param   path Audio path on which to stop
 */
void STB_AVStopAudioSample(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the codec to be used when decoding the next i-frame from memory
 * @param   path video path
 * @param   codec codec to be used
 * @return  TRUE if the codec is supported and is set correctly, FALSE otherwise
 */
BOOLEAN STB_AVSetIFrameCodec(U8BIT path, E_STB_AV_VIDEO_CODEC codec)
{
    BOOLEAN supported = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }
    
    return(supported);
}

/**
 * @brief   Loads a video I Frame for subsequent decode and display
 * @param   path the video decode path to be used
 * @param   data the I frame data to be loaded
 * @param   size the size of the data in bytes
 */
void STB_AVLoadIFrame(U8BIT path, U8BIT *data, U32BIT size)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Decode and display previously loaded I frame data
 * @param   path the video path to use
 */
void STB_AVShowIFrame(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Hides a previously shown I frame
 * @param   path the video path containing the I frame
 */
void STB_AVHideIFrame(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns minimum video play speed as a percentage.
 * @param   video_decoder video decoder path
 * @return  Minimum play speed.
 */
S16BIT STB_AVGetMinPlaySpeed(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return 10;
}

/**
 * @brief   Returns maximum video play speed as a percentage.
 * @param   video_decoder video decoder path
 * @return  Maximum play speed.
 */
S16BIT STB_AVGetMaxPlaySpeed(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return 10;
}

/**
 * @brief   Returns the next valid speed that is +/- inc above or below the
 *          given speed. Slow motion speeds (>-100% and < 100%) can be included.
 * @param   path Decode path
 * @param   speed Percentage speed above/below which the new speed is calculated
 * @param   inc number of speeds above that specified to return
 * @param   include_slow_speeds selects whether speeds >-100% and <100% are included
 * @return  Speed as a percentage
 */
S16BIT STB_AVGetNextPlaySpeed(U8BIT path, S16BIT speed, S16BIT inc, BOOLEAN include_slow_speeds)
{
    S16BIT new_speed = 10;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(new_speed);
}

/**
 * @brief     Sets the source of the audio decoder
 * @param     path - audio path to configure
 * @param     source - the source device to use
 * @param     param - tuner or demux number
 */
void STB_AVSetADSource(U8BIT path, E_STB_AV_DECODE_SOURCE source, U32BIT param)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Configures the audio description channel mode (stereo/left/right) in the case where
 *          dual-mono audio is used, such that only the audio from one channel is heard.
 * @param   path audio path to be configured
 * @param   mode audio mode to use
 */
void STB_AVChangeADMode(U8BIT path, E_STB_AV_AUDIO_MODE mode)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Starts decoding audio description on the given audio path
 * @param   path audio decoder path to be started
 */
BOOLEAN STB_AVStartADDecoding(U8BIT path)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}

/**
 * @brief   Stops decoding audio description on the given audio path.
 * @param   path audio decoder path to be stopped
 */
void STB_AVStopADDecoding(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the codec to be used for audio description when decoding audio
 *          with the given audio decoder path
 * @param   path audio path
 * @param   codec codec to be used
 * @return  TRUE if the codec is supported and is set correctly, FALSE otherwise
 */
BOOLEAN STB_AVSetADCodec(U8BIT path, E_STB_AV_AUDIO_CODEC codec)
{
    BOOLEAN success = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(success);
}

/**
 * @brief   Sets the volume of the audio description output
 * @param   path audio path to be configured
 * @param   vol audio volume (0-100%)
 */
void STB_AVSetADVolume(U8BIT path, U8BIT vol)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the standby state of the HDMI output
 * @param   standby TRUE to put the HDMI in standby, FALSE to come out of standby
 */
void STB_AVSetHDMIStandby(BOOLEAN standby)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the resolutions supported by the HDMI
 * @param   modes array of supported modes
 * @return  number of supported modes
 */
U8BIT STB_AVGetHDMISupportedModes(E_STB_AV_VIDEO_FORMAT **modes)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return (10);
}


/**
 * @brief   Enables AV output to HDMI
 */
void STB_AVEnableHDMIDecoding(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Disables AV output to HDMI
 */
void STB_AVDisableHDMIDecoding(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns whether HDCP has authenticated
 * @return  TRUE if authenticated, FALSE otherwise
 */
BOOLEAN STB_AVIsHDCPAuthenticated(void)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return (TRUE);
}

/**
 * @brief   Sets the audio delay on the given path
 * @param   path decoder path
 * @param   millisecond audio delay to be applied
 */
void STB_AVSetAudioDelay(U8BIT path, U16BIT millisecond)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}



/**
 * @brief   Sets the SPDIF output mode, PCM or compressed audio
 * @param   path decoder path
 * @param   audio_type PCM or compressed
 */
void STB_AVSetSpdifMode(U8BIT path, E_STB_DIGITAL_AUDIO_TYPE audio_type)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the current size of the screen in pixels
 * @param   path output path
 * @param   width returned width
 * @param   height returned height
 */
void STB_AVGetScreenSize(U8BIT path, U16BIT *width, U16BIT *height)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the HDMI audio output mode, PCM or compressed
 * @param   path decoder path
 * @param   audio_type PCM or compressed
 */
void STB_AVSetHDMIAudioMode(U8BIT path, E_STB_DIGITAL_AUDIO_TYPE audio_type)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the native resolution, i.e. the resolution that is
 *          set with a call to STB_AVSetTVType(path, ratio, VIDEO_FORMAT_AUTO);
 * @param   width pointer to the variable where to store the width
 * @param   height pointer to the variable where to store the height
 */
void STB_AVGetHDMINativeResolution(U16BIT *width, U16BIT *height)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Apply System Renewability Message (SRM) to HDCP function
 * @param   path output path
 * @param   data SRM data
 * @param   len length of SRM data in bytes
 * @return  SRM_OK, SRM_BUSY or SRM_NOT_REQUIRED
 */
E_STB_AV_SRM_REPLY STB_AVApplySRM(U8BIT path, U8BIT *data, U32BIT len)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return SRM_NOT_REQUIRED;
}

/**
 * @brief   Returns the frame rate of the video being decoded
 * @param   path video path
 * @return  video frame rate in frame per seconds
 */
U8BIT STB_AVGetVideoFrameRate(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return 0;
}



/**
 * @brief Apply the specified copy protection. This function is used for CI+
 * @param copy_protection  - settings to be used for each output
 */
void STB_AVSetCopyProtection(S_STB_AV_COPY_PROTECTION *copy_protection)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}

/**
 * @brief   Sync decoding info from pvr
 * @param   path the audio decoder path to be started
 */
void STB_AVSyncDecodingFromPVR(U8BIT audio_decoder, U8BIT video_decoder)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


void STB_AVNotifyEventHandler(U8BIT audio_path, U8BIT video_path, void *event)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the decoding mode
 * @param   path decoder path
 * @param   decoding mode
 */
void STB_AVSetDecodingMode(U8BIT audio_decoder, U8BIT video_decoder, E_STB_DECODING_MODE mode)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}

BOOLEAN STB_AVAcquirePath(U8BIT video_decoder, U8BIT audio_decoder)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return TRUE;
}

BOOLEAN STB_AVReleasePath(U8BIT video_decoder, U8BIT audio_decoder)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return TRUE;
}

void STB_AVSetADMixLevel(U8BIT path, U8BIT vol)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}






