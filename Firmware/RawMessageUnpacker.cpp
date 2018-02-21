#include "RawMessageUnpacker.h"


#define StartByte 0xFF


bool RawMessageUnpacker::Unpack(uint8_t data, RawMessage &message)
{
  return Process(data, message);
}


bool RawMessageUnpacker::Process(uint8_t data, RawMessage &message)
{
    switch (dataSize)
    {
        case 0:
            ProcessStart(data);
            return false;
        case 1:
            ProcessId(data);
            return false;
        case 2:
            ProcessLength(data);
            return false;
        case 3:
            ProcessChecksum(data);
            return false;
        default:
            return ProcessPayload(data, message);
            break;
    }
}


void RawMessageUnpacker::ProcessStart(uint8_t data)
{
    AddByte(data);

    if (data != StartByte)
    {
        Abort();
    }
}


void RawMessageUnpacker::ProcessId(uint8_t data)
{
    AddByte(data);

    id = data;
}


void RawMessageUnpacker::ProcessLength(uint8_t data)
{
    AddByte(data);

    length = data;
    //payloadData = new byte[length];
}


void RawMessageUnpacker::ProcessChecksum(uint8_t data)
{
    AddByte(data);

    checksum = data;
}


bool RawMessageUnpacker::ProcessPayload(uint8_t data, RawMessage &message)
{
    // TODO: If length==0 then this code will still consume one byte as payload
    AddByte(data);

    auto payloadSize = dataSize - 4;
    payloadData[payloadSize - 1] = data;

    if (payloadSize >= length)
    {
        // Verify checksum
        auto expectedChecksum = CalcChecksum(payloadData, payloadSize);
        if (checksum != expectedChecksum)
        {
            Abort();
            return false;
        }

        // We are done!
        message.Setup(id, payloadData, payloadSize);

        Reset();
        return true;
    }

    return false;
}


void RawMessageUnpacker::AddByte(uint8_t data)
{
    dataSize++;
    //data[dataSize++] = data;
}


void RawMessageUnpacker::Abort()
{
    // TODO: Log discarded data?

    Reset();
}

void RawMessageUnpacker::Reset()
{
    dataSize = 0;
    //payloadData = null;
}

