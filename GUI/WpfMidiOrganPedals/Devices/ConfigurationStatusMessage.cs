namespace WpfMidiOrganPedals.Devices
{
    internal class ConfigurationStatusMessage : Message
    {
        public const byte Id = 0x02;
        public const int PinCount = 32;

        private bool configurationOk;
        private byte firstNote;
        private byte velocity;
        private byte debouncingTime;
        private byte[] pedalPins;

        public ConfigurationStatusMessage(byte[] rawData)
        {
            var extractor = new RawMessageExtractor(rawData);
            extractor.Get(ref configurationOk);
            extractor.Get(ref firstNote);
            extractor.Get(ref velocity);
            extractor.Get(ref debouncingTime);
            extractor.Get(ref pedalPins, PinCount);
            extractor.Finish();
        }

        public ConfigurationStatusMessage()
        {
            configurationOk = true;
            firstNote = 12;
            velocity = 34;
            debouncingTime = 56;
            pedalPins = new byte[] { 1, 2, 3, 4 };
        }

        public bool ConfigurationOk => configurationOk;
        public byte FirstNote => firstNote;
        public byte Velocity => velocity;
        public byte DebouncingTime => debouncingTime;
        public byte[] PedalPins => pedalPins;

        public override RawMessage Pack()
        {
            var rawMessageBuilder = new RawMessageBuilder();
            rawMessageBuilder.Add(configurationOk);
            rawMessageBuilder.Add(firstNote);
            rawMessageBuilder.Add(velocity);
            rawMessageBuilder.Add(debouncingTime);
            rawMessageBuilder.Add(pedalPins, PinCount);
            var rawData = rawMessageBuilder.GetData();
            var message = new RawMessage(Id, rawData);
            return message;
        }
    }
}
