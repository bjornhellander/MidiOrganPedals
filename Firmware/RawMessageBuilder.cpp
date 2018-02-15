#include "RawMessageBuilder.h"


RawMessageBuilder::RawMessageBuilder(uint8_t id)
{
  this->size = 0;
  this->id = id;
}


void RawMessageBuilder::Add(bool value)
{
  AddImpl(value ? 1 : 0);
}


void RawMessageBuilder::Add(uint8_t value)
{
  AddImpl(value);
}


void RawMessageBuilder::Add(uint8_t value[], uint8_t count)
{
  for (uint8_t i = 0; i < count; i++) {
    AddImpl(value[i]);
  }
}


void RawMessageBuilder::Add(uint16_t value)
{
  AddImpl((uint8_t)value);
  AddImpl((uint8_t)(value >> 8));
}


void RawMessageBuilder::Add(uint32_t value)
{
  AddImpl((uint8_t)value);
  AddImpl((uint8_t)(value >> 8));
  AddImpl((uint8_t)(value >> 16));
  AddImpl((uint8_t)(value >> 24));
}


void RawMessageBuilder::Add(char value[], uint8_t count)
{
  auto length = strlen(value);

  for (uint8_t i = 0; i < count; i++) {
    char ch = i < length ? value[i] : '\0';
    AddImpl((uint8_t)ch);
  }
}


void RawMessageBuilder::AddImpl(uint8_t value)
{
  if (size < sizeof(data)) {
    data[size++] = value;
  }
  else {
    while (true);
  }
}


void RawMessageBuilder::CopyTo(RawMessage &result)
{
  result.Setup(id, data, size);
}

