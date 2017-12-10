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

        public override void SendMessage(Message message)
        {
            throw new NotImplementedException();
        }

        private void HandleDataReceived()
        {
            //// NOTE: This method is not called on the UI thread
            try
            {
                var data = new byte[serialPort.BytesToRead];
                serialPort.Read(data, 0, data.Length);

                var text = "";
                foreach (var @byte in data)
                {
                    var @char = (char)@byte;
                    text = text + @char;
                }

                HandleMessageFound(text);
            }
            catch (Exception e)
            {
                NotifyException(e);
                throw;
            }
        }

        private void HandleMessageFound(string text)
        {
            var message = new RawMessage(text);
            NotifyDataReceived(message);
        }
    }
}
