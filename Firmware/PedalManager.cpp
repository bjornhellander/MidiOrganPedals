#include "PedalManager.h"


// Value read for a pressed pedal
#define PRESSED_PIN_STATE LOW


PedalManager::PedalManager(MidiPort &midiPort)
  : midiPort(midiPort)
{
}


void PedalManager::Setup(const uint8_t pedalPins[], uint8_t pedalPinCount)
{
  for (uint8_t i = 0; i < 32; i++) {
    if (i < pedalPinCount && pedalPins[i] != 0) {
      auto pin = pedalPins[i];
      this->pedalPins[i] = pin;
      pinMode(pin, INPUT_PULLUP);
    }
    else {
      this->pedalPins[i] = 0;
    }
  }

  for (uint8_t i = 0; i < 32; i++) {
    pedalsPressed[i] = false;
    notesPlayed[i] = false;
  }

  numberOfToggledPedals = 0;
  numberOfToggledNotes = 0;
}


void PedalManager::Process()
{
  // Detect pedal changes
  for (uint8_t i = 0; i < 32; i++) {
    auto pin = pedalPins[i];
    if (pin != 0) {
      auto state = digitalRead(pin);
      auto pressed = (state == PRESSED_PIN_STATE);
      if (pedalsPressed[i] != pressed) {
        numberOfToggledPedals++;
        pedalsPressed[i] = pressed;
      }
    }
  }

  // Play notes
  for (uint8_t i = 0; i < 32; i++) {
    auto pin = pedalPins[i];
    if (pin != 0) {
      if (pedalsPressed[i] != notesPlayed[i]) {
        bool ok;
        if (pedalsPressed[i]) {
          ok = midiPort.PlayNote(i);
        }
        else {
          ok = midiPort.StopNote(i);
        }

        if (ok) {
          notesPlayed[i] = pedalsPressed[i];
          numberOfToggledNotes++;
        }
        else {
          break;
        }
      }
    }
  }
}


uint32_t PedalManager::IsPedalPressed(uint8_t i)
{
  if (i < sizeof(pedalsPressed)/sizeof(pedalsPressed[0])) {
    return pedalsPressed[i];
  }
  else {
    return false;
  }
}


uint32_t PedalManager::IsNotePlayed(uint8_t i)
{
  if (i < sizeof(notesPlayed)/sizeof(notesPlayed[0])) {
    return notesPlayed[i];
  }
  else {
    return false;
  }
}


uint16_t PedalManager::GetNumberOfToggledPedals()
{
  return numberOfToggledPedals;
}


uint16_t PedalManager::GetNumberOfToggledNotes()
{
  return numberOfToggledNotes;
}

