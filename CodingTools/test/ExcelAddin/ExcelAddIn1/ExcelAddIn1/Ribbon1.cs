﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using System.Windows.Forms;

using MySql.Data.MySqlClient;
 
 
using System.Xml.Linq;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Windows.Forms;
using System.Text.RegularExpressions;
namespace ExcelAddIn1
{
    public partial class ETools
    {
        protected class SqlReturn
        {
            public SqlReturn()
            {
                ordernumber = "NULL";
                name = "NULL";
                type = "NULL";
                currency = "NULL";
                price = 0;
                provider = "NULL";

            }
            public string ordernumber ;
            public string name ;
            public string type ;
            public string currency ;
            public float price;
            public string provider ;

        }
        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {

        }

        private void toggleButton1_Click(object sender, RibbonControlEventArgs e)
        {
            MessageBox.Show("toogled");
        }

        private void button1_Click(object sender, RibbonControlEventArgs e)
        {
            MySqlConnection myconn = null;
            MySqlCommand mycom = null;

            MySqlDataReader sdr;

            Excel.Worksheet activeWorksheet = (Globals.ThisAddIn.Application.ActiveSheet);
            try {
                //MySqlDataAdapter myrec = null;
                myconn = new MySqlConnection("Host =192.168.56.2;Database=MEPurchase;Username=root;Password=123456;Charset=utf8;");
                myconn.Open();
                mycom = myconn.CreateCommand();

                Excel.Range selectedrange = Globals.ThisAddIn.Application.Selection;
                foreach (Excel.Range cel in selectedrange) {
                    if (cel.Value2 != null) {

                        string keyword = cel.Value2.ToString();
                        keyword = new Regex("[\\s]+").Replace(keyword, "%"); 

                        string sql = string.Format(@"select 
                                                ordernumber, name, type, currency, price, provider 
                                                from vprice where type like {0} limit 1"
                                                   , "'%" + keyword + "%'");

                        mycom.CommandText = sql;

                        sdr = mycom.ExecuteReader();
                        sdr.Read();
                        cel.ClearComments();
                        SqlReturn sqlrt = new SqlReturn();
                        try { sqlrt.ordernumber = sdr.GetString(0); }
                        catch { };
                        try { sqlrt.name = sdr.GetString(1); }
                        catch { };
                        try { sqlrt.type = sdr.GetString(2); }
                        catch { };
                        try { sqlrt.currency = sdr.GetString(3); }
                        catch { };
                        try { sqlrt.price = sdr.GetFloat(4); }
                        catch { };
                        try { sqlrt.provider = sdr.GetString(5); }
                        catch { };

                        sdr.Close();
                        Excel.Comment c = cel.AddComment(string.Format("订货号：{0}\n名称  ：{1}\n型号  ：{2}\n币种  ：{3}\n单价  ：{4}\n供应商：{5}\n", 
                                                                        sqlrt.ordernumber, sqlrt.name, sqlrt.type, sqlrt.currency, sqlrt.price, sqlrt.provider));
                        c.Shape.TextFrame.AutoSize = true; ;
                    }
                }
            }
            catch (Exception ee) {

                MessageBox.Show(ee.ToString());

            }
        }
    }
}
