#include "DebugMessage.h"
#include "RawMessagePacker.h"


#define DEBUG_MESSAGE_ID (0x00)


DebugMessage::DebugMessage(const char text[])
{
  auto length = sizeof(this->text) - 1;
  strncpy(this->text, text, length);
  this->text[length] = '\0';
}


void DebugMessage::Pack(RawMessage &result)
{
  RawMessagePacker packer(DEBUG_MESSAGE_ID);
  packer.Add(text, sizeof(text));
  packer.CopyTo(result);
}

