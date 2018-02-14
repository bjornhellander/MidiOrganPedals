using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace WpfMidiOrganPedals.UI
{
    public class BoolToVisibleHiddenConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var value2 = value as bool? ?? false;
            var visibility = value2 ? Visibility.Visible : Visibility.Hidden;
            return visibility;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
