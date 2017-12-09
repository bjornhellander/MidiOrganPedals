namespace WpfMidiOrganPedals.Devices
{
    public class SerialPortDeviceInfo : IDeviceInfo
    {
        public SerialPortDeviceInfo(string name)
        {
            Name = name;
        }

        public string Name { get; }

        public IDevice Open()
        {
            var device = new SerialPortDevice(this);
            return device;
        }
    }
}
