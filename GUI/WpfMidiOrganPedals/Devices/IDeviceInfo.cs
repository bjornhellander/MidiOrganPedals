namespace WpfMidiOrganPedals.Devices
{
    public interface IDeviceInfo
    {
        string Name { get; }

        IDevice Open();
    }
}
