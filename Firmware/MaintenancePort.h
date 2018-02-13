#ifndef __MaintenancePort_h
#define __MaintenancePort_h


#include "Arduino.h"
#include "RawMessage.h"


class MaintenancePort
{
public:
  void Setup();
  void Send(const RawMessage message);
};


#endif

