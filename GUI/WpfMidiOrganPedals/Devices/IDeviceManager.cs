using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public interface IDeviceManager
    {
        INotifiable<IDeviceInfo> DeviceAdded { get; }

        INotifiable<IDeviceInfo> DeviceDeleted { get; }
    }
}
