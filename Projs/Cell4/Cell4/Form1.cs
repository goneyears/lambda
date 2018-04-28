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

namespace Cell4
{
    public partial class Form1 : Form
    {
 
        public Form1()
        {
            InitializeComponent();
        }
          
        USBCopyer usbCopyer;
        MESController mesController; 
        SystemState systemState;
        private void Form1_Load(object sender, EventArgs e)
        {

            Control.CheckForIllegalCrossThreadCalls = false;

            InitialSystemComponent();
             

            Thread MainProcessThread = new Thread(MainProcess);

            MainProcessThread.Start();
 
        }

        public void InitialSystemComponent()
        {
            mesController = new MESController();

            usbCopyer = new USBCopyer();

           // CameraColorTestTransfer camTransfer = new CameraColorTestTransfer();

            systemState = new SystemState(sysGridView);
        }

        public void DeleteSystemComponenet()
        {
            mesController = null;

            usbCopyer = null;

            systemState = null;
        }

        public void MainProcess()
        {

            AsyncMESControlTask();
            AsyncDisplayInformation();

            AsyncCheckSystemState();
           


        }

        public string MessageOutput;
        public async void AsyncMESControlTask()
        {

                while (true) {
                    Messages.WriteLine("等待PLC和夹具就绪");
                    await mesController.WaitUntil(2000, mesController.GetPLCState, PLCSTATE.READY);
                    Messages.WriteLine("夹具到位");

                    Messages.WriteLine("等待MES任务");
                    await mesController.WaitUntil(2000, mesController.GetNewTask, MESSTATE.NEWTASKAVAILABLE);
                    Messages.WriteLine("任务已接收");

                    await mesController.WaitUntil(2000, mesController.SendCurrentTaskToPLC, COMMANDREUSLT.COMPLETE);
                    Messages.WriteLine("任务已发送至PLC");

                    await mesController.WaitUntil(1000, mesController.GetPLCState, PLCSTATE.BUSY);
                    Messages.WriteLine("机器人正在组装U盘");

                    await mesController.WaitUntil(2000, mesController.GetPLCState, PLCSTATE.READY, PLCSTATE.AVAILABLE);
                    Messages.WriteLine("U盘组装测试完成");


                    Messages.WriteLine("获取测试结果...");
                    await mesController.WaitUntil(2000, mesController.GetTaskResult, CHECKSTATE.CHECKED);
                    


                    Messages.WriteLine("测试结果发送至MES...");
                    await mesController.WaitUntil(2000, mesController.SendTaskResultToMES, COMMANDREUSLT.COMPLETE);
                    Messages.WriteLine("测试结果发送成功");


                    Messages.WriteLine("任务完成\r\n");


                    mesController.CancelTask = false;
                    
                }

            //Debug.WriteLine("-----------");         

        }

        public async void AsyncCheckSystemState()
        {
            while (true) {
                
                systemState.QueryState();
                await Task.Delay(1000); 
            }
        }

        public async void AsyncDisplayInformation()
        {
            while (true) {
                MessageTextBox.Text = Messages.Text;
                if (AutoRollChk.Checked) {
                    MessageTextBox.Focus();
                    MessageTextBox.Select(MessageTextBox.TextLength, 0);
                    MessageTextBox.ScrollToCaret();
                }


                await Task.Delay(500);
            }


        }

 
     
        private void ResetBtn_Click(object sender, EventArgs e)
        {
            mesController.CancelTask = true;

            string str = Interaction.InputBox("请输入密码", "提示", "123456",100, 100);
            if (str == "123456") {
                systemState.ResetControlSystem();
            }
            else if(str!=""){
                
                MessageBox.Show("密码错误");
            }
            
        }

         

        private void button3_Click(object sender, EventArgs e)
        {
            //string[] str;
            //str=Directory.GetFiles(@"C:\Users\BM021671\Documents\ProjectFiles\Cell4\SourceFiles\");
            //foreach (var s in str) {
            //    Debug.WriteLine(s);
            //}
            //string scdir=@"c:\a";
            ////string dstdir=@"c:\b";
            //List<string> files = new List<string>();
            //files.Add("1.exe");
            //files.Add("2.txt");

            ////try {

            ////    Debug.WriteLine(FileSys.CompareFileWithMD5(Path.Combine(scdir, "2.txt"), Path.Combine(dstdir, "33.txt")));
            ////}
            ////catch (Exception ee) {
            ////    Debug.WriteLine(ee.ToString());
            ////}

            ////   FileSys.CopyToUDisk(files);
            //Common.copyfilelist = files;
            //usbCopyer.UdiskCopyTest();
            //DataTable dt = new DataTable();

            //dt.Columns.Add("No.", System.Type.GetType("System.Int16"));

            //dt.Columns.Add("Name", System.Type.GetType("System.String"));

            //dt.Columns.Add("Step", System.Type.GetType("System.Int16"));
            //DataRow dr = dt.NewRow();
            //dr["No."] = 1;
            //dr["Name"] = "WPCPosing";

            //dr["Step"] = 2;
            //dt.Rows.Add(dr);
            //StateGridView.DataSource = dt;
            //systemState.QueryState();


           // stbtcp = new TCPConnector("192.168.10.130", 5653);
           // stbtcp.SendString("test"); 
            //SQLConnector SQLc;
            //SQLc = new SQLConnector("Server=192.168.10.100;Database=PhoenixDB;user id=sa ;password=Phoenix@123 ;");
            
            //DataTable TaskDataTable = new DataTable();

            //TaskDataTable = SQLc.GetNewData(
            //    "select top 1 ID,SN,PROCESS_CODE,PROCESS_FILE_PATH from CMD_WIP_PROCESS "
            //    + " where (PROCESS_STATUS=1 or PROCESS_STATUS=2 ) and WORK_CENTER_CODE=4 "
            //    + " order by PRIORITY_LEVEL desc,ID asc");
            
         //DataTable TaskDataTable = new DataTable();
         //   TaskDataTable = new DataTable(); 

         //   TaskDataTable = SQLc.GetNewData(
         //       "select top 1 ID,SN,PROCESS_CODE,PROCESS_FILE_PATH from CMD_WIP_PROCESS "
         //       );

         //   string ID = TaskDataTable.Rows[0]["ID"].ToString();
         //   int i = 1;
         //   i++;
           // InitialSystemComponent();
           // Application.Restart();
            ;
        } 

         
        //private   void button2_Click_1(object sender, EventArgs e)
        //{
        //    Debug.WriteLine("start----"); 
        //    Debug.WriteLine("end----");
        //}
        //private void button4_Click(object sender, EventArgs e)
        //{
        //    mesController.GetTaskResult();
        //}

        protected override void WndProc(ref Message m)
        {

            Udisk.DeviceChanged(ref m);
            base.WndProc(ref m);
        }

        public TCPConnector stbtcp;

        private void button1_Click(object sender, EventArgs e)
        {
            //DeleteSystemComponenet();
        }

        private void sysGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            Messages.WriteLine("datagrid view error");
        }

        private void AutoRollChk_CheckedChanged(object sender, EventArgs e)
        {
            Debug.WriteLine(AutoRollChk.Checked);
        }



        private void ForceFreeChk_Click(object sender, EventArgs e)
        {

            mesController.FreeForce();
            Debug.WriteLine("force:" + mesController.CurrentMESTask.Force);
            MessageBox.Show("停止强制，下个任务生效");

        }

        private void ForceGoodChk_Click(object sender, EventArgs e)
        {
            mesController.ForceGood();
            Debug.WriteLine("force:" + mesController.CurrentMESTask.Force);
            MessageBox.Show("强制检测合格，下个任务生效");

        }

        private void ForceNGChk_Click(object sender, EventArgs e)
        {
            mesController.ForceNG();
            Debug.WriteLine("force:" + mesController.CurrentMESTask.Force);
            MessageBox.Show("强制检测不合格，下个任务生效");

        }








    }
}
