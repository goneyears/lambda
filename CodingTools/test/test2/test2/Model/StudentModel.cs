using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel; 


namespace test2.Model
{

    public class UnitModel : INotifyPropertyChanged
    {

        /// <summary>  
        /// 大小
        /// </summary>  
        private int size1;
        public int Size1
        {
            get
            {
                return size1;
            }
            set
            {
                size1 = value;
                NotifyPropertyChanged("Size1");
            }
        }

        private int size2;
        public int Size2
        {
            get
            {
                return size2;
            }
            set
            {
                size2 = value;
                NotifyPropertyChanged("Size2");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null) {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}  
