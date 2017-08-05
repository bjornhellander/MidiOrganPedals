namespace WpfMidiOrganPedals
{
    public class DeviceViewModel
    {
        public DeviceViewModel(string name, IDeviceInfo info)
        {
            Name = name;
            Info = info;
        }

        public string Name { get; }

        public IDeviceInfo Info { get; }
    }
}
