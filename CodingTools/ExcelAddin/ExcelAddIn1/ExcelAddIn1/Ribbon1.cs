﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using System.Windows.Forms;

using MySql.Data.MySqlClient;
using System.Data;
 
using System.Xml.Linq;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
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
                                                from vprice where 
                                                type like {0} or 
                                                name like {0} or
                                                ordernumber like {0} or
                                                provider like {0} limit 1"
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

        private void FullPriceBtn_Click(object sender, RibbonControlEventArgs e)
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
                                                from vprice where 
                                                type like {0} or 
                                                name like {0} or
                                                ordernumber like {0} or
                                                provider like {0} limit 99"
                                                   , "'%" + keyword + "%'");

                        mycom.CommandText = sql;

                        sdr = mycom.ExecuteReader();

                        int irow = 0;

                        SqlReturn[] sqlrt = new SqlReturn[100];
                        for (int i = 0; i < sqlrt.Length; i++) {
                            sqlrt[i] = new SqlReturn();
                        }
                        MessageForm fm2 = new MessageForm("Name: "+cel.Value2);
                        fm2.Show();
                        DataTable dt = new DataTable();

                        initialTable(ref dt);
                        while (sdr.Read()) {
                            if (sdr.HasRows) {

                                try { sqlrt[irow].ordernumber = sdr.GetString(0); }
                                catch { };
                                try { sqlrt[irow].name = sdr.GetString(1); }
                                catch { };
                                try { sqlrt[irow].type = sdr.GetString(2); }
                                catch { };
                                try { sqlrt[irow].currency = sdr.GetString(3); }
                                catch { };
                                try { sqlrt[irow].price = sdr.GetFloat(4); }
                                catch { };
                                try { sqlrt[irow].provider = sdr.GetString(5); }
                                catch { };
                                //res = res+string.Format("{0}    {1}    {2}    {3}    {4}    {5}\n", sqlrt[irow].ordernumber, sqlrt[irow].name, sqlrt[irow].type, sqlrt[irow].currency, sqlrt[irow].price, sqlrt[irow].provider);
                               
                                DataRow dr = dt.NewRow();
                                dr["订货号"] = sqlrt[irow].ordernumber;
                                dr["名称"] = sqlrt[irow].name;
                                dr["型号"] = sqlrt[irow].type;
                                dr["币种"] = sqlrt[irow].currency;
                                dr["单价"] = sqlrt[irow].price;
                                dr["供应商"] = sqlrt[irow].provider;

                                dt.Rows.Add(dr);

                                irow++;
                            }
                            else {
                                break;
                            }
                        }

                        fm2.ShowMessage(dt);

                        sdr.Close();

          
                    }
                }
            }
            catch (Exception ee) {

                MessageBox.Show(ee.ToString());

            }
        }
        public void insertTableRow(DataRow dr)
        {

        }

        public void initialTable(ref DataTable dt)
        {
            dt = new DataTable(); 
            dt.Columns.Add("订货号", System.Type.GetType("System.String"));
            dt.Columns.Add("名称", System.Type.GetType("System.String"));
            dt.Columns.Add("型号", System.Type.GetType("System.String"));
            dt.Columns.Add("币种", System.Type.GetType("System.String"));
            dt.Columns.Add("单价", System.Type.GetType("System.String"));
            dt.Columns.Add("供应商", System.Type.GetType("System.String"));

             

        }
    }
}
