#ifndef __RawMessage_h
#define __RawMessage_h


#include "Arduino.h"


class RawMessage
{
  byte id;
  byte data[255];
  byte size;
  
public:
  RawMessage();
  
  void Setup(byte id, const byte payloadData[], byte payloadSize);

  byte GetId() const;
  byte GetSize() const;
  const byte *GetData() const;
};


#endif

