namespace WpfMidiOrganPedals.Devices
{
    public class RawMessage
    {
        public RawMessage(string text)
        {
            Text = text;
        }

        public string Text { get; }
    }
}
