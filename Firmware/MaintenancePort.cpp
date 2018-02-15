#include "MaintenancePort.h"


void MaintenancePort::Setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}


void MaintenancePort::Send(const RawMessage message)
{
  unsigned int length = message.GetSize();
  const byte *buffer = message.GetData();
  Serial.write(buffer, length);
}


uint8_t MaintenancePort::Receive(uint8_t buffer[], uint8_t bufferSize)
{
  uint8_t size = 0;
  while (Serial.available() > 0 && size < bufferSize) {
    byte temp = Serial.read();
    buffer[size++] = temp;
  }

  return size;
}

