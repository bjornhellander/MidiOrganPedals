#include "ConfigurationStatusMessage.h"
#include "RawMessagePacker.h"
#include "Misc.h"


#define CONFIGURATION_STATUS_MESSAGE_ID (0x02)


ConfigurationStatusMessage::ConfigurationStatusMessage(
  uint8_t firstNote,
  uint8_t velocity,
  uint8_t debouncingTime,
  uint8_t pedalPins[],
  uint8_t pedalPinCount)
{
  this->firstNote = firstNote;
  this->velocity = velocity;
  this->debouncingTime = debouncingTime;

  for (uint8_t i = 0; i < ARRAY_SIZE(this->pedalPins); i++) {
    if (i < pedalPinCount) {
      this->pedalPins[i] = pedalPins[i];
    }
    else {
      this->pedalPins[i] = 0;
    }
  }
}


void ConfigurationStatusMessage::Pack(RawMessage &result)
{
  RawMessagePacker packer(CONFIGURATION_STATUS_MESSAGE_ID);
  packer.Add(firstNote);
  packer.Add(velocity);
  packer.Add(debouncingTime);
  packer.Add(pedalPins, ARRAY_SIZE(pedalPins));
  packer.CopyTo(result);
}

