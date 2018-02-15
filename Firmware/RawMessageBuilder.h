#ifndef __RawMessageBuilder_h
#define __RawMessageBuilder_h


#include "Arduino.h"
#include "RawMessage.h"


class RawMessageBuilder
{
  uint8_t data[255];
  uint32_t size;
  
public:
  RawMessageBuilder();

  void Add(bool value);
  void Add(uint8_t value);
  void Add(uint8_t value[], uint8_t count);
  void Add(uint16_t value);
  void Add(uint32_t value);
  void Add(char value[], uint8_t count);

  void CopyTo(RawMessage &result);

private:
  void AddImpl(uint8_t value);
};


#endif

