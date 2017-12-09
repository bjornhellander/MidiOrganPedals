#include "RawMessage.h"


RawMessage::RawMessage(const char text[])
{
  int maxSize = sizeof(this->text) - 1;
  strncpy(this->text, text, maxSize);
  this->text[maxSize] = '\0';
}


const char *RawMessage::GetText() const
{
  return text;
}

