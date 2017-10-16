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
        public struct AGVMOTIONTASK
        {
            public int ID;
            public string AGV_INDEX;
            public int LOGISTIC_STATUS;
            public int MOVE_STATUS;
            public int QTY;
            public string SOURCE_AREA;
            public string[] SOURCE_LOCATION=new string[5];
            public string LOGISTIC_STATUS;
            public string TARGET_AREA;
            public string[] TARGET_LOCATION=new string[5];


        }

        public SystemState(DataGridView sysGridView)
        {
            
            initialStatesTable();
            SetDataGridViewAppearance(sysGridView);
            sysGridView.DataSource = statesTable;
 
            SQLc = new SQLConnector("Server=192.168.10.100;Database=PhoenixDB;user id=sa ;password=Phoenix@123 ;");
           
        }


        private TCP_Client MESTcp;
        private SQLConnector SQLc;
        private void SetDataGridViewAppearance(DataGridView dataGridView)
        {
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;

            dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            //dataGridView.RowTemplate.Height = 20;
            
        } 

        private TCP_Client StateTcp; 

        public void QueryState()
        {
        }

        public DataTable statesTable;
        public void initialStatesTable(){
            statesTable = new DataTable();

            statesTable.Columns.Add("id", System.Type.GetType("System.Int16"));
          
            statesTable.Columns.Add("agv", System.Type.GetType("System.String"));

            statesTable.Columns.Add("movestatus", System.Type.GetType("System.Int16"));

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


                }
                statesTable.Rows.Add(dr);
            }

        }

        public void SetStatesTable()
        { 
            if(statesTable.Rows.Count>8){
            statesTable.Rows[0][2] = 1   ;
            statesTable.Rows[1][2] = 2	      ;
            statesTable.Rows[2][2] = 3          ;
            statesTable.Rows[3][2] = 4         ;
            }

        }

        public void GetNewTask()
        {
            DataTable AGVTaskDataTable = new DataTable();
            AGVMOTIONTASK agvMotionTask=new AGVMOTIONTASK();

            AGVTaskDataTable = SQLc.GetNewData(
                "select ID from CMD_ITEM_MOVE "
                + " where (MOVE_STATUS=1 or MOVE_STATUS=2 ) "
                +" order by PRIORITY_LEVEL desc,ID asc");
            if (AGVTaskDataTable.Rows.Count == 0) {  

            }else{
                Debug.WriteLine(AGVTaskDataTable.Rows.Count);
                agvMotionTask.ID = TaskDataTable.Rows[0]["ID"].ToString();
                agvMotionTask.SN = TaskDataTable.Rows[0]["SN"].ToString();
                agvMotionTask.copyfilestr = TaskDataTable.Rows[0]["PROCESS_FILE_PATH"].ToString();
                Common.copyfilelist = ExtractCopyFiles(CurrentMESTask.copyfilestr);
            }
        public void ResetControlSystem()
        {
        }



    }
}
