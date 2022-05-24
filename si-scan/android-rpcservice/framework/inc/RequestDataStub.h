#ifndef GLUE_REQUESTDATASTUB_H
#define GLUE_REQUESTDATASTUB_H

#include "RequestData.h"

/*
 * A stub implementation that always returns the default value. Useful for invoking functions internally that have a
 * full set of valid default values (e.g. signal callbacks).
 *
 * The interface for reading requests. The interface described here is only concerned with reading arguments, it is for
 * implementations to identify the requested function and invoke it. Arguments are identified by their position (i.e.
 * are positional arguments) and are read at most once from first to last. This is compatible with sub-protocols that
 * use named arguments (e.g. use names indicating position).
 */
class RequestDataStub: public RequestData
{
   public:
   RequestDataStub();

   /**
    * @brief Removes the first element from the list of positional arguments for this request and if that element is
    *    convetible to a boolean, returns that element, otherwise returns the defaultValue.
    * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a bool.
    */
   bool shiftBool(bool defaultValue);

   /**
    * @brief Removes the first element from the list of positional arguments for this request and if that element is
    *    convetible to a number, returns that element, otherwise returns the defaultValue.
    * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a number.
    * @param min If the value is less than min, defaultValue is returned.
    * @param max If the value is greater than max, defaultValue is returned.
    */
   int32_t shiftInt32(int32_t defaultValue, int32_t min = INT32_MIN, int32_t max = INT32_MAX);

   /**
    * @brief Removes the first element from the list of positional arguments for this request and if that element is
    *    convetible to a 32 bit unsigned integer, returns that element, otherwise returns the defaultValue.
    * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a 32 bit unsigned integer.
    * @param min If the value is less than min, defaultValue is returned.
    * @param max If the value is greater than max, defaultValue is returned.
    */
   uint32_t shiftUInt32(uint32_t defaultValue, uint32_t min = 0, uint32_t max = UINT32_MAX);

   /**
    * @brief Removes the first element from the list of positional arguments for this request and if that element is
    *    convetible to a string, returns that element, otherwise returns the defaultValue.
    * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a string.
    */
   std::string shiftString(std::string defaultValue);
};

#endif

