#include "ChecksumCalculator.h"


byte ChecksumCalculator::CalcChecksum(const uint8_t payloadData[], uint8_t payloadSize)
{
  uint8_t result = 0;

  for (uint8_t i = 0; i < payloadSize; i++) {
    result = result ^ payloadData[i]; // TODO: Make this better at detecting errors
  }

  return result;
}

