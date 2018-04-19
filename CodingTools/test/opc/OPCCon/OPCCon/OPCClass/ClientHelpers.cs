using System.Collections.Generic;
using System;
using System.Text;
using System.Xml;
using System.Data;
using System.IO;
using OPCAutomation;
using System.Diagnostics;
namespace OPCCon
{
    public class OPCServerInfo
    {

        public DateTime StartTime { get; set; }

        public string ServerVersion { get; set; }

    }



    public class OPCDataItem
    {

        public object ItemName { get; set; }

        public object ItemValue { get; set; }

        public object Quality { get; set; }

        public object TimeStamp { get; set; }

    }



    public class GroupProperty
    {

        public bool DefaultGroupIsActive { get; set; }

        public float DefaultGroupDeadband { get; set; }

        public int UpdateRate { get; set; }

        public bool IsActive { get; set; }

        public bool IsSubscribed { get; set; }



        public GroupProperty()
        {

            DefaultGroupIsActive = true;

            DefaultGroupDeadband = 0;

            UpdateRate = 250;

            IsActive = true;

            IsSubscribed = true;

        }

    }


    public class ClientHelper
    {

        /// <summary>

        /// 获取可以使用的OPC服务器

        /// </summary>

        /// <param name="hostName">获取OPC服务器的主机名称</param>

        /// <returns>返回OPC服务器列表</returns>

        public static List<string> GetOPCServerName(string hostName)
        {

            //try {

                OPCServer OpcServer = new OPCServer();

                object opcServers = OpcServer.GetOPCServers(hostName);

                List<string> serverList = new List<string>();

                foreach (string opcServer in (Array)opcServers) {

                    serverList.Add(opcServer);

                }

                return serverList;

            //}

            //catch (Exception ex) {

            //    throw ex;

            //}

        }



        /// <summary>

        /// 连接到指定的OPC服务器

        /// </summary>

        /// <param name="serverName">服务器名称</param>

        /// <param name="serverIP">服务器IP</param>

        /// <returns>返回的OPC服务器</returns>

        public static OPCServer ConnectToServer(string serverName, string serverIP)
        {

            OPCServer opcServer = new OPCServer();

            try {

                opcServer.Connect(serverName, serverIP);

                if (opcServer.ServerState != (int)OPCServerState.OPCRunning) {

                    opcServer.Disconnect();

                    return null;

                }

            }

            catch {

                opcServer.Disconnect();

                return null;

            }

            return opcServer;

        }



        /// <summary>

        /// 获取OPC服务器的相关信息

        /// </summary>

        /// <param name="opcServer">OPC服务器对象</param>

        /// <returns>OPC服务器信息</returns>

        public static OPCServerInfo GetServerInfo(OPCServer opcServer)
        {

            OPCServerInfo serverInfo = new OPCServerInfo();

            serverInfo.StartTime = opcServer.StartTime;

            serverInfo.ServerVersion = opcServer.MajorVersion.ToString() + "." + opcServer.MinorVersion.ToString() + "." + opcServer.BuildNumber.ToString();

            return serverInfo;

        }



        /// <summary>

        /// 展开OPC服务器的节点

        /// </summary>

        /// <param name="opcServer">OPC服务器</param>

        /// <returns>返回展开后的节点数据</returns>

        public static OPCBrowser RecurBrowse(OPCServer opcServer)
        {

            OPCBrowser opcBrowser = opcServer.CreateBrowser();

            //展开分支

            opcBrowser.ShowBranches();

            //展开叶子

            opcBrowser.ShowLeafs(true);

            return opcBrowser;

        }



        public static OPCGroup CreateGroup(OPCServer opcServer, OPCItems opcItems, string opcGroupName, GroupProperty groupProperty)
        {

            try {

                OPCGroup opcGroup = opcServer.OPCGroups.Add(opcGroupName);



                opcServer.OPCGroups.DefaultGroupIsActive = groupProperty.DefaultGroupIsActive;

                opcServer.OPCGroups.DefaultGroupDeadband = groupProperty.DefaultGroupDeadband;

                opcGroup.UpdateRate = groupProperty.UpdateRate;

                opcGroup.IsActive = groupProperty.IsActive;

                opcGroup.IsSubscribed = groupProperty.IsSubscribed;



                //opcGroup.DataChange += new DIOPCGroupEvent_DataChangeEventHandler(OpcGroupDataChange);

                //opcGroup.AsyncWriteComplete += new DIOPCGroupEvent_AsyncWriteCompleteEventHandler(KepGroup_AsyncWriteComplete);

                //opcItems = opcGroup.OPCItems;

                return opcGroup;

            }

            catch (Exception err) {

                throw err;

            }

        }

    }

}
