using System;
using System.Timers;

namespace WpfMidiOrganPedals.Devices
{
    public class SimulatedDevice : DeviceBase
    {
        private RawMessagePacker rawMessagePacker = new RawMessagePacker();
        private Timer timer;
        private int count = 0;

        public SimulatedDevice()
        {
            timer = new Timer(1000);
            timer.Elapsed += (s, e) => HandleTimerTick();
            timer.AutoReset = false;
            timer.Start();
        }

        public override void Close()
        {
            timer.Stop();
            timer = null;
        }

        public override void SendMessage(Message message)
        {
            throw new NotImplementedException();
        }

        private void HandleTimerTick()
        {
            count++;
            var text = $"Hello ({count})";
            SendMessage(text);

            timer.Start();
        }

        private void SendMessage(string text)
        {
            var message = new DebugMessage(text);
            var rawMessage = message.Pack();
            var rawData = CreateRawData(rawMessage);
            ProcessReceivedData(rawData);
        }

        private byte[] CreateRawData(RawMessage rawMessage)
        {
            var result = rawMessagePacker.Pack(rawMessage.RawData);
            return result;
        }
    }
}
