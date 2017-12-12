namespace WpfMidiOrganPedals.Devices
{
    public class DebugMessage : Message
    {
        public const byte Id = 0x00;

        public DebugMessage(byte[] rawData)
        {
            var text = "";
            foreach (var @byte in rawData)
            {
                text += (char)@byte;
            }

            Text = text;
        }

        public DebugMessage(string text)
        {
            Text = text;
        }

        public string Text { get; }

        internal RawMessage Pack()
        {
            var rawData = new byte[Text.Length];
            for (var i = 0; i < Text.Length; i++)
            {
                rawData[i] = (byte)Text[i];
            }

            var result = new RawMessage(Id, rawData);
            return result;
        }
    }
}
