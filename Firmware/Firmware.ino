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

#include "MaintenancePort.h"
#include "DebugMessage.h"
#include "GeneralStatusMessage.h"
#include "PedalManager.h"


static const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
static const uint8_t pedalPins[] = {
  1, 2, 3, 4, 0
};


static int count = 0;
static int ledOn = 1;


static MaintenancePort maintenancePort;
static PedalManager pedalManager;


void setup()
{
  maintenancePort.Setup();
  pedalManager.Setup(pedalPins);
  pinMode(ledPin, OUTPUT);
}


static void SendDebugMessage()
{
  char messageText[50];
  snprintf(messageText, sizeof(messageText), "Hello World (%d)\n", count);
  
  DebugMessage message(messageText);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  maintenancePort.Send(rawMessage);
}


static void SendGeneralStatusMessage()
{
  uint32_t pressedPedals = 0, playedNotes = 0;
  for (uint8_t i = 0; i < 32; i++) {
    pressedPedals |= pedalManager.IsPedalPressed(i) << i;
    playedNotes = pedalManager.IsNotePlayed(i) << i;
  }
  auto numberOfToggledPedals = pedalManager.GetNumberOfToggledPedals();
  auto numberOfToggledNotes = pedalManager.GetNumberOfToggledNotes();
  
  GeneralStatusMessage message(true, pressedPedals, playedNotes, numberOfToggledPedals, numberOfToggledNotes, 14);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  maintenancePort.Send(rawMessage);
}


void loop()
{
  pedalManager.Process();

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

