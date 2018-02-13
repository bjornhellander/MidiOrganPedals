#ifndef __MidiPort_h
#define __MidiPort_h


#include "Arduino.h"


class MidiPort
{
  uint8_t channel; // 0-15
  uint8_t firstNote; // 0-127
  uint8_t velocity; // 0-127
  
public:
  void Setup(uint8_t channel, uint8_t firstNote, uint8_t velocity);
  
  bool PlayNote(uint8_t note);
  bool StopNote(uint8_t note);

private:
  bool SendCommand(uint8_t command[], uint8_t size);
};


#endif

