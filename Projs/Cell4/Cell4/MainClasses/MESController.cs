using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Threading;
namespace Cell4
{
    public struct MESTASK
    {
        public bool Available;
        public string ID;
        public string SN;
        public string UBodyColor;
        public string UCoverColor;
        public string copyfilestr;

        public int Force;//0:ForceFree,1:ForceGood;2:FoceNG;
        public int preForce;//pre set force value, apply the force function in next mes task
    }



    public struct TASKINFO
    {
        public TASKINFO(bool pres)
        {
            TaskResult = TASKRESULT.NOTGOOD;
            RejectReason = REJECTREASON.UNDETECTED;
            PQCFilePath = "\' \'";
        }
        public TASKRESULT TaskResult;
        public REJECTREASON RejectReason;
        public string PQCFilePath;
        //public string others;

    }

    public enum COMMANDREUSLT
    {
        FAILED=0,
        COMPLETE=1
    }
    public enum TASKRESULT
    {
        NOTGOOD =0,
        GOOD =1 
    }
    public enum REJECTREASON
    {
        UNDETECTED=0,
        WRONGCOLOR=1,
        LEDOFF=2,
        COPYFAILURE=3,
        WRONGVOLUME=4,
        ForceNG=99
    }
    public enum CHECKSTATE
    {
        UNCHECKED=0,
        CHECKED=1
    }
    public enum PLCSTATE
    {
        UNKNOWN = 0,
        READY = 1,
        AVAILABLE=2,
        BUSY = 3
    }

    public enum MESSTATE
    {
        UNKNOWN=0,
        NONEWTASK=1,
        NEWTASKAVAILABLE=2
    }
     
    class MESController
    {
        public MESController()
        {
            Messages.WriteLine("建立MES-PLC通信连接");
            MESTcp = new TCP_Client("192.168.10.40", "50002");

            MESTcp.MessageReceived += AnalyzePLCMessage;
            SQLc = new SQLConnector("Server=192.168.10.100;Database=PhoenixDB;user id=sa ;password=Phoenix@123 ;");

            CancelTask = false;
        }


        private TCP_Client MESTcp;
        private SQLConnector SQLc;
        private DataTable TaskDataTable = new DataTable();

        public bool CancelTask {get;set;}


        public MESTASK CurrentMESTask = new MESTASK();
        public MESSTATE GetNewTask()
        {
            TaskDataTable = new DataTable();
            CurrentMESTask.Available = false;  

            TaskDataTable = SQLc.GetNewData(
                "select top 1 ID,SN,PROCESS_CODE,PROCESS_FILE_PATH from CMD_WIP_PROCESS "
                + " where (PROCESS_STATUS=1 or PROCESS_STATUS=2 ) and WORK_CENTER_CODE=4 "
                +" order by PRIORITY_LEVEL desc,ID asc");
            if (TaskDataTable.Rows.Count == 0) {  
               // Debug.WriteLine("no result from sql database");
                CurrentMESTask.Available = false;
            }else{
                Debug.WriteLine(TaskDataTable.Rows.Count);
                CurrentMESTask.Available = true;
                CurrentMESTask.ID = TaskDataTable.Rows[0]["ID"].ToString();
                CurrentMESTask.SN = TaskDataTable.Rows[0]["SN"].ToString();
                CurrentMESTask.copyfilestr = TaskDataTable.Rows[0]["PROCESS_FILE_PATH"].ToString();
                Common.copyfilelist = ExtractCopyFiles(CurrentMESTask.copyfilestr);

                string c=TaskDataTable.Rows[0]["PROCESS_CODE"].ToString();
                if (c == "1") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "1";
                }
                else if (c == "2") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "2";
                }
                else if (c == "4") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "7";
                }
                else if (c == "5") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "7";
                }//add ucover color type (4)
                else if (c == "6") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "8";
                }
                else if (c == "7") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "9";
                }
                else if (c == "8") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "10";
                }
                else if (c == "9") {
                    CurrentMESTask.UBodyColor = "1";
                    CurrentMESTask.UCoverColor = "11";
                }
                else if (c == "10") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "8";
                }
                else if (c == "11") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "9";
                }
                else if (c == "12") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "10";
                }
                else if (c == "13") {
                    CurrentMESTask.UBodyColor = "2";
                    CurrentMESTask.UCoverColor = "11";
                }
                else {
                    Debug.WriteLine("unknown color code");
                }
                

                SQLc.SendCommand("update CMD_WIP_PROCESS SET PROCESS_STATUS=2 , UPDATE_BY='PxC',ACTUAL_START_DATE=GetDate(),UPDATE_DATE=GetDate() " 
                    +" where ID="
                    + CurrentMESTask.ID);

              //  Debug.WriteLine(TaskDataTable.Rows[0]["ID"].ToString());
                
            }

            if (CurrentMESTask.Available) {
                return MESSTATE.NEWTASKAVAILABLE;
            }
            else {
                return MESSTATE.NONEWTASK;
            }

                 
        }
        public COMMANDREUSLT SendCurrentTaskToPLC()
        {
            CurrentMESTask.Force = CurrentMESTask.preForce;
            SendPLCTask(CurrentMESTask);
            return COMMANDREUSLT.COMPLETE;
        }

        public string TaskInfoString;
        public void SendPLCTask(MESTASK _mesTask)
        {
            SendMessageToPlc("StartNewTask " + _mesTask.ID + " " + _mesTask.SN + " " + _mesTask.UBodyColor+" "+_mesTask.UCoverColor+" "+_mesTask.Force);
            Debug.WriteLine("StartNewTask " + "ID: " + _mesTask.ID + "SN: " + _mesTask.SN + "BodyColor: " + _mesTask.UBodyColor + "CoverColor: " + _mesTask.UCoverColor + " Force:" + _mesTask.Force.ToString());
            TaskInfoString = "任务信息:" + " ID:" + _mesTask.ID + " SN:" + _mesTask.SN + " U盘颜色:" + _mesTask.UBodyColor + " U盘帽颜色:" + _mesTask.UCoverColor + " 烧录文件名"+_mesTask.copyfilestr+" Force"+_mesTask.Force;
            Messages.WriteLine(TaskInfoString);
        }

        public COMMANDREUSLT SendTaskResultToMES()
        {

            string strcmd = "update CMD_WIP_PROCESS SET PROCESS_STATUS=3 ,UPDATE_BY='PxC', ACTUAL_FINISH_DATE=GetDate(),UPDATE_DATE=GetDate() "
            + " ,PQC_RESULT="
            + (int)TaskInfo.TaskResult
            + " ,PQC_DEFECT_CODE="
            + (int)TaskInfo.RejectReason
            + " ,PQC_FILE_PATH="
            + "'" + TaskInfo.PQCFilePath + "'"
            + " where ID="
            + CurrentMESTask.ID
            + " and PROCESS_STATUS<>4" ;

            SQLc.SendCommand(strcmd);

            string info =  "发送给MES结果信息: PQC_RESULT="
            + (int)TaskInfo.TaskResult
            + " ,PQC_DEFECT_CODE="
            + (int)TaskInfo.RejectReason
            + " ,PQC_FILE_PATH="
            + "'" + TaskInfo.PQCFilePath + "'"
            + " ID="
            + CurrentMESTask.ID;
            Messages.WriteLine(info);
            return COMMANDREUSLT.COMPLETE;
        }
                
        private ManualResetEvent eventWait = new ManualResetEvent(false); 
        private PLCSTATE _PLCstate;
        public PLCSTATE GetPLCState()
        { 
            _PLCstate = PLCSTATE.UNKNOWN;
            SendMessageToPlc("request state");
          //  Debug.WriteLine("request send done");
            eventWait.Reset();
            eventWait.WaitOne(2000);  
            Debug.WriteLine("getplcstate: "+_PLCstate.ToString());
            return _PLCstate;
        }

        public TASKINFO TaskInfo=new TASKINFO(true);
        public CHECKSTATE GetTaskResult()
        {
            TaskInfo.TaskResult = TASKRESULT.NOTGOOD;
            TaskInfo.RejectReason = REJECTREASON.UNDETECTED;
            SendMessageToPlc("request task result");
            eventWait.Reset();
            eventWait.WaitOne(2000);
            //Debug.WriteLine("requesttaskresult: "+_TaskInfo.TaskResult.ToString());
            if (TaskInfo.RejectReason != REJECTREASON.UNDETECTED || TaskInfo.TaskResult == TASKRESULT.GOOD) {
                return CHECKSTATE.CHECKED;
            }
            else {
                return CHECKSTATE.UNCHECKED;
            } 
        }

        public void SendMessageToPlc(string str)
        {
            MESTcp.Send(str);
        } 

        public delegate T DelegMethod<T>();  

        public async Task WaitUntil<T>(int timeSpan,DelegMethod<T> CheckMethod, params T[] continueCondition)
        {
            if (CancelTask) {
                Messages.WriteLine("----------以下步骤被取消：");
            }
             while (!CancelTask) {
                 try {
                     foreach (T t in continueCondition) {
                         
                         if (EqualityComparer<T>.Default.Equals(CheckMethod(), t)) {
                             return;
                         }
                     }
                 }
                 catch (Exception e) {
                     Messages.WriteLine("错误:");
                     Messages.WriteLine(e.ToString());
                 }
 
                await Task.Delay(timeSpan);
            }
        }

  
        public void AnalyzePLCMessage(Object sender, TCPEventArgs e)
        { 
            
            string recStr = e.receivedmessage;
            string[] recStrArr = recStr.Split(' ');
            //Debug.WriteLine(recStr);
            if (recStr == "control system is available") {
                _PLCstate = PLCSTATE.AVAILABLE;
            }
            else if (recStr == "control system and wpc is ready") {
                _PLCstate = PLCSTATE.READY;
            }
            else if (recStr == "control system is busy") {
                _PLCstate = PLCSTATE.BUSY;
            }
            else if (recStrArr[0] == "result:") {

                int taskResult = 0;
                int checkRejectReason = 0;
                int.TryParse(recStrArr[1], out taskResult);
                int.TryParse(recStrArr[2], out checkRejectReason);

                if (CurrentMESTask.Force == 0) {
                    if (taskResult == 1) {
                        TaskInfo.TaskResult = TASKRESULT.GOOD;
                    }
                    else {
                        TaskInfo.TaskResult = TASKRESULT.NOTGOOD;
                    }

                    TaskInfo.RejectReason = (REJECTREASON)checkRejectReason;
                }
                else if (CurrentMESTask.Force == 1) {
                    TaskInfo.TaskResult = TASKRESULT.GOOD;
                    TaskInfo.RejectReason = (REJECTREASON)0;
                }
                else if (CurrentMESTask.Force == 2) {

                    TaskInfo.TaskResult = TASKRESULT.NOTGOOD;
                    TaskInfo.RejectReason = (REJECTREASON)REJECTREASON.ForceNG;
                }
                else {
                    Messages.WriteLine("Force Value Error Input");
                }

                
                TaskInfo.PQCFilePath = recStrArr[3];
                Debug.WriteLine("taskresult is :" + TaskInfo.TaskResult.ToString());
                Debug.WriteLine("rejectreason is :" + TaskInfo.RejectReason.ToString());
                Debug.WriteLine(recStr);

            }
           // Debug.WriteLine("anastate: "+ _PLCstate.ToString());

            eventWait.Set();
          //  Debug.WriteLine(recStr);
        }


        public List<string> ExtractCopyFiles(string filesStr)
        {
            filesStr.Replace(" ", "");
            string[] strArr = filesStr.Split('|');

            List<string> files = new List<string>(strArr);

            return files;


        }

         
        public void ForceGood()
        {
            CurrentMESTask.preForce = 1;
            Messages.WriteLine("FORCE GOOD WILL BE ACTIVATED IN NEXT CYCLE");
        }

        public void ForceNG()
        {
            CurrentMESTask.preForce = 2;
            Messages.WriteLine("FORCE NOTGOOD WILL BE ACTIVATED IN NEXT CYCLE");
        }

        public void FreeForce()
        {
            CurrentMESTask.preForce = 0;
            Messages.WriteLine("FREE FORCE WILL BE ACTIVATED IN NEXT CYCLE");
        }
    }
}
