#include "RawMessagePacker.h"


#define START_BYTE (0xFF)


void RawMessagePacker::Pack(const RawMessage &input)
{
  uint8_t id = input.GetId();
  const uint8_t *payloadData = input.GetData();
  uint8_t payloadSize = input.GetSize();
  uint8_t checksum = CalcChecksum(payloadData, payloadSize);
  
  data[0] = START_BYTE;
  data[1] = id;
  data[2] = payloadSize;
  data[3] = checksum;
  memcpy(data+4, payloadData, payloadSize);
  size = 4 + payloadSize;
}


uint16_t RawMessagePacker::GetSize() const
{
  return size;
}


const uint8_t *RawMessagePacker::GetData() const
{
  return data;
}


byte RawMessagePacker::CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize)
{
  uint8_t result = 0;

  for (uint8_t i = 0; i < payloadSize; i++) {
    result = result ^ payloadData[i]; // TODO: Make this better at detecting errors
  }

  return result;
}

