#ifndef __ConfigurationRequestMessage_h
#define __ConfigurationRequestMessage_h


#include "Arduino.h"
#include "ConfigurationMessageBase.h"
#include "RawMessage.h"


class ConfigurationRequestMessage : public ConfigurationMessageBase
{
public:
  static const uint8_t Id = 0x03;

public:
  bool Unpack(const RawMessage &result);
};


#endif

