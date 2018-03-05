#include "ConfigurationManager.h"
#include "ChecksumCalculator.h"
#include "Misc.h"
#include <EEPROM.h>


#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#ifdef TEENSYDUINO
static int validPins[] = { 0, 1, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 38, 39, 40, 41, 42, 43, 44, 45 };
#endif
#ifdef MATTAIRTECH
#error Add valid pins for MattairTech board
#endif
#endif


void ConfigurationManager::ReadValues()
{
  static const uint16_t size = sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  uint8_t checksum;
  EEPROM.get(0, checksum);
  EEPROM.get(1, firstNote);
  EEPROM.get(2, velocity);
  EEPROM.get(3, debouncingTime);
  EEPROM.get(4, pedalPins);

  uint8_t expectedChecksum = ChecksumCalculator::CalcChecksum(&firstNote, sizeof(firstNote));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &velocity, sizeof(velocity));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &debouncingTime, sizeof(debouncingTime));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &pedalPins, sizeof(pedalPins));

  if (checksum != expectedChecksum) {
    memset(&firstNote, 0, sizeof(firstNote));
    memset(&velocity, 0, sizeof(velocity));
    memset(&debouncingTime, 0, sizeof(debouncingTime));
    memset(&pedalPins, UNUSED_PIN_NUMBER, sizeof(pedalPins));
  }
}


void ConfigurationManager::Setup()
{
  ReadValues();
  SetupImpl(firstNote, velocity, debouncingTime, pedalPins, ARRAY_SIZE(pedalPins));
  CheckIfOk();
}


void ConfigurationManager::WriteValues()
{
  static const uint16_t size = sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  uint8_t checksum = ChecksumCalculator::CalcChecksum(&firstNote, sizeof(firstNote));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &velocity, sizeof(velocity));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &debouncingTime, sizeof(debouncingTime));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &pedalPins, sizeof(pedalPins));

  EEPROM.put(0, checksum);
  EEPROM.put(1, firstNote);
  EEPROM.put(2, velocity);
  EEPROM.put(3, debouncingTime);
  EEPROM.put(4, pedalPins);
}


void ConfigurationManager::Setup(uint8_t firstNote, uint8_t velocity, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  SetupImpl(firstNote, velocity, debouncingTime, pedalPins, pedalPinCount);
  WriteValues();
  CheckIfOk();
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
      this->pedalPins[i] = UNUSED_PIN_NUMBER;
    }
  }
}


void ConfigurationManager::CheckIfOk()
{
  auto firstNoteIsOk = IsValidPin(firstNote);
  auto velocityIsOk = true;
  auto debouncingTimeIsOk = true;

  auto pedalPinsIsOk = true;
  for (uint8_t i = 0; i < ARRAY_SIZE(this->pedalPins); i++) {
    auto pin = pedalPins[i];
    auto pedalPinIsOk = pin == UNUSED_PIN_NUMBER ? true : IsValidPin(pin);
    pedalPinsIsOk = pedalPinsIsOk && pedalPinIsOk;
  }

  isOk = firstNoteIsOk && velocityIsOk && debouncingTimeIsOk && pedalPinsIsOk;
}


bool ConfigurationManager::IsValidPin(int pin)
{
  for (int i = 0; i < ARRAY_SIZE(validPins); i++) {
    if (validPins[i] == pin) {
      return true;
    }
  }

  return false;
}


bool ConfigurationManager::IsOk()
{
  return isOk;
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
    return UNUSED_PIN_NUMBER;
  }

  return pedalPins[i];
}

