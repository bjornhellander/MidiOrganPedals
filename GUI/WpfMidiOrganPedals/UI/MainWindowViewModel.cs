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
        private readonly ObservableCollection<OnOffIndicatorViewModel> pressedPedals;
        private readonly ObservableCollection<OnOffIndicatorViewModel> playedNotes;
        private readonly ObservableCollection<OnOffIndicatorViewModel> pedalPins;

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

            pressedPedals = new ObservableCollection<OnOffIndicatorViewModel>();
            PressedPedals = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(pressedPedals);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                pressedPedals.Add(new OnOffIndicatorViewModel(i + 1, i % 2 != 0));
            }

            playedNotes = new ObservableCollection<OnOffIndicatorViewModel>();
            PlayedNotes = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(playedNotes);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                playedNotes.Add(new OnOffIndicatorViewModel(i + 1, i % 2 == 0));
            }

            FirstNote.SetValue(40);
            Velocity.SetValue(70);
            DebouncingTime.SetValue(125);

            pedalPins = new ObservableCollection<OnOffIndicatorViewModel>();
            PedalPins = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(pedalPins);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                pedalPins.Add(new OnOffIndicatorViewModel(i + 1, false));
            }

            EditCommand = new ManualCommand(HandleEditCommand, true);
            ApplyCommand = new ManualCommand(HandleApplyCommand, false);

            IsEditingConfiguration.SetValue(true);
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

            pressedPedals = new ObservableCollection<OnOffIndicatorViewModel>();
            PressedPedals = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(pressedPedals);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                pressedPedals.Add(new OnOffIndicatorViewModel(i + 1, false));
            }

            playedNotes = new ObservableCollection<OnOffIndicatorViewModel>();
            PlayedNotes = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(playedNotes);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                playedNotes.Add(new OnOffIndicatorViewModel(i + 1, false));
            }

            pedalPins = new ObservableCollection<OnOffIndicatorViewModel>();
            PedalPins = new ReadOnlyObservableCollection<OnOffIndicatorViewModel>(pedalPins);
            for (var i = 0; i < 8 * sizeof(uint); i++)
            {
                pedalPins.Add(new OnOffIndicatorViewModel(0, false));
            }

            EditCommand = new ManualCommand(HandleEditCommand, true);
            ApplyCommand = new ManualCommand(HandleApplyCommand, false);

            IsEditingConfiguration.SetValue(false);

            mainWindowView.DataContext = this;
        }

        public ReadOnlyObservableCollection<DeviceViewModel> AvailableDevices { get; }

        public Property<DeviceViewModel> SelectedDevice { get; } = new Property<DeviceViewModel>();

        public ReadOnlyObservableCollection<MessageViewModel> ReceivedMessages { get; }

        public ReadOnlyObservableCollection<OnOffIndicatorViewModel> PressedPedals { get; }

        public ReadOnlyObservableCollection<OnOffIndicatorViewModel> PlayedNotes { get; }

        public Property<int> FirstNote { get; } = new Property<int>();

        public Property<int> Velocity { get; } = new Property<int>();

        public Property<int> DebouncingTime { get; } = new Property<int>();

        public ReadOnlyObservableCollection<OnOffIndicatorViewModel> PedalPins { get; }

        public ManualCommand EditCommand { get; }

        public ManualCommand ApplyCommand { get; }

        public Property<bool> IsEditingConfiguration { get; } = new Property<bool>();

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
                var viewModelMessage = ProcessMessageViewModel(modelMessage);
                receivedMessages.Add(viewModelMessage);
            });
        }

        private MessageViewModel ProcessMessageViewModel(Message input)
        {
            string text;

            if (input is DebugMessage)
            {
                text = ((DebugMessage)input).Text;
            }
            else if (input is GeneralStatusMessage)
            {
                var input2 = (GeneralStatusMessage)input;
                text = $"General Status: {input2.ConfigurationOk}, {Convert.ToString(input2.PressedPedals, 2).PadLeft(32, '0')}, {Convert.ToString(input2.PlayedNotes, 2).PadLeft(32, '0')}, {input2.NumberOfToggledPedals}, {input2.NumberOfToggledNotes}, {input2.NumberOfReceivedBytes}, {input2.NumberOfDiscardedBytes}";

                for (int i = 0; i < 8 * sizeof(uint); i++)
                {
                    var pressed = (input2.PressedPedals >> i) % 2 != 0;
                    pressedPedals[i].IsOn.SetValue(pressed);

                    var played = (input2.PlayedNotes >> i) % 2 != 0;
                    playedNotes[i].IsOn.SetValue(played);
                }
            }
            else if (input is ConfigurationStatusMessage)
            {
                var input2 = (ConfigurationStatusMessage)input;
                var pedalPinsText = string.Join(", ", input2.PedalPins.Select(x => x.ToString()));
                text = $"Configuration Status: {input2.FirstNote}, {input2.Velocity}, {input2.DebouncingTime}, [{pedalPinsText}]";

                if (!IsEditingConfiguration.Value)
                {
                    FirstNote.SetValue(input2.FirstNote);
                    Velocity.SetValue(input2.Velocity);
                    DebouncingTime.SetValue(input2.DebouncingTime);

                    for (var i = 0; i < input2.PedalPins.Length; i++)
                    {
                        var obj = pedalPins[i];
                        obj.Value.SetValue(input2.PedalPins[i]);
                    }
                }
            }
            else
            {
                throw new NotImplementedException();
            }

            var output = new MessageViewModel(text);
            return output;
        }

        private void HandleExceptionCaught(Exception e)
        {
            //// NOTE: This method is not called on the UI thread
            dispatcher.Invoke(() =>
            {
                throw new AggregateException(e);
            });
        }

        private void HandleEditCommand()
        {
            EditCommand.CanExecute = false;
            ApplyCommand.CanExecute = true;

            IsEditingConfiguration.SetValue(true);

            foreach (var pedalPin in pedalPins)
            {
                pedalPin.IsEditable.SetValue(true);
            }
        }

        private void HandleApplyCommand()
        {
            EditCommand.CanExecute = true;
            ApplyCommand.CanExecute = false;

            IsEditingConfiguration.SetValue(false);

            foreach (var pedalPin in pedalPins)
            {
                pedalPin.IsEditable.SetValue(false);
            }

            var message = new ConfigurationRequestMessage(FirstNote.Value, Velocity.Value, DebouncingTime.Value, PedalPins.Select(x => x.Value.Value).ToArray());
            currentDevice.SendMessage(message);
        }
    }
}
