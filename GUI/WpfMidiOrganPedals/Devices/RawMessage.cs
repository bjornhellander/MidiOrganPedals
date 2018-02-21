using System;

namespace WpfMidiOrganPedals.Devices
{
    public class RawMessage
    {
        public RawMessage(byte id, byte[] rawData)
        {
            if (rawData == null)
            {
                throw new ArgumentNullException(nameof(rawData));
            }

            Id = id;
            RawData = rawData;
        }

        public byte Id { get; }

        public byte[] RawData { get; }
    }
}
