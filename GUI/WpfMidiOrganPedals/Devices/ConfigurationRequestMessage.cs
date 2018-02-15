using System.Linq;

namespace WpfMidiOrganPedals.Devices
{
    internal class ConfigurationRequestMessage : ConfigurationMessageBase
    {
        public const byte Id = 0x03;

        public ConfigurationRequestMessage(int firstNote, int velocity, int debouncingTime, int[] pedalPins)
        {
            this.firstNote = (byte)firstNote;
            this.velocity = (byte)velocity;
            this.debouncingTime = (byte)debouncingTime;
            this.pedalPins = pedalPins.Select(x => (byte)x).ToArray();
        }

        public override RawMessage Pack()
        {
            return Pack(Id);
        }
    }
}
