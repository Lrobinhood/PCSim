#ifndef GLUE_RESPONSEDATA_H
#define GLUE_RESPONSEDATA_H

#include <string>
#include <stdint.h>

/*
 * The interface for writing responses. Designed to be compatible with a variety of messaging technologies.
 */
class ResponseData
{
   public:
   class Object;
   class Array
   {
      public:
      Array() {};
      virtual ~Array() {};

      /**
       * @brief Append a bool with the key 'key' and value 'value'.
       */
      virtual void appendBool(bool value) = 0;

      /**
       * @brief Append an integer with the key 'key' and value 'value'.
       */
      virtual void appendInt32(int32_t value) = 0;

      /**
       * @brief Append an unsigned integer with the key 'key' and value 'value'.
       */
      virtual void appendUInt32(uint32_t value) = 0;

      /**
       * @brief Append an long long with the key 'key' and value 'value'.
       */
      virtual void appendLong64(int64_t value) = 0;

      /**
       * @brief Append an unsigned long long with the key 'key' and value 'value'.
       */
      virtual void appendULong64(uint64_t value) = 0;

      /**
       * @brief Append a string with the key 'key' and value 'value'.
       */
      virtual void appendString(const std::string& value) = 0;

      /**
       * @brief Append an array. Until the appended array is finished, this array cannot be finished.
       */
      virtual Array* appendArray(int size) = 0;

      /**
       * @brief Append an object. Until the appended object is finished, this array cannot be finished.
       */
      virtual Object* appendObject(int size) = 0;

      /**
       * @brief Finish this array. Before calling this method, non-primitive values (arrays and objects) must be finished.
       */
      virtual void finish() = 0;

      /**
       * @brief This data is finished.
       */
      virtual bool isFinished() = 0;

      private:
      Array(Object const&);
      Array& operator=(Array const&);
   };

   class Object
   {
      public:
      Object() {};
      virtual ~Object() {};

      /**
       * @brief Insert a bool with the key 'key' and value 'value'.
       */
      virtual void insertBool(const std::string& key, bool value) = 0;

      /**
       * @brief Insert an integer with the key 'key' and value 'value'.
       */
      virtual void insertInt32(const std::string& key, int32_t value) = 0;

      /**
       * @brief Insert an unsigned integer with the key 'key' and value 'value'.
       */
      virtual void insertUInt32(const std::string& key, uint32_t value) = 0;

      /**
       * @brief Insert an long long with the key 'key' and value 'value'.
       */
      virtual void insertLong64(const std::string& key, int64_t value) = 0;

      /**
       * @brief Insert an unsigned long long with the key 'key' and value 'value'.
       */
      virtual void insertULong64(const std::string& key, uint64_t value) = 0;

      /**
       * @brief Insert a string with the key 'key' and value 'value'.
       */
      virtual void insertString(const std::string& key, const std::string& value) = 0;

      /**
       * @brief Insert an array. Until the inserted array is finished, this object cannot be finished.
       */
      virtual Array* insertArray(const std::string& key, int size) = 0;

      /**
       * @brief Insert an object. Until the inserted object is finished, this object cannot be finished.
       */
      virtual Object* insertObject(const std::string& key, int size) = 0;

      /**
       * @brief Finish this object. Before calling this method, non-primitive values (arrays and objects) must be finished.
       */
      virtual void finish() = 0;

      /**
       * @brief This data is finished.
       */
      virtual bool isFinished() = 0;

      private:
      Object(Object const&);
      Object& operator=(Object const&);
   };

   ResponseData() {};
   virtual ~ResponseData() {};

   /**
    * @brief Set the data to a bool with value 'value'.
    */
   virtual void setBool(bool value) = 0;

   /**
    * @brief Set the data to an integer with value 'value'.
    */
   virtual void setInt32(int32_t value) = 0;

   /**
    * @brief Set the data to an unsigned integer with value 'value'.
    */
   virtual void setUInt32(uint32_t value) = 0;

   /**
    * @brief Set the data to an long long with value 'value'.
    */
   virtual void setLong64(int64_t value) = 0;

   /**
    * @brief Set the data to an unsigned long long with value 'value'.
    */
   virtual void setULong64(uint64_t value) = 0;

   /**
    * @brief Set the data to a string with value 'value'.
    */
   virtual void setString(const std::string& value) = 0;

   /**
    * @brief Set the data to an array. Until the array is finished, this data cannot be finished.
    */
   virtual Array* setArray(int size) = 0;

   /**
    * @brief Set the data to an object. Until the object is finished, this data cannot be finished.
    */
   virtual Object* setObject(int size) = 0;

   /**
    * @brief Finish this data. Before calling this method, non-primitive values (arrays and objects) must be finished.
    */
   virtual void finish() = 0;

   /**
    * @brief This data is finished.
    */
   virtual bool isFinished() = 0;

   private:
   ResponseData(ResponseData const&);
   ResponseData& operator=(ResponseData const&);
};

#endif

