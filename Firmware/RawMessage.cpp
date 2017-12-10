#include "RawMessage.h"


#define START_BYTE (0xFF)


RawMessage::RawMessage()
{
  size = 0;
}


void RawMessage::Setup(byte id, const byte payloadData[], byte payloadSize)
{
  byte checksum = CalcChecksum(payloadData, payloadSize);
  
  data[0] = START_BYTE;
  data[1] = id;
  data[2] = payloadSize;
  data[3] = checksum;
  memcpy(data+4, payloadData, payloadSize);
  size = 4 + payloadSize;
}


unsigned int RawMessage::GetSize() const
{
  return size;
}


const byte *RawMessage::GetData() const
{
  return data;
}


byte RawMessage::CalcChecksum(const byte payloadData[], byte payloadSize)
{
  byte result = 0;

  for (byte i = 0; i < payloadSize; i++) {
    result = result ^ payloadData[i]; // TODO: Make this better at detecting errors
  }

  return result;
}

