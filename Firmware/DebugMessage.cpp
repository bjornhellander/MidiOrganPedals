#include "DebugMessage.h"
#include "RawMessageBuilder.h"


DebugMessage::DebugMessage(const char text[])
{
  auto length = sizeof(this->text) - 1;
  strncpy(this->text, text, length);
  this->text[length] = '\0';
}


void DebugMessage::Pack(RawMessage &result)
{
  RawMessageBuilder packer;
  packer.Add(text, sizeof(text));
  packer.CopyTo(result);
}

