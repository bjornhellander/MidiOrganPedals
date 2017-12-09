using System;

namespace WpfMidiOrganPedals.Utils
{
    public interface INotifiable
    {
        void Subscribe(Action subscriber);
    }
}
