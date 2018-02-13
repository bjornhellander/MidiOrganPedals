#include "MaintenancePort.h"
#include "MidiPort.h"
#include "DebugMessage.h"
#include "GeneralStatusMessage.h"
#include "PedalManager.h"


static const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
static const uint8_t channel = 0;
static const uint8_t velocity = 0;
static const uint8_t firstNote = 30;
static const uint8_t pedalPins[] = {
  1, 2, 3, 4, 0
};


static int count = 0;
static int ledOn = 1;


static MaintenancePort maintenancePort;
static MidiPort midiPort;
static PedalManager pedalManager(midiPort);


void setup()
{
  maintenancePort.Setup();
  midiPort.Setup(channel, firstNote, velocity);
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

