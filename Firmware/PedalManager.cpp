#include "PedalManager.h"
#include "Misc.h"


static const int PRESSED_PIN_STATE = LOW; // Value read for a pressed pedal


PedalManager::PedalManager(MidiPort &midiPort)
  : midiPort(midiPort)
{
}


void PedalManager::Setup(const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    auto pedal = &pedals[i];
    if (i < pedalPinCount && pedalPins[i] != UNUSED_PIN_NUMBER) {
      auto pin = pedalPins[i];
      pedal->pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }
    else {
      pedal->pin = UNUSED_PIN_NUMBER;
    }

    pedal->pressed = false;
    pedal->played = false;
  }

  numberOfToggledPedals = 0;
  numberOfToggledNotes = 0;
}


void PedalManager::Process()
{
  // Detect pedal changes
  for (uint8_t i = 0; i < ARRAY_SIZE(pedals); i++) {
    auto pedal = &pedals[i];
    if (pedal->pin != UNUSED_PIN_NUMBER) {
      auto state = digitalRead(pedal->pin);
      auto pressed = (state == PRESSED_PIN_STATE);
      if (pedal->pressed != pressed) {
        numberOfToggledPedals++;
        pedal->pressed = pressed;
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


uint32_t PedalManager::IsPedalPressed(uint8_t i)
{
  if (i >= ARRAY_SIZE(pedals)) {
    return false;
  }
  
  return pedals[i].pressed;
}


uint32_t PedalManager::IsNotePlayed(uint8_t i)
{
  if (i >= ARRAY_SIZE(pedals)) {
    return false;
  }
  
  return pedals[i].played;
}


uint16_t PedalManager::GetNumberOfToggledPedals()
{
  return numberOfToggledPedals;
}


uint16_t PedalManager::GetNumberOfToggledNotes()
{
  return numberOfToggledNotes;
}

