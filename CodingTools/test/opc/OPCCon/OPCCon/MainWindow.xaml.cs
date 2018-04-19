using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using OPCAutomation;
using System.Net;


namespace OPCCon
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Automation o1 = new Automation();
            string xmlfile = System.IO.Directory.GetCurrentDirectory() + @"\config.xml";
            bool b = o1.Init(xmlfile);
            o1.Start();
            Debug.WriteLine(b);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            ClientHelper opcclass = new ClientHelper();
            List<string> servers = ClientHelper.GetOPCServerName("127.0.0.1");

        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            //          OPCServer KepServer;
            //          OPCGroups KepGroups;
            //          OPCGroup KepGroup;
            //          OPCItems KepItems;
            //          OPCItem KepItem;

            //          string strHostIP;
            //          string strHostName;
            //          string cmbServerName;
            ////3.   枚举网络OPC服务器

            //      //枚举OPC服务器用到GetOPCServers（）函数

            //          //获取计算机IP,计算机名称
            //          IPHostEntry IPHost = Dns.Resolve(Environment.MachineName);
            //          if (IPHost.AddressList.Length > 0)
            //          {
            //              strHostIP = IPHost.AddressList[0].ToString();
            //          }
            //          else
            //          {
            //              return;
            //          }
            //          //通过IP来获取计算机名称，可用在局域网内


            //          IPHostEntry ipHostEntry = Dns.GetHostByAddress(strHostIP);
            //          strHostName = ipHostEntry.HostName.ToString();//获取本地计算机上的OPCServerName
            //          try
            //          {
            //              KepServer = new OPCServer();
            //              object serverList = KepServer.GetOPCServers(strHostName);

            //              //枚举网络所有OPC服务器并写入ComboBox控件

            //              foreach (string turn in (Array)serverList)
            //              {
            //                  cmbServerName.Items.Add(turn);
            //              }

            //              cmbServerName.SelectedIndex = 0;
            //              btnConnServer.Enabled = true;
            //          }
            //          catch (Exception err)
            //          {
            //              MessageBox.Show("枚举本地OPC服务器出错：" + err.Message, "提示信息", MessageBoxButtons.OK,   MessageBoxIcon.Warning);
            //          }



            //    // 4.    连接OPC服务器



            //         try
            //          {
            //              KepServer.Connect(remoteServerName, remoteServerIP);

            //              if (KepServer.ServerState == (int)OPCServerState.OPCRunning)
            //              {
            //                  tsslServerState.Text = "已连接到-" + KepServer.ServerName + "   ";
            //              }
            //              else
            //              {
            //                  //这里你可以根据返回的状态来自定义显示信息，请查看自动化接口API文档
            //                  tsslServerState.Text = "状态：" + KepServer.ServerState.ToString() + "   ";
            //              }

            //          }
            //          catch (Exception err)
            //          {
            //              MessageBox.Show("连接远程服务器出现错误：" + err.Message, "提示信息", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            //              return false;
            //          }



            //    //5.   创建组和列出OPC服务器中所有节点

            //      //创建组

            //      try
            //          {
            //              KepGroups = KepServer.OPCGroups;
            //              KepGroup = KepGroups.Add("OPCDOTNETGROUP");
            //              SetGroupProperty();
            //              KepGroup.DataChange += new DIOPCGroupEvent_DataChangeEventHandler(KepGroup_DataChange);
            //              KepGroup.AsyncWriteComplete += new DIOPCGroupEvent_AsyncWriteCompleteEventHandler(KepGroup_AsyncWriteComplete);
            //              KepItems = KepGroup.OPCItems;
            //          }
            //          catch (Exception err)
            //          {
            //              MessageBox.Show("创建组出现错误："+err.Message,"提示信息",MessageBoxButtons.OK,MessageBoxIcon.Warning);
            //              return false;
            //          }



            //        //列出OPC服务器中所有节点
            //          OPCBrowser opcBrowser = KepServer.CreateBrowser();
            //         //展开分支
            //          opcBrowser.ShowBranches();
            //          //展开叶子
            //          opcBrowser.ShowLeafs(true);
            //          foreach (object turn in opcBrowser)
            //          {
            //              listBox1.Items.Add(turn.ToString());
            //          }




        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {

            IPHostEntry ipHostEntry = Dns.GetHostByAddress("127.0.0.1");
                      string strHostName = ipHostEntry.HostName.ToString();//获取本地计算机上的OPCServerName
                      OPCHelper opch = new OPCHelper("127.0.0.1", strHostName,100);

        }

    }
}