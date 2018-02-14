namespace WpfMidiOrganPedals.Devices
{
    public class DebugMessage : Message
    {
        public const byte Id = 0x00;
        private const int TextLength = 32;

        private string text;

        public DebugMessage(byte[] rawData)
        {
            var extractor = new RawMessageExtractor(rawData);
            extractor.Get(ref text, TextLength);
            extractor.Finish();
        }

        public DebugMessage(string text)
        {
            this.text = text;
        }

        public string Text => text;

        public override RawMessage Pack()
        {
            var rawMessageBuilder = new RawMessageBuilder();
            rawMessageBuilder.Add(text, TextLength);
            var rawData = rawMessageBuilder.GetData();
            var message = new RawMessage(Id, rawData);
            return message;
        }
    }
}
