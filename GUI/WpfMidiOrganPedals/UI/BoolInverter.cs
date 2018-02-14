using System;
using System.Globalization;
using System.Windows.Data;

namespace WpfMidiOrganPedals.UI
{
    public class BoolInverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var value2 = value as bool? ?? false;
            return !value2;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
