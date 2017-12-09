#ifndef __ConfigurationPort_h
#define __ConfigurationPort_h


#include "Arduino.h"
#include "Message.h"


class ConfigurationPort
{
public:
  void Setup();
  void Send(const Message message);
};


#endif


