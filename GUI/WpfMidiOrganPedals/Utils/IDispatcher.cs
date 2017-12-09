using System;

namespace WpfMidiOrganPedals.Utils
{
    public interface IDispatcher
    {
        void Invoke(Action action);
    }
}
