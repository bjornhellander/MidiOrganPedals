#include "MidiPort.h"


#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define SERIAL Serial1
#endif

#ifdef ARDUINO_AVR_UNO
#define SERIAL Serial
#endif


void MidiPort::Setup(uint8_t channel, uint8_t firstNote, uint8_t velocity)
{
  this->velocity = velocity;
  
  SERIAL.begin(31250);
}


bool MidiPort::PlayNote(uint8_t note)
{
  uint8_t command[3];
  command[0] = 0x90 | channel;
  command[1] = firstNote + note;
  command[2] = velocity;
  return SendCommand(command, sizeof(command));
}


bool MidiPort::StopNote(uint8_t note)
{
  uint8_t command[3];
  command[0] = 0x80 | channel;
  command[1] = firstNote + note;
  command[2] = velocity;
  return SendCommand(command, sizeof(command));
}


bool MidiPort::SendCommand(uint8_t command[], uint8_t size)
{
  if (size > SERIAL.availableForWrite()) {
    return false;
  }

  SERIAL.write(command, size);
  return true;
}

