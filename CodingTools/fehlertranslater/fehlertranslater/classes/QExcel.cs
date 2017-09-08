using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Office.Core;
using System.Reflection;
using Excel = Microsoft.Office.Interop.Excel;

using System.Diagnostics;
using System.Text.RegularExpressions;



namespace fehlertranslater
{
    class QExcel
    {

         private Excel.Application oXL {get;set;}
         private Excel.Workbooks oWBs{get;set;}
         private Excel.Workbook oWB { get; set; }
 //        private Excel.Worksheets oShts { get; set; }
         private Excel.Worksheet oSht {get;set;}

         public string Path { get; set; }   

        public QExcel(string path)
        {
            Path = path;
            oXL = new Excel.Application();
            oWBs = oXL.Workbooks;
            oWB = oWBs.Add(Path);
            oSht = oWB.Worksheets[1];
            oXL.AlertBeforeOverwriting = false;
        }

        public QExcel(string path,int shtNumber)
        {
            Path = path;
            oXL = new Excel.Application();
            oWBs = oXL.Workbooks;
            oWB = oWBs.Add(Path);
            oSht = oWB.Worksheets[shtNumber];
            oXL.AlertBeforeOverwriting = false;
        }

        public Excel.Sheets Sheets
        {
            get
            {
                 return oWB.Worksheets;
            }


        }
        public void Display()
        {
            for(int i=1;i<=20;i++)
            {
                string str = oSht.Cells[i, 2].value;
            }
        }
        public void Close()
        {
            oXL.Quit();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(oXL);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(oWBs);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(oWB);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(oSht);
            oXL = null;
            oWBs = null;
            oWB = null;
            oSht = null;
            GC.Collect();


        }
        public void SaveAndClose()
        {

            oWB.Save();
            Close();

        }

    }
}
