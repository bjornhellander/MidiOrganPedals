using WpfMidiOrganPedals;

namespace WpfMidiOrganPedals
{
    public interface IDeviceProvider
    {
        INotifiable<IDeviceInfo> DeviceAdded { get; }

        INotifiable<IDeviceInfo> DeviceDeleted { get; }

        void Start();
    }
}
