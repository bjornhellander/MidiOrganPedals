namespace WpfMidiOrganPedals.Devices
{
    internal class GeneralStatusMessage : Message
    {
        public const byte Id = 0x01;

        private bool configurationOk;
        private uint pressedPedals;
        private uint playedNotes;
        private ushort numberOfToggledPedals;
        private ushort numberOfToggledNotes;
        private ushort numberOfDiscardedBytes;

        public GeneralStatusMessage(byte[] rawData)
        {
            var extractor = new RawMessageExtractor(rawData);
            extractor.Get(ref configurationOk);
            extractor.Get(ref pressedPedals);
            extractor.Get(ref playedNotes);
            extractor.Get(ref numberOfToggledPedals);
            extractor.Get(ref numberOfToggledNotes);
            extractor.Get(ref numberOfDiscardedBytes);
            extractor.Finish();
        }

        public GeneralStatusMessage()
        {
            configurationOk = true;
            pressedPedals = 0b01010101010101010101010101010101;
            playedNotes = 0b10101010101010101010101010101010;
            numberOfToggledPedals = 33;
            numberOfToggledNotes = 34;
            numberOfDiscardedBytes = 123;
        }

        public bool ConfigurationOk => configurationOk;
        public uint PressedPedals => pressedPedals;
        public uint PlayedNotes => playedNotes;
        public ushort NumberOfToggledPedals => numberOfToggledPedals;
        public ushort NumberOfToggledNotes => numberOfToggledNotes;
        public ushort NumberOfDiscardedBytes => numberOfDiscardedBytes;

        public override RawMessage Pack()
        {
            var rawMessageBuilder = new RawMessageBuilder();
            rawMessageBuilder.Add(configurationOk);
            rawMessageBuilder.Add(pressedPedals);
            rawMessageBuilder.Add(playedNotes);
            rawMessageBuilder.Add(numberOfToggledPedals);
            rawMessageBuilder.Add(numberOfToggledNotes);
            rawMessageBuilder.Add(numberOfDiscardedBytes);
            var rawData = rawMessageBuilder.GetData();
            var message = new RawMessage(Id, rawData);
            return message;
        }
    }
}
