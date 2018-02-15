#ifndef __DebugMessage_h
#define __DebugMessage_h


#include "Arduino.h"
#include "RawMessage.h"


class DebugMessage
{
public:
  static const uint8_t Id = 0x00;

private:
  char text[32];
  
public:
  DebugMessage(const char text[]);

  void Pack(RawMessage &result);
};


#endif

