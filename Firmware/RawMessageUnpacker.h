#ifndef __RawMessageUnpacker_h
#define __RawMessageUnpacker_h


#include "Arduino.h"
#include "RawMessageHandler.h"
#include "RawMessage.h"


class RawMessageUnpacker : public RawMessageHandler
{
  uint16_t dataSize;
  uint8_t id;
  uint8_t length;
  uint8_t checksum;
  uint8_t payloadData[255];
  
public:
  bool Unpack(uint8_t data, RawMessage &input);
  
  //uint16_t GetSize() const;
  //const uint8_t *GetData() const;
  
private:
  //uint8_t CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize);
  bool Process(uint8_t data, RawMessage &message);
  void ProcessStart(uint8_t data);
  void ProcessId(uint8_t data);
  void ProcessLength(uint8_t data);
  void ProcessChecksum(uint8_t data);
  bool ProcessPayload(uint8_t data, RawMessage &message);
  void AddByte(uint8_t data);
  void Abort();
  void Reset();
};


#endif

