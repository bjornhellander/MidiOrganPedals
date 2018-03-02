#ifndef __ChecksumCalculator_h
#define __ChecksumCalculator_h


#include "Arduino.h"


class ChecksumCalculator
{
public:
  static uint8_t CalcChecksum(const void *data, uint8_t size);
  static uint8_t ModifyChecksum(uint8_t checksum, const void *data, uint8_t size);
};


#endif

