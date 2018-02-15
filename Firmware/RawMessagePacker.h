#ifndef __RawMessagePacker_h
#define __RawMessagePacker_h


#include "Arduino.h"
#include "RawMessage.h"


class RawMessagePacker
{
  uint8_t data[255+4];
  uint16_t size;
  
public:
  void Pack(uint8_t id, const RawMessage &input);
  
  uint16_t GetSize() const;
  const uint8_t *GetData() const;
  
private:
  uint8_t CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize);
};


#endif

