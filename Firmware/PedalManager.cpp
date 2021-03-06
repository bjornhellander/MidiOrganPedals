#include "PedalManager.h"
#include "Misc.h"


static const int PRESSED_PIN_STATE = LOW; // Value read for a pressed pedal


PedalManager::PedalManager(MidiPort &midiPort)
  : midiPort(midiPort)
{
}


void PedalManager::Setup(bool configurationIsOk, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  // NOTE: If this method is called because of a received ConfigurationRequestMessage, previously used pins might be left in INPUT_PULLUP mode,
  // but that is not a problem.
  // NOTE: If this method is called because of a received ConfigurationRequestMessage while notes are playing, those notes will continue playing.
  
  this->debouncingTime = debouncingTime;
  
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    auto pedal = &pedals[i];
    if (configurationIsOk && i < pedalPinCount && pedalPins[i] != UNUSED_PIN_NUMBER) {
      auto pin = pedalPins[i];
      pedal->pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }
    else {
      pedal->pin = UNUSED_PIN_NUMBER;
    }

    pedal->timeOfTentativeChange = 0;
    pedal->tentativelyPressed = false;
    pedal->pressed = false;
    pedal->played = false;
  }

  numberOfToggledPedals = 0;
  numberOfToggledNotes = 0;
}


void PedalManager::Process()
{
  uint32_t now = millis();
  
  // Detect pedal changes
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    auto pedal = &pedals[i];
    if (pedal->pin != UNUSED_PIN_NUMBER) {
      auto state = digitalRead(pedal->pin);
      auto pressed = (state == PRESSED_PIN_STATE);
      if (pedal->tentativelyPressed != pressed) {
        // Input has changed. Wait until it stabilizes...
        pedal->tentativelyPressed = pressed;
        pedal->timeOfTentativeChange = now;
      }
      if (pedal->pressed != pressed) {
        uint32_t timeSinceTentativeChange = now - pedal->timeOfTentativeChange;
        if (timeSinceTentativeChange >= debouncingTime) {
          // The input seems stable. Accept the new input!
          numberOfToggledPedals++;
          pedal->pressed = pressed;
        }
      }
    }
  }

  // Play notes
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    auto pedal = &pedals[i];
    if (pedal->pressed != pedal->played) {
      bool ok;
      if (pedal->pressed) {
        ok = midiPort.PlayNote(i);
      }
      else {
        ok = midiPort.StopNote(i);
      }

      if (ok) {
        pedal->played = pedal->pressed;
        numberOfToggledNotes++;
      }
      else {
        break;
      }
    }
  }
}


bool PedalManager::IsPedalPressed(uint8_t i)
{
  if (i >= ARRAY_SIZE(pedals)) {
    return false;
  }
  
  return pedals[i].pressed;
}


bool PedalManager::IsNotePlayed(uint8_t i)
{
  if (i >= ARRAY_SIZE(pedals)) {
    return false;
  }
  
  return pedals[i].played;
}


uint8_t PedalManager::GetNumberOfPressedPedals()
{
  uint8_t count = 0;
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    if (pedals[i].pressed) {
      count++;
    }
  }
  
  return count;
}


uint16_t PedalManager::GetNumberOfToggledPedals()
{
  return numberOfToggledPedals;
}


uint16_t PedalManager::GetNumberOfToggledNotes()
{
  return numberOfToggledNotes;
}

