using System;

namespace WpfMidiOrganPedals.Utils
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
