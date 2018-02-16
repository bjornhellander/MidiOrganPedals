#include "RawMessage.h"


RawMessage::RawMessage()
{
  size = 0;
}


void RawMessage::Setup(byte id, const byte payloadData[], byte payloadSize)
{
  this->id = id;
  memcpy(data, payloadData, payloadSize);
  size = payloadSize;
}


byte RawMessage::GetId() const
{
  return id;
}


byte RawMessage::GetSize() const
{
  return size;
}


const byte *RawMessage::GetData() const
{
  return data;
}

