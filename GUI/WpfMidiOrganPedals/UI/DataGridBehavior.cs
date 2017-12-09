using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Windows;
using System.Windows.Controls;

namespace WpfMidiOrganPedals.UI
{
    public static class DataGridBehavior
    {
        public static readonly DependencyProperty AutoScrollProperty = DependencyProperty.RegisterAttached(
            "AutoScroll", typeof(bool), typeof(DataGridBehavior), new PropertyMetadata(default(bool), AutoScrollChangedCallback));

        private static readonly Dictionary<DataGrid, NotifyCollectionChangedEventHandler> Handlers = new Dictionary<DataGrid, NotifyCollectionChangedEventHandler>();

        public static void SetAutoScroll(DependencyObject element, bool value)
        {
            element.SetValue(AutoScrollProperty, value);
        }

        public static bool GetAutoScroll(DependencyObject element)
        {
            return (bool)element.GetValue(AutoScrollProperty);
        }

        private static void AutoScrollChangedCallback(DependencyObject dependencyObject, DependencyPropertyChangedEventArgs args)
        {
            var dataGrid = dependencyObject as DataGrid;
            if (dataGrid == null)
            {
                throw new InvalidOperationException("Dependency object is not DataGrid.");
            }

            if ((bool)args.NewValue)
            {
                Subscribe(dataGrid);
                dataGrid.Unloaded += DataGridOnUnloaded;
                dataGrid.Loaded += DataGridOnLoaded;
            }
            else
            {
                Unsubscribe(dataGrid);
                dataGrid.Unloaded -= DataGridOnUnloaded;
                dataGrid.Loaded -= DataGridOnLoaded;
            }
        }

        private static void DataGridOnLoaded(object sender, RoutedEventArgs routedEventArgs)
        {
            var dataGrid = (DataGrid)sender;
            if (GetAutoScroll(dataGrid))
            {
                Subscribe(dataGrid);
            }
        }

        private static void DataGridOnUnloaded(object sender, RoutedEventArgs routedEventArgs)
        {
            var dataGrid = (DataGrid)sender;
            if (GetAutoScroll(dataGrid))
            {
                Unsubscribe(dataGrid);
            }
        }

        private static void Subscribe(DataGrid dataGrid)
        {
            if (!Handlers.ContainsKey(dataGrid))
            {
                var handler = new NotifyCollectionChangedEventHandler((sender, eventArgs) => ScrollToEnd(dataGrid));
                Handlers.Add(dataGrid, handler);
                ((INotifyCollectionChanged)dataGrid.Items).CollectionChanged += handler;
            }

            ScrollToEnd(dataGrid);
        }

        private static void Unsubscribe(DataGrid dataGrid)
        {
            NotifyCollectionChangedEventHandler handler;
            Handlers.TryGetValue(dataGrid, out handler);
            if (handler == null)
            {
                return;
            }

            ((INotifyCollectionChanged)dataGrid.Items).CollectionChanged -= handler;
            Handlers.Remove(dataGrid);
        }

        private static void ScrollToEnd(DataGrid datagrid)
        {
            if (datagrid.Items.Count == 0)
            {
                return;
            }

            datagrid.ScrollIntoView(datagrid.Items[datagrid.Items.Count - 1]);
        }
    }
}
