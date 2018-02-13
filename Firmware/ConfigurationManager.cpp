#include "ConfigurationManager.h"
#include "Misc.h"


// These should be retrieved from EEPROM
static const uint8_t FirstNote = 30;
static const uint8_t Velocity = 60;
static const uint8_t DebouncingTime = 0;
static const uint8_t PedalPins[] = {
  10, 11, 12, 13
};


void ConfigurationManager::Setup()
{
  SetupImpl(FirstNote, Velocity, DebouncingTime, PedalPins, ARRAY_SIZE(PedalPins));
}


void ConfigurationManager::Setup(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  SetupImpl(firstNote, velocity, debouncingTime, pedalPins, pedalPinCount);
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

