#ifndef __Message_h
#define __Message_h


#include "Arduino.h"


class RawMessage
{
  char text[256];
  
public:
  RawMessage(const char text[]);
  
  const char *GetText() const;
};


#endif

