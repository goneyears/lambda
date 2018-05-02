using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using FLR.Model;
using System.Diagnostics;
using System.Windows;
using System.Windows.Threading;


namespace FLR.ViewModel
{
    public class UnitViewModel
    {

        public DispatcherTimer dispatcherTimer = new DispatcherTimer();



        public DelegateCommand ShowCommand { get; set; }
        public UnitModel Unit { get; set; }

        public int leftpers;
        public UnitViewModel()
        {

            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1);
            dispatcherTimer.Start();

            leftpers = 10;


            Unit = new UnitModel();
            for (int i = 0; i < 10; i++) {
                Unit.Size[i] = 128;
            }

            ShowCommand = new DelegateCommand();
            ShowCommand.ExecuteCommand = new Action<object>(ApplyChange);
        }

/// <summary>
        /// 定时器回调函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
           object obj = new Object();
           if(leftpers >1){
           ApplyChange(obj);
           }else
           {
               Unit.Result="End";
           }

         }

        Random rd = new Random();

        private void ApplyChange(object obj)
        {
            Unit.setBat();

            int r=0;
            r = rd.Next(0,2);
            int sbatsize;
            int batsize = (int)((minarr(Unit.Size)+1)*0.3);
            if (batsize == 0) batsize++;
            sbatsize = rd.Next(1, batsize);
            Debug.WriteLine("restult:   " + r + "    sbat: " + sbatsize.ToString());

            int wins = 0;
            leftpers = 0;
            for (int i = 0; i < 10; i++) {
                if (Unit.Size[i] > 0) {
                    leftpers++;
                    if (r == 1) {
                        if (Unit.Bat[i] == true) wins++;
                    }
                    else {

                        if (Unit.Bat[i] == false) wins++;
                    }
                }
            }

            int aget=0;
            if (wins != 0) {
                aget = sbatsize * leftpers / wins;


                for (int i = 0; i < 10; i++) {
                    if (Unit.Size[i] > 0) {
                        if (r == 1) {
                            if (Unit.Bat[i] == true) Unit.Size[i] += aget;
                            Unit.Size[i] -= sbatsize;
                        }
                        else {

                            if (Unit.Bat[i] == false) Unit.Size[i] += aget;
                            Unit.Size[i] -= sbatsize;
                        }
                    }
                }
            }

            bool rescale = false;
            for (int i = 0; i < 10; i++) {
                if (Unit.Size[i] > 0) {
                    Unit.Size[i] += rd.Next(0,3)* 1;
                }

                if (Unit.Size[i] > 900) rescale = true;
            }

            if (rescale) {
                for (int i = 0; i < 10; i++) {
                    if (Unit.Size[i] > 0) {
                        Unit.Size[i] /=2;
                    }
                     
                }
            }

            Unit.Size = Unit.Size;
            Unit.Result = "";
            int total = 0;
            for (int i = 0; i < 10; i++) {
                if (Unit.Size[i] == 0) {
                    Unit.Result += i.ToString()+"End";
                }
                total += Unit.Size[i];

            }
            Debug.WriteLine(total);
        }

        private int minarr(int[] arr)
        {
            int min = 999;
            for(int i=1 ; i<arr.Length; i++){
                if (arr[i] > 0) {
                    if (arr[i] < min) min = arr[i];
                }
            }
            return min;
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
