#include "Misc.h"
#include "ConfigurationManager.h"
#include "MaintenancePort.h"
#include "MidiPort.h"
#include "DebugMessage.h"
#include "GeneralStatusMessage.h"
#include "ConfigurationStatusMessage.h"
#include "ConfigurationRequestMessage.h"
#include "PedalManager.h"
#include "RawMessagePacker.h"
#include "RawMessageUnpacker.h"
#include "Misc.h"


// #if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
// #ifdef DTEENSYDUINO
// #ifdef MATTAIRTECH


static const int ledPin = LED_BUILTIN; // Teensy++ 2.0 has the LED on pin 6, Mattair MT-DB-U6 has LED on pin 0
static const uint8_t channel = 0;


static int count = 0;
static int ledOn = 1;
static uint16_t numberOfReceivedBytes = 0;


static ConfigurationManager configurationManager;
static MaintenancePort maintenancePort;
static MidiPort midiPort;
static PedalManager pedalManager(midiPort);
static RawMessageUnpacker receivedMessageUnpacker;


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
  rawMessagePacker.Pack(rawMessage);
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
  rawMessagePacker.Pack(rawMessage);
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
  rawMessagePacker.Pack(rawMessage);
  maintenancePort.Send(rawMessagePacker.GetData(), rawMessagePacker.GetSize());
}


static void ProcessConfigurationRequestMessage(const RawMessage &rawMessage)
{
  ConfigurationRequestMessage message;
  
  if (message.Unpack(rawMessage)) {
    configurationManager.Setup(message.FirstNote, message.Velocity, message.DebouncingTime, message.PedalPins, ARRAY_SIZE(message.PedalPins));
  }
}


static void ProcessMaintenanceMessages()
{
  uint8_t buffer[128];
  uint8_t length = maintenancePort.Receive(buffer, sizeof(buffer));

  for (uint8_t i = 0; i < length; i++) {
    RawMessage rawMessage;
    if (receivedMessageUnpacker.Unpack(buffer[i], rawMessage)) {
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn);

      switch (rawMessage.GetId()) {
        case ConfigurationRequestMessage::Id:
          ProcessConfigurationRequestMessage(rawMessage);
          break;
      }
    }

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

  delay(1000);
}

