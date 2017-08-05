namespace WpfMidiOrganPedals
{
    public interface IDeviceManager
    {
        INotifiable<IDeviceInfo> DeviceAdded { get; }

        INotifiable<IDeviceInfo> DeviceDeleted { get; }
    }
}
