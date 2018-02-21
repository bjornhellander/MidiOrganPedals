#include "RawMessageExtractor.h"


RawMessageExtractor::RawMessageExtractor(const uint8_t data[], uint8_t size)
{
  memcpy(this->data, data, sizeof(this->data));
  this->size = size;
  this->i = 0;
}


bool RawMessageExtractor::Get(uint8_t &value)
{
  if (i + 1 > size) {
    return false;
  }

  value = data[i++];
  return true;
}


bool RawMessageExtractor::Get(uint8_t values[], uint8_t count)
{
  if (i + count > size) {
    return false;
  }

  for (auto j = 0; j < count; j++) {
    values[j] = data[i++];
  }
  return true;
}


bool RawMessageExtractor::Finish()
{
  if (i != size) {
    return false;
  }

  return true;
}

