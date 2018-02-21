#ifndef __ConfigurationManager_h
#define __ConfigurationManager_h


#include "Arduino.h"
#include "MidiPort.h"


class ConfigurationManager
{
public:
  static const uint8_t MaxPedals = 32;

private:
  uint8_t firstNote;
  uint8_t velocity;
  uint8_t debouncingTime;
  uint8_t pedalPins[MaxPedals];

public:
  void Setup(); // Reads from EEPROM
  void Setup(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount);

  uint8_t GetFirstNote();
  uint8_t GetVelocity();
  uint8_t GetDebouncingTime();
  uint32_t GetPedalPin(uint8_t i);

private:
  void SetupImpl(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount);
  void ReadValues();
  void WriteValues();
};


#endif

