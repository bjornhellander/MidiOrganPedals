#include "MaintenancePort.h"


void MaintenancePort::Setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec
}


void MaintenancePort::Send(const uint8_t buffer[], uint16_t bufferSize)
{
  Serial.write(buffer, bufferSize);
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

