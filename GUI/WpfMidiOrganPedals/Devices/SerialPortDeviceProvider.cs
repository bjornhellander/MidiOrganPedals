using System.Collections.Generic;
using System.Linq;

namespace WpfMidiOrganPedals.Devices
{
    public class SerialPortDeviceProvider : DeviceProviderBase
    {
        protected override IReadOnlyList<IDeviceInfo> GetDevicesImpl()
        {
            var portNames = System.IO.Ports.SerialPort.GetPortNames();
            var devices = portNames.Select(x => new SerialPortDeviceInfo(x)).ToList();
            return devices;
        }
    }
}
