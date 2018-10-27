#ifndef __PedalManager_h
#define __PedalManager_h


#include "Arduino.h"
#include "MidiPort.h"


class PedalManager
{
  MidiPort &midiPort;
  uint8_t debouncingTime;
  
  typedef struct {
    uint8_t pin;
    uint32_t timeOfTentativeChange;
    bool tentativelyPressed;
    bool pressed;
    bool played;
  } PedalInfo;
  PedalInfo pedals[32];
  uint16_t numberOfToggledPedals;
  uint16_t numberOfToggledNotes;
  
public:
  PedalManager(MidiPort &midiPort);
  
  void Setup(bool configurationIsOk, uint8_t debouncingTime, const uint8_t pedalPins[], uint8_t pedalPinCount);

  void Process();

  bool IsPedalPressed(uint8_t i);
  bool IsNotePlayed(uint8_t i);
  uint8_t GetNumberOfPressedPedals();
  uint16_t GetNumberOfToggledPedals();
  uint16_t GetNumberOfToggledNotes();
};


#endif

