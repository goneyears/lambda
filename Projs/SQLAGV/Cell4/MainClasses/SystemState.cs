using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Data;
using System.Windows.Forms;

namespace SQLAGV
{

    class SystemState
    {
        public struct _STEPS
        {
           public int RobotInterface;
           public int WPCPreStop;
           public int WPCPosing;
           public int PCUSBTest;
           public int PCCommandToRobot;
           public int CameraColorTest;
           public int RFIDCheck;
           public int RobotAssemblyStep;
        }

        public _STEPS Steps = new _STEPS();

        public SystemState(DataGridView sysGridView)
        {
            Messages.WriteLine("建立状态监控-PLC通信连接");
            StateTcp = new TCP_Client("192.168.10.40", "50003");
            
            initialStatesTable();
            SetDataGridViewAppearance(sysGridView);
            sysGridView.DataSource = statesTable;
            StateTcp.MessageReceived += AnalyzePLCMessage; 
        }

        private void SetDataGridViewAppearance(DataGridView dataGridView)
        {
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;

            dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            //dataGridView.RowTemplate.Height = 20;
            
        } 

        private TCP_Client StateTcp;

        public void QueryState()
        {
            StateTcp.Send("request steps state"); 
        }

        public DataTable statesTable;
        public void initialStatesTable(){
            statesTable = new DataTable();

            statesTable.Columns.Add("No", System.Type.GetType("System.Int16"));
          
            statesTable.Columns.Add("Name", System.Type.GetType("System.String"));

            statesTable.Columns.Add("Step", System.Type.GetType("System.Int16"));

            for (int i = 0; i < 20; i++) {
                DataRow dr = statesTable.NewRow(); 
                dr["No"] = i;
                switch (i) {
                case 0:
                    dr["Name"]="Robot Interface";
                    break;
                case 1:
                    dr["Name"] = "WPC PreStop";
                    break;       
                case 2:          
                    dr["Name"] = "WPC Posing Step";
                    break;
                case 3:
                    dr["Name"] = "RFID Check Step";
                    break;
                case 4:
                    dr["Name"] = "PC USB Test Step";
                    break;
                case 5:
                    dr["Name"] = "Camera Color Test Step";
                    break;
                case 6:
                    dr["Name"] = "PC Command To Robot Step";
                    break;
                case 7:
                    dr["Name"] = "Robot Assembly Step";
                    break;
                case 8:
                    dr["Name"] = "reserved";
                    break;
                case 9:
                    dr["Name"] = "reserved";
                    break;
                case 10:
                    dr["Name"] = "reserved";
                    break;
                case 11:
                    dr["Name"] = "reserved";
                    break;

                }
                statesTable.Rows.Add(dr);
            }

        }

        public void SetStatesTable()
        { 
            if(statesTable.Rows.Count>8){
            statesTable.Rows[0][2] = Steps.RobotInterface     ;
            statesTable.Rows[1][2] = Steps.WPCPreStop 	      ;
            statesTable.Rows[2][2] = Steps.WPCPosing          ;
            statesTable.Rows[3][2] = Steps.RFIDCheck          ;
            statesTable.Rows[4][2] = Steps.PCUSBTest          ;
            statesTable.Rows[5][2] = Steps.CameraColorTest    ;
            statesTable.Rows[6][2] = Steps.PCCommandToRobot   ;
            statesTable.Rows[7][2] = Steps.RobotAssemblyStep  ;
            }
            else {
                Messages.WriteLine("statestable error");
            }
        }


        public void ResetControlSystem()
        {
            StateTcp.Send("reset all"); 
        }


        private void AnalyzePLCMessage(object sender, TCPEventArgs e)
        {
            Debug.WriteLine(e.receivedmessage);
                        
            string recStr = e.receivedmessage;

            recStr.Replace(" ", "");
            string[] recStrArr = recStr.Split(' ');
            if (recStrArr[0] == "steps:" ) {

                Steps.RobotInterface    = int.Parse(recStrArr[1]);
				Steps.WPCPreStop 	    = int.Parse(recStrArr[2]);
				Steps.WPCPosing         = int.Parse(recStrArr[3]);
				Steps.RFIDCheck         = int.Parse(recStrArr[4]);
				Steps.PCUSBTest         = int.Parse(recStrArr[5]);
				Steps.CameraColorTest   = int.Parse(recStrArr[6]);
				Steps.PCCommandToRobot  = int.Parse(recStrArr[7]);
                Steps.RobotAssemblyStep = int.Parse(recStrArr[8]);

                SetStatesTable();
            }

                  
            //throw new NotImplementedException();
        }



    }
}
