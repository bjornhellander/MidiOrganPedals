using System;
using System.Windows.Input;

namespace WpfMidiOrganPedals.UI
{
    public class DelegateCommand : ICommand
    {
        private readonly Action doExecute;
        private bool canExecute;

        public DelegateCommand(Action doExecute, bool canExecute = true)
        {
            this.canExecute = canExecute;
            this.doExecute = doExecute;
        }

        public event EventHandler CanExecuteChanged;

        public bool CanExecute
        {
            get
            {
                return canExecute;
            }

            set
            {
                canExecute = value;
                CanExecuteChanged(this, new EventArgs());
            }
        }

        bool ICommand.CanExecute(object parameter)
        {
            return canExecute;
        }

        public void Execute(object parameter)
        {
            doExecute();
        }
    }
}
