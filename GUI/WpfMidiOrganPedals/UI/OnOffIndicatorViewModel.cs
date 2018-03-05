namespace WpfMidiOrganPedals.UI
{
    public class OnOffIndicatorViewModel : ViewModelBase
    {
        public OnOffIndicatorViewModel()
        {
            Value = new Property<int>(123);
            IsOn = new Property<bool>(true);
            IsEditable = new Property<bool>(false);
        }

        public OnOffIndicatorViewModel(int value, bool isOn)
        {
            Value = new Property<int>(value);
            IsOn = new Property<bool>(isOn);
            IsEditable = new Property<bool>(false);
        }

        public Property<int> Value { get; }

        public Property<bool> IsOn { get; }

        public Property<bool> IsEditable { get; }
    }
}
