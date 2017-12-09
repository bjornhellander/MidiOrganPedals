#include "ConfigurationPort.h"


void ConfigurationPort::Setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}


void ConfigurationPort::Send(const Message message)
{
  const char *buffer = message.GetText();
  byte length = strlen(buffer);
  Serial.write(buffer, length);
}


