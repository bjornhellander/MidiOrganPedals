using System;

namespace WpfMidiOrganPedals
{
    public interface IDispatcher
    {
        void Invoke(Action action);
    }
}
