#include "RequestDataStub.h"

RequestDataStub::RequestDataStub()
{
}

bool RequestDataStub::shiftBool(bool defaultValue)
{
   return defaultValue;
}

int32_t RequestDataStub::shiftInt32(int32_t defaultValue, int32_t min, int32_t max)
{
   return defaultValue;
}

uint32_t RequestDataStub::shiftUInt32(uint32_t defaultValue, uint32_t min, uint32_t max)
{
   return defaultValue;
}

std::string RequestDataStub::shiftString(std::string defaultValue)
{
   return defaultValue;
}

