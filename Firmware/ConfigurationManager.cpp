#include "ConfigurationManager.h"
#include "Misc.h"
#include <EEPROM.h>


void ConfigurationManager::ReadValues()
{
  static const uint16_t size = sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  EEPROM.get(0, firstNote);
  EEPROM.get(1, velocity);
  EEPROM.get(2, debouncingTime);
  EEPROM.get(3, pedalPins);
}


void ConfigurationManager::Setup()
{
  ReadValues();
  SetupImpl(firstNote, velocity, debouncingTime, pedalPins, ARRAY_SIZE(pedalPins));
}


void ConfigurationManager::WriteValues()
{
  static const uint16_t size = sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  EEPROM.put(0, firstNote);
  EEPROM.put(1, velocity);
  EEPROM.put(2, debouncingTime);
  EEPROM.put(3, pedalPins);
}


void ConfigurationManager::Setup(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  SetupImpl(firstNote, velocity, debouncingTime, pedalPins, pedalPinCount);
  WriteValues();
}


void ConfigurationManager::SetupImpl(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  this->firstNote = firstNote;
  this->velocity = velocity;
  this->debouncingTime = debouncingTime;

  for (uint8_t i = 0; i < ARRAY_SIZE(this->pedalPins); i++) {
    if (i < pedalPinCount) {
      this->pedalPins[i] = pedalPins[i];
    }
    else {
      this->pedalPins[i] = 0;
    }
  }
}


uint8_t ConfigurationManager::GetFirstNote()
{
  return firstNote;
}


uint8_t ConfigurationManager::GetVelocity()
{
  return velocity;
}


uint8_t ConfigurationManager::GetDebouncingTime()
{
  return debouncingTime;
}


uint32_t ConfigurationManager::GetPedalPin(uint8_t i)
{
  if (i >= ARRAY_SIZE(pedalPins)){
    return 0;
  }

  return pedalPins[i];
}

