using System;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.Devices
{
    public interface IDevice
    {
        INotifiable<Message> MessageReceived { get; }

        INotifiable<Exception> ExceptionCaught { get; }

        void Close();

        void SendMessage(Message message);
    }
}
