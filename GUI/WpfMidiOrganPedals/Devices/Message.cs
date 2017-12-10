using System;

namespace WpfMidiOrganPedals.Devices
{
    public class Message
    {
        public Message(string text)
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

            var result = new RawMessage(rawData);
            return result;
        }
    }
}
