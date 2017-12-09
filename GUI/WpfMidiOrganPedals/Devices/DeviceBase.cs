using System;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public abstract class DeviceBase : IDevice
    {
        private readonly Notifiable<Message> messageReceived = new Notifiable<Message>();

        private readonly Notifiable<Exception> exceptionCaught = new Notifiable<Exception>();

        public INotifiable<Message> MessageReceived => messageReceived;

        public INotifiable<Exception> ExceptionCaught => exceptionCaught;

        public abstract void Close();

        public abstract void SendMessage(Message message);

        protected void NotifyDataReceived(Message msg)
        {
            messageReceived.Notify(msg);
        }

        protected void NotifyException(Exception e)
        {
            exceptionCaught.Notify(e);
        }
    }
}
