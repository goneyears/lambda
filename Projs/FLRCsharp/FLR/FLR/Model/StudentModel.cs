using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
namespace FLR.Model
{

    public class Pers
    {
        public Pers()
        {
            
        }

        public int Size;
        public bool State;
        public bool Bat;
    }

    public class UnitModel : INotifyPropertyChanged
    {
        public UnitModel()
        {
            for (int i = 0; i < 10; i++) {
                State[i] = true;
            }
        }
        /// <summary>  
        /// 大小
        /// </summary>  
        private int[] size = new int[10];
        public int[] Size
        {
            get
            {
                return size;
            }
            set
            {
                size = value;
                NotifyPropertyChanged("Size");
            }
        }

        private bool[] bat = new bool[10];
        public bool[] Bat
        {
            get
            {
                return bat;
            }
            set
            {
                bat = value;
                NotifyPropertyChanged("Bat");
            }
        }

        public bool[] state = new bool[10];
        public bool[] State
        {
            get
            {
                for (int i = 0; i < 10; i++) {
                    if (Size[i] > 0) {
                        state[i] = true;
                    }
                    else {
                        state[i] = false;
                    }
                }
                return state;
            }
            set
            {
                state = value;
                NotifyPropertyChanged("State");
            }
        }

        public void setBat()
        {
            Random rd = new Random();
            for (int i = 0; i < 10; i++) {
                if (rd.Next(0, 2) == 1) {
                    Bat[i] = true;
                }
                else {
                    Bat[i] = false;
                }
                Debug.WriteLine(Bat[i]);
            }
        }
        private string result;
        public string Result
        {
            get
            {
                return result;
            }
            set
            {
                result = value;
                NotifyPropertyChanged("Result");
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
