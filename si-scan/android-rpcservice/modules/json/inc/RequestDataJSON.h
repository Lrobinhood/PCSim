#ifndef REQUESTDATAJSON_H
#define REQUESTDATAJSON_H

#include "RequestData.h"

#include <json/json.h>

/*
 * A JSON implementation of RequestData. Better implementations are possible.
 */
class RequestDataJSON: public RequestData
{
    public:
        RequestDataJSON() {}
        RequestDataJSON(const Json::Value &data);
        bool shiftBool(bool defaultValue);
        int32_t shiftInt32(int32_t defaultValue, int32_t min = INT32_MIN, int32_t max = INT32_MAX);
        uint32_t shiftUInt32(uint32_t defaultValue, uint32_t min = 0, uint32_t max = UINT32_MAX);
        std::string shiftString(std::string defaultValue);
        void setData(const Json::Value &data);
        void resetDataIdx() {m_index = 0;}

        // Test
        Json::Value shiftJsonValue();
    private:
        Json::Value m_json;
        unsigned m_index;
};

#endif // REQUESTDATAJSON_H

