using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OPCAutomation;  
using System.ComponentModel;
using System.Data;
using System.Drawing;  
using System.Net;
using System.Collections;
using OPCAutomation;
using System.Diagnostics;
using System.Linq;

namespace OPCLib
{
    public class OPCClient
    { 
        #region 私有变量
        /// <summary>
        /// OPCServer Object
        /// </summary>
        OPCServer PxServer;
        /// <summary>
        /// OPCGroups Object
        /// </summary>
        OPCGroups PxGroups;
        /// <summary>
        /// OPCGroup Object
        /// </summary>
        OPCGroup PxGroup;
        /// <summary>
        /// OPCItems Object
        /// </summary>
        OPCItems PxItems;
        /// <summary>
        /// OPCItem Object
        /// </summary>
        OPCItem PxItem;
        /// <summary>
        /// 主机IP
        /// </summary>
        string strHostIP = "";
        /// <summary>
        /// 主机名称
        /// </summary>
        string strHostName = "";
        /// <summary>
        /// 连接状态
        /// </summary>
        bool opc_connected = false;
        /// <summary>
        /// 客户端句柄
        /// </summary>
        int itmHandleClient = 0;
        /// <summary>
        /// 服务端句柄
        /// </summary>
        int itmHandleServer = 0;
        /// <summary>
        /// 变量名称
        /// </summary>
        public List<string> OPCItemNames = new List<string>();
        /// <summary>
        /// 变量名称及对应的服务端句柄
        /// </summary>
        //public Dictionary<string, int> DicItems = new Dictionary<string, int>();
        private Dictionary<string, OPCItem> OPCItemDic = new Dictionary<string, OPCItem>(); 
        //public List<OPCItem> OPCItemList = new List<OPCItem>();
        #endregion

        //#region 方法
        /// <summary>
        /// 枚举本地OPC服务器
        /// 返回查询到的服务器list
        /// </summary>
        public List<string> GetLocalServer()
        {
            List<string> ls = new List<string>();
            //获取本地计算机IP,计算机名称
            IPHostEntry IPHost = Dns.Resolve(Environment.MachineName);
            if (IPHost.AddressList.Length > 0) {
                strHostIP = IPHost.AddressList[0].ToString();
                //通过IP来获取计算机名称，可用在局域网内
                IPHostEntry ipHostEntry = Dns.GetHostByAddress(strHostIP);
                strHostName = ipHostEntry.HostName.ToString();

                //获取本地计算机上的OPCServerName
                try {
                    PxServer = new OPCServer();
                    object serverList = PxServer.GetOPCServers(strHostName);

                    foreach (string turn in (Array)serverList) {
                        ls.Add(turn);
                    }

                }
                catch (Exception err) {
                    Debug.WriteLine("枚举本地OPC服务器出错：" + err.Message, "提示信息");
                }

            }
            return ls;

        }
        
        /// <summary>
        /// 创建组
        /// </summary>
        private bool CreateGroup()
        {
            try {
                PxGroups = PxServer.OPCGroups;
                PxGroup = PxGroups.Add("OPCDOTNETGROUP");
                SetGroupProperty();
                PxGroup.DataChange += new DIOPCGroupEvent_DataChangeEventHandler(KepGroup_DataChange);
                PxGroup.AsyncWriteComplete += new DIOPCGroupEvent_AsyncWriteCompleteEventHandler(KepGroup_AsyncWriteComplete);
                PxItems = PxGroup.OPCItems;
            }
            catch (Exception err) {
                Debug.WriteLine("创建组出现错误：" + err.Message, "提示信息");
                return false;
            }
            return true;
        }
        /// <summary>
        /// 设置组属性
        /// </summary>
        private void SetGroupProperty()
        {
            string txtGroupIsActive = "true";
            string txtGroupDeadband = "0";
            string txtUpdateRate = "250";
            string txtIsActive = "true";
            string txtIsSubscribed = "true";
            PxServer.OPCGroups.DefaultGroupIsActive = Convert.ToBoolean(txtGroupIsActive);
            PxServer.OPCGroups.DefaultGroupDeadband = Convert.ToInt32(txtGroupDeadband);
            PxGroup.UpdateRate = Convert.ToInt32(txtUpdateRate);
            PxGroup.IsActive = Convert.ToBoolean(txtIsActive);
            PxGroup.IsSubscribed = Convert.ToBoolean(txtIsSubscribed);
        }
        /// <summary>
        /// 列出OPC服务器中所有节点
        /// </summary>
        /// <param name="oPCBrowser"></param>
        private void RecurBrowse(OPCBrowser oPCBrowser)
        {
            //展开分支
            oPCBrowser.ShowBranches();
            //展开叶子
            oPCBrowser.ShowLeafs(true);
            foreach (object turn in oPCBrowser) {
                //OPCItemDic2.Add(turn.ToString(), );
                OPCItemNames.Add(turn.ToString());

            }
        }
        /// <summary>
        /// 获取服务器信息，并显示在窗体状态栏上
        /// </summary>
        private void GetServerInfo()
        {
            string tsslServerStartTime;
            string tsslversion;
            tsslServerStartTime = "开始时间:" + PxServer.StartTime.ToString() + "    ";
            tsslversion = "版本:" + PxServer.MajorVersion.ToString() + "." + PxServer.MinorVersion.ToString() + "." + PxServer.BuildNumber.ToString();
            Debug.WriteLine(tsslServerStartTime);
            Debug.WriteLine(tsslversion);
        }
        /// <summary>
        /// 连接OPC服务器
        /// </summary>
        /// <param name="remoteServerIP">OPCServerIP</param>
        /// <param name="remoteServerName">OPCServer名称</param>
        private bool ConnectRemoteServer(string remoteServerIP, string remoteServerName)
        {
            string tsslServerState;
            try {
                PxServer.Connect(remoteServerName, remoteServerIP);

                if (PxServer.ServerState == (int)OPCServerState.OPCRunning) {
                    tsslServerState = "已连接到-" + PxServer.ServerName + "   ";
                }
                else {
                    //这里你可以根据返回的状态来自定义显示信息，请查看自动化接口API文档
                    tsslServerState = "状态：" + PxServer.ServerState.ToString() + "   ";
                }
            }
            catch (Exception err) {
                Debug.WriteLine("连接远程服务器出现错误：" + err.Message, "提示信息");
                return false;
            }
            return true;
        }
        public bool ConnectServer(string servername, string ip)
        {
            try {
                if (!ConnectRemoteServer(ip, servername)) {
                    return false;
                }

                opc_connected = true;

                GetServerInfo();

                RecurBrowse(PxServer.CreateBrowser());

                if (!CreateGroup()) {
                    return false;
                }
                return true;
            }
            catch (Exception err) {
                Debug.WriteLine("初始化出错：" + err.Message, "提示信息");
                return false;
            }

        }

        public void DisConnectServer()
        {
            if (!opc_connected) {
                return;
            }

            if (PxGroup != null) {
                PxGroup.DataChange -= new DIOPCGroupEvent_DataChangeEventHandler(KepGroup_DataChange);
            }

            if (PxServer != null) {
                PxServer.Disconnect();
                PxServer = null;
            }

            opc_connected = false;
        }


        public void AddItems(List<string> ls)
        { 
            try {

                itmHandleClient = 1000; 
                foreach (string itm in ls) {
                    itmHandleClient++;
                    PxItem = PxItems.AddItem(itm, itmHandleClient);
                    itmHandleServer = PxItem.ServerHandle;
                    OPCItemDic.Add(itm, PxItem); 
                }
                 
            }
            catch (Exception err) {
                //没有任何权限的项，都是OPC服务器保留的系统项，此处可不做处理。
                itmHandleClient = 0;
                Debug.WriteLine("此项为系统保留项:" + err.Message );
            } 
        }

        public void AddAllItems()
        {
            AddItems(OPCItemNames);
           
        }
        /// <summary>
        /// 写入
        /// </summary>
        public void WriteItem(string itemname, string value)
        {
            OPCItem bItem = PxItems.GetOPCItem(OPCItemDic[itemname].ServerHandle);
            int[] temp = new int[2] { 0, bItem.ServerHandle };
            Array serverHandles = (Array)temp;
            object[] valueTemp = new object[2] { "", value };
            Array values = (Array)valueTemp;
            Array Errors;
            int cancelID;
            PxGroup.AsyncWrite(1, ref serverHandles, ref values, out Errors, 2009, out cancelID);
            //KepItem.Write(txtWriteTagValue.Text);//这句也可以写入，但并不触发写入事件
            GC.Collect();
        }
         
        public object ReadItem(string itemname)
        {
            //object o = new object();
            object o = OPCItemDic[itemname].Value; 
            return o;
 

        }
       // public void 

        #region 事件
        /// <summary>
        /// 写入TAG值时执行的事件
        /// </summary>
        /// <param name="TransactionID"></param>
        /// <param name="NumItems"></param>
        /// <param name="ClientHandles"></param>
        /// <param name="Errors"></param>
        void KepGroup_AsyncWriteComplete(int TransactionID, int NumItems, ref Array ClientHandles, ref Array Errors)
        {
            //lblState.Text = "";
            //for (int i = 1; i <= NumItems; i++) {
            //    lblState.Text += "Tran:" + TransactionID.ToString() + "   CH:" + ClientHandles.GetValue(i).ToString() + "   Error:" + Errors.GetValue(i).ToString();
            //}
        }
        /// <summary>
        /// 每当项数据有变化时执行的事件
        /// </summary>
        /// <param name="TransactionID">处理ID</param>
        /// <param name="NumItems">项个数</param>
        /// <param name="ClientHandles">项客户端句柄</param>
        /// <param name="ItemValues">TAG值</param>
        /// <param name="Qualities">品质</param>
        /// <param name="TimeStamps">时间戳</param>
        void KepGroup_DataChange(int TransactionID, int NumItems, ref Array ClientHandles, ref Array ItemValues, ref Array Qualities, ref Array TimeStamps)
        {
            //为了测试，所以加了控制台的输出，来查看事物ID号
            //Console.WriteLine("********"+TransactionID.ToString()+"*********");
            //数组类型的读取和写入暂未加入，读取稍复杂，需要先读取类型，再定义相应类型，把数据取出来。
            //写入更麻烦，目前看来写的话必须同时写入数组所有数据，为了不影响其它数据的值，可能需要
            //先把所有数据读出来，再写进去。方法见注释

            //Debug.WriteLine("numitems:" + NumItems.ToString());
            //for (int i = 1; i <= NumItems; i++) { 
            //    object item;
            //    object clienthandl;
            //    clienthandl = ClientHandles.GetValue(i);
            //    item = ItemValues.GetValue(i);
            //    Debug.WriteLine("in for cycle");

            //    Debug.WriteLine(item);

            //    //this.txtQualities.Text = Qualities.GetValue(i).ToString();
            //    //this.txtTimeStamps.Text = TimeStamps.GetValue(i).ToString();
            //}
        }
        #endregion





    }
}
