using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace WpfMidiOrganPedals
{
    public class Notifiable<T> : INotifiable<T>
    {
        private Collection<Action<T>> subscribers = new Collection<Action<T>>();

        public void Subscribe(Action<T> subscriber)
        {
            subscribers.Add(subscriber);
        }

        public void Notify(T value)
        {
            var tempSubscribers = subscribers.ToList();
            foreach (var subscriber in tempSubscribers)
            {
                subscriber(value);
            }
        }
    }
}
