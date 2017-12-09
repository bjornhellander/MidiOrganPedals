using System;

namespace WpfMidiOrganPedals.Utils
{
    public interface INotifiable<T>
    {
        void Subscribe(Action<T> subscriber);
    }
}
