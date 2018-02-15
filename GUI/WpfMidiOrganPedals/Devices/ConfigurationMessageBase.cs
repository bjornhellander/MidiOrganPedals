namespace WpfMidiOrganPedals.Devices
{
    internal abstract class ConfigurationMessageBase : Message
    {
        public const int PinCount = 32;

        protected byte firstNote;
        protected byte velocity;
        protected byte debouncingTime;
        protected byte[] pedalPins;

        public byte FirstNote => firstNote;
        public byte Velocity => velocity;
        public byte DebouncingTime => debouncingTime;
        public byte[] PedalPins => pedalPins;

        protected RawMessage Pack(byte id)
        {
            var rawMessageBuilder = new RawMessageBuilder();
            rawMessageBuilder.Add(firstNote);
            rawMessageBuilder.Add(velocity);
            rawMessageBuilder.Add(debouncingTime);
            rawMessageBuilder.Add(pedalPins, PinCount);
            var rawData = rawMessageBuilder.GetData();
            var message = new RawMessage(id, rawData);
            return message;
        }
    }
}
