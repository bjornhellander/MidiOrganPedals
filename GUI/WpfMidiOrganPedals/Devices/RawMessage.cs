namespace WpfMidiOrganPedals.Devices
{
    public class RawMessage
    {
        public RawMessage(byte id, byte[] rawData)
        {
            Id = id;
            RawData = rawData;
        }

        public byte Id { get; }

        public byte[] RawData { get; }
    }
}
