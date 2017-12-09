using System;
using System.Timers;

namespace WpfMidiOrganPedals.Devices
{
    public class SimulatedDevice : DeviceBase
    {
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
            var message = new Message(text);
            NotifyDataReceived(message);
        }
    }
}
