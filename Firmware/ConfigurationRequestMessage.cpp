#include "ConfigurationRequestMessage.h"
#include "RawMessageExtractor.h"
#include "Misc.h"


bool ConfigurationRequestMessage::Unpack(const RawMessage &input)
{
  RawMessageExtractor extractor(input.GetData(), input.GetSize());
  
  if (!extractor.Get(FirstNote)) {
    return false;
  }
  
  if (!extractor.Get(Velocity)) {
    return false;
  }
  
  if (!extractor.Get(DebouncingTime)) {
    return false;
  }
  
  if (!extractor.Get(PedalPins, ARRAY_SIZE(PedalPins))) {
    return false;
  }
  
  if (!extractor.Finish()) {
    return false;
  }
  
  return true;
}

