using WpfMidiOrganPedals;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public interface IDeviceProvider
    {
        INotifiable<IDeviceInfo> DeviceAdded { get; }

        INotifiable<IDeviceInfo> DeviceDeleted { get; }

        void Start();
    }
}
