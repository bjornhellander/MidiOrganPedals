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


static const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
static int count = 0;
static int ledOn = 1;


static ConfigurationPort configurationPort;


void setup()
{
  configurationPort.Setup();
  pinMode(ledPin, OUTPUT);
}


void loop()
{
  count++;
  char messageText[50];
  snprintf(messageText, sizeof(messageText), "Hello World (%d)\n", count);
  Message message(messageText);
  configurationPort.Send(message);

  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);

  delay(1000);
}
