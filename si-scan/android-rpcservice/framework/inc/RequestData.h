#ifndef GLUE_REQUESTDATA_H
#define GLUE_REQUESTDATA_H

#include <string>
#include <stdint.h>

/*
 * The interface for reading requests. The interface described here is only concerned with reading arguments, it is for
 * implementations to identify the requested function and invoke it. Arguments are identified by their position (i.e.
 * are positional arguments) and are read at most once from first to last. This is compatible with sub-protocols that
 * use named arguments (e.g. use names indicating position).
 */
class RequestData
{
    public:
        RequestData() {};
        virtual ~RequestData() {};

        /**
         * @brief Removes the first element from the list of positional arguments for this request and if that element is
         *    convetible to a boolean, returns that element, otherwise returns the defaultValue.
         * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a bool.
         */
        virtual bool shiftBool(bool defaultValue) = 0;

        /**
         * @brief Removes the first element from the list of positional arguments for this request and if that element is
         *    convetible to a 32 bit integer, returns that element, otherwise returns the defaultValue.
         * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a 32 bit integer.
         * @param min If the value is less than min, defaultValue is returned.
         * @param max If the value is greater than max, defaultValue is returned.
         */
        virtual int32_t shiftInt32(int32_t defaultValue, int32_t min = INT32_MIN, int32_t max = INT32_MAX) = 0;

        /**
         * @brief Removes the first element from the list of positional arguments for this request and if that element is
         *    convetible to a 32 bit unsigned integer, returns that element, otherwise returns the defaultValue.
         * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a 32 bit unsigned integer.
         * @param min If the value is less than min, defaultValue is returned.
         * @param max If the value is greater than max, defaultValue is returned.
         */
        virtual uint32_t shiftUInt32(uint32_t defaultValue, uint32_t min = 0, uint32_t max = UINT32_MAX) = 0;

        /**
         * @brief Removes the first element from the list of positional arguments for this request and if that element is
         *    convetible to a string, returns that element, otherwise returns the defaultValue.
         * @param defaultValue A value that is returned if the first element is non-existent or not convertible to a string.
         */
        virtual std::string shiftString(std::string defaultValue) = 0;

        virtual void resetDataIdx() {};

    private:
        RequestData(RequestData const&);
        RequestData& operator=(RequestData const&);
};

#endif

