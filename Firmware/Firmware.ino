#include "Misc.h"
#include "ConfigurationManager.h"
#include "MaintenancePort.h"
#include "MidiPort.h"
#include "DebugMessage.h"
#include "GeneralStatusMessage.h"
#include "ConfigurationStatusMessage.h"
#include "PedalManager.h"
#include "RawMessagePacker.h"


static const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
static const uint8_t channel = 0;


static int count = 0;
static int ledOn = 1;
static uint16_t numberOfReceivedBytes = 0;


static ConfigurationManager configurationManager;
static MaintenancePort maintenancePort;
static MidiPort midiPort;
static PedalManager pedalManager(midiPort);


void setup()
{
  configurationManager.Setup();
  
  maintenancePort.Setup();
  
  midiPort.Setup(channel, configurationManager.GetFirstNote(), configurationManager.GetVelocity());

  uint8_t pedalPins[ConfigurationManager::MaxPedals];
  for (uint8_t i = 0; i < ARRAY_SIZE(pedalPins); i++) {
    pedalPins[i] = configurationManager.GetPedalPin(i);
  }
  pedalManager.Setup(pedalPins, ARRAY_SIZE(pedalPins));
  
  pinMode(ledPin, OUTPUT);
}


static void SendDebugMessage()
{
  char messageText[50];
  snprintf(messageText, sizeof(messageText), "Hello World (%d)\n", count);

  DebugMessage message(messageText);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  RawMessagePacker rawMessagePacker;
  rawMessagePacker.Pack(DebugMessage::Id, rawMessage);
  maintenancePort.Send(rawMessagePacker.GetData(), rawMessagePacker.GetSize());
}


static void SendGeneralStatusMessage()
{
  uint32_t pressedPedals = 0, playedNotes = 0;
  for (uint8_t i = 0; i < 32; i++) {
    pressedPedals |= pedalManager.IsPedalPressed(i) << i;
    playedNotes |= pedalManager.IsNotePlayed(i) << i;
  }
  auto numberOfToggledPedals = pedalManager.GetNumberOfToggledPedals();
  auto numberOfToggledNotes = pedalManager.GetNumberOfToggledNotes();
  
  GeneralStatusMessage message(true, pressedPedals, playedNotes, numberOfToggledPedals, numberOfToggledNotes, numberOfReceivedBytes, 14);
  RawMessage rawMessage;
  message.Pack(rawMessage);
  RawMessagePacker rawMessagePacker;
  rawMessagePacker.Pack(GeneralStatusMessage::Id, rawMessage);
  maintenancePort.Send(rawMessagePacker.GetData(), rawMessagePacker.GetSize());
}


static void SendConfigurationStatusMessage()
{
  auto firstNote = configurationManager.GetFirstNote();
  auto velocity = configurationManager.GetVelocity();
  auto debouncingTime = configurationManager.GetDebouncingTime();

  uint8_t pedalPins[ConfigurationManager::MaxPedals];
  for (uint8_t i = 0; i < ARRAY_SIZE(pedalPins); i++) {
    pedalPins[i] = configurationManager.GetPedalPin(i);
  }

  ConfigurationStatusMessage message(firstNote, velocity, debouncingTime, pedalPins, ARRAY_SIZE(pedalPins));
  RawMessage rawMessage;
  message.Pack(rawMessage);
  RawMessagePacker rawMessagePacker;
  rawMessagePacker.Pack(ConfigurationStatusMessage::Id, rawMessage);
  maintenancePort.Send(rawMessagePacker.GetData(), rawMessagePacker.GetSize());
}


static void ProcessMaintenanceMessages()
{
  uint8_t buffer[128];
  uint8_t length = maintenancePort.Receive(buffer, sizeof(buffer));

  for (uint8_t i = 0; i < length; i++) {
    numberOfReceivedBytes++;
  }
}


void loop()
{
  ProcessMaintenanceMessages();
  
  pedalManager.Process();

  switch (count++ % 3) {
    case 0:
      SendDebugMessage();
      break;

    case 1:
      SendGeneralStatusMessage();
      break;

    case 2:
      SendConfigurationStatusMessage();
      break;
  }

  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);

  delay(1000);
}

