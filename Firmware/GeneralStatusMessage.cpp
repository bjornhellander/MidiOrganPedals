#include "GeneralStatusMessage.h"
#include "RawMessageBuilder.h"


GeneralStatusMessage::GeneralStatusMessage(
  bool configurationOk,
  uint32_t pressedPedals,
  uint32_t playedNotes,
  uint16_t numberOfToggledPedals,
  uint16_t numberOfToggledNotes,
  uint16_t numberOfReceivedBytes,
  uint16_t numberOfDiscardedBytes)
{
  this->configurationOk = configurationOk;
  this->pressedPedals = pressedPedals;
  this->playedNotes = playedNotes;
  this->numberOfToggledPedals = numberOfToggledPedals;
  this->numberOfToggledNotes = numberOfToggledNotes;
  this->numberOfReceivedBytes = numberOfReceivedBytes;
  this->numberOfDiscardedBytes = numberOfDiscardedBytes;
}


void GeneralStatusMessage::Pack(RawMessage &result)
{
  RawMessageBuilder packer;
  packer.Add(configurationOk);
  packer.Add(pressedPedals);
  packer.Add(playedNotes);
  packer.Add(numberOfToggledPedals);
  packer.Add(numberOfToggledNotes);
  packer.Add(numberOfReceivedBytes);
  packer.Add(numberOfDiscardedBytes);
  packer.CopyTo(Id, result);
}

