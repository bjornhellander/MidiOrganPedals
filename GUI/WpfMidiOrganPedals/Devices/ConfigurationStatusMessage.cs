namespace WpfMidiOrganPedals.Devices
{
    internal class ConfigurationStatusMessage : ConfigurationMessageBase
    {
        public const byte Id = 0x02;

        public ConfigurationStatusMessage(byte[] rawData)
        {
            var extractor = new RawMessageExtractor(rawData);
            extractor.Get(ref firstNote);
            extractor.Get(ref velocity);
            extractor.Get(ref debouncingTime);
            extractor.Get(ref pedalPins, PinCount);
            extractor.Finish();
        }

        public ConfigurationStatusMessage()
        {
            firstNote = 12;
            velocity = 34;
            debouncingTime = 56;
            pedalPins = new byte[] { 1, 2, 3, 4 };
        }

        public override RawMessage Pack()
        {
            return Pack(Id);
        }
    }
}
