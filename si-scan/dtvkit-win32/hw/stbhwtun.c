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
 * @brief   Set Top Box - Hardware Layer, Tuning/Front-End functions
 * @file    stbhwtun.c
 * @date    October 2018
 */



/*---includes for this file--------------------------------------------------*/
/* compiler library header files */
#include <stdio.h>
#include <string.h>
//#include <errno.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/ioctl.h>
//#include <sys/poll.h>
//#include <fcntl.h>
//#include <unistd.h>

//#include "frontend.h"
/* STB header files */
#include "techtype.h"
#include "dbgfuncs.h"

#include "stbhwdef.h"
#include "stbhwtun.h"
#include "stbhwmem.h"
#include "stbhwos.h"
#include "stberc.h"

#include "stbdpc.h"

#include "autotest_cfg.h"


#include "cert_log.h"

#define TAG "STBHWTUN_STUB"

// B: Local Variable Define
E_STB_TUNE_SIGNAL_TYPE sg_tuner_sig_type = TUNE_SIGNAL_NONE;
E_STB_TUNE_SYSTEM_TYPE sg_tuner_system_type = TUNE_SYSTEM_TYPE_UNKNOWN;

U8BIT sg_sig_strength   = 50;
U8BIT sg_sig_quality    = 50;


// E: Local Variable Define

/*---global function definitions---------------------------------------------*/

/**
 * @brief   Initialises the tuner component
 * @param   paths number of tuning paths to initialise
 */
void STB_TuneInitialise(U8BIT paths)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Enables or disabled auto tuner relocking
 * @param   path the tuner path to configure
 * @param   state TRUE enables relocking, FALSE disables it
 */
void STB_TuneAutoRelock(U8BIT path, BOOLEAN state)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Gets the signal types of the given tuner path.
 *          This will be a bitmask of supported types defined by E_STB_TUNE_SIGNAL_TYPE
 * @param   path tuner path
 * @return  the signal types supported by the given tuner
 */
U16BIT STB_TuneGetSignalType(U8BIT path)
{
    U16BIT sig_type =  TUNE_SIGNAL_QPSK | TUNE_SIGNAL_COFDM | TUNE_SIGNAL_QAM | TUNE_SIGNAL_ISDBT;

    CERT_LOG_DEBG(TAG, "[%s] path:%u, sig type:%u", __FUNCTION__, path, sig_type);

    return sig_type;
}

/**
 * @brief   This function is only relevant for tuners that support more than one signal type;
 *          for tuners that don't support more than one signal type it can be a blank function.
 *          It will be called to inform the platform which of the supported signal types is being
 *          used.
 * @param   path tuner path
 * @param   type signal type that is being used for this tuner
 */
void STB_TuneSetSignalType(U8BIT path, E_STB_TUNE_SIGNAL_TYPE type)
{
    CERT_LOG_DEBG(TAG, "[%s] path:%u old type:%u new_type:%u", __FUNCTION__, path, sg_tuner_sig_type, type);

    sg_tuner_sig_type = type;
}

static BOOLEAN locked = FALSE;
void AutoTest_STBHWTUN_ResetTunerStartTuner()
{
    locked = FALSE;
}

/**
 * @brief   Starts the tuner, it will then attempt to lock specified signal
 * @param   path the tuner path to start
 * @param   freq the frequency to tune to
 * @param   srate the symbol rate to lock
 * @param   fec The forward error correction rate
 * @param   freq_off The frequency offset to use
 * @param   tmode The COFDM mode
 * @param   tbwidth The signal bandwidth
 * @param   cmode The QAM mode
 * @param   anlg_vtype The type of video for analogue tuner
 * @note     unrequired parameters can be passed as 0 (zero)
 */

static stb_tuneStartTunerDvbs(U8BIT path, U32BIT freq, U32BIT freqoffset, U32BIT lofreq, U32BIT pol)
{
    U32BIT idx = AUTOTEST_GetMatchModulatorIndex_Dvbs(freq, freqoffset, lofreq, pol);

    if (INVALID_MODULATOR_INDEX != idx)
    {
        AUTOTEST_UpdateCurMod(idx);

        sg_sig_strength = AUTOTEST_Get_CurCfg_SigStrength();
        sg_sig_quality  = AUTOTEST_Get_CurCfg_SigQuality();

        CERT_LOG_DEBG(TAG, "[%s] [ch %d] [freq:%d] locked", __FUNCTION__, (idx + 1), freq);
        STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_LOCKED, &path, sizeof(U8BIT));
    }
    else
    {
        CERT_LOG_DEBG(TAG, "[%s] [freq:%d] unlocked", __FUNCTION__, freq);
        STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_NOTLOCKED, &path, sizeof(U8BIT));
    }
}

void STB_TuneStartTuner(U8BIT path, U32BIT freq, U32BIT srate, E_STB_TUNE_FEC fec,
   S8BIT freq_off, E_STB_TUNE_TMODE tmode, E_STB_TUNE_TBWIDTH tbwidth,
   E_STB_TUNE_CMODE cmode, E_STB_TUNE_ANALOG_VIDEO_TYPE anlg_vtype)
{
    // !!! Later, which event to send will by test cfg file !!!
    U32BIT offset = TUNE_SIGNAL_QPSK == sg_tuner_sig_type ? 2 : 5000;

    if (TUNE_SIGNAL_QPSK == sg_tuner_sig_type && AUTOTEST_isGoMulMod())
    {
        stb_tuneStartTunerDvbs(path, freq/1000, offset, 0, STB_DPGetPolarity(path));
        return;
    }

    if (AUTOTEST_Is_CH_Cfg_Valid() && !AUTOTEST_Is_AllTunerLocked())
    {
        if (locked)
        {
            if (AUTOTEST_Get_NetScan())
            {
                U32BIT netscan_freq = freq;

                if (TUNE_SYSTEM_TYPE_DVBS == sg_tuner_system_type ||
                    TUNE_SYSTEM_TYPE_DVBS2 == sg_tuner_system_type)
                {
                    netscan_freq = freq / 1000;
                }

                if (AUTOTEST_Update_Netscan_Cfg(sg_tuner_system_type, sg_tuner_sig_type, netscan_freq, STB_DPGetPolarity(path)))
                {
                    locked = FALSE;
                }
            }
            else
            {
                AUTOTEST_Update_Autoscan_CH_Cfg(FALSE, NULL);
                locked = FALSE;
            }
        }

        if (TUNE_SYSTEM_TYPE_DVBS == sg_tuner_system_type ||
            TUNE_SYSTEM_TYPE_DVBS2 == sg_tuner_system_type)
        {
            if (STB_DPGetPolarity(path) == AUTOTEST_Get_CurCfg_Polairty())
            {
                freq = freq / 1000;
            }
            else
            {
                ; // not locked
            }
        }

        CERT_LOG_DEBG(TAG, "[%s] CfgFreq:%u, offset:%u", __FUNCTION__, AUTOTEST_Get_CurCfg_Freq(), offset);

        if ((sg_tuner_system_type == AUTOTEST_Get_CurCfg_TuneSys() ||
              (TUNE_SYSTEM_TYPE_UNKNOWN == AUTOTEST_Get_CurCfg_TuneSys() &&  TUNE_SYSTEM_TYPE_DVBT2 == sg_tuner_system_type)) &&
            sg_tuner_sig_type == AUTOTEST_Get_CurCfg_TuneSig() &&
            (freq >= AUTOTEST_Get_CurCfg_Freq() - offset && freq <= AUTOTEST_Get_CurCfg_Freq() + offset))
        {
            CERT_LOG_DEBG(TAG, "[%s] Freq:%u sigtype:%u, systye:%u Send: HW_EV_TYPE_LOCKED", __FUNCTION__, freq, sg_tuner_sig_type, sg_tuner_system_type);

            sg_sig_strength = AUTOTEST_Get_CurCfg_SigStrength();
            sg_sig_quality  = AUTOTEST_Get_CurCfg_SigQuality();
            STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_LOCKED, &path, sizeof(U8BIT));

            locked = TRUE;
        }
        else
        {
            CERT_LOG_DEBG(TAG, "[%s] Freq:%u sigtype:%u, systye:%u Send: HW_EV_TYPE_NOTLOCKED", __FUNCTION__, freq, sg_tuner_sig_type, sg_tuner_system_type);

            STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_NOTLOCKED, &path, sizeof(U8BIT));
        }

    }
    else
    {

        if (TUNE_SIGNAL_COFDM == sg_tuner_sig_type)
        {
            if ((freq == 842000000 && sg_tuner_system_type == TUNE_SYSTEM_TYPE_DVBT)
              ||(freq == 858000000 && sg_tuner_system_type == TUNE_SYSTEM_TYPE_DVBT))
            {
                CERT_LOG_DEBG(TAG, "[%s] Freq:%u sigtype:%u, systye:%u Send: HW_EV_TYPE_LOCKED", __FUNCTION__, freq, sg_tuner_sig_type, sg_tuner_system_type);

                STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_LOCKED, &path,
                                sizeof(U8BIT));
            }
            else
            {
                CERT_LOG_DEBG(TAG, "[%s] Freq:%u sigtype:%u, systye:%u Send: HW_EV_TYPE_NOTLOCKED", __FUNCTION__, freq, sg_tuner_sig_type, sg_tuner_system_type);

                STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_NOTLOCKED, &path,
                                sizeof(U8BIT));
            }
        }
        else
        {
            CERT_LOG_DEBG(TAG, "[%s] Freq:%u sigtype:%u, systye:%u Send: HW_EV_TYPE_LOCKED", __FUNCTION__, freq, sg_tuner_sig_type, sg_tuner_system_type);

            STB_OSSendEvent(FALSE, HW_EV_CLASS_TUNER, HW_EV_TYPE_LOCKED, &path,
                            sizeof(U8BIT));
        }
    }
}


/**
 * @brief   Stops any locking attempt, or unlocks if locked
 * @param   path the tuner path to stop
 */
void STB_TuneStopTuner(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the minimum tuner symbol rate
 * @param   path the tuner path to query
 * @return  minimum tuner symbol rate
 */
U32BIT STB_TuneGetMinTunerSymbolRate(U8BIT path)
{
    U32BIT symbol_rate = 1;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(symbol_rate);
}

/**
 * @brief   Returns the maxmum tuner symbol rate
 * @param   path the tuner path to query
 * @return  maxmum tuner symbol rate
 */
U32BIT STB_TuneGetMaxTunerSymbolRate(U8BIT path)
{
    U32BIT symbol_rate = 28000000;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(symbol_rate);
}


/**
 * @brief   Returns the minimum tuner frequency in KHz
 * @param   path the tuner path to query
 * @return  minimum frequency in Khz
 */
U32BIT STB_TuneGetMinTunerFreqKHz(U8BIT path)
{
    U32BIT min_freq = 10000;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(min_freq);
}

/**
 * @brief   Returns the maximum tuner frequency in KHz
 * @param   path the tuner path to query
 * @return  maximum frequency in Khz
 */
U32BIT STB_TuneGetMaxTunerFreqKHz(U8BIT path)
{
    U32BIT max_freq = 2000000;

    if (TUNE_SIGNAL_QPSK == sg_tuner_sig_type)
    {
        max_freq = 2000000000;
    }

    FUNCTION_START(STB_TuneGetMaxTunerFreqKHz);

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(max_freq);
}

/**
 * @brief   Returns the current signal strength
 * @param   path the tuner path to query
 * @return  the signal strength as percentage of maximum (0-100)
 */
U8BIT STB_TuneGetSignalStrength(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] %u", __FUNCTION__, sg_sig_strength);

    return sg_sig_strength;
}

/**
 * @brief   Returns the current data integrity
 * @param   path the tuner path to query
 * @return  the data integrity as percentage of maximum possible (0-100)
 * @todo     Confirm DVB API BER units
 */
U8BIT STB_TuneGetDataIntegrity(U8BIT path)
{
    U8BIT retval = 0;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return retval;
}

/**
 * @brief   Returns the current signal quality
 * @param   path the tuner path to query
 * @return  the signal quality
 * @todo     Confirm DVB API BER units
 */
U8BIT STB_TuneGetSignalQuality(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] %u", __FUNCTION__, sg_sig_quality);

    return sg_sig_quality;
}


/**
 * @brief   Returns the actual frequency of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the frequency in Hz
 */
U32BIT STB_TuneGetActualTerrFrequency(U8BIT path)
{
    U32BIT freq = 818000000;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(freq);
}

/**
 * @brief   Returns the actual freq offset of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the frequency offset in Hz
 */
S8BIT STB_TuneGetActualTerrFreqOffset(U8BIT path)
{
    S8BIT offset = 0;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(offset);
}

/**
 * @brief   Returns the actual mode of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the tuning mode
 */
E_STB_TUNE_TMODE STB_TuneGetActualTerrMode(U8BIT path)
{
    E_STB_TUNE_TMODE mode = TUNE_MODE_COFDM_8K;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(mode);
}

/**
 * @brief   Returns the actual bandwidth of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the signal bandwidth
 */
E_STB_TUNE_TBWIDTH STB_TuneGetActualTerrBwidth(U8BIT path)
{
    E_STB_TUNE_TBWIDTH bwidth = TUNE_TBWIDTH_8MHZ;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return bwidth;
}

/**
 * @brief   Returns the constellation of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the constellation
 */
E_STB_TUNE_TCONST STB_TuneGetActualTerrConstellation(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return 0;
}

/**
 * @brief   Returns the heirarchy of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the heirarchy
 */
E_STB_TUNE_THIERARCHY STB_TuneGetActualTerrHierarchy(U8BIT path)
{
    E_STB_TUNE_THIERARCHY retval = TUNE_THIERARCHY_8;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return retval;
}


/**
 * @brief   Returns the heirarchy of the current terrestrial signal.
 * @param   path the tuner path to query
 * @param   plp_list, out param, to store all the pip id in the current freq
 * @param   listlen,  in  param, the max numbers of pipid that can be stored in the list
 * @return  the pip number of the current frequency.
 */
S32BIT STB_TuneGetMPLPIDList(U8BIT path, U8BIT *plp_list, U16BIT listlen)
{
    S32BIT retval = 0;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return retval;
}


/**
 * @brief   Returns the LP code rate of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  The LP code rate
 */
E_STB_TUNE_TCODERATE STB_TuneGetActualTerrLpCodeRate(U8BIT path)
{
    {
            CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(TUNE_TCODERATE_UNDEFINED);
}

/**
 * @brief   Returns the HP code rate of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  The HP code rate
 */
E_STB_TUNE_TCODERATE STB_TuneGetActualTerrHpCodeRate(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(TUNE_TCODERATE_UNDEFINED);
}

/**
 * @brief   Returns the guard interval of the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the guard interval
 */
E_STB_TUNE_TGUARDINT STB_TuneGetActualTerrGuardInt(U8BIT path)
{
    {
            CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(TUNE_TGUARDINT_UNDEFINED);
}

/**
 * @brief   Returns the cell id the current terrestrial signal
 * @param   path the tuner path to query
 * @return  the cell id
 */
U16BIT STB_TuneGetActualTerrCellId(U8BIT path)
{
    {
            CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(0);
}

/**
 * @brief   Returns the actual bandwidth of the current isdbt signal
 * @param   path the tuner path to query
 * @return  the signal bandwidth
 */
E_STB_TUNE_TBWIDTH STB_TuneGetActualIsdbtBwidth(U8BIT path)
{
    E_STB_TUNE_TBWIDTH bwidth = TUNE_TBWIDTH_8MHZ;

    {
            CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return bwidth;
}

/**
 * @brief   Enables/disables aerial power for DVB-T
 * @param   path tuner path
 * @param   enabled TRUE to enable
 */
void STB_TuneActiveAerialPower(U8BIT path, BOOLEAN enabled)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the LNB voltage for the given tuner
 * @param   path tuner path
 * @param   voltage voltage setting
 */
void STB_TuneSetLNBVoltage(U8BIT path, E_STB_TUNE_LNB_VOLTAGE voltage)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}

void STB_TuneSetFrontendFd(U8BIT path, U32BIT fe_fd)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


void STB_TuneSetVoltageInterface(U8BIT path, E_STB_TUNE_LNB_VOLTAGE vol)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}



/**
 * @brief   Sets the type of modulation for the specified tuner
 * @param   path tuner path
 * @param   modulation type of modulation
 */
void STB_TuneSetModulation(U8BIT path, E_STB_TUNE_MODULATION modulation)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Turns the 22 kHz tone on or off
 * @param   path tuner path
 * @param   state TRUE to turn the tone on, FALSE to turn it off
 */
void STB_TuneSet22kState(U8BIT path, BOOLEAN state)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}

/**
 * @brief   Sets the 12V switch for the given tuner
 * @param   path tuner path
 * @param   state TRUE for on
 */
void STB_TuneSet12VSwitch(U8BIT path, BOOLEAN state)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sends the DisEqc message
 * @param   path - tuner path
 * @param   data - message data
 * @param   size - number of bytes in message data
 */
void STB_TuneSendDISEQCMessage(U8BIT path, U8BIT *data, U8BIT size)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the pulse limit for the east
 * @param   path tuner path
 * @param   count east limit count
 */
void STB_TuneSetPulseLimitEast(U8BIT path, U16BIT count)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the pulse limit for the west
 * @param   path tuner path
 * @param   count west limit count
 */
void STB_TuneSetPulseLimitWest(U8BIT path, U16BIT count)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


void STB_TuneChangePulsePosition(U8BIT path, U16BIT count)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the current pulse position
 * @param   path tuner path
 * @return  Current puls position
 */
U16BIT STB_TuneGetPulsePosition(U8BIT path)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }


    return(0);
}

void STB_TuneAtPulsePosition(U8BIT path, U16BIT position)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief Changes the value of skew position count
 * @param path tuner path
 * @param count skew position count
 */
void STB_TuneChangeSkewPosition(U8BIT path, U16BIT count)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the local oscillator frequency used by the LNB
 * @param   path the tuner path to query
 */
void STB_TuneSetLOFrequency(U8BIT tuner, U16BIT lo_freq)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the carrier signal strength as a percentage
 * @param   path tuner path
 * @param   freq carrier frequency
 * @return  Strength as a percentage
 */
U8BIT STB_TuneSatGetCarrierStrength(U8BIT path, U32BIT freq)
{
    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(0);
}

/**
 * @brief   Set the demodulator's signal type. This function must be called
 *          before each call to STB_TuneStartTuner in a dvb-t2 system and
 *          never in a dvb-t system.
 * @param   U8BIT path - the tuner path to set up
 * @param   E_STB_TUNE_TERR_TYPE type: TUNE_TERR_TYPE_DVBT,
 *          TUNE_TERR_TYPE_DVBT2 or TUNE_TERR_TYPE_UNKNOWN. When the signal
 *          type has been set to TUNE_TERR_TYPE_UNKNOWN, a call to
 *          STB_TuneStartTuner will force the driver to try with DVB-T first,
 *          and if no signal is found, with DVB-T2. When a signal has been
 *          found, STB_TuneGetTerrType will return the actual signal type.
 */
void STB_TuneSetSystemType(U8BIT path, E_STB_TUNE_SYSTEM_TYPE type)
{

    CERT_LOG_DEBG(TAG, "[%s] path:%u, old_type:%u, new_type:%u", __FUNCTION__,
                        path, sg_tuner_system_type, type);

    sg_tuner_system_type = type;
}


/**
 * @brief   Returns the signal type as set by STB_TuneSetTerrType or as
 *          re-written by the driver.
 * @param   path the tuner path to query
 * @return  Signal type.
 */
E_STB_TUNE_SYSTEM_TYPE STB_TuneGetSystemType(U8BIT path)
{
    E_STB_TUNE_SYSTEM_TYPE type = sg_tuner_system_type;

    {
        CERT_LOG_DEBG(TAG, "[%s] path:%u, type:%u", __FUNCTION__, path, type);
    }

   return(type);
}



/**
 * @brief   Sets the Physical Layer Pipe to be acquired
 * @param   path the tuner path to set up
 * @param   plp Physical Layer Pipe to be acquired
 */
void STB_TuneSetPLP(U8BIT path, U8BIT plp)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the actual symbol rate when a tuner has locked
 * @param   path tuner path
 * @return  Symbol rate in symbols per second
 */
U32BIT STB_TuneGetActualSymbolRate(U8BIT path)
{
    U32BIT srate = 28000;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return(srate);
}

/**
 * @brief   Returns the cable mode when the tuner has locked
 * @param   path tuner path
 * @return  QAM mode
 */
E_STB_TUNE_CMODE STB_TuneGetActualCableMode(U8BIT path)
{
    E_STB_TUNE_CMODE mode = TUNE_MODE_QAM_32;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

   return(mode);
}

/**
 * @brief   Returns the system type supported by the path. This function
 *          differs from STB_TuneGetSystemType which only returns T2 or S2 if
 *          the tuner is currently performing T2 or S2 operations.
 * @param   path  the tuner path to query
 * @return  (E_STB_TUNE_SYSTEM_TYPE) the system type supported by this path.
 *          TUNE_SYSTEM_TYPE_DVBT2 means both DVBT and DVBT2 are supported,
 *          TUNE_SYSTEM_TYPE_DVBS2 means both DVBS and DVBS2 are supported
 */
void STB_TuneGetSupportedSystemType(U8BIT path, U8BIT *support_sys)
{
     *support_sys = TUNE_SYSTEM_TYPE_DVBT;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }
}

void STB_TuneUpdateFeUsage(U8BIT path, BOOLEAN use)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


void STB_TuneAllStart()
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


void STB_TuneAllStop()
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}

BOOLEAN STB_Tnue_BlindScan(U8BIT path, STB_Tnue_BlindCallback_t cb, void *user_data, unsigned int start_freq, unsigned int stop_freq)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }


    return ret;
}

BOOLEAN STB_Tnue_BlindExit(U8BIT path)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}

void STB_Tnue_BlindGetTPCount(U8BIT path, U8BIT *count)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


BOOLEAN STB_Tnue_BlindGetTPInfo(U8BIT path, struct dvb_frontend_parameters *para, U8BIT *count)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}

BOOLEAN STB_TuneOpen(U8BIT path)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


U16BIT STB_TuneGetActualSignalType(U8BIT path)
{

    U16BIT sig_type = sg_tuner_sig_type;

    CERT_LOG_DEBG(TAG, "[%s] path:%u, current signal_type=%u", __FUNCTION__, path, sig_type);

    return sig_type;
}

BOOLEAN STB_TuneIsOpened(U8BIT path)
{
    BOOLEAN ret = TRUE;

    CERT_LOG_DEBG(TAG, "[%s] path:%u, Tune is Open=%u", __FUNCTION__, path, ret);

    return ret;
}

void STB_TuneSetSearchMode(U8BIT path, BOOLEAN mode)
{
    CERT_LOG_ERROR(TAG, "[%s] Not implement!", __FUNCTION__);
}

void STB_TuneSendBurstMessage(U8BIT path, U8BIT data)
{
    CERT_LOG_ERROR(TAG, "[%s] Not implement!", __FUNCTION__);
}



