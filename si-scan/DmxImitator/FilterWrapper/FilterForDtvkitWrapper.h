#ifndef __FILTER_FOR_DTVKIT_WRAPPER_H__
#define __FILTER_FOR_DTVKIT_WRAPPER_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*FILTER_CALLBACK)(U8BIT path, U16BIT bytes, U16BIT pfilt_id);


void Wrapper_DMXInitialise(U8BIT paths, BOOLEAN inc_pes_collection);

void Wrapper_SetTsSource(U8BIT paths, const char *FilePathName);
void Wrapper_StartTsLoop(U8BIT paths);
void Wrapper_EnableTsLoop();
void Wrapper_DisableTsLoop();
void Wrapper_SetTsLoopDelayMS(U32BIT delayms);
U32BIT Wrapper_CalcTsLoopDelay(long filelen, long duration);

U16BIT Wrapper_DMXGrabPIDFilter(U8BIT path, U16BIT pid, FILTER_CALLBACK func);
void Wrapper_DMXReleasePIDFilter(U8BIT path, U16BIT pfilt_id);
void Wrapper_DMXStartPIDFilter(U8BIT path, U16BIT pfilt_id);
void Wrapper_DMXStopPIDFilter(U8BIT path, U16BIT pfilt_id);

U16BIT Wrapper_DMXGrabSectFilter(U8BIT path, U16BIT pfilt_id);
void Wrapper_DMXSetupSectFilter(U8BIT path, U16BIT sfilt_id, U8BIT *match_ptr, U8BIT *mask_ptr,
                                     U8BIT not_equal_byte_index, BOOLEAN crc);
void Wrapper_DMXReleaseSectFilter(U8BIT path, U16BIT sfilt_id);

BOOLEAN Wrapper_DMXCopyPIDFilterSect(U8BIT path, U8BIT *buffer, U16BIT size, U16BIT pfilt_id);


#ifdef __cplusplus
}
#endif

#endif
