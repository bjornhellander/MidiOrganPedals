#ifndef __RawMessagePacker_h
#define __RawMessagePacker_h


#include "Arduino.h"
#include "RawMessageHandler.h"
#include "RawMessage.h"


class RawMessagePacker : public RawMessageHandler
{
  uint8_t data[255+4];
  uint16_t size;
  
public:
  void Pack(const RawMessage &input);
  
  uint16_t GetSize() const;
  const uint8_t *GetData() const;
};


#endif

