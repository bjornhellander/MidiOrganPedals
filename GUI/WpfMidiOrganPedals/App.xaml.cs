using System.Windows;
using WpfMidiOrganPedals.Devices;
using WpfMidiOrganPedals.UI;
using WpfMidiOrganPedals.Utils;

namespace WpfMidiOrganPedals
{
    public partial class App : Application
    {
        private void StartApp(object sender, StartupEventArgs e)
        {
            var serialPortDeviceProvider = new SerialPortDeviceProvider();
            var simulatedDeviceProvider = new SimulatedDeviceProvider(addSimulatedDevice: true);
            var deviceManager = new DeviceManager(new IDeviceProvider[] { serialPortDeviceProvider, simulatedDeviceProvider });

            var mainWindowView = new MainWindow();
            var dispatcher = new Dispatcher();
            var mainWindowViewModel = new MainWindowViewModel(mainWindowView, deviceManager, dispatcher);
            Current.MainWindow = mainWindowView;
            mainWindowView.Show();
        }
    }
}
