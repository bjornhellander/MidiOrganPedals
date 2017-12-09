#ifndef __Message_h
#define __Message_h


#include "Arduino.h"


class Message
{
  char text[256];
  
public:
  Message(const char text[]);
  
  const char *GetText() const;
};


#endif

