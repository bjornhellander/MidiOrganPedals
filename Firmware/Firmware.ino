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


#define TIME_BETWEEN_SENT_MESSAGES 1000


static const int ledPin = LED_BUILTIN;
static const uint8_t channel = 0; // TODO: Should this be configurable instead?
static const enum {
  PressedKeys,
  ReceivedMessages
} ledMode = PressedKeys;


static bool configurationIsOk;
static int count = 0;
static uint16_t numberOfReceivedMessages = 0;
static uint16_t numberOfReceivedBytes = 0;


static ConfigurationManager configurationManager;
static MaintenancePort maintenancePort;
static MidiPort midiPort;
static PedalManager pedalManager(midiPort);
static RawMessageUnpacker receivedMessageUnpacker;


static void ApplyConfiguration()
{
  configurationIsOk = configurationManager.IsOk();
  auto debouncingTime = configurationManager.GetDebouncingTime();
  uint8_t pedalPins[ConfigurationManager::MaxPedals];
  for (uint8_t i = 0; i < ARRAY_SIZE(pedalPins); i++) {
    pedalPins[i] = configurationManager.GetPedalPin(i);
  }

  maintenancePort.Setup();

  midiPort.Setup(channel, configurationManager.GetFirstNote(), configurationManager.GetVelocity());

  pedalManager.Setup(configurationIsOk, debouncingTime, pedalPins, ARRAY_SIZE(pedalPins));

  pinMode(ledPin, OUTPUT);
}


void setup()
{
  configurationManager.Setup();
  ApplyConfiguration();
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
  
  GeneralStatusMessage message(configurationIsOk, pressedPedals, playedNotes, numberOfToggledPedals, numberOfToggledNotes, numberOfReceivedBytes, 14);
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
    ApplyConfiguration();
  }
}


static void ProcessMaintenanceMessages()
{
  uint8_t buffer[128];
  uint8_t length = maintenancePort.Receive(buffer, sizeof(buffer));

  for (uint8_t i = 0; i < length; i++) {
    RawMessage rawMessage;
    if (receivedMessageUnpacker.Unpack(buffer[i], rawMessage)) {
      numberOfReceivedMessages++;

      switch (rawMessage.GetId()) {
        case ConfigurationRequestMessage::Id:
          ProcessConfigurationRequestMessage(rawMessage);
          break;
      }
    }

    numberOfReceivedBytes++;
  }
}


static void UpdateLed()
{
  int ledState = LOW;

  switch (ledMode) {
  case PressedKeys:
    ledState = pedalManager.GetNumberOfPressedPedals() % 2;
    break;

  case ReceivedMessages:
    ledState = numberOfReceivedMessages % 2;
    break;
  }

  digitalWrite(ledPin, ledState);
}


void loop()
{
  static unsigned long timeOfLastSentMessage = 0;
  unsigned long now = millis();
  
  ProcessMaintenanceMessages();

  pedalManager.Process();

  if (now - timeOfLastSentMessage >= TIME_BETWEEN_SENT_MESSAGES) {
    timeOfLastSentMessage = now;
    
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
  }

  UpdateLed();
}

