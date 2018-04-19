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
    class OPCHelper : IDisposable
    {
        private string strHostIP;
        private string strHostName;
        private OPCServer opcServer;
        private OPCGroups opcGroups;
        private OPCGroup opcGroup;
        private List<int> itemHandleClient = new List<int>();
        private List<int> itemHandleServer = new List<int>();
        private List<string> itemNames = new List<string>();
        private OPCItems opcItems;
        private OPCItem opcItem;
        private Dictionary<string, string> itemValues = new Dictionary<string, string>();
        public bool Connected = false;

        public OPCHelper(string strHostIP, string strHostName, int UpdateRate)
        {
            this.strHostIP = strHostIP;
            this.strHostName = strHostName;
            if (!CreateServer())
                return;
            if (!ConnectServer(strHostIP, strHostName))
                return;
            Connected = true;
           
            opcGroups = opcServer.OPCGroups;
            opcGroup = opcServer.OPCGroups.Add("AXC3050");
            SetGroupProperty(opcGroup, UpdateRate);
            opcGroup.DataChange += new DIOPCGroupEvent_DataChangeEventHandler(opcGroup_DataChange);
            opcGroup.AsyncWriteComplete += new DIOPCGroupEvent_AsyncWriteCompleteEventHandler(opcGroup_AsyncWriteComplete);
            opcItems = opcGroup.OPCItems;
            int i = 3;
        }


        /// <summary>  
        /// 创建服务  
        /// </summary>  
        /// <returns></returns>  
        private bool CreateServer()
        {
          //  try {
                opcServer = new OPCServer();
           // }
           // catch {
           //     return false;
           // }
            return true;
        }

        /// <summary>  
        /// 连接到服务器  
        /// </summary>  
        /// <param name="strHostIP"></param>  
        /// <param name="strHostName"></param>  
        /// <returns></returns>  
        private bool ConnectServer(string strHostIP, string strHostName)
        {
          //  try {
            opcServer.Connect("PhoenixContact.AX-Server");
          //  }
          //  catch {
          //      return false;
           // }
            return true;
        }

        /// <summary>  
        /// 设置组的属性   
        /// </summary>  
        /// <param name="opcGroup"></param>  
        /// <param name="updateRate"></param>  
        private void SetGroupProperty(OPCGroup opcGroup, int updateRate)
        {
            opcGroup.IsActive = true;
            opcGroup.DeadBand = 0;
            opcGroup.UpdateRate = updateRate;
            opcGroup.IsSubscribed = true;
        }

        public bool Contains(string itemNameContains)
        {
            foreach (string key in itemValues.Keys) {
                if (key == itemNameContains)
                    return true;
            }
            return false;
        }

        public void AddItems(string[] itemNamesAdded)
        {
            for (int i = 0; i < itemNamesAdded.Length; i++) {
                this.itemNames.Add(itemNamesAdded[i]);
                itemValues.Add(itemNamesAdded[i], "");
            }
            for (int i = 0; i < itemNamesAdded.Length; i++) {
                itemHandleClient.Add(itemHandleClient.Count != 0 ? itemHandleClient[itemHandleClient.Count - 1] + 1 : 1);
                opcItem = opcItems.AddItem(itemNamesAdded[i], itemHandleClient[itemHandleClient.Count - 1]);
                itemHandleServer.Add(opcItem.ServerHandle);
            }
        }


        public string[] GetItemValues(string[] getValuesItemNames)
        {
            string[] getedValues = new string[getValuesItemNames.Length];
            for (int i = 0; i < getValuesItemNames.Length; i++) {
                if (Contains(getValuesItemNames[i]))
                    itemValues.TryGetValue(getValuesItemNames[i], out getedValues[i]);
            }
            return getedValues;
        }


        /// <summary>  
        /// 异步写   
        /// </summary>  
        /// <param name="writeItemNames"></param>  
        /// <param name="writeItemValues"></param>  
        public void AsyncWrite(string[] writeItemNames, string[] writeItemValues)
        {
            OPCItem[] bItem = new OPCItem[writeItemNames.Length];
            for (int i = 0; i < writeItemNames.Length; i++) {
                for (int j = 0; j < itemNames.Count; j++) {
                    if (itemNames[j] == writeItemNames[i]) {
                        bItem[i] = opcItems.GetOPCItem(itemHandleServer[j]);
                        break;
                    }
                }
            }
            int[] temp = new int[writeItemNames.Length + 1];
            temp[0] = 0;
            for (int i = 1; i < writeItemNames.Length + 1; i++) {
                temp[i] = bItem[i - 1].ServerHandle;
            }
            Array serverHandles = (Array)temp;
            object[] valueTemp = new object[writeItemNames.Length + 1];
            valueTemp[0] = "";
            for (int i = 1; i < writeItemNames.Length + 1; i++) {
                valueTemp[i] = writeItemValues[i - 1];
            }
            Array values = (Array)valueTemp;
            Array Errors;
            int cancelID;
            opcGroup.AsyncWrite(writeItemNames.Length, ref serverHandles, ref values, out Errors, 2009, out cancelID);
            GC.Collect();
        }

        public void SyncWrite(string[] writeItemNames, string[] writeItemValues)
        {
            OPCItem[] bItem = new OPCItem[writeItemNames.Length];
            for (int i = 0; i < writeItemNames.Length; i++) {
                for (int j = 0; j < itemNames.Count; j++) {
                    if (itemNames[j] == writeItemNames[i]) {
                        bItem[i] = opcItems.GetOPCItem(itemHandleServer[j]);
                    }
                }
            }
            int[] temp = new int[writeItemNames.Length + 1];
            temp[0] = 0;
            for (int i = 1; i < writeItemNames.Length; i++) {
                temp[i] = bItem[i - 1].ServerHandle;
            }
            Array serverHandles = (Array)temp;
            object[] valueTemp = new object[writeItemNames.Length + 1];
            valueTemp[0] = "";
            for (int i = 1; i < writeItemNames.Length + 1; i++) {
                valueTemp[i] = writeItemValues[i - 1];
            }
            Array values = (Array)valueTemp;
            Array Errors;
            opcGroup.SyncWrite(writeItemNames.Length, ref serverHandles, ref values, out Errors);

            GC.Collect();
        }





        void opcGroup_DataChange(int TransactionID, int NumItems, ref Array ClientHandles, ref Array ItemValues, ref Array Qualities, ref Array TimeStamps)
        {
            for (int i = 1; i <= NumItems; i++) {
                itemValues[itemNames[Convert.ToInt32(ClientHandles.GetValue(i)) - 1]] = ItemValues.GetValue(i).ToString();
            }
        }

        void opcGroup_AsyncWriteComplete(int TransactionID, int NumItems, ref Array ClientHandles, ref Array Errors)
        {
            throw new NotImplementedException();
        }


        public void Dispose()
        {
            if (opcGroup != null) {
                opcGroup.DataChange -= new DIOPCGroupEvent_DataChangeEventHandler(opcGroup_DataChange);
                opcGroup.AsyncWriteComplete -= new DIOPCGroupEvent_AsyncWriteCompleteEventHandler(opcGroup_AsyncWriteComplete);
            }
            if (opcServer != null) {
                opcServer.Disconnect();
                opcServer = null;
            }
            Connected = false;
        }


    }
}