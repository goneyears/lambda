using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using test2.Model;  
namespace test2.ViewModel
{
    public class UnitViewModel
    {
        public DelegateCommand ShowCommand { get; set; }
        public UnitModel Unit { get; set; }
        public UnitViewModel()
        {
            Unit = new UnitModel();
            Unit.Size1 = 30;

            Unit.Size2 = 30;
            ShowCommand = new DelegateCommand();
            ShowCommand.ExecuteCommand = new Action<object>(ApplyChange);
        }
        private void ApplyChange(object obj)
        {
            Unit.Size1 = Unit.Size1 + 20;
            Unit.Size2 = Unit.Size2 + 20;
        }
    }

    public class DelegateCommand : ICommand
    {
        public Action<object> ExecuteCommand = null;
        public Func<object, bool> CanExecuteCommand = null;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            if (CanExecuteCommand != null) {
                return this.CanExecuteCommand(parameter);
            }
            else {
                return true;
            }
        }

        public void Execute(object parameter)
        {
            if (this.ExecuteCommand != null) {
                this.ExecuteCommand(parameter);
            }
        }

        public void RaiseCanExecuteChanged()
        {
            if (CanExecuteChanged != null) {
                CanExecuteChanged(this, EventArgs.Empty);
            }
        }
    }
}  
