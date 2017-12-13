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
            switch (count++ % 2)
            {
                case 0:
                    SimulateDebugMessage();
                    break;
                case 1:
                    SimulateGeneralStatusMessage();
                    break;
            }

            timer.Start();
        }

        private void SimulateDebugMessage()
        {
            var text = $"Hello ({count})";
            var message = new DebugMessage(text);
            SimulateMessage(DebugMessage.Id, message);
        }

        private void SimulateGeneralStatusMessage()
        {
            var message = new GeneralStatusMessage();
            SimulateMessage(GeneralStatusMessage.Id, message);
        }

        private void SimulateMessage(byte id, Message message)
        {
            var rawMessage = message.Pack();
            var rawData = CreateRawData(id, rawMessage);
            ProcessReceivedData(rawData);
        }

        private byte[] CreateRawData(byte id, RawMessage rawMessage)
        {
            var result = rawMessagePacker.Pack(id, rawMessage.RawData);
            return result;
        }
    }
}
