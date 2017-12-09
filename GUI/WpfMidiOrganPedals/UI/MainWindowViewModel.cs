using System;
using System.Collections.ObjectModel;
using System.Linq;
using WpfMidiOrganPedals.Devices;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals.UI
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly IDeviceManager deviceManager;
        private readonly IDispatcher dispatcher;
        private readonly ObservableCollection<DeviceViewModel> availableDevices;
        private readonly ObservableCollection<MessageViewModel> receivedMessages;

        private IDevice currentDevice;

        public MainWindowViewModel()
        {
            availableDevices = new ObservableCollection<DeviceViewModel>();
            var dummyDevice = new DeviceViewModel("COM1", null);
            availableDevices.Add(dummyDevice);
            AvailableDevices = new ReadOnlyObservableCollection<DeviceViewModel>(availableDevices);
            SelectedDevice.SetValue(dummyDevice);

            receivedMessages = new ObservableCollection<MessageViewModel>();
            receivedMessages.Add(new MessageViewModel("A"));
            receivedMessages.Add(new MessageViewModel("B"));
            receivedMessages.Add(new MessageViewModel("C"));
            ReceivedMessages = new ReadOnlyObservableCollection<MessageViewModel>(receivedMessages);
        }

        public MainWindowViewModel(
            IMainWindow mainWindowView,
            IDeviceManager deviceManager,
            IDispatcher dispatcher)
        {
            this.deviceManager = deviceManager;
            this.dispatcher = dispatcher;

            availableDevices = new ObservableCollection<DeviceViewModel>();
            var noDeviceViewModel = new DeviceViewModel("-", null);
            availableDevices.Add(noDeviceViewModel);
            AvailableDevices = new ReadOnlyObservableCollection<DeviceViewModel>(availableDevices);
            SelectedDevice.SetValue(noDeviceViewModel);
            SelectedDevice.ValueChanged.Subscribe(HandleDeviceChanged);

            receivedMessages = new ObservableCollection<MessageViewModel>();
            ReceivedMessages = new ReadOnlyObservableCollection<MessageViewModel>(receivedMessages);

            deviceManager.DeviceAdded.Subscribe(HandleDeviceAdded);
            deviceManager.DeviceDeleted.Subscribe(HandleDeviceDeleted);

            mainWindowView.DataContext = this;
        }

        public ReadOnlyObservableCollection<DeviceViewModel> AvailableDevices { get; }

        public Property<DeviceViewModel> SelectedDevice { get; } = new Property<DeviceViewModel>();

        public ReadOnlyObservableCollection<MessageViewModel> ReceivedMessages { get; }

        private void HandleDeviceAdded(IDeviceInfo deviceInfo)
        {
            var deviceViewModel = new DeviceViewModel(deviceInfo.Name, deviceInfo);
            availableDevices.Add(deviceViewModel);
        }

        private void HandleDeviceDeleted(IDeviceInfo deviceInfo)
        {
            if (SelectedDevice.Value == deviceInfo)
            {
                var noDevice = availableDevices.Single(x => x.Info == null);
                SelectedDevice.SetValue(noDevice);
            }

            var deviceViewModel = availableDevices.Single(x => x.Info == deviceInfo);
            availableDevices.Remove(deviceViewModel);
        }

        private void HandleDeviceChanged(DeviceViewModel newDevice)
        {
            if (currentDevice != null)
            {
                currentDevice.Close();
                currentDevice = null;
            }

            if (newDevice.Info != null)
            {
                currentDevice = newDevice.Info.Open();
                currentDevice.MessageReceived.Subscribe(HandleMessageReceived);
                currentDevice.ExceptionCaught.Subscribe(HandleExceptionCaught);
            }
        }

        private void HandleMessageReceived(Message modelMessage)
        {
            //// NOTE: This method is not called on the UI thread
            dispatcher.Invoke(() =>
            {
                var viewModelMessage = new MessageViewModel(modelMessage.Text);
                receivedMessages.Add(viewModelMessage);
            });
        }

        private void HandleExceptionCaught(Exception e)
        {
            //// NOTE: This method is not called on the UI thread
            dispatcher.Invoke(() =>
            {
                throw new AggregateException(e);
            });
        }
    }
}
