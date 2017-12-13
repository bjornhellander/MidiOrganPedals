/* Simple "Hello World" example.

   After uploading this to your board, use Serial Monitor
   to view the message.  When Serial is selected from the
   Tools > USB Type menu, the correct serial port must be
   selected from the Tools > Serial Port AFTER Teensy is
   running this code.  Teensy only becomes a serial device
   while this code is running!  For non-Serial types,
   the Serial port is emulated, so no port needs to be
   selected.
*/

#include "ConfigurationPort.h"
#include "DebugMessage.h"
#include "GeneralStatusMessage.h"


static const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
static int count = 0;
static int ledOn = 1;


static ConfigurationPort configurationPort;


void setup()
{
  configurationPort.Setup();
  pinMode(ledPin, OUTPUT);
}


static void SendDebugMessage()
{
  char messageText[50];
  snprintf(messageText, sizeof(messageText), "Hello World (%d)\n", count);
  DebugMessage message(messageText);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  configurationPort.Send(rawMessage);
}


static void SendGeneralStatusMessage()
{
  GeneralStatusMessage message(true, 0b00110011001100110011001100110011, 0b01010101010101010101010101010101, 12, 13, 14);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  configurationPort.Send(rawMessage);
}


void loop()
{
  switch (count++ % 2) {
    case 0:
      SendDebugMessage();
      break;

    case 1:
      SendGeneralStatusMessage();
      break;
  }
  
  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);

  delay(1000);
}

