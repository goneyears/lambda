
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Data;
using System.IO;
using OPCAutomation;
using System.Diagnostics;
namespace OPCCon
{
    public class Automation
    {
        public Automation()
        {
            OPCServer = new OPCAutomation.OPCServerClass();
        }
        private OPCAutomation.OPCServerClass OPCServer;   //OPC Server通讯对象
        private OPCAutomation.OPCGroup opcGroup;          //OPC Server组对象
        private Hashtable opcHash;                        //存储OPC Server信息哈希表
        private Hashtable groupHash;                      //OPC Server组信息哈希表
        private Hashtable readHash;                       //读单元哈希表
        private Hashtable writeHash;                      //写单元哈希表
        private bool bInit = false;                       //初始化成功标志
        private bool bConnect = false;                    //连接成功标志
        private string lastErrInfo;                       //错误信息
        private string cfgFileName;


        public bool Init(string fileName)               //初始化
        {
            //try {
                if (!File.Exists(fileName)) {
                    this.lastErrInfo = "配置文件不存在";
                    Debug.WriteLine(this.lastErrInfo);
                    return false;
                }
                cfgFileName = fileName;
                DataSet opcSet = GetCfgData("Config//OPC");
                if (!opcSet.Tables.Contains("OPC")) {
                    this.lastErrInfo = "配置文件没有OPC结点";
                    Debug.WriteLine(this.lastErrInfo);
                    return false;
                }
                if (!opcSet.Tables.Contains("OPCGroup")) {
                    this.lastErrInfo = "配置文件没有OPCGroup结点";
                    Debug.WriteLine(this.lastErrInfo);
                    return false;
                }
                opcHash = new Hashtable();
                opcHash.Add("OPCConnectString", opcSet.Tables["OPC"].Rows[0]["OPCConnectString"]);
                opcHash.Add("OPCNode", opcSet.Tables["OPC"].Rows[0]["OPCNode"]);

                groupHash = new Hashtable();
                groupHash.Add("OPCGroupName", opcSet.Tables["OPCGroup"].Rows[0]["OPCGroupName"]);
                groupHash.Add("OPCGroupString", opcSet.Tables["OPCGroup"].Rows[0]["OPCGroupString"]);
                groupHash.Add("GroupDeadband", opcSet.Tables["OPCGroup"].Rows[0]["GroupDeadband"]);
                groupHash.Add("GroupLocaleID", opcSet.Tables["OPCGroup"].Rows[0]["GroupLocaleID"]);
                groupHash.Add("GroupUpdateRate", opcSet.Tables["OPCGroup"].Rows[0]["GroupUpdateRate"]);
                groupHash.Add("GroupTimeBias", opcSet.Tables["OPCGroup"].Rows[0]["GroupTimeBias"]);
                groupHash.Add("ISACTIVE", opcSet.Tables["OPCGroup"].Rows[0]["ISACTIVE"]);

                int clientHandle = 0;
                readHash = new Hashtable();
                DataRow[] row = opcSet.Tables["OPCItem"].Select("RWType='0' AND ISACTIVE='1'");
                for (int i = 0; i < row.Length; i++) {
                    Item opcItem = new Item();
                    opcItem.OPCItemName = row[i]["OPCItemName"].ToString();
                    opcItem.IsActivue = row[i]["ISACTIVE"].ToString();
                    opcItem.OPCItemString = row[i]["OPCItemString"].ToString();
                    opcItem.ClientHandle = ++clientHandle;

                    readHash.Add(opcItem.OPCItemName, opcItem);
                }

                writeHash = new Hashtable();
                row = opcSet.Tables["OPCItem"].Select("RWType='1' AND ISACTIVE='1'");
                for (int i = 0; i < row.Length; i++) {
                    Item opcItem = new Item();
                    opcItem.OPCItemName = row[i]["OPCItemName"].ToString();
                    opcItem.IsActivue = row[i]["ISACTIVE"].ToString();
                    opcItem.OPCItemString = row[i]["OPCItemString"].ToString();
                    opcItem.ClientHandle = ++clientHandle;

                    writeHash.Add(opcItem.OPCItemName, opcItem);
                }

                row = opcSet.Tables["OPCItem"].Select("RWType='2' AND ISACTIVE='1'");
                for (int i = 0; i < row.Length; i++) {
                    Item opcItem1 = new Item();
                    opcItem1.OPCItemName = row[i]["OPCItemName"].ToString();
                    opcItem1.IsActivue = row[i]["ISACTIVE"].ToString();
                    opcItem1.OPCItemString = row[i]["OPCItemString"].ToString();
                    opcItem1.ClientHandle = ++clientHandle;
                    writeHash.Add(opcItem1.OPCItemName, opcItem1);

                    Item opcItem2 = new Item();
                    opcItem2.OPCItemName = row[i]["OPCItemName"].ToString();
                    opcItem2.IsActivue = row[i]["ISACTIVE"].ToString();
                    opcItem2.OPCItemString = row[i]["OPCItemString"].ToString();
                    opcItem2.ClientHandle = ++clientHandle;
                    readHash.Add(opcItem2.OPCItemName, opcItem2);
                }
            //}
            //catch (Exception e) {
            //    this.lastErrInfo = e.Message;
            //    Debug.WriteLine(this.lastErrInfo);
            //    return false;
            //}
            bInit = true;
            return true;
        }



        public bool Start()
        {
            if (!bInit) {
                this.lastErrInfo = "初始化未完成，先执行Init操作";
                return false;
            }

            //try {
                string opcGroupString = groupHash["OPCGroupString"].ToString();
                string s1 = opcHash["OPCConnectString"].ToString();
                string s2 = opcHash["OPCNode"].ToString();
                object o = OPCServer.GetOPCServers();
                OPCServer.Connect(opcHash["OPCConnectString"].ToString(), opcHash["OPCNode"]);
                ////Group的默认死区，变化量超过死区后将会触发DataChange事件，合理的设置该值可以提高程序性能
                //OPCServer.OPCGroups.DefaultGroupDeadband = int.Parse(groupHash["GroupDeadband"].ToString());
                ////组（Group）的默认通信区域编号，如1024
                //OPCServer.OPCGroups.DefaultGroupLocaleID = int.Parse(groupHash["GroupLocaleID"].ToString());
                ////组（Group）的默认刷新率
                //OPCServer.OPCGroups.DefaultGroupUpdateRate = int.Parse(groupHash["GroupUpdateRate"].ToString());
                //组（Group）的默认时间偏差
                OPCBrowser opcBrowser = OPCServer.CreateBrowser();

                //展开分支

                opcBrowser.ShowBranches();

                //展开叶子

                opcBrowser.ShowLeafs(true); 

               // OPCServer.OPCGroups.DefaultGroupTimeBias = int.Parse(groupHash["GroupTimeBias"].ToString());
      

                opcGroup = OPCServer.OPCGroups.Add("AXC3050");

                opcGroup.IsActive = false;
                opcGroup.IsSubscribed = false;

                int clientHandle = 1;
                OPCAutomation.OPCItems opcItems = opcGroup.OPCItems;
                IDictionaryEnumerator ide = readHash.GetEnumerator();
                while (ide.MoveNext()) {
                    Item item = ide.Value as Item;
                    if (item.IsActive) {
                        opcItems.AddItem(opcGroupString + item.OPCItemString, clientHandle);
                        clientHandle++;
                    }
                }

                ide = writeHash.GetEnumerator();
                while (ide.MoveNext()) {
                    Item item = ide.Value as Item;
                    if (item.IsActive) {
                        opcItems.AddItem(opcGroupString + item.OPCItemString, clientHandle);
                        clientHandle++;
                    }
                }

                opcGroup.DataChange += new OPCAutomation.DIOPCGroupEvent_DataChangeEventHandler(Automation_DataChange);

                opcGroup.IsActive = true;
                opcGroup.IsSubscribed = true;

            //}
            //catch (SystemException ex) {
            //    this.lastErrInfo = ex.Message;
            //    return false;
            //}
            bConnect = true;
            return true;
        }




        public DataSet GetCfgData(string xmlPathNode)  //查找数据，返回DataSet
        {
            DataSet ds = new DataSet();
            XmlDocument objXmlDoc = new XmlDocument();
            objXmlDoc.Load(cfgFileName);
            StringReader read = new StringReader(objXmlDoc.SelectSingleNode(xmlPathNode).OuterXml);
            ds.ReadXml(read);
            return ds;
        }

        private void Automation_DataChange(int TransactionID, int NumItems, ref Array ClientHandles, ref Array ItemValues, ref Array Qualities, ref Array TimeStamps)
        {

            //此处代码省略，贴出来的代码已经完成最主要的功能

        }


        public class Group
        {
            private string opcGroupName;   //组定义名称
            private string opcGroupString; //组连接串
            private int groupDeadband;     //默认死区
            private int groupLocaleID;     //通信区域编号
            private int groupUpdateRate;   //刷新率
            private int groupTimeBias;     //时间偏差
            private string isActivue;  //是否激活的值 0:未激活；1:激活
            public string OPCGroupName
            {
                get { return opcGroupName; }
                set { opcGroupName = value; }
            }
            public string OPCGroupString
            {
                get { return opcGroupString; }
                set { opcGroupString = value; }
            }
            public int GroupDeadband
            {
                get { return groupDeadband; }
                set { groupDeadband = value; }
            }

            public int GroupLocaleID
            {
                get { return groupLocaleID; }
                set { groupLocaleID = value; }
            }
            public int GroupUpdateRate
            {
                get { return groupUpdateRate; }
                set { groupUpdateRate = value; }
            }
            public int GroupTimeBias
            {
                get { return groupTimeBias; }
                set { groupTimeBias = value; }
            }

            public string IsActivue
            {
                get { return isActivue; }
                set { isActivue = value; }
            }

            public bool IsActive
            {
                get
                {
                    if (isActivue.Equals("1")) {
                        return true;
                    }
                    return false;
                }
            }
        }
        public class Item
        {
            private int clientHandle = 1;               //指定单元的序号
            private string isActivue = "1";         //是否激活的值 0:未激活；1:激活
            private string opcItemName;                 //单元名称
            private string opcItemString;               //单元数据块

            public int ClientHandle
            {
                get { return clientHandle; }
                set { clientHandle = value; }
            }

            public string IsActivue
            {
                get { return isActivue; }
                set { isActivue = value; }
            }

            public bool IsActive
            {
                get
                {
                    if (isActivue.Equals("1")) {
                        return true;
                    }
                    return false;
                }
            }

            public string OPCItemName
            {
                get { return opcItemName; }
                set { opcItemName = value; }
            }
            public string OPCItemString
            {
                get { return opcItemString; }
                set { opcItemString = value; }
            }


        }


    }
}