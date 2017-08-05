using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace WpfMidiOrganPedals
{
    public class Notifiable : INotifiable
    {
        private Collection<Action> subscribers = new Collection<Action>();

        public void Subscribe(Action subscriber)
        {
            subscribers.Add(subscriber);
        }

        public void Notify()
        {
            var tempSubscribers = subscribers.ToList();
            foreach (var subscriber in tempSubscribers)
            {
                subscriber();
            }
        }
    }
}
