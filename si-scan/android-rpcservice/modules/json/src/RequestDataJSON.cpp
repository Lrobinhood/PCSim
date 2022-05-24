#include "RequestDataJSON.h"

#include <json/json.h>

RequestDataJSON::RequestDataJSON(const Json::Value &data) :
   m_index(0)
{
   m_json = data;
}

bool RequestDataJSON::shiftBool(bool defaultValue)
{
   if (m_json.size() <= m_index || !m_json[m_index].isConvertibleTo(Json::booleanValue))
   {
      m_index++;
      return defaultValue;
   }

   return m_json[m_index++].asBool();
}

int32_t RequestDataJSON::shiftInt32(int32_t defaultValue, int32_t min, int32_t max)
{
   if (m_json.size() <= m_index || !m_json[m_index].isConvertibleTo(Json::intValue))
   {
      m_index++;
      return defaultValue;
   }

   Json::Int64 value = m_json[m_index++].asInt64();
   if (value < min || max < value)
   {
      return defaultValue;
   }

   return value;
}

uint32_t RequestDataJSON::shiftUInt32(uint32_t defaultValue, uint32_t min, uint32_t max)
{
   if (m_json.size() <= m_index || !m_json[m_index].isConvertibleTo(Json::uintValue))
   {
      m_index++;
      return defaultValue;
   }

   Json::Int64 value = m_json[m_index++].asInt64();
   if (value < min || max < value)
   {
      return defaultValue;
   }

   return value;
}

std::string RequestDataJSON::shiftString(std::string defaultValue)
{
   if (m_json.size() <= m_index || !m_json[m_index].isConvertibleTo(Json::stringValue))
   {
      m_index++;
      return defaultValue;
   }

   return m_json[m_index++].asString();
}

Json::Value RequestDataJSON::shiftJsonValue()
{
    if (m_json.size() <= m_index)
    {
        m_index++;

        return Json::nullValue;
    }

    return m_json[m_index++];
}


void RequestDataJSON::setData(const Json::Value &data)
{
   m_index = 0;
   m_json = data;
}
