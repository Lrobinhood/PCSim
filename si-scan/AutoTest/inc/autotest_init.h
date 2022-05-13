#ifndef __AUTOTEST_INIT_H__
#define __AUTOTEST_INIT_H__

typedef void (*DVB_EVENT_HANDLE_FUNC)(unsigned int event, void *event_data, unsigned int data_size);

void AUTOTEST_Init_DVB(DVB_EVENT_HANDLE_FUNC dvb_event_handle_func);

void AUTOTEST_Init_Filter_Wrapper();


#endif
