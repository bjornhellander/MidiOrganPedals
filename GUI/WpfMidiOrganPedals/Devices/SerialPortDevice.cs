﻿using System;

namespace WpfMidiOrganPedals.Devices
{
    public class SerialPortDevice : DeviceBase
    {
        private System.IO.Ports.SerialPort serialPort;

        public SerialPortDevice(SerialPortDeviceInfo deviceInfo)
        {
            serialPort = new System.IO.Ports.SerialPort(deviceInfo.Name);
            serialPort.Open();
            serialPort.DataReceived += (s, e) => HandleDataReceived();
        }

        public override void Close()
        {
            serialPort.Close();
            serialPort = null;
        }

        protected override void SendMessage(byte[] buffer)
        {
            serialPort.Write(buffer, 0, buffer.Length);
        }

        private void HandleDataReceived()
        {
            //// NOTE: This method is not called on the UI thread
            try
            {
                var data = new byte[serialPort.BytesToRead];
                serialPort.Read(data, 0, data.Length);
                ProcessReceivedData(data);
            }
            catch (Exception e)
            {
                NotifyException(e);
                throw;
            }
        }
    }
}
