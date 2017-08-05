using System.Collections.ObjectModel;

namespace WpfMidiOrganPedals
{
    public class DeviceManager : IDeviceManager
    {
        private readonly Collection<IDeviceInfo> availableDevices = new Collection<IDeviceInfo>();
        private readonly Notifiable<IDeviceInfo> deviceAdded = new Notifiable<IDeviceInfo>();
        private readonly Notifiable<IDeviceInfo> deviceDeleted = new Notifiable<IDeviceInfo>();
        private readonly IDeviceProvider[] deviceProviders;

        public DeviceManager(IDeviceProvider[] deviceProviders)
        {
            this.deviceProviders = deviceProviders;

            foreach (var deviceProvider in deviceProviders)
            {
                deviceProvider.DeviceAdded.Subscribe(HandleDeviceAdded);
                deviceProvider.DeviceDeleted.Subscribe(HandleDeviceDeleted);
                deviceProvider.Start();
            }
        }

        public INotifiable<IDeviceInfo> DeviceAdded => deviceAdded;

        public INotifiable<IDeviceInfo> DeviceDeleted => deviceDeleted;

        private void HandleDeviceAdded(IDeviceInfo device)
        {
            availableDevices.Add(device);
            deviceAdded.Notify(device);
        }

        private void HandleDeviceDeleted(IDeviceInfo device)
        {
            availableDevices.Remove(device);
            deviceAdded.Notify(device);
        }
    }
}
