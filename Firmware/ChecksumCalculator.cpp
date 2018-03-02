#include "ChecksumCalculator.h"


byte ChecksumCalculator::CalcChecksum(const uint8_t data[], uint8_t size)
{
  return ModifyChecksum(0, data, size);
}


byte ChecksumCalculator::ModifyChecksum(uint8_t checksum, const uint8_t data[], uint8_t size)
{
  uint8_t result = 0;

  for (uint8_t i = 0; i < size; i++) {
    result = result ^ data[i]; // TODO: Make this better at detecting errors
  }

  return result;
}

