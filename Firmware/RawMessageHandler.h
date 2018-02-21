#ifndef __RawMessageHandler_h
#define __RawMessageHandler_h


#include "Arduino.h"


class RawMessageHandler
{
public:
  static const uint8_t StartByte = 0xFF;

protected:
  uint8_t CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize);
};


#endif

