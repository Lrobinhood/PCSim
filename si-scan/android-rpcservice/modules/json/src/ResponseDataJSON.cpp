#include "ResponseDataJSON.h"

#include <cassert>
#include <memory>
#include <json/json.h>

#ifdef RDK_COMPILE
#ifdef assert
#undef assert
#endif
#define assert
#endif

ResponseDataJSON::ArrayJSON::ArrayJSON(Json::Value *json, int size) :
   m_finished(false),
   m_json(json),
   m_size(size)
{
}

void ResponseDataJSON::ArrayJSON::appendBool(bool value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

void ResponseDataJSON::ArrayJSON::appendInt32(int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

void ResponseDataJSON::ArrayJSON::appendUInt32(uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

void ResponseDataJSON::ArrayJSON::appendLong64(int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

void ResponseDataJSON::ArrayJSON::appendULong64(uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

void ResponseDataJSON::ArrayJSON::appendString(const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
   m_json->append(value);
}

ResponseData::Array* ResponseDataJSON::ArrayJSON::appendArray(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_array = std::unique_ptr<ArrayJSON>(new ArrayJSON(&m_json->append(Json::arrayValue), size));
   return m_array.get();
}

ResponseData::Object* ResponseDataJSON::ArrayJSON::appendObject(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_object = std::unique_ptr<ObjectJSON>(new ObjectJSON(&m_json->append(Json::objectValue), size));
   return m_object.get();
}

void ResponseDataJSON::ArrayJSON::finish()
{
   assert(areChildrenFinished());
   assert(m_json->size() == m_size);
   m_finished = true;
}

bool ResponseDataJSON::ArrayJSON::isFinished()
{
   return m_finished;
}

bool ResponseDataJSON::ArrayJSON::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

ResponseDataJSON::ObjectJSON::ObjectJSON(Json::Value *json, int size) :
   m_finished(false),
   m_json(json),
   m_size(size)
{
}

void ResponseDataJSON::ObjectJSON::insertBool(const std::string& key, bool value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

void ResponseDataJSON::ObjectJSON::insertInt32(const std::string& key, int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

void ResponseDataJSON::ObjectJSON::insertUInt32(const std::string& key, uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

void ResponseDataJSON::ObjectJSON::insertLong64(const std::string& key, int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

void ResponseDataJSON::ObjectJSON::insertULong64(const std::string& key, uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

void ResponseDataJSON::ObjectJSON::insertString(const std::string& key, const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = value;
}

ResponseData::Array* ResponseDataJSON::ObjectJSON::insertArray(const std::string& key, int size)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = Json::arrayValue;
   m_array = std::unique_ptr<ArrayJSON>(new ArrayJSON(&(*m_json)[key], size));
   return m_array.get();
}

ResponseData::Object* ResponseDataJSON::ObjectJSON::insertObject(const std::string& key, int size)
{
   assert(!isFinished() && areChildrenFinished());
   (*m_json)[key] = Json::objectValue;
   m_object = std::unique_ptr<ObjectJSON>(new ObjectJSON(&(*m_json)[key], size));
   return m_object.get();
}

void ResponseDataJSON::ObjectJSON::finish()
{
   assert(areChildrenFinished());
   assert(m_json->size() == m_size);
   m_finished = true;
}

bool ResponseDataJSON::ObjectJSON::isFinished()
{
   return m_finished;
}

bool ResponseDataJSON::ObjectJSON::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

ResponseDataJSON::ResponseDataJSON(Json::Value *json) :
   m_finished(false)
{
   m_json = json;
}

void ResponseDataJSON::setBool(bool value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

void ResponseDataJSON::setInt32(int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

void ResponseDataJSON::setUInt32(uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

void ResponseDataJSON::setLong64(int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

void ResponseDataJSON::setULong64(uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

void ResponseDataJSON::setString(const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = value;
}

ResponseData::Array* ResponseDataJSON::setArray(int size)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = Json::arrayValue;
   m_array = std::unique_ptr<ArrayJSON>(new ArrayJSON(m_json, size));
   return m_array.get();
}

ResponseData::Object* ResponseDataJSON::setObject(int size)
{
   assert(!isFinished() && areChildrenFinished());
   *m_json = Json::objectValue;
   m_object = std::unique_ptr<ObjectJSON>(new ObjectJSON(m_json, size));
   return m_object.get();
}

void ResponseDataJSON::finish()
{
   assert(areChildrenFinished());
   m_finished = true;
}

bool ResponseDataJSON::isFinished()
{
   return m_finished;
}

bool ResponseDataJSON::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

