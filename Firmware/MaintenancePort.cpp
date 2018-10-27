#include "MaintenancePort.h"


#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define SERIAL Serial
#endif

#ifdef ARDUINO_AVR_UNO
// This board only has one serial port and it's used for sending MIDI
#undef SERIAL
#endif


void MaintenancePort::Setup()
{
#ifdef SERIAL
  SERIAL.begin(9600); // USB is always 12 Mbit/sec
#endif
}


void MaintenancePort::Send(const uint8_t buffer[], uint16_t bufferSize)
{
#ifdef SERIAL
  SERIAL.write(buffer, bufferSize);
#endif
}


uint8_t MaintenancePort::Receive(uint8_t buffer[], uint8_t bufferSize)
{
  uint8_t size = 0;
  
#ifdef SERIAL
  while (SERIAL.available() > 0 && size < bufferSize) {
    byte temp = Serial.read();
    buffer[size++] = temp;
  }
#endif
  
  return size;
}

