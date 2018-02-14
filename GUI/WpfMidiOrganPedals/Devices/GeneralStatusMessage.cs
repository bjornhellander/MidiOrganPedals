namespace WpfMidiOrganPedals.Devices
{
    internal class GeneralStatusMessage : Message
    {
        public const byte Id = 0x01;

        private uint pressedPedals;
        private uint playedNotes;
        private ushort numberOfToggledPedals;
        private ushort numberOfToggledNotes;
        private ushort numberOfDiscardedBytes;

        public GeneralStatusMessage(byte[] rawData)
        {
            var extractor = new RawMessageExtractor(rawData);
            extractor.Get(ref pressedPedals);
            extractor.Get(ref playedNotes);
            extractor.Get(ref numberOfToggledPedals);
            extractor.Get(ref numberOfToggledNotes);
            extractor.Get(ref numberOfDiscardedBytes);
            extractor.Finish();
        }

        public GeneralStatusMessage()
        {
            pressedPedals = 0b01010101010101010101010101010101;
            playedNotes = 0b10101010101010101010101010101010;
            numberOfToggledPedals = 33;
            numberOfToggledNotes = 34;
            numberOfDiscardedBytes = 123;
        }

        public uint PressedPedals => pressedPedals;
        public uint PlayedNotes => playedNotes;
        public ushort NumberOfToggledPedals => numberOfToggledPedals;
        public ushort NumberOfToggledNotes => numberOfToggledNotes;
        public ushort NumberOfDiscardedBytes => numberOfDiscardedBytes;

        public override RawMessage Pack()
        {
            var rawMessageBuilder = new RawMessageBuilder();
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
