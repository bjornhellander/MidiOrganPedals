#ifndef __ConfigurationPort_h
#define __ConfigurationPort_h


#include "Arduino.h"


class ConfigurationPort
{
public:
  void Setup();
  void Send(const byte buffer[], int length);
};


#endif


