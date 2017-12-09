#ifndef __Message_h
#define __Message_h


#include "Arduino.h"


#define MAX_MESSAGE_TEXT_LENGTH 256


class Message
{
  char text[MAX_MESSAGE_TEXT_LENGTH];
  
public:
  Message(const char text[]);
  
  const char *GetText() const;
};


#endif

