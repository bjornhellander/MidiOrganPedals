#ifndef __ConfigurationMessageBase_h
#define __ConfigurationMessageBase_h


#include "Arduino.h"
#include "RawMessage.h"


class ConfigurationMessageBase
{
public:
  uint8_t FirstNote;
  uint8_t Velocity;
  uint8_t DebouncingTime;
  uint8_t PedalPins[32];
};


#endif

