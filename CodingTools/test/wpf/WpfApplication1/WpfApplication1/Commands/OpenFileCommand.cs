using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Forms;

namespace WpfApplication1
{
    public class OpenFileCommand : ICommand
    {
        private MainViewModel _data;
        public OpenFileCommand(MainViewModel data)
        {
            _data = data;
        }
        public event EventHandler CanExecuteChanged;
        public bool CanExecute(object parameter)
        {
            return true;
        }
        public void Execute(object parameter)
        {
            OpenFileDialog dialog = new OpenFileDialog() { Filter = "Image Files|*.jpg;*.png;*.bmp;*.gif" };
            dialog.ShowDialog();
            if (true) {
                _data.ImagePath = dialog.FileName;
            }
        }
    }
}
