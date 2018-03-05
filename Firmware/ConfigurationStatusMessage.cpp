#include "ConfigurationStatusMessage.h"
#include "RawMessageBuilder.h"
#include "Misc.h"


ConfigurationStatusMessage::ConfigurationStatusMessage(
  uint8_t firstNote,
  uint8_t velocity,
  uint8_t debouncingTime,
  uint8_t pedalPins[],
  uint8_t pedalPinCount)
{
  FirstNote = firstNote;
  Velocity = velocity;
  DebouncingTime = debouncingTime;

  for (uint8_t i = 0; i < ARRAY_SIZE(PedalPins); i++) {
    if (i < pedalPinCount) {
     PedalPins[i] = pedalPins[i];
    }
    else {
      PedalPins[i] = UNUSED_PIN_NUMBER;
    }
  }
}


void ConfigurationStatusMessage::Pack(RawMessage &result)
{
  RawMessageBuilder packer;
  packer.Add(FirstNote);
  packer.Add(Velocity);
  packer.Add(DebouncingTime);
  packer.Add(PedalPins, ARRAY_SIZE(PedalPins));
  packer.CopyTo(Id, result);
}

