using System;

namespace WpfMidiOrganPedals
{
    public class Dispatcher : IDispatcher
    {
        public void Invoke(Action action)
        {
            var nativeDispatcher = System.Windows.Application.Current.Dispatcher;
            nativeDispatcher.Invoke(action);
        }
    }
}
