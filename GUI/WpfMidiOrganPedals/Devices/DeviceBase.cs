using System;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public abstract class DeviceBase : IDevice
    {
        private readonly RawMessagePacker rawMessagePacker = new RawMessagePacker();
        private readonly RawMessageUnpacker rawMessageUnpacker = new RawMessageUnpacker();
        private readonly MessageUnpacker messageUnpacker = new MessageUnpacker();
        private readonly Notifiable<Message> messageReceived = new Notifiable<Message>();
        private readonly Notifiable<Exception> exceptionCaught = new Notifiable<Exception>();

        public DeviceBase()
        {
            rawMessageUnpacker.MessageFound += HandleRawMessageFound;
        }

        public INotifiable<Message> MessageReceived => messageReceived;

        public INotifiable<Exception> ExceptionCaught => exceptionCaught;

        public abstract void Close();

        public void SendMessage(Message message)
        {
            var rawMessage = message.Pack();
            var buffer = rawMessagePacker.Pack(rawMessage.Id, rawMessage.RawData);
            SendMessage(buffer);
        }

        protected abstract void SendMessage(byte[] buffer);

        protected void ProcessReceivedData(byte[] data)
        {
            rawMessageUnpacker.Process(data);
        }

        private void HandleRawMessageFound(RawMessage rawMessage)
        {
            var message = messageUnpacker.Unpack(rawMessage);
            messageReceived.Notify(message);
        }

        protected void NotifyException(Exception e)
        {
            exceptionCaught.Notify(e);
        }
    }
}
