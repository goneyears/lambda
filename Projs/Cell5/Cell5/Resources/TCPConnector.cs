using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Diagnostics;
using System.Windows.Forms;
namespace Cell5
{
    public class TCPConnector
    {
        public string receivedMessage;
        public int receivedMessageCount = 0;
        protected TcpClient tcpclient = null;  //全局客户端对象  
        protected NetworkStream networkstream = null;//全局数据流传输对象  

        public delegate void TCPEventHandler(Object sender, TCPEventArgs e);
        public event TCPEventHandler MessageReceived;

        public class TCPEventArgs : EventArgs
        {
            public readonly string receivedmessage;
            public TCPEventArgs(string receivedmessage)
            {
                this.receivedmessage = receivedmessage;
            }
        }

        protected virtual void OnReceived(TCPEventArgs e)
        {
            if (MessageReceived != null)
            {
                MessageReceived(this, e);
            }
        }


        /// <summary>  
        /// 
        /// 进行远程服务器的连接  
        /// </summary>  
        /// <param name="ip">ip地址</param>  
        /// <param name="port">端口</param>  
        public TCPConnector(string ip, int port)
        {
            _ip = ip;
            _port = port;

            StartConnect();

        }

        public void StartConnect()
        {
            networkstream = null;
            tcpclient = new TcpClient();  //对象转换成实体  
            //ip="192.168.111.111";
            tcpclient.BeginConnect(System.Net.IPAddress.Parse(_ip), _port, new AsyncCallback(Connected), tcpclient);  //开始进行尝试连接  

        }

        public string _ip;
        public int _port;
        public bool IsOnline()
        {

            return !((tcpclient.Client.Poll(1000, SelectMode.SelectRead) && (tcpclient.Client.Available == 0)) || !tcpclient.Client.Connected);
        }
        /// <summary>  
        /// 发送数据  
        /// </summary>  
        /// <param name="data">数据</param>  
        public void SendData(byte[] data)
        {
            Debug.WriteLine("tcpconnectstate: " + IsOnline().ToString());
            if (IsOnline())
            {
                if (networkstream != null)
                    networkstream.Write(data, 0, data.Length);  //向服务器发送数据  
            }
            else
            {
                //Debug.WriteLine("reconnecting.....");
                ReConnect();
            }
        }

        public void Send(string str)
        {
            byte[] sendBytes = System.Text.Encoding.UTF8.GetBytes(str);
            SendData(sendBytes);
        }
        /// <summary>  
        /// 关闭  
        /// </summary>  
        public void Close()
        {
            networkstream.Dispose(); //释放数据流传输对象  
            tcpclient.Close(); //关闭连接  
        }
        /// <summary>  
        /// 关闭  
        /// </summary>  
        /// <param name="result">传入参数</param>  
        protected void Connected(IAsyncResult result)
        {
            TcpClient tcpclt = (TcpClient)result.AsyncState;  //将传递的参数强制转换成TcpClient  
            networkstream = tcpclt.GetStream();  //获取数据流传输对象  
            byte[] data = new byte[1000];  //新建传输的缓冲  
            networkstream.BeginRead(data, 0, 1000, new AsyncCallback(DataRec), data); //挂起数据的接收等待  

        }

        protected void ReConnect()
        {


            Debug.WriteLine("reconnecting.....");
            Close();
            StartConnect();

            Debug.WriteLine("tcpconnectstate-----------new: " + "_ip" + IsOnline().ToString());
        }
        /// <summary>  
        /// 数据接收委托函数  
        /// </summary>  
        /// <param name="result">传入参数</param>  
        protected void DataRec(IAsyncResult result)
        {
            if (IsOnline())
            {
                int length = networkstream.EndRead(result);  //获取接收数据的长度  
                List<byte> data = new List<byte>(); //新建byte数组  
                data.AddRange((byte[])result.AsyncState); //获取数据  
                data.RemoveRange(length, data.Count - length); //根据长度移除无效的数据  
                byte[] data2 = new byte[1000]; //重新定义接收缓冲  

                bool c = tcpclient.Connected;
                networkstream.BeginRead(data2, 0, 1000, new AsyncCallback(DataRec), data2);  //重新挂起数据的接收等待  
                //自定义代码区域，处理数据data  
                //for (int i = 0; i < data.Count;i++ )
                //{
                //    Debug.WriteLine(data[i]);
                //}
                Encoding receiveEncoding_ = Encoding.UTF8;
                string receiveStr = receiveEncoding_.GetString((byte[])result.AsyncState, 0, length);
                receivedMessage = receiveStr;
                receivedMessageCount++;
                //  Debug.WriteLine(receiveStr);

                TCPEventArgs e = new TCPEventArgs(receiveStr);
                OnReceived(e);

                if (length == 0)
                {
                    //连接已经关闭  
                    Debug.WriteLine("connection closed by server----------------");
                }
            }
            else
            {
                ReConnect();
            }

        }
    }
}
