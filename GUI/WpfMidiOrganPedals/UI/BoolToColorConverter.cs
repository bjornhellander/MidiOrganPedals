using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;

namespace WpfMidiOrganPedals.UI
{
    // TODO: Do this in a style instead!
    public class BoolToColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var value2 = value as bool? ?? false;
            var color = value2 ? Colors.Green : Colors.Gray;
            var brush = new SolidColorBrush(color);
            return brush;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
