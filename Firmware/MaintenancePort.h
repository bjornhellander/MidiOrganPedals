#ifndef __MaintenancePort_h
#define __MaintenancePort_h


#include "Arduino.h"
#include "RawMessage.h"


class MaintenancePort
{
public:
  void Setup();
  void Send(const uint8_t buffer[], uint16_t size);
  uint8_t Receive(uint8_t buffer[], uint8_t size);
};


#endif

