#ifndef __RawMessage_h
#define __RawMessage_h


#include "Arduino.h"


class RawMessage
{
  byte data[255];
  byte size;
  
public:
  RawMessage();
  
  void Setup(const byte payloadData[], byte payloadSize);
  
  byte GetSize() const;
  const byte *GetData() const;
};


#endif

