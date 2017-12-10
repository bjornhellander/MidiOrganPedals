#ifndef __RawMessage_h
#define __RawMessage_h


#include "Arduino.h"


class RawMessage
{
  byte data[255+4];
  unsigned int size;
  
public:
  RawMessage();
  
  void Setup(byte id, const byte payloadData[], byte payloadSize);
  
  unsigned int GetSize() const;
  const byte *GetData() const;
  
private:
  byte CalcChecksum(const byte payloadData[], byte payloadSize);
};


#endif

