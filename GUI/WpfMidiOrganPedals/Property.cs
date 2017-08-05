namespace WpfMidiOrganPedals
{
    public class Property<T> : NotifyPropertyChangedBase
    {
        private readonly Notifiable<T> valueChanged = new Notifiable<T>();
        private T currentValue;

        public T Value
        {
            get
            {
                return currentValue;
            }

            // NOTE: This should ONLY be used from XAML!!! Code should use SetValue() instead!
            set
            {
                var changed = SetProperty(ref currentValue, value);
                if (changed)
                {
                    valueChanged.Notify(value);
                }
            }
        }

        public INotifiable<T> ValueChanged => valueChanged;

        public void SetValue(T newValue)
        {
            SetProperty(ref currentValue, newValue, "Value");
        }

        public void SetValueFromTest(T newValue)
        {
            Value = newValue;
        }
    }
}
