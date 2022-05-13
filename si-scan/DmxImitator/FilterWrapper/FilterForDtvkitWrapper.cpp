#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <map>
#include <pthread.h>





#include "AnaBase.h"

#include "TsPackageFilter.h"
#include "PidFilter.h"
#include "SectionFilter.h"
#include "DbgManager.h"



#include "techtype.h"
#include "stbhwos.h"
#include "stbheap.h"

#include "cert_log.h"

#include "FilterForDtvkitWrapper.h"

#define TAG "Flt_for_Dtvkit_Wrapper"

//#define WRAPPER_DEBUG

#define MAX_DMXMSG_NUMBER   100000
#define DMXMSG_TIMEOUT      100 // ms: TIMEOUT_NEVER

#define FILT_TASK_PRIORITY                13    // 1 higher than UI

#define FILT_TASK_STACK_SIZE            4096


typedef struct tag_DmxMsg
{
    U8BIT path;
    U16BIT bytes;
    U16BIT filt_id;
    U8BIT *buf;
    FILTER_CALLBACK cb_func;
}StruDmxMsg;

// B: local variable define

static U16BIT gu16PidFltId = 0;
static U16BIT gu16SecFltId = 0;

static map<U16BIT, CPidFilter *> gmapPidFlt;
static map<U16BIT, CSectionFilter *> gmapSecFlt;
static map<CPidFilter *, FILTER_CALLBACK> gmapPidFltCB;

static CTsPackageFilter gTsFilter;
static CRoundBuf gRoundBuf(1024);
static CFileStream *gpFileStream = NULL;

static void *sgMutex = NULL;


static u8 sg_Filter_Loop_Flag = 0;


static void *dmx_task_ptr = NULL;

static void *dmx_task_msg_queue = NULL;
static StruDmxMsg dmx_msg;

static U32BIT sg_tsloop_1000_package_sleep_time = 0; // ms
// E: local variable define




#ifdef __cplusplus
extern "C" {
#endif

class AutoLock {

public:
    AutoLock(void *pMutex);
    ~AutoLock();

private:
    void *m_pMutex;
};

AutoLock::AutoLock(void * pMutex):m_pMutex(pMutex)
{
    if (NULL != m_pMutex)
    {
        STB_OSMutexLock(m_pMutex);
    }
}

AutoLock::~AutoLock()
{
    if (NULL != m_pMutex)
    {
        STB_OSMutexUnlock(m_pMutex);
    }
}



// B: Local Function Declare
CPidFilter* FindPidFilterById(U16BIT PidFltId);
FILTER_CALLBACK FindPidFilterCBFunc(CPidFilter *pPidFlt);
CSectionFilter* FindSecFilterById(U16BIT SecFltId);


static void wrapper_dmx_task(void *notused);
static void send_dmx_msg(U8BIT path, U16BIT bytes, U16BIT pfilt_id, U8BIT *buf, FILTER_CALLBACK cb_func);

// E: Local Function Declare

void Wrapper_DMXInitialise(U8BIT paths, BOOLEAN inc_pes_collection)
{
    //roundBuf.ConnectFileSource(&fileStream);

    gTsFilter.SetRoundBuf(&gRoundBuf);

    sgMutex = STB_OSCreateMutex();

    dmx_task_ptr = STB_OSCreateTask(wrapper_dmx_task, NULL, FILT_TASK_STACK_SIZE, FILT_TASK_PRIORITY, (U8BIT *)"dmx-task");
    dmx_task_msg_queue = STB_OSCreateQueue(sizeof(StruDmxMsg), MAX_DMXMSG_NUMBER);
    memset(&dmx_msg, 0, sizeof(StruDmxMsg));
}

void Wrapper_SetTsSource(U8BIT paths, const char *FilePathName)
{
    AutoLock lock(sgMutex);

    if (NULL != gpFileStream)
    {
        delete gpFileStream;
    }

    gpFileStream = new CFileStream(FilePathName);

    gRoundBuf.ResetBufSize();
    gRoundBuf.ConnectFileSource(gpFileStream);
}

void Wrapper_EnableTsLoop()
{
    sg_Filter_Loop_Flag = 1;
}

void Wrapper_DisableTsLoop()
{
    sg_Filter_Loop_Flag = 0;
}

void Wrapper_SetTsLoopDelayMS(U32BIT delayms)
{
    sg_tsloop_1000_package_sleep_time = delayms;
    CERT_LOG_FATAL(TAG, "[%s] sg_tsloop_sleep_time:%u", __FUNCTION__, sg_tsloop_1000_package_sleep_time);
}

U32BIT Wrapper_CalcTsLoopDelay(long filelen, long duration)
{
    U32BIT ret = (duration * 1000) / (filelen / 188);

    CERT_LOG_DEBG(TAG, "[%s] filelen:%lu, duration:%lu, ret:%u", __FUNCTION__, filelen, duration, ret);

    return ret;
}


void Wrapper_StartTsLoop(U8BIT paths)
{
    u8 tsPackBuf[188];
    u32 getlen  = 0;
    u32 start   = 0;
    u32 end     = 0;

    size_t fileOffset = 0;

    CERT_LOG_FATAL(TAG, "[%s] sg_tsloop_1000_package_sleep_time:%u", __FUNCTION__, sg_tsloop_1000_package_sleep_time);

    do
    {
        static long i = 0;

        STB_OSMutexLock(sgMutex);

        if (0 != sg_tsloop_1000_package_sleep_time)
        {
            start  = timeGetTime();

            getlen = gTsFilter.GetTsPackageEx(tsPackBuf, fileOffset);

            if (999 == i%1000)
            {
                do {

                    end = timeGetTime();

                }while(end - start < sg_tsloop_1000_package_sleep_time);
            }

            i++;
        }
        else
        {
            getlen = gTsFilter.GetTsPackageEx(tsPackBuf, fileOffset);
        }

        STB_OSMutexUnlock(sgMutex);

    } while ( 0!= getlen && 1 == sg_Filter_Loop_Flag);
}


U16BIT Wrapper_DMXGrabPIDFilter(U8BIT path, U16BIT pid, FILTER_CALLBACK func)
{
    U16BIT pid_filter_id = gu16PidFltId;

    CPidFilter *pPidFlt = new CPidFilter();

    AutoLock lock(sgMutex);

    if (NULL == pPidFlt)
    {
        CERT_LOG_FATAL(TAG, "New CPidFilter Failed!");
        return 0;
    }

    pPidFlt->SetPid(pid);
    gmapPidFlt.insert(pair<U16BIT, CPidFilter *>(pid_filter_id, pPidFlt));
    gmapPidFltCB.insert(pair<CPidFilter *, FILTER_CALLBACK>(pPidFlt, func));


    gTsFilter.RegisterNotify(pid_filter_id, pPidFlt);

    gu16PidFltId++;

    return pid_filter_id;
}


void Wrapper_DMXReleasePIDFilter(U8BIT path, U16BIT pfilt_id)
{
    CPidFilter *pPidFlt = NULL;

    map<U16BIT, CPidFilter *>::iterator iter;
    map<CPidFilter *, FILTER_CALLBACK>::iterator iter_func;

    AutoLock lock(sgMutex);

    iter = gmapPidFlt.find(pfilt_id);

    if (iter != gmapPidFlt.end())
    {
        pPidFlt = iter->second;
        pPidFlt->DisableFilter();
        gTsFilter.UnRegisterNotify(pfilt_id);

        iter_func = gmapPidFltCB.find(pPidFlt);

        if (iter_func != gmapPidFltCB.end())
        {
            gmapPidFltCB.erase(iter_func);
        }

        gmapPidFlt.erase(iter);
    }
}




void Wrapper_DMXStartPIDFilter(U8BIT path, U16BIT pfilt_id)
{
    AutoLock lock(sgMutex);

    CPidFilter *pPidFlt = FindPidFilterById(pfilt_id);

    if (NULL != pPidFlt)
    {
        #ifdef WRAPPER_DEBUG
        pPidFlt->SetDebug(true);
        #endif

        pPidFlt->EnableFilter();
    }
}


void Wrapper_DMXStopPIDFilter(U8BIT path, U16BIT pfilt_id)
{
    AutoLock lock(sgMutex);

    CPidFilter *pPidFlt = FindPidFilterById(pfilt_id);

    if (NULL != pPidFlt)
    {
        #ifdef WRAPPER_DEBUG
        pPidFlt->SetDebug(true);
        #endif

        pPidFlt->DisableFilter();
    }
}





U16BIT Wrapper_DMXGrabSectFilter(U8BIT path, U16BIT pfilt_id)
{
    U16BIT sec_filter_id = gu16SecFltId;

    CPidFilter *pPidFlt = NULL;

    FILTER_CALLBACK funcCB = NULL;
    CSectionFilter *pSecFlt = new CSectionFilter();


    AutoLock lock(sgMutex);

    if (NULL == pSecFlt)
    {
        CERT_LOG_FATAL(TAG, "New CSectionFilter Failed!");

        return 0;
    }

    pSecFlt->SetSecFltId(sec_filter_id);

    pPidFlt = FindPidFilterById(pfilt_id);
    funcCB  = FindPidFilterCBFunc(pPidFlt);

    pSecFlt->SetFilterCBFunc(funcCB);
    pSecFlt->SetFatherFlt(pPidFlt);
    pSecFlt->SetSendDmxMsgFunc(send_dmx_msg);
    pSecFlt->EnableFilter();

    gmapSecFlt.insert(pair<U16BIT, CSectionFilter *>(sec_filter_id, pSecFlt));


    pPidFlt->RegisterNotify(pSecFlt, *pSecFlt);

    gu16SecFltId++;

    return sec_filter_id;
}



void Wrapper_DMXSetupSectFilter(U8BIT path, U16BIT sfilt_id, U8BIT *match_ptr, U8BIT *mask_ptr,
                                     U8BIT not_equal_byte_index, BOOLEAN crc)
{
    // Now is a simplified implemetation, only match table id
    CSectionFilter *pSecFlt = NULL;

    AutoLock lock(sgMutex);

    pSecFlt = FindSecFilterById(sfilt_id);

    if (0 == match_ptr[1] && 0 == match_ptr[2] && 0 == mask_ptr[1] && 0 == mask_ptr[2]) // SI_XTID_MATCH_DONT_CARE
        pSecFlt->SetFilterTableId(match_ptr[0], ~mask_ptr[0]);
    else
        pSecFlt->SetFilterTableId(match_ptr[0], ~mask_ptr[0], match_ptr[1] << 8 | match_ptr[2], 0);
}



void Wrapper_DMXReleaseSectFilter(U8BIT path, U16BIT sfilt_id)
{
    CSectionFilter *pSecFlt = NULL;
    CPidFilter *pPidFlt = NULL;

    map<U16BIT, CSectionFilter *>::iterator iter;

    AutoLock lock(sgMutex);

    iter = gmapSecFlt.find(sfilt_id);

    if (iter != gmapSecFlt.end())
    {
        pSecFlt = iter->second;
        pSecFlt->DisableFilter();

        pPidFlt = static_cast<CPidFilter *>(pSecFlt->GetFatherFlt());

        if (NULL != pPidFlt)
        {
            pPidFlt->UnRegisterNotify(pSecFlt);
        }

        gmapSecFlt.erase(iter);
    }
}


BOOLEAN Wrapper_DMXCopyPIDFilterSect(U8BIT path, U8BIT *buffer, U16BIT size, U16BIT pfilt_id)
{
    U32BIT get_data_len = 0;

    BOOLEAN ret = FALSE;

    if (dmx_msg.path == path && dmx_msg.filt_id == pfilt_id && size >= dmx_msg.bytes)
    {
        memcpy(buffer, dmx_msg.buf, dmx_msg.bytes);

        ret = TRUE;
    }
    else
    {
        CERT_LOG_ERROR(TAG, "[%s] Err path(%u), pfilt_id:(%u), size(%u)", __FUNCTION__, path, pfilt_id, size);
        CERT_LOG_ERROR(TAG, "[%s] Err dmx.path(%u), dmx.filt_id:(%u), dmx.bytes(%u)", __FUNCTION__,
                            dmx_msg.path, dmx_msg.filt_id, dmx_msg.bytes);
    }

    delete [] dmx_msg.buf;

    memset(&dmx_msg, 0, sizeof(StruDmxMsg));

    return ret;
}



// B: Local Function Define
CPidFilter * FindPidFilterById(U16BIT PidFltId)
{
    CPidFilter *pPidFlt = NULL;

    map<U16BIT, CPidFilter *>::iterator iter;

    iter = gmapPidFlt.find(PidFltId);

    if (iter != gmapPidFlt.end())
    {
        pPidFlt = iter->second;
    }


    return pPidFlt;
}



FILTER_CALLBACK FindPidFilterCBFunc(CPidFilter *pPidFlt)
{
    FILTER_CALLBACK func = NULL;

    map<CPidFilter *, FILTER_CALLBACK>::iterator iter;

    iter = gmapPidFltCB.find(pPidFlt);

    if (iter != gmapPidFltCB.end())
    {
        func = iter->second;
    }

    return func;
}



CSectionFilter* FindSecFilterById(U16BIT SecFltId)
{
    CSectionFilter *pSecFlt = NULL;

    map<U16BIT, CSectionFilter *>::iterator iter;

    iter = gmapSecFlt.find(SecFltId);

    if (iter != gmapSecFlt.end())
    {
        pSecFlt = iter->second;
    }


    return pSecFlt;
}

static void wrapper_dmx_task(void *notused)
{
    BOOLEAN msg_ready = FALSE;

    while (1)
    {
        // Waits for a section received to be reported
        msg_ready = STB_OSReadQueue(dmx_task_msg_queue, (void *)&dmx_msg, sizeof(StruDmxMsg), TIMEOUT_NEVER);
        if (msg_ready == TRUE)
        {
            if (NULL != dmx_msg.cb_func)
            {
                dmx_msg.cb_func(dmx_msg.path, dmx_msg.bytes, dmx_msg.filt_id);
            }
            else
            {
                if (NULL != dmx_msg.buf)
                {
                    delete [] dmx_msg.buf;
                }

                CERT_LOG_ERROR(TAG, "[%s] NULL cb_func!", __FUNCTION__);
            }
        }
    }

}

static void send_dmx_msg(U8BIT path, U16BIT bytes, U16BIT pfilt_id, U8BIT *buf, FILTER_CALLBACK cb_func)
{
    u32 start   = 0;
    u32 end     = 0;

    StruDmxMsg tmp_dmxmsg;

    tmp_dmxmsg.path     = path;
    tmp_dmxmsg.bytes    = bytes;
    tmp_dmxmsg.filt_id  = pfilt_id;
    tmp_dmxmsg.cb_func  = cb_func;

    tmp_dmxmsg.buf = new u8[bytes];

    memcpy(tmp_dmxmsg.buf, buf, bytes);

#ifdef WRAPPER_DEBUG
    dbg_show_mem(tmp_dmxmsg.buf, bytes);
#endif

    while (!STB_OSWriteQueue(dmx_task_msg_queue, &tmp_dmxmsg, sizeof(StruDmxMsg), DMXMSG_TIMEOUT))
    {
        //delete [] tmp_dmxmsg.buf;

        STB_OSMutexUnlock(sgMutex);

        start  = timeGetTime();

        do {

                end = timeGetTime();

        }while(end - start < DMXMSG_TIMEOUT);

        CERT_LOG_ERROR(TAG, "[%s] WriteQueue Failed & Wait:%u ms to try Again!", __FUNCTION__, DMXMSG_TIMEOUT);

        STB_OSMutexLock(sgMutex);


    }
}



// E: Local Function Define

#ifdef __cplusplus
}
#endif

