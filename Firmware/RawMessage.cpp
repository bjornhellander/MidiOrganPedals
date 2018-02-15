#include "RawMessage.h"


RawMessage::RawMessage()
{
  size = 0;
}


void RawMessage::Setup(const byte payloadData[], byte payloadSize)
{
  memcpy(data, payloadData, payloadSize);
  size = payloadSize;
}


byte RawMessage::GetSize() const
{
  return size;
}


const byte *RawMessage::GetData() const
{
  return data;
}

