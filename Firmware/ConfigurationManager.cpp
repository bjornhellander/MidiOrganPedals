#include "ConfigurationManager.h"
#include "ChecksumCalculator.h"
#include "Misc.h"
#include <EEPROM.h>


#define EXPECTED_VERSION 0
#define DEFAULT_FIRST_NOTE 20
#define DEFAULT_VELOCITY 70
#define DEFAULT_DEBOUNCING_TIME 0


#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#ifdef TEENSYDUINO
// NOTE: USB pins are not easily accessible on the board. They are not in this list.
static uint8_t validPins[] = { 0, 1, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 }; // RX=2, TX=3, LED=6
#endif
#ifdef MATTAIRTECH
#error Add valid pins for MattairTech board
#endif
#endif

#ifdef ARDUINO_AVR_UNO
static uint8_t validPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0, A1, A2, A3, A4, A5 }; // RX=0, TX=1, LED=13
#endif


void ConfigurationManager::ReadValues()
{
  static const uint16_t size = sizeof(version) + sizeof(checksum) + sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  EEPROM.get(0, version);
  EEPROM.get(1, checksum);
  EEPROM.get(2, firstNote);
  EEPROM.get(3, velocity);
  EEPROM.get(4, debouncingTime);
  EEPROM.get(5, pedalPins);

  uint8_t expectedChecksum = ChecksumCalculator::CalcChecksum(&firstNote, sizeof(firstNote));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &velocity, sizeof(velocity));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &debouncingTime, sizeof(debouncingTime));
  expectedChecksum = ChecksumCalculator::ModifyChecksum(expectedChecksum, &pedalPins, sizeof(pedalPins));

  if (checksum != expectedChecksum || version != EXPECTED_VERSION) {
    firstNote = DEFAULT_FIRST_NOTE;
    velocity = DEFAULT_VELOCITY;
    debouncingTime = DEFAULT_DEBOUNCING_TIME;
    for (uint8_t i = 0; i < ARRAY_SIZE(pedalPins); i++) {
      uint8_t pin = i < ARRAY_SIZE(validPins) ? validPins[i] : UNUSED_PIN_NUMBER;
      pedalPins[i] = pin;
    }
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
  static const uint16_t size = sizeof(version) + sizeof(checksum) + sizeof(firstNote) + sizeof(velocity) + sizeof(debouncingTime) + sizeof(pedalPins);

  if (EEPROM.length() < size)
  {
    return;
  }

  version = EXPECTED_VERSION;

  checksum = ChecksumCalculator::CalcChecksum(&firstNote, sizeof(firstNote));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &velocity, sizeof(velocity));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &debouncingTime, sizeof(debouncingTime));
  checksum = ChecksumCalculator::ModifyChecksum(checksum, &pedalPins, sizeof(pedalPins));

  EEPROM.put(0, version);
  EEPROM.put(1, checksum);
  EEPROM.put(2, firstNote);
  EEPROM.put(3, velocity);
  EEPROM.put(4, debouncingTime);
  EEPROM.put(5, pedalPins);
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
  auto firstNoteIsOk = IsValidNote(firstNote);
  auto velocityIsOk = true;
  auto debouncingTimeIsOk = true;

  auto pedalPinsAreOk = true;
  int noteDiff = 0;
  for (uint8_t i = 0; i < ARRAY_SIZE(this->pedalPins); i++) {
    auto pin = pedalPins[i];
    if (pin != UNUSED_PIN_NUMBER) {
      auto pedalPinIsOk = IsValidPin(pin);
      auto pedalPinIsUnused = IsUnusedPin(pin, pedalPins, i);
      auto noteIsOk = IsValidNote(firstNote + noteDiff);
      pedalPinsAreOk = pedalPinsAreOk && pedalPinIsOk && pedalPinIsUnused && noteIsOk;

      noteDiff++;
    }
  }

  isOk = firstNoteIsOk && velocityIsOk && debouncingTimeIsOk && pedalPinsAreOk;
}


bool ConfigurationManager::IsValidPin(int pin)
{
  for (uint8_t i = 0; i < ARRAY_SIZE(validPins); i++) {
    if (validPins[i] == pin) {
      return true;
    }
  }

  return false;
}


bool ConfigurationManager::IsUnusedPin(int pin, uint8_t pins[], int size)
{
  for (int i = 0; i < size; i++) {
    if (pins[i] == pin) {
      return false;
    }
  }

  return true;
}


bool ConfigurationManager::IsValidNote(int note)
{
  auto result = (note >= 0) && (note < 128);
  return result;
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

