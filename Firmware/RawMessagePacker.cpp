#include "RawMessagePacker.h"


RawMessagePacker::RawMessagePacker(uint8_t id)
{
  this->size = 0;
  this->id = id;
}


void RawMessagePacker::Add(bool value)
{
  AddImpl(value ? 1 : 0);
}


void RawMessagePacker::Add(uint16_t value)
{
  AddImpl((uint8_t)value);
  AddImpl((uint8_t)(value >> 8));
}


void RawMessagePacker::Add(uint32_t value)
{
  AddImpl((uint8_t)value);
  AddImpl((uint8_t)(value >> 8));
  AddImpl((uint8_t)(value >> 16));
  AddImpl((uint8_t)(value >> 24));
}


void RawMessagePacker::AddImpl(uint8_t value)
{
  if (size < sizeof(data)) {
    data[size++] = value;
  }
  else {
    while (true);
  }
}


void RawMessagePacker::CopyTo(RawMessage &result)
{
  result.Setup(id, data, size);
}

