#ifndef __ConfigurationManager_h
#define __ConfigurationManager_h


#include "Arduino.h"
#include "MidiPort.h"


class ConfigurationManager
{
public:
  static const uint8_t MaxPedals = 32;

private:
  bool isOk;
  uint8_t version;
  uint8_t checksum;
  uint8_t firstNote;
  uint8_t velocity;
  uint8_t debouncingTime;
  uint8_t pedalPins[MaxPedals];

public:
  void Setup(); // Reads from EEPROM
  void Setup(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount);

  bool IsOk();
  uint8_t GetFirstNote();
  uint8_t GetVelocity();
  uint8_t GetDebouncingTime();
  uint32_t GetPedalPin(uint8_t i);

private:
  void SetupImpl(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount);
  void ReadValues();
  void WriteValues();
  void CheckIfOk();
  bool IsValidPin(int pin);
  bool IsUnusedPin(int pin, uint8_t pins[], int size);
  bool IsValidNote(int note);
};


#endif

