using System.Collections.Generic;

namespace WpfMidiOrganPedals
{
    public class SimulatedDeviceProvider : DeviceProviderBase
    {
        private readonly bool addSimulatedDevice;
        private readonly SimulatedDeviceInfo simulatedDeviceInfo;

        public SimulatedDeviceProvider(bool addSimulatedDevice)
        {
            this.addSimulatedDevice = addSimulatedDevice;

            simulatedDeviceInfo = new SimulatedDeviceInfo();
        }

        protected override IReadOnlyList<IDeviceInfo> GetDevicesImpl()
        {
            var devices = new List<IDeviceInfo>();

            if (addSimulatedDevice)
            {
                devices.Add(simulatedDeviceInfo);
            }

            return devices;
        }
    }
}
