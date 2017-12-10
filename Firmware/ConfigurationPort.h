#ifndef __ConfigurationPort_h
#define __ConfigurationPort_h


#include "Arduino.h"
#include "RawMessage.h"


class ConfigurationPort
{
public:
  void Setup();
  void Send(const RawMessage message);
};


#endif

