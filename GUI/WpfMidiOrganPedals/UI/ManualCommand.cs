using System;
using System.Windows.Input;

namespace WpfMidiOrganPedals.UI
{
    public class ManualCommand : ICommand
    {
        private readonly Action execute;
        private bool canExecute;

        public ManualCommand(Action execute, bool canExecute)
        {
            this.execute = execute;
            this.canExecute = canExecute;
        }

        public event EventHandler CanExecuteChanged;
        
        public bool CanExecute
        {
            set
            {
                canExecute = value;
                CanExecuteChanged(this, EventArgs.Empty);
            }
        }

        bool ICommand.CanExecute(object parameter)
        {
            return canExecute;
        }

        void ICommand.Execute(object parameter)
        {
            execute();
        }
    }
}
