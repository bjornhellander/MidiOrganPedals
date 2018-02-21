#ifndef __RawMessageExtractor_h
#define __RawMessageExtractor_h


#include "Arduino.h"


class RawMessageExtractor
{
  uint8_t data[255];
  uint8_t size;
  uint8_t i;
  
public:
  RawMessageExtractor(const uint8_t data[], uint8_t size);

  bool Get(uint8_t &value);
  bool Get(uint8_t values[], uint8_t count);

  bool Finish();
};


#endif

