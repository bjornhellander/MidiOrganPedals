#ifndef __ChecksumCalculator_h
#define __ChecksumCalculator_h


#include "Arduino.h"


class ChecksumCalculator
{
public:
  static uint8_t CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize);
};


#endif

