#include "ResponseDataStub.h"

#include <cassert>
#include <memory>

ResponseDataStub::ArrayStub::ArrayStub(int size) :
   m_finished(false),
   m_size(size)
{
}

void ResponseDataStub::ArrayStub::appendBool(bool value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ArrayStub::appendInt32(int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ArrayStub::appendUInt32(uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ArrayStub::appendLong64(int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ArrayStub::appendULong64(uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ArrayStub::appendString(const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

ResponseData::Array* ResponseDataStub::ArrayStub::appendArray(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
   m_array = std::unique_ptr<ArrayStub>(new ArrayStub(size));
   return m_array.get();
}

ResponseData::Object* ResponseDataStub::ArrayStub::appendObject(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
   m_object = std::unique_ptr<ObjectStub>(new ObjectStub(size));
   return m_object.get();
}

void ResponseDataStub::ArrayStub::finish()
{
   assert(areChildrenFinished());
   assert(m_size == 0);
   m_finished = true;
}

bool ResponseDataStub::ArrayStub::isFinished()
{
   return m_finished;
}

bool ResponseDataStub::ArrayStub::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

ResponseDataStub::ObjectStub::ObjectStub(int size) :
   m_finished(false),
   m_size(size)
{
}

void ResponseDataStub::ObjectStub::insertBool(const std::string& key, bool value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ObjectStub::insertInt32(const std::string& key, int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ObjectStub::insertUInt32(const std::string& key, uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ObjectStub::insertLong64(const std::string& key, int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ObjectStub::insertULong64(const std::string& key, uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

void ResponseDataStub::ObjectStub::insertString(const std::string& key, const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
}

ResponseData::Array* ResponseDataStub::ObjectStub::insertArray(const std::string& key, int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
   m_array = std::unique_ptr<ArrayStub>(new ArrayStub(size));
   return m_array.get();
}

ResponseData::Object* ResponseDataStub::ObjectStub::insertObject(const std::string& key, int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_size--;
   m_object = std::unique_ptr<ObjectStub>(new ObjectStub(size));
   return m_object.get();
}

void ResponseDataStub::ObjectStub::finish()
{
   assert(areChildrenFinished());
   assert(m_size == 0);
   m_finished = true;
}

bool ResponseDataStub::ObjectStub::isFinished()
{
   return m_finished;
}

bool ResponseDataStub::ObjectStub::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

ResponseDataStub::ResponseDataStub() :
   m_finished(false)
{
}

void ResponseDataStub::setBool(bool value)
{
   assert(!isFinished() && areChildrenFinished());
}

void ResponseDataStub::setInt32(int32_t value)
{
   assert(!isFinished() && areChildrenFinished());
}

void ResponseDataStub::setUInt32(uint32_t value)
{
   assert(!isFinished() && areChildrenFinished());
}

void ResponseDataStub::setLong64(int64_t value)
{
   assert(!isFinished() && areChildrenFinished());
}

void ResponseDataStub::setULong64(uint64_t value)
{
   assert(!isFinished() && areChildrenFinished());
}

void ResponseDataStub::setString(const std::string& value)
{
   assert(!isFinished() && areChildrenFinished());
}

ResponseData::Array* ResponseDataStub::setArray(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_array = std::unique_ptr<ArrayStub>(new ArrayStub(size));
   return m_array.get();
}

ResponseData::Object* ResponseDataStub::setObject(int size)
{
   assert(!isFinished() && areChildrenFinished());
   m_object = std::unique_ptr<ObjectStub>(new ObjectStub(size));
   return m_object.get();
}

void ResponseDataStub::finish()
{
   assert(areChildrenFinished());
   m_finished = true;
}

bool ResponseDataStub::isFinished()
{
   return m_finished;
}

bool ResponseDataStub::areChildrenFinished()
{
   return (!m_array.get() || m_array->isFinished()) && (!m_object.get() || m_object->isFinished());
}

