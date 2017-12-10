using System;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public abstract class DeviceBase : IDevice
    {
        private readonly RawMessageUnpacker rawMessageUnpacker = new RawMessageUnpacker();
        private readonly Notifiable<Message> messageReceived = new Notifiable<Message>();
        private readonly Notifiable<Exception> exceptionCaught = new Notifiable<Exception>();

        public DeviceBase()
        {
            rawMessageUnpacker.MessageFound += HandleRawMessageFound;
        }

        public INotifiable<Message> MessageReceived => messageReceived;

        public INotifiable<Exception> ExceptionCaught => exceptionCaught;

        public abstract void Close();

        public abstract void SendMessage(Message message);

        protected void ProcessReceivedData(byte[] data)
        {
            rawMessageUnpacker.Process(data);
        }

        private void HandleRawMessageFound(RawMessage rawMessage)
        {
            var text = "";
            foreach (var @byte in rawMessage.RawData)
            {
                if (@byte == 0)
                {
                    break;
                }

                text += (char)@byte;
            }

            var message = new Message(text);
            messageReceived.Notify(message);
        }

        protected void NotifyException(Exception e)
        {
            exceptionCaught.Notify(e);
        }
    }
}
