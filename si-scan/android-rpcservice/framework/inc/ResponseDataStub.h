#ifndef GLUE_RESPONSEDATASTUB_H
#define GLUE_RESPONSEDATASTUB_H

#include "ResponseData.h"

#include <cassert>
#include <memory>

/*
 * A stub implementation of ResponseData.
 */
class ResponseDataStub: public ResponseData
{
   public:
   class ObjectStub;
   class ArrayStub : public Array
   {
      public:
      ArrayStub(int size);

      /**
       * @brief Append a bool with the key 'key' and value 'value'.
       */
      void appendBool(bool value);

      /**
       * @brief Append an integer with the key 'key' and value 'value'.
       */
      void appendInt32(int32_t value);

      /**
       * @brief Append an unsigned integer with the key 'key' and value 'value'.
       */
      void appendUInt32(uint32_t value);

      /**
       * @brief Append an long long with the key 'key' and value 'value'.
       */
      void appendLong64(int64_t value);

      /**
       * @brief Append an unsigned long long with the key 'key' and value 'value'.
       */
      void appendULong64(uint64_t value);

      /**
       * @brief Append a string with the key 'key' and value 'value'.
       */
      void appendString(const std::string& value);

      /**
       * @brief Append an array. Until the appended array is finished, this array cannot be finished.
       */
      ResponseData::Array* appendArray(int size);

      /**
       * @brief Append an object. Until the appended object is finished, this array cannot be finished.
       */
      ResponseData::Object* appendObject(int size);

      /**
       * @brief Finish this array. Before calling this method, non-primitive values (arrays and objects) must be finished.
       */
      void finish();

      /**
       * @brief This data is finished.
       */
      bool isFinished();

      private:
      bool areChildrenFinished();
      bool m_finished;
      int m_size;
      std::unique_ptr<ArrayStub> m_array;
      std::unique_ptr<ObjectStub> m_object;
   };

   class ObjectStub : public Object
   {
      public:
      ObjectStub(int size);

      /**
       * @brief Insert a bool with the key 'key' and value 'value'.
       */
      void insertBool(const std::string& key, bool value);

      /**
       * @brief Insert an integer with the key 'key' and value 'value'.
       */
      void insertInt32(const std::string& key, int32_t value);

      /**
       * @brief Insert an unsigned integer with the key 'key' and value 'value'.
       */
      void insertUInt32(const std::string& key, uint32_t value);

      /**
       * @brief Insert an long long with the key 'key' and value 'value'.
       */
      void insertLong64(const std::string& key, int64_t value);

      /**
       * @brief Insert an unsigned long long with the key 'key' and value 'value'.
       */
      void insertULong64(const std::string& key, uint64_t value);

      /**
       * @brief Insert a string with the key 'key' and value 'value'.
       */
      void insertString(const std::string& key, const std::string& value);

      /**
       * @brief Insert an array. Until the inserted array is finished, this object cannot be finished.
       */
      ResponseData::Array* insertArray(const std::string& key, int size);

      /**
       * @brief Insert an object. Until the inserted object is finished, this object cannot be finished.
       */
      ResponseData::Object* insertObject(const std::string& key, int size);

      /**
       * @brief Finish this object. Before calling this method, non-primitive values (arrays and objects) must be finished.
       */
      void finish();

      /**
       * @brief This data is finished.
       */
      bool isFinished();

      private:
      bool areChildrenFinished();
      bool m_finished;
      int m_size;
      std::unique_ptr<ArrayStub> m_array;
      std::unique_ptr<ObjectStub> m_object;
   };

   ResponseDataStub();

   /**
    * @brief Set the data to a bool with value 'value'.
    */
   void setBool(bool value);

   /**
    * @brief Set the data to an integer with value 'value'.
    */
   void setInt32(int32_t value);

   /**
    * @brief Set the data to an unsigned integer with value 'value'.
    */
   void setUInt32(uint32_t value);

   /**
    * @brief Set the data to an long long with value 'value'.
    */
   void setLong64(int64_t value);

   /**
    * @brief Set the data to an unsigned long long with value 'value'.
    */
   void setULong64(uint64_t value);

   /**
    * @brief Set the data to a string with value 'value'.
    */
   void setString(const std::string& value);

   /**
    * @brief Set the data to an array. Until the array is finished, this data cannot be finished.
    */
   ResponseData::Array* setArray(int size);

   /**
    * @brief Set the data to an object. Until the object is finished, this data cannot be finished.
    */
   ResponseData::Object* setObject(int size);

   /**
    * @brief Finish this data. Before calling this method, non-primitive values (arrays and objects) must be finished.
    */
   void finish();

   /**
    * @brief This data is finished.
    */
   bool isFinished();

   private:
   bool areChildrenFinished();
   bool m_finished;
   std::unique_ptr<ArrayStub> m_array;
   std::unique_ptr<ObjectStub> m_object;
};

#endif

