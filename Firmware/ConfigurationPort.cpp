#include "ConfigurationPort.h"
#include "Arduino.h"


void ConfigurationPort::Setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}


void ConfigurationPort::Send(const char message[])
{
  Serial.println(message);
}

