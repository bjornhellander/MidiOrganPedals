using System;

namespace WpfMidiOrganPedals
{
    public interface INotifiable
    {
        void Subscribe(Action subscriber);
    }
}
