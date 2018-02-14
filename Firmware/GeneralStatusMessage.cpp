#include "GeneralStatusMessage.h"
#include "RawMessagePacker.h"


#define GENERAL_STATUS_MESSAGE_ID (0x01)


GeneralStatusMessage::GeneralStatusMessage(
  uint32_t pressedPedals,
  uint32_t playedNotes,
  uint16_t numberOfToggledPedals,
  uint16_t numberOfToggledNotes,
  uint16_t numberOfDiscardedBytes)
{
  this->pressedPedals = pressedPedals;
  this->playedNotes = playedNotes;
  this->numberOfToggledPedals = numberOfToggledPedals;
  this->numberOfToggledNotes = numberOfToggledNotes;
  this->numberOfDiscardedBytes = numberOfDiscardedBytes;
}


void GeneralStatusMessage::Pack(RawMessage &result)
{
  RawMessagePacker packer(GENERAL_STATUS_MESSAGE_ID);
  packer.Add(pressedPedals);
  packer.Add(playedNotes);
  packer.Add(numberOfToggledPedals);
  packer.Add(numberOfToggledNotes);
  packer.Add(numberOfDiscardedBytes);
  packer.CopyTo(result);
}

