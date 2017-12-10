#include "ConfigurationPort.h"


void ConfigurationPort::Setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}


void ConfigurationPort::Send(const RawMessage message)
{
  unsigned int length = message.GetSize();
  const byte *buffer = message.GetData();
  Serial.write(buffer, length);
}

