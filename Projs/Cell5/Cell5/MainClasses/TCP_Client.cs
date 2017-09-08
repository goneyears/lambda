using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;
using System.Threading;

namespace Cell5
{
    public delegate void TCPEventHandle(Object sender, TCPEventArgs param);
    public delegate void ConnectEventHandle(object sender);

    public class TCPEventArgs : EventArgs
    {
        public readonly string receivedmessage;
        public Socket client;
        public TCPEventArgs(string message, Socket Client)
        {
            receivedmessage = message;
            client = Client;
        }
    }
    public class TCP_Client : IDisposable
    {
        IPAddress IP;
        IPEndPoint Host;
        public Socket client;
        public event TCPEventHandle MessageReceived;
        public event ConnectEventHandle isconnect;
        public Thread thpolling;
        private bool mark = false;
        private object ob = new object();
        private char[] HexDigits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f' };
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="ip"></param>
        /// <param name="port"></param>
        public TCP_Client(string ip, string port)
        {
            IP = IPAddress.Parse(ip);
            Host = new IPEndPoint(IP, Convert.ToInt32(port));
            Connect();
            BuildThread();
        }
        public bool BuildThread()
        {
            try
            {
                thpolling = new Thread(Polling);
                thpolling.IsBackground = true;
                mark = true;
                thpolling.Start();
                return true;
            }
            catch
            {
                return false;
            }
        }
        /// <summary>
        /// 连接
        /// </summary>
        /// <returns></returns>
        public bool Connect()
        {
            try
            {
                client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                client.Connect(Host);
                return true;
            }
            catch
            {
                return false;
            }
        }
        private void Polling()
        {
            while (mark)
            {
                try
                {
                    string data = Recieve();
                    if (data != "")
                    {
                        TCPEventArgs args = new TCPEventArgs(data, client);

                        if (MessageReceived != null)
                            MessageReceived(this,args);
                        //Messages.WriteLine(data);
                    }
                    Thread.Sleep(20);
                    if (isconnect != null)
                        isconnect(IsConnected());
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("网络循环出现错误，信息为" + ex.Message);
                }
            }
        }
        private bool CharInArray(char aChar, char[] charArray)
        {
            return (Array.Exists<char>(charArray, delegate(char a) { return a == aChar; }));
        }
        /// <summary>
        /// 十六进制字符串转换字节数组
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        private byte[] HexStringToByteArray(string s)
        {
            // s = s.Replace(" ", "");

            StringBuilder sb = new StringBuilder(s.Length);
            foreach (char aChar in s)
            {
                if (CharInArray(aChar, HexDigits))
                    sb.Append(aChar);
            }
            s = sb.ToString();
            int bufferlength;
            if ((s.Length % 2) == 1)
                bufferlength = s.Length / 2 + 1;
            else bufferlength = s.Length / 2;
            byte[] buffer = new byte[bufferlength];
            for (int i = 0; i < bufferlength - 1; i++)
                buffer[i] = (byte)Convert.ToByte(s.Substring(2 * i, 2), 16);
            if (bufferlength > 0)
                buffer[bufferlength - 1] = (byte)Convert.ToByte(s.Substring(2 * (bufferlength - 1), (s.Length % 2 == 1 ? 1 : 2)), 16);
            return buffer;
        }
        /// <summary>
        /// 字节数组转换十六进制字符串
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        private string ByteArrayToHexString(byte[] data)
        {
            StringBuilder sb = new StringBuilder(data.Length * 3);
            foreach (byte b in data)
                sb.Append(Convert.ToString(b, 16).PadLeft(2, '0').PadRight(3, ' '));
            return sb.ToString().ToUpper();
        }
        public bool IsConnected()
        {
            lock (ob)
            {
                try
                {
                    if (client != null && (!(client.Poll(1000, SelectMode.SelectRead) && client.Available == 0)) && client.Connected)
                        return true;
                    else
                        return false;
                }
                catch
                {
                    return false;
                }
            }
        }
        public void WaitReadAll(long time)
        {
            int prenum = client.Available;
            int nownum = 0;
            for (int i = 0; i < time / 10; i++)
            {
                Thread.Sleep(10);
                nownum = client.Available;
                if (prenum == nownum)
                    break;
                else
                {
                    prenum = nownum;
                }
            }
        }
        /// <summary>
        /// 接收数据
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public string Recieve()
        {
            lock (ob)
            {
                try
                {
                    if (IsConnected())
                    {
                        if (client.Available > 0)
                        {
                            WaitReadAll(10000);
                            byte[] data = new byte[client.Available];
                            client.Receive(data);
                            return Encoding.ASCII.GetString(data);   //已ASCII编码形式接受
                        }
                        else
                        {
                            return "";
                        }
                    }
                    else
                    {
                        Connect();
                        return "";
                    }
                }
                catch
                {
                    return "";
                }
            }
        }


        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public bool Send(string str)
        {
            lock (ob)
            {
                try
                {
                    if (IsConnected())
                    {
                        byte[] data = Encoding.ASCII.GetBytes(str);
                        client.Send(data);
                        return true;
                    }
                    else
                    {
                        Connect();
                        return false;
                    }
                }
                catch
                {
                    return false;
                }
            }
        }
        public void Dispose()
        {
            if (thpolling != null)
            {
                mark = false;
                thpolling.Abort();
            }
            if (client != null)
            {
                if (client.Connected && (!client.Poll(1000, SelectMode.SelectRead)))
                {
                    try
                    {
                        client.Shutdown(SocketShutdown.Both);
                        client.Disconnect(true);
                    }
                    catch
                    {

                    }
                }
                client.Close();
                client = null;
            }

        }

    }
}
