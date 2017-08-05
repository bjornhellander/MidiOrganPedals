using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Threading;

namespace WpfMidiOrganPedals
{
    public abstract class DeviceProviderBase : IDeviceProvider
    {
        private readonly List<IDeviceInfo> availableDevices = new List<IDeviceInfo>();
        private readonly Notifiable<IDeviceInfo> inputDeviceAdded = new Notifiable<IDeviceInfo>();
        private readonly Notifiable<IDeviceInfo> inputDeviceDeleted = new Notifiable<IDeviceInfo>();

        public INotifiable<IDeviceInfo> DeviceAdded => inputDeviceAdded;

        public INotifiable<IDeviceInfo> DeviceDeleted => inputDeviceDeleted;

        public void Start()
        {
            var timer = new DispatcherTimer();
            timer.Tick += (s, e) => HandleDeviceQueryTimer();
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.IsEnabled = true;
        }

        public void UpdateAvailableDevicesFromTest()
        {
            UpdateAvailableDevices();
        }

        protected abstract IReadOnlyList<IDeviceInfo> GetDevicesImpl();

        private void HandleDeviceQueryTimer()
        {
            UpdateAvailableDevices();
        }

        private void UpdateAvailableDevices()
        {
            var existingDevices = GetDevicesImpl();
            UpdateAvailableDevices(availableDevices, existingDevices, inputDeviceAdded, inputDeviceDeleted);
        }

        private void UpdateAvailableDevices<T>(ICollection<T> availableDevices, IReadOnlyCollection<T> existingDevices, Notifiable<T> deviceAdded, Notifiable<T> deviceDeleted)
            where T : IDeviceInfo
        {
            var devicesToRemove = availableDevices.Where(x => !existingDevices.Any(y => y.Name == x.Name)).ToList();
            foreach (var deviceToRemove in devicesToRemove)
            {
                availableDevices.Remove(deviceToRemove);
                deviceDeleted.Notify(deviceToRemove);
            }

            var devicesToAdd = existingDevices.Where(x => !availableDevices.Any(y => y.Name == x.Name)).ToList();
            foreach (var deviceToAdd in devicesToAdd)
            {
                availableDevices.Add(deviceToAdd);
                deviceAdded.Notify(deviceToAdd);
            }
        }
    }
}
