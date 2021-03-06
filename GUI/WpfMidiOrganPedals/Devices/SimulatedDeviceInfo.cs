﻿namespace WpfMidiOrganPedals.Devices
{
    public class SimulatedDeviceInfo : IDeviceInfo
    {
        public string Name => "Simulator";

        public IDevice Open()
        {
            return new SimulatedDevice();
        }
    }
}
