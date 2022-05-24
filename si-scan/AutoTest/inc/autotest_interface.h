#pragma once


#ifdef __cplusplus

extern "C" void autotest_interface_reginterface();
extern "C" void autotest_interface_notify(unsigned int event, void *event_data, unsigned int data_size);

extern "C" void autotest_interface_request(char *resource, char *json);

#else

void autotest_interface_reginterface();
void autotest_interface_notify(unsigned int event, void *event_data, unsigned int data_size);
void autotest_interface_request(char *resource, char *json);

#endif

