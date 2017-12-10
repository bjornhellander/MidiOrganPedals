namespace WpfMidiOrganPedals.Devices
{
    public class RawMessage
    {
        public RawMessage(byte[] rawData)
        {
            RawData = rawData;
        }

        public byte[] RawData { get; }
    }
}
