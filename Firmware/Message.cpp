#include "Message.h"


Message::Message(const char text[])
{
  int maxSize = sizeof(this->text) - 1;
  strncpy(this->text, text, maxSize);
  this->text[maxSize] = '\0';
}


const char *Message::Message::GetText() const
{
  return text;
}

