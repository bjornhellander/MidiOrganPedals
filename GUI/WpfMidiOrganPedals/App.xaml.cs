using System.Windows;

namespace WpfMidiOrganPedals
{
    public partial class App : Application
    {
        private void StartApp(object sender, StartupEventArgs e)
        {
            var mainWindowView = new MainWindow();
            Current.MainWindow = mainWindowView;
            mainWindowView.Show();
        }
    }
}
