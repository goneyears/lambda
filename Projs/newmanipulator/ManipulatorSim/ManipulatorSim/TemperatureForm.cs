using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Windows.Forms.DataVisualization.Charting;
using DATATYPE = System.Double;

namespace ManipulatorSim
{
    public partial class TemperatureForm : Form
    {
        Form1 mainForm;
        FirstOrderSystem S1;
        FirstOrderSystem S2;

        Series tempCurve;
        Series heatWatchBlock;
        public TemperatureForm()
        {
            InitializeComponent();
        }

        private void TemperatureForm_Load(object sender, EventArgs e)
        {
            mainForm =(Form1)this.Owner ;

            S1 = new FirstOrderSystem(50, 1.5, 1);
            S2 = new FirstOrderSystem(10, 3.9, 1);

            timer1.Enabled = true;
            timer2.Enabled = true;


            // 设置曲线的样式
            tempCurve = chart1.Series[1];
            heatWatchBlock = chart1.Series[0];
            // 画样条曲线（Spline）
            tempCurve.ChartType = SeriesChartType.Spline;
            heatWatchBlock.ChartType = SeriesChartType.Column;
            heatWatchBlock.Color = System.Drawing.Color.MistyRose;
            // 线宽2个像素
            tempCurve.BorderWidth = 1; 
            // 图示上的文字
            //series.LegendText = "温度变化曲线";



        }

        static bool manualHeaton = false;
        object plcHeaton;
        bool Heat;
        static bool pause = false;
        private void button1_Click(object sender, EventArgs e)
        {
            if (pause)
            {
                button1.Text = "Playing";
                pause = false;
                timer1.Enabled = true;
                timer2.Enabled = true;
            }
            else
            {
                button1.Text = "Pausing";
                pause = true;
                timer1.Enabled = false;
                timer2.Enabled = false;
            }
             

        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            ReadAllPLC();

            S1.h=S1.Ts0 *(S1.que_c.Dequeue());

            Heat = manualHeaton || (bool)plcHeaton;
            if (Heat)
            {
                S1.que_r.Enqueue(300);
                // chart1.Legends[0].ForeColor
                tempCurve.Color = System.Drawing.Color.Red;

            }
            else
            {
                S1.que_r.Enqueue(28);
                tempCurve.Color = System.Drawing.Color.SeaGreen;
                 
            }
            Debug.WriteLine("plcHeaton" + plcHeaton.ToString()); 
            S1.r = S1.que_r.Dequeue();
             
            S1.g = S1.Ts1 * S1.K * S1.r;
            S1.c = S1.h + S1.g;
            S1.que_c.Enqueue(S1.c);
            Debug.Write("S1.c:  " + S1.c.ToString() + "  ");

             
            S2.h = S2.Ts0 * (S2.que_c.Dequeue());
            S2.que_r.Enqueue(S1.c);
            S2.r = S2.que_r.Dequeue();
            S2.g = S2.Ts1 * S2.K * S2.r;
            S2.c = S2.h + S2.g;

            S2.que_c.Enqueue(S2.c);
            Debug.WriteLine("S2.c: " + S2.c.ToString());
           // T_label.Text = Math.Ceiling(S2.c).ToString();


            int piwValue = (int)(S2.c*27648/300);
            mainForm.ps.WriteInputPoint(290-2, 0, piwValue);

        }

        int x = 0;
        private void displaySpline()
        { 

            // 在chart中显示数据
 
                tempCurve.Points.AddXY(x, S2.c);
                if (Heat)
                {
                    heatWatchBlock.Points.AddXY(x, 100);
                }
                else
                {
                    heatWatchBlock.Points.AddXY(x, 20);
                }
                
                x++;
                if (x == 1000)
                {
                    x = 0;
                    tempCurve.Points.Clear();
                    heatWatchBlock.Points.Clear();

                }
                tempCurve.LegendText = ((int)(S2.c)).ToString();

            // 设置显示范围
            ChartArea chartArea = chart1.ChartAreas[0];
            chartArea.AxisX.Minimum = 0;
            chartArea.AxisX.Maximum = 1000;
            chartArea.AxisY.Minimum = 20d;
            chartArea.AxisY.Maximum = 100d;
            chartArea.AxisY.Interval = 10;
        }
        private void TemperatureForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            timer1.Enabled = false;
            timer2.Enabled = false;
        }

        private void PrintQueue<T>(Queue<T> _queue, string info = "Queue")
        {
            Debug.WriteLine(" ");
            Debug.Write(info + " ");
            foreach(T qData in _queue)
            {
                Debug.Write(qData + " ");
            }
            Debug.WriteLine(" ");
        }

        private void ReadAllPLC()
        {
            plcHeaton=mainForm.ReadPLCBit('Q', 5, 0);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

            displaySpline();
        }
    }


 

    class FirstOrderSystem
    {
        public FirstOrderSystem(DATATYPE T, DATATYPE toi, DATATYPE K)
        {
            const double NormalTemp = 28;
            this.T = T;
            this.toi = toi;
            this.K = K;

            c = NormalTemp;

            T0 = 0.1;
            Ts0 = T / (T + T0);
            Ts1 = T0 / (T0 + T);
            int n_toi_size = int.Parse(Math.Ceiling(toi / T0).ToString());
            Debug.WriteLine(n_toi_size);

            que_r = new Queue<DATATYPE>(n_toi_size);
            for (int i = 1; i <= n_toi_size - 1; i++)
            {
                que_r.Enqueue(NormalTemp);
            }

            que_h = new Queue<DATATYPE>(2);
            for (int i = 1; i <= 1; i++)
            {
                que_h.Enqueue(Ts0 * NormalTemp);
            }

            que_c = new Queue<DATATYPE>(2);
            for (int i = 1; i <= 1; i++)
            {
                que_c.Enqueue(NormalTemp);
            }
        }

        public DATATYPE T;
        public DATATYPE T0;
        public DATATYPE toi;
        public DATATYPE K;

        public DATATYPE Ts0;
        public DATATYPE Ts1;

        public DATATYPE c;
        public DATATYPE h;
        public DATATYPE g;
        public DATATYPE r;

        public Queue<DATATYPE> que_r;
        public Queue<DATATYPE> que_h;
        public Queue<DATATYPE> que_c;


    }
}
