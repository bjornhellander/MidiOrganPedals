#include "ChecksumCalculator.h"


byte ChecksumCalculator::CalcChecksum(const void *data, uint8_t size)
{
  return ModifyChecksum(0, data, size);
}


byte ChecksumCalculator::ModifyChecksum(uint8_t checksum, const void *data, uint8_t size)
{
  uint8_t result = 0;

  uint8_t *d = (uint8_t*)data;
  for (uint8_t i = 0; i < size; i++) {
    result = result + d[i]; // TODO: Make this better at detecting errors
  }

  return result;
}

