using System;

namespace WpfMidiOrganPedals.Devices
{
    internal class MessageUnpacker
    {
        internal Message Unpack(RawMessage input)
        {
            Message output;

            switch (input.Id)
            {
                case DebugMessage.Id:
                    output = new DebugMessage(input.RawData);
                    break;
                case GeneralStatusMessage.Id:
                    output = new GeneralStatusMessage(input.RawData);
                    break;
                default:
                    throw new NotImplementedException();
            }

            return output;
        }
    }
}
