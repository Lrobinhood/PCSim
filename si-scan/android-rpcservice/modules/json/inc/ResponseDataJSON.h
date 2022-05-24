#ifndef RESPONSEDATAJSON_H
#define RESPONSEDATAJSON_H

#include "ResponseData.h"

#include <cassert>
#include <memory>
#include <json/json.h>

/*
 * A JSON implementation of ResponseData. Better implementations are possible, especially with different libraries.
 */
class ResponseDataJSON: public ResponseData
{
   public:
   class ObjectJSON;
   class ArrayJSON : public Array
   {
      public:
      ArrayJSON(Json::Value *json, int size);
      void appendBool(bool value);
      void appendInt32(int32_t value);
      void appendUInt32(uint32_t value);
      void appendLong64(int64_t value);
      void appendULong64(uint64_t value);
      void appendString(const std::string& value);
      ResponseData::Array* appendArray(int size);
      ResponseData::Object* appendObject(int size);
      void finish();
      bool isFinished();

      private:
      bool areChildrenFinished();
      bool m_finished;
      Json::Value *m_json;
      unsigned m_size;
      std::unique_ptr<ArrayJSON> m_array;
      std::unique_ptr<ObjectJSON> m_object;
   };

   class ObjectJSON : public Object
   {
      public:
      ObjectJSON(Json::Value *json, int size);
      void insertBool(const std::string& key, bool value);
      void insertInt32(const std::string& key, int32_t value);
      void insertUInt32(const std::string& key, uint32_t value);
      void insertLong64(const std::string& key, int64_t value);
      void insertULong64(const std::string& key, uint64_t value);
      void insertString(const std::string& key, const std::string& value);
      ResponseData::Array* insertArray(const std::string& key, int size);
      ResponseData::Object* insertObject(const std::string& key, int size);
      void finish();
      bool isFinished();

      private:
      bool areChildrenFinished();
      bool m_finished;
      Json::Value *m_json;
      unsigned m_size;
      std::unique_ptr<ArrayJSON> m_array;
      std::unique_ptr<ObjectJSON> m_object;
   };

   ResponseDataJSON(Json::Value *json);
   void setBool(bool value);
   void setInt32(int32_t value);
   void setUInt32(uint32_t value);
   void setLong64(int64_t value);
   void setULong64(uint64_t value);
   void setString(const std::string& value);
   ResponseData::Array* setArray(int size);
   ResponseData::Object* setObject(int size);
   void finish();
   bool isFinished();

   private:
   bool areChildrenFinished();
   bool m_finished;
   Json::Value *m_json;
   std::unique_ptr<ArrayJSON> m_array;
   std::unique_ptr<ObjectJSON> m_object;
};

#endif // RESPONSEDATAJSON_H

