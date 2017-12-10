#ifndef __DebugMessage_h
#define __DebugMessage_h


#include "Arduino.h"
#include "RawMessage.h"


class DebugMessage
{
  char text[256];
  
public:
  DebugMessage(const char text[]);

  void Pack(RawMessage &result);
};


#endif

