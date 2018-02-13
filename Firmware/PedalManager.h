#ifndef __PedalManager_h
#define __PedalManager_h


#include "Arduino.h"
#include "MidiPort.h"


class PedalManager
{
  MidiPort &midiPort;
  
  uint8_t pedalPins[32];
  bool pedalsPressed[32];
  bool notesPlayed[32];
  uint16_t numberOfToggledPedals;
  uint16_t numberOfToggledNotes;
  
public:
  PedalManager(MidiPort &midiPort);
  
  void Setup(const uint8_t pedalPins[], uint8_t pedalPinCount);

  void Process();

  uint32_t IsPedalPressed(uint8_t i);
  uint32_t IsNotePlayed(uint8_t i);
  uint16_t GetNumberOfToggledPedals();
  uint16_t GetNumberOfToggledNotes();
};


#endif

