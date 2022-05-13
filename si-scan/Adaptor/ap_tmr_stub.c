/*******************************************************************************
 * Copyright © 2014 The DTVKit Open Software Foundation Ltd (www.dtvkit.org)
 * Copyright © 2004 Ocean Blue Software Ltd
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
 * @brief   Timer handling functions used by the application
 *
 * @file    ap_tmr.c
 * @date    27/05/2004
 * @author  Ocean Blue
 */

//---includes for this file-------------------------------------------------------------------------
// compiler library header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// third party header files

// Ocean Blue Software header files
#include "techtype.h"   //generic data definitions
#include "dbgfuncs.h"   //obs debug functions

#include "stbhwdsk.h"
#include "stbhwos.h"
#include "stbhwc.h"     // STB_SPDebugWrite

#include "stbgc.h"
#include "stbdpc.h"
#include "stbsiflt.h"
#include "stbsitab.h"
#include "stbpvr.h"     // STB PVR
//#include "stbpvrmsg.h"
#include "stbheap.h"    // STB_AppFreeMemory
#include "stbuni.h"     // STB_ConcatUnicodeStrings()
#include "stbllist.h"
#include "stberc.h"

#ifdef INTEGRATE_HBBTV
#include "hbbtv_api.h"
#endif

#include "app.h"
#include "ap_pvr.h"     // for PVR functionality

#include "ap_cfg.h"
#include "ap_dbacc.h"
#include "ap_tmr.h"
#include "ap_dbdef.h"
#include "ap_cntrl.h"
#include "ap_state.h"

#include "dba.h"

#include "cert_log.h"

#define TAG "AP_TMR_STUB"

//---constant definitions for this file-------------------------------------------------------------

//---local typedefs, structs, enumerations for this file--------------------------------------------

/* This structure is used for timer database filters */



//---local (static) variable declarations for this file---------------------------------------------
//   (internal variables declared static to make them local)

//---local function prototypes for this file--------------------------------------------------------
//   (internal functions declared static to make them local)


//---global function definitions-----------------------------------------------

/**
 * @brief   Performs initialisation of the timers, reading existing entries from the database,
 *          rescheduling or deleting any timers that have been missed and starting background tasks
 */
void ATMR_Initialise(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Creates a new timer based on the information supplied
 * @param   info timer info used to create the timer
 * @return  timer handle, or INVALID_TIMER_HANDLE if creation fails
 */
U32BIT ATMR_AddTimer(S_TIMER_INFO *info)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Creates a timer based on the given event. If a recording timer is created, it will
 *          be set to record on the default disk, which can be changed afterwards using
 *          ATMR_SetDiskId.
 * @param   event_ptr - pointer to the event to be recorded
 * @param   serv_ptr service the event is on
 * @param   record TRUE if a recording timer is to be created, FALSE for an alarm timer
 * @param   event_triggered TRUE if the timer should be triggered by the change of event
 *                          rather than the time
 * @return  timer handle, or INVALID_TIMER_HANDLE if the timer couldn't be created
 */
U32BIT ATMR_AddTimerForEvent(void *event_ptr, void *serv_ptr, BOOLEAN record, BOOLEAN event_triggered)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Updates the duration for an existing PVR recording timer
 * @param   handle handle of timer to be updated
 * @param   duration duration to be set in the timer
 * @return  TRUE if the timer is updated, FALSE otherwise
 */
BOOLEAN ATMR_UpdateTimerDuration(U32BIT handle, U32DHMS duration)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Updates all the timer fields
 * @param   handle handle of timer to be updated
 * @param   info timer info used to update the timer
 * @return  TRUE if the timer exists and is deleted, FALSE otherwise
 */
BOOLEAN ATMR_UpdateTimer(U32BIT handle, S_TIMER_INFO *info)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Delete the timer with the given handle
 * @param   handle handle of timer to be deleted
 * @return  TRUE if timer exists and is deleted, FALSE otherwise
 */
BOOLEAN ATMR_DeleteTimer(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns a list of all the timer handles and the number of items in the list.
 * @param   timer_list pointer to an array of timer handles, the array is allocated by this function
 * @param   list_size_ptr pointer to the number of items in the returned list
 * @param   list_type type of timers to put in the list
 * @param   date_time_order TRUE if the list is to be returned in date/time order,
 *                          FALSE returns the list in alphabetical name order
 * @return  TRUE if a list is returned, FALSE otherwise
 */
BOOLEAN ATMR_GetTimerList(U32BIT **timer_list, U16BIT *list_size_ptr, E_TIMER_TYPE list_type,
   BOOLEAN date_time_order)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Release the given array of timer handles
 * @param   timer_list - timer array to be freed
 * @param   list_size - number of items in the list
 */
void ATMR_ReleaseTimerList(U32BIT *timer_list, U16BIT list_size)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Finds the timer using the given decode path and if it's a recording timer
 *          the recording will be started
 * @param   path decode path being used for the recording
 * @return  TRUE if the recording is started, FALSE otherwise
 */
BOOLEAN ATMR_StartRecord(U8BIT path)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Handles the timer when a recording fails to start for some reason.
 *          This may result in the timer being deleted.
 * @param   path - recording path
 */
void ATMR_RecordingFailed(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets up the given timer info structure with default values for the given timer type
 *          using the service and event depending on timer type.
 * @param   timer_info pointer to timer info structure to be initialised
 * @param   timer_type type of timer to initialise the structure for
 * @param   serv_ptr service that will be used for alarm and PVR recording timers. It can be NULL,
 *          if not, it is used to initialise the service IDs in the alarm and PVR timers and to
 *          initialise the programme CRID field in PVR timers.
 * @param   event_ptr event that will be used for alarm and PVR recording timers. It can be NULL,
 *          if not, it is used to initialise start time and name in alarm and PVR timers and other
 *          event related fields in PVR timers. When event_ptr is specified for a PVR timer, it
 *          will be initialised as 'event triggered';
 * @return  TRUE if the structure was setup, FALSE otherwise
 */
BOOLEAN ATMR_InitialiseTimer(S_TIMER_INFO *timer_info, E_TIMER_TYPE timer_type, void *serv_ptr,
   void *event_ptr)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Copies timer data for the given timer info the info structure provided
 * @param   handle timer handle the data is to be copied from
 * @param   timer_info will be filled with info from the timer
 * @return  TRUE if the timer is valid and data is returned, FALSE otherwise
 */
BOOLEAN ATMR_GetTimerInfo(U32BIT handle, S_TIMER_INFO *timer_info)
{
   BOOLEAN ret = TRUE;

   {
       CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
   }

   return ret;
}


/**
 * @brief   Returns the service for the recording timer on the given path
 * @param   path recording path
 * @return  service pointer, or NULL if timer not found or service referenced by timer not found
 */
void* ATMR_GetRecordService(U8BIT path)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Get the name of the timer with the given handle
 * @param   handle timer handle
 * @return  pointer to timer name, this value shouldn't be freed
 */
U8BIT* ATMR_GetName(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Sets the name of the timer with the given handle
 * @param   handle timer handle
 */
void ATMR_SetName(U32BIT handle, U8BIT *name)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Get the start date & time of the timer with the given handle.
 *          The date/time returned will be in UTC
 * @param   handle timer handle
 * @return  UTC start date/time, or 0 if the timer handle isn't valid
 */
U32DHMS ATMR_GetStartDateTime(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the duration of the PVR record timer with the given handle
 * @param   handle timer handle
 * @return  timer duration, or 0 if the timer handle isn't valid
 */
U32DHMS ATMR_GetDuration(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Get the end date & time of the timer with the given handle.
 *          The date/time returned will be in UTC
 * @param   handle timer handle
 * @return  UTC end date/time, or 0 if the timer handle isn't valid
 */
U32DHMS ATMR_GetEndDateTime(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the type of the given timer
 * @param   handle timer handle
 * @return  type of the timer, or TIMER_TYPE_NONE if handle isn't valid
 */
E_TIMER_TYPE ATMR_GetType(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the frequency setting for the given timer
 * @param   handle timer handle
 * @return  frequency setting of the timer, or TIMER_FREQ_ONCE if handle isn't valid
 */
E_TIMER_FREQ ATMR_GetFrequency(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the change service setting for an alarm timer
 * @param   handle timer handle
 * @return  value of change service setting, or FALSE if timer is invalid or isn't an alarm timer
 */
BOOLEAN ATMR_GetChangeService(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns the ramp volume setting for an alarm timer
 * @param   handle timer handle
 * @return  value of ramp volume setting, or FALSE if timer is invalid or isn't an alarm timer
 */
BOOLEAN ATMR_GetRampVolume(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns the event ID for a PVR recording timer
 * @param   handle timer handle
 * @return  event ID, or 0 if the timer isn't valid or isn't a recording timer
 */
U16BIT ATMR_GetEventId(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the service ID for an alarm or PVR recording timer
 * @param   handle timer handle
 * @return  service ID, or ADB_INVALID_DVB_ID if the timer isn't valid or isn't
 *          an alarm or recording timer
 */
U16BIT ATMR_GetServiceId(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the transport ID for an alarm or PVR recording timer
 * @param   handle timer handle
 * @return  transport ID, or ADB_INVALID_DVB_ID if the timer isn't valid or isn't
 *          an alarm or recording timer
 */
U16BIT ATMR_GetTransportId(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Returns the original network ID for an alarm or PVR recording timer
 * @param   handle timer handle
 * @return  original network ID, or ADB_INVALID_DVB_ID if the timer isn't valid or isn't
 *          an alarm or recording timer
 */
U16BIT ATMR_GetOriginalNetworkId(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Gets the timer's missed flag
 * @param   handle timer handle
 * @return  TRUE if the timer is marked as missed, FALSE otherwise
 */
BOOLEAN ATMR_GetMissed(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns a pointer to the programme CRID string from a recording timer.
 *          The returned value shouldn't be changed or freed.
 * @param   handle timer handle
 * @return  CRID string, NULL if there isn't a CRID or the timer isn't a recording timer
 */
U8BIT* ATMR_GetProgrammeCrid(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Does the timer have a series crid?
 * @param   handle timer handle
 * @return  TRUE if the timer is valid and is a recording timer and has a series CRID,
 *          FALSE otherwise
 */
BOOLEAN ATMR_HasSeriesCrid(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Does the timer have a recommendation crid?
 * @param   handle timer handle
 * @return  TRUE if the timer is valid and is a recording timer and has a recommendation CRID,
 *          FALSE otherwise
 */
BOOLEAN ATMR_HasRecommendationCrid(U32BIT handle)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns the disk id for the given timer if the timer is a PVR recording timer
 * @param   handle timer handle
 * @return  disk id if timer is valid and is a recording timer, INVALID_DISK_ID otherwise
 */
U16BIT ATMR_GetDiskId(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Set the disk for the given timer if the timer is a recording timer
 * @param   handle timer handle
 * @param   disk_id disk id
 */
void ATMR_SetDiskId(U32BIT handle, U16BIT disk_id)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Returns the recording handle associated with a PVR recording timer
 * @param   handle timer handle
 * @return  recording handle, or 0 if the timer isn't a PVR recording timer or no
 *          recording has been started
 */
U32BIT ATMR_GetRecordingHandle(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Used by the DVB stack to handle an event for the given timer.
 *          If the timer requires the app to deal with it, such as for sleep or alarm
 *          timers, then another event will be sent to the app with an S_TIMER_INFO
 *          structure as the event data containing the timer's details to allow the
 *          app deal with it. The timer itself will have been updated or deleted.
 * @param   handle timer handle
 */
void ATMR_HandleTimerEvent(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Checks all timers to see whether any recordings should be started or stopped
 *          as a result of the now event being changed.
 * @param   recordings_can_start TRUE if the event should be checked to start a recording
 * @return  TRUE if a record can be/has been started
 */
BOOLEAN ATMR_CheckRecordStatus(BOOLEAN recordings_can_start)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Checks each recording timer that's linked to an event to see whether
 *          the event is still in the schedule and whether the time has changed,
 *          and if it has changed then the timer is updated.
 */
void ATMR_EitUpdated(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Delete the PVR record timer with the given recording handle
 * @param   recording_handle recording handle used by the timer to be deleted
 */
void ATMR_DeleteRecordingTimer(U32BIT recording_handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Counts the number of simultaneous recordings (EXT and PVR) between
 *          the given start and end dates/times.
 * @param   max_recordings the max recordings that can take place at the same time
 * @param   start_date_time start date and time of the period to be checked
 * @param   end_date_time end date and time of the period to be checked
 * @param   conflicting_timers pointer to the list of conflicting timers, the
 *          list must to be freed by the caller. If NULL it's ignored.
 * @return  Number of simultaneous recordings during the given period
 */
U8BIT ATMR_GetNumSimultaneousRecordings(U8BIT max_recordings, U32DHMS start_date_time,
   U32DHMS end_date_time, U32BIT **conflicting_timers)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Adds a timer to perform a recording based on the given event and service.
 *          Conflicts are checked and a search is made for an alternative event if necessary.
 * @param   serv_ptr pointer to service on which recording is to take place
 * @param   event_ptr event to be recorded
 * @param   prog_crid programme CRID or NULL
 * @param   other_crid series or recommendation CRID, or NULL
 * @param   is_recommendation TRUE if the above crid is a recommendation crid, FALSE for series
 * @param   check_alternatives TRUE if alternative events are to be searched for if the specified
 *                             event can't be recorded
 * @return  pointer to the event actually recorded, which may be different from the one given,
 *          or NULL if the event can't be recorded
 */
void* ATMR_RecordEvent(void *serv_ptr, void *event_ptr, U8BIT *prog_crid, U8BIT *other_crid,
   BOOLEAN is_recommendation, BOOLEAN check_alternatives)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Searches for events within 3 hours of the given start date/time for an
 *          event with the given programme CRID and creates a timer to record any found.
 *          The search is performed forward or backward from the given start date/time
 *          as defined by the search direction argument.
 * @param   serv_ptr pointer to service on which search is to take place
 * @param   prog_crid programme CRID to be searched for
 * @param   start_date_time date and time to start searching from
 * @param   radio_service TRUE if the search is on a radio service
 * @param   search_forward TRUE if the search is to be made for events following the given date/time
 * @return  TRUE if an event is found and is set for recording, FALSE otherwise
 */
BOOLEAN ATMR_RecordSplitEvent(void *serv_ptr, U8BIT *prog_crid, U32DHMS start_date_time,
   BOOLEAN radio_service, BOOLEAN search_forward)
{
   BOOLEAN ret = TRUE;

   {
       CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
   }

   return ret;
}


/**
 * @brief   Searches the timers for the first timer that will cause the DVB to wakeup that hasn't
 *          been missed. This will be an alarm or PVR recording timer.
 * @param   date_time pointer to return the date/time of the first timer found
 * @param   onet_id returns the original network ID of the service associated with the timer
 * @param   trans_id returns the transport ID of the service associated with the timer
 * @param   service_id returns the service ID of the service associated with the timer
 * @return  timer handle, or INVALID_TIMER_HANDLE if no timer is found
 */
U32BIT ATMR_GetFirstWakeupTime(U32DHMS *date_time, U16BIT *onet_id, U16BIT *trans_id,
   U16BIT *service_id)
{
   CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

   return 0;
}


/**
 * @brief   Searches the timers for a recording timer with the given event and service IDs
 * @param   onet_id original network ID or the service
 * @param   trans_id transport ID of the service
 * @param   serv_id service ID
 * @param   event_id event ID
 * @return  handle of timer, or INVALID_TIMER_HANDLE if no timer is found
 */
U32BIT ATMR_FindTimerFromEvent(U16BIT onet_id, U16BIT trans_id, U16BIT serv_id, U16BIT event_id)
{
   CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

   return 0;
}


/**
 * @brief   Searches the timers for a recording timer with the given programme CRID
 * @param   prog_crid the programme CRID to be searched for
 * @return  handle of timer, or INVALID_TIMER_HANDLE if no timer is found
 */
U32BIT ATMR_FindTimerFromCrid(U8BIT *prog_crid)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Searches the timers for a recording timer with the given programme
 *          CRID and event ID.
 * @param   prog_crid the programme CRID to search for
 * @param   service_id service ID of the event
 * @param   event_id ID of the event
 * @return  handle of timer, or INVALID_TIMER_HANDLE if no timer is found
 */
U32BIT ATMR_FindTimerFromCridAndEvent(U8BIT *prog_crid, U16BIT service_id, U16BIT event_id)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Deletes any PVR record timers with the given series CRID
 * @param   crid the series/recommendation CRID to be searched for
 * @param   is_recommendation TRUE if the given crid is for a recommendation, FALSE otherwise
 */
void ATMR_DeleteTimersForSeriesRecommendations(U8BIT *crid, BOOLEAN is_recommendation)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Sets the additioinal information string for the specified timer and commits the change
 *          to the database
 * @param   handle Timer handle
 * @param   info pointer to the string
 * @param   size number of bytes in the string
 */
void ATMR_SetAdditionalInfo(U32BIT handle, U8BIT *info, U32BIT size)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


/**
 * @brief   Gets the additional information string associated with a timer.
 *          The name is allocated in UI temp memory.
 * @param   handle Timer handle
 * @param   size Pointer to variable containing the number of bytes in the string
 * @return  additional information string, or NULL
 */
U8BIT* ATMR_GetAdditionalInfo(U32BIT handle, U32BIT *size)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Returns the value of start_padding associated with the specified timer
 *          The start padding is the number of seconds before (after, if negative) the actual
 *          timer start time the timer will be triggered.
 * @param   handle Timer handle
 * @return  start_padding
 */
S32BIT ATMR_GetStartPadding(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Sets the value of start_padding associated with the specified timer
 *          The start padding is the number of seconds before (after, if negative) the actual
 *          timer start time the timer will be triggered.
 * @param   handle Timer handle
 * @param   start_padding new value for the timer start_padding
 * @return  TRUE if the start_padding could be changed, FALSE otherwise (e.g. due to a conflict)
 */
BOOLEAN ATMR_SetStartPadding(U32BIT handle, S32BIT start_padding)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/**
 * @brief   Returns the value of end_padding associated with the specified timer
 *          The end padding is the number of seconds after (before, if negative) the actual
 *          timer end time the timer will expire.
 * @param   handle Timer handle
 * @return  start_padding
 */
S32BIT ATMR_GetEndPadding(U32BIT handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);

    return 0;
}


/**
 * @brief   Sets the value of end_padding associated with the specified timer
 *          The end padding is the number of seconds after (before, if negative) the actual
 *          timer end time the timer will expire.
 * @param   handle Timer handle
 * @param   end_padding new value for the timer end_padding
 * @return  TRUE if the start_padding could be changed, FALSE otherwise (e.g. due to a conflict)
 */
BOOLEAN ATMR_SetEndPadding(U32BIT handle, S32BIT end_padding)
{
    BOOLEAN ret = TRUE;

    {
        CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
    }

    return ret;
}


/*!**************************************************************************
 * @brief   Prints details of all existing timers
 ****************************************************************************/
void ATMR_DumpAllTimers(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func!", __FUNCTION__);
}


//---local function definitions------------------------------------------------

