#ifndef __GeneralStatusMessage_h
#define __GeneralStatusMessage_h


#include "Arduino.h"
#include "RawMessage.h"


class GeneralStatusMessage
{
public:
  static const uint8_t Id = 0x01;

private:
  bool configurationOk;
  uint32_t pressedPedals;
  uint32_t playedNotes;
  uint16_t numberOfToggledPedals;
  uint16_t numberOfToggledNotes;
  uint16_t numberOfReceivedBytes;
  uint16_t numberOfDiscardedBytes;
  
public:
  GeneralStatusMessage(
    bool configurationOk,
    uint32_t pressedPedals,
    uint32_t playedNotes,
    uint16_t numberOfToggledPedals,
    uint16_t numberOfToggledNotes,
    uint16_t numberOfReceivedBytes,
    uint16_t numberOfDiscardedBytes);

  void Pack(RawMessage &result);
};


#endif

