#ifndef __PedalManager_h
#define __PedalManager_h


#include "Arduino.h"
#include "MidiPort.h"


class PedalManager
{
  MidiPort &midiPort;

  typedef struct {
    uint8_t pin;
    bool pressed;
    bool played;
  } PedalInfo;
  PedalInfo pedals[32];
  uint16_t numberOfToggledPedals;
  uint16_t numberOfToggledNotes;
  
public:
  PedalManager(MidiPort &midiPort);
  
  void Setup(bool configurationIsOk, const uint8_t pedalPins[], uint8_t pedalPinCount);

  void Process();

  bool IsPedalPressed(uint8_t i);
  bool IsNotePlayed(uint8_t i);
  uint8_t GetNumberOfPressedPedals();
  uint16_t GetNumberOfToggledPedals();
  uint16_t GetNumberOfToggledNotes();
};


#endif

