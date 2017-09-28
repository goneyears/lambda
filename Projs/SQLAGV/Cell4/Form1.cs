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
            port = 9877;
            host = "127.0.0.1";//服务器端ip地址

            ip = IPAddress.Parse(host);
            ipe = new IPEndPoint(ip, port);

            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            clientSocket.Connect(ipe);
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


    }
}
