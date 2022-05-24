#ifndef DVBSINTERFACE_H
#define DVBSINTERFACE_H

#include "Glue.h"
#include "RequestData.h"
#include "ResponseData.h"

#include <iostream>

/**
 * @ingroup metaapi
 * @defgroup dvbsmetaapi DVB-S Meta-API
 * Dvb
 */

class DvbsInterface : public Glue::Interface
{
public:
    static DvbsInterface& instance()
    {
        static DvbsInterface instance;
        return instance;
    }

    bool getStatus(RequestData* request, ResponseData* response);
    bool scanControl(RequestData* request, ResponseData* response);


private:
    DvbsInterface();
    DvbsInterface(DvbsInterface const&);
    DvbsInterface& operator=(DvbsInterface const&);

    static void eventHandler(unsigned int code,
                                    const void* data,
                                    unsigned int data_size);

    bool scanControl_M7(RequestData* request, ResponseData* response);
    bool startSearch_M7(RequestData* request, ResponseData* response);
    bool finishSearch_M7(RequestData* request, ResponseData* response);
    
    static void eventHandler_M7(unsigned int code,
                                const void* data,
                                unsigned int data_size);

 };

#endif // DVBSINTERFACE_H
