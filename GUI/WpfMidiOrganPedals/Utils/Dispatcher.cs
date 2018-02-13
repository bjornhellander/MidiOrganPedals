using System;

namespace WpfMidiOrganPedals.Utils
{
    public class Dispatcher : IDispatcher
    {
        public void Invoke(Action action)
        {
            var application = System.Windows.Application.Current;
            if (application != null) // Can become null while shutting down. Just ignore it in that case.
            {
                var nativeDispatcher = application.Dispatcher;
                nativeDispatcher.Invoke(action);
            }
        }
    }
}
