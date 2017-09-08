using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
namespace Cell5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        LabelPrinter labelPrinter;
        private void button1_Click(object sender, EventArgs e)
        {
           // labelPrinter.GetImage();
         //   labelPrinter.PrintImage();
        }

 

        private void button2_Click(object sender, EventArgs e)
        {

         
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //labelPrinter.GetImage("59a901265a6f151e004734ef.png");
           // labelPrinter.PrintImage();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            labelPrinter = new LabelPrinter(pictureBox);
        }

        private void MessageTimer_Tick(object sender, EventArgs e)
        {
            MessageTextBox.Text = Messages.Text;
            MessageTextBox.Focus();
            MessageTextBox.Select(MessageTextBox.TextLength, 0);
            MessageTextBox.ScrollToCaret();
        }  
    }
}
