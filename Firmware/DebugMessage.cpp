#include "DebugMessage.h"


#define DEBUG_MESSAGE_ID (0x00)


DebugMessage::DebugMessage(const char text[])
{
  auto length = sizeof(this->text) - 1;
  strncpy(this->text, text, length);
  this->text[length] = '\0';
}


void DebugMessage::Pack(RawMessage &result)
{
  byte payload[255];

  byte size = min(sizeof(payload), strlen(text));
  
  for (byte i = 0; i < size;  i++) {
    payload[i] = text[i];
  }

  for (byte i = size; i < sizeof(payload); i++) {
    payload[i] = 0;
  }

  result.Setup(DEBUG_MESSAGE_ID, payload, size);
}

