namespace WpfMidiOrganPedals.UI
{
    public class OnOffIndicatorViewModel : ViewModelBase
    {
        public OnOffIndicatorViewModel()
        {
            Text = new Property<string>("ABC");
            IsOn = new Property<bool>(true);
            IsEditable = new Property<bool>(false);
        }

        public OnOffIndicatorViewModel(string text, bool isOn)
        {
            Text = new Property<string>(text);
            IsOn = new Property<bool>(isOn);
            IsEditable = new Property<bool>(false);
        }

        public Property<string> Text { get; }

        public Property<bool> IsOn { get; }

        public Property<bool> IsEditable { get; }
    }
}
