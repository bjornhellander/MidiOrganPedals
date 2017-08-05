using System;

namespace WpfMidiOrganPedals
{
    public interface INotifiable<T>
    {
        void Subscribe(Action<T> subscriber);
    }
}
