namespace WpfMidiOrganPedals
{
    public interface IDeviceInfo
    {
        string Name { get; }

        IDevice Open();
    }
}
