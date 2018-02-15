#ifndef __ConfigurationStatusMessage_h
#define __ConfigurationStatusMessage_h


#include "Arduino.h"
#include "RawMessage.h"


class ConfigurationStatusMessage
{
public:
  static const uint8_t Id = 0x02;

private:
  uint8_t firstNote;
  uint8_t velocity;
  uint8_t debouncingTime;
  uint8_t pedalPins[32];
  
public:
  ConfigurationStatusMessage(
    uint8_t firstNote,
    uint8_t velocity,
    uint8_t debouncingTime,
    uint8_t pedalPins[32],
    uint8_t pedalPinCount);

  void Pack(RawMessage &result);
};


#endif

