using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;
using System.Threading;
using System.Data;
using System.Drawing;
using System.Collections;
using System.IO;
using System.IO.Ports;
using System.Diagnostics;
using DCCK_Vision;

namespace DCCK_Com
{

    // 作服务器

    public class TCP_Server
    {
        Socket server, client;
        public void Open(string ip, string port)
        {
            IPAddress IP = IPAddress.Parse(ip);
            Int32 PORT = Int32.Parse(port);
            IPEndPoint SERVER = new IPEndPoint(IP, PORT);//生成服务器网络端点
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); // 构造一个socket
            server.Bind(SERVER); //将socket和服务器绑定
            server.Listen(8); //开始监听，允许连接队列的长度为8
            AsyncCallback callback = new AsyncCallback(OnConnectRequest);
            server.BeginAccept(callback, server);//开始接受一个异步操作来接受传入的连接尝试
        }
        private void OnConnectRequest(IAsyncResult result)
        {
            try
            {
                client = server.EndAccept(result);
                if (client != null && client.Available > 0)
                {
                    byte[] data = new byte[client.Available];
                    client.Receive(data);
                }
                AsyncCallback callback = new AsyncCallback(OnConnectRequest);
                server.BeginAccept(callback, server);//开始接受一个异步操作来接受传入的连接尝试
            }
            catch { }

        }
        public string Read()
        {
            string str = string.Empty;
            try
            {
                if (client != null && client.Available > 0)
                {
                    WaitReadAll(10000);
                    byte[] data = new byte[client.Available];
                    client.Receive(data);
                    str = Encoding.ASCII.GetString(data);
                }
            }
            catch
            {
                AsyncCallback callback = new AsyncCallback(OnConnectRequest);
                server.BeginAccept(callback, server);//开始接受一个异步操作来接受传入的连接尝试
                MessageBox.Show("与机械手通信连接中断");
            }
            return str;
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
        public void Write(string str)
        {
            try
            {
                client.Send(Encoding.ASCII.GetBytes(str.ToCharArray()));
            }
            catch
            {
                AsyncCallback callback = new AsyncCallback(OnConnectRequest);
                server.BeginAccept(callback, server);//开始接受一个异步操作来接受传入的连接尝试
                MessageBox.Show("与机械手通信连接中断");
            }
        }
        public void Close()
        {
            //AsyncCallback callback = new AsyncCallback(OnConnectRequest);
            //server.BeginDisconnect(false , callback, server);
            // server.EndAccept(OnConnectRequest);
            client = null;
            //server.Disconnect(false);
            server.Close();
            server.Dispose();
            //server = null;
            System.GC.Collect();
            //client.Close();
        }
    }
}

