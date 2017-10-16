using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Data.SqlClient;
using Microsoft.VisualBasic;
using System.Net;
using System.Net.Sockets; 
namespace SQLAGV
{
    public partial class Form1 : Form
    {
 
        public Form1()
        {
            InitializeComponent();
        }
        TCP_Client tcpclient;
        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;

        }

        private void sysGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            MessageBox.Show("datagrid view error");
        }

        private void button1_Click(object sender, EventArgs e)
        {

            tcpclient = new TCP_Client("127.0.0.1", "9876");
            tcpclient.Send("csharpsend\r\n");
            Debug.WriteLine(tcpclient.IsConnected());
            tcpclient.Dispose();
        }
        byte addressOffset = 0xc8;
        int port;
        string host;//服务器端ip地址

        IPAddress ip;
        IPEndPoint ipe;

        Socket clientSocket;
        private void button2_Click(object sender, EventArgs e)
        {


      
            string str = "ab\n";
            byte[] sendBytes = Encoding.UTF8.GetBytes(str);
            Debug.WriteLine(sendBytes.ToString());
            clientSocket.Send(sendBytes);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string str = "bc\n";
            byte[] sendBytes = Encoding.UTF8.GetBytes(str);
            Debug.WriteLine(sendBytes.ToString());
            clientSocket.Send(sendBytes);
        }


        public Cell cell1;
        public Cell cell2;
        Graphics g;
        private void button1_Click_1(object sender, EventArgs e)
        {
            cell1.Connect(cell2);
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            cell1.Release(cell2);
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            g = CreateGraphics();
            g.Clear(Color.White);
            cell1 = new Cell(g, new Point(300, 200));
            cell2 = new Cell(g, new Point(100, 200));
        }


    }
}
