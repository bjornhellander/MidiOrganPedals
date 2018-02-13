#include "MidiPort.h"


void MidiPort::Setup(uint8_t channel, uint8_t firstNote, uint8_t velocity)
{
  this->velocity = velocity;
  
  Serial1.begin(31250);
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
  if (size > Serial1.availableForWrite()) {
    return false;
  }

  Serial1.write(command, size);
  return true;
}

