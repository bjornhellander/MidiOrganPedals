#include "RawMessagePacker.h"
#include "ChecksumCalculator.h"


void RawMessagePacker::Pack(const RawMessage &input)
{
  uint8_t id = input.GetId();
  const uint8_t *payloadData = input.GetData();
  uint8_t payloadSize = input.GetSize();
  uint8_t checksum = ChecksumCalculator::CalcChecksum(payloadData, payloadSize);
  
  data[0] = StartByte;
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

