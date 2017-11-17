using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Data.SqlClient;
using Microsoft.Office.Core;
using System.Reflection;
using Excel = Microsoft.Office.Interop.Excel;
using System.Text.RegularExpressions;

using System.Data.OleDb; 

namespace fehlertranslater
{
    

    public partial class Form1 : Form
    {
        public OleDbDataAdapter thisAdapter = new OleDbDataAdapter();


        string fehlerPath = "";
        string fehlerUnicodePath = "";

        const int MAXEXCELROW = 1000;

        int fileLines = 0;
        int transLines = 0;
        int fehlerLines = 0;
        int untransLines = 0;
              
        List<string> untranslist= new List<string>();
        #region hide
        public Form1()
        {
            InitializeComponent();
        }

        private void translate_btn_Click(object sender, EventArgs e)

        {
            fileLines = 0;
            transLines = 0;
            fehlerLines = 0;
            untransLines = 0;
            OleDbConnection thisConnection = new OleDbConnection(@"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=dictionary.accdb;Persist Security Info=False");
                   
            thisConnection.Open();


            string sql1 = "select  OriginalField,TranslationField from BasicDictionary WHERE ((OriginalField not In (SELECT OriginalField FROM BasicDictionary As Tmp GROUP BY OriginalField HAVING Count(*)>1 )))";
            string sql2 = "select  OriginalField,TranslationField from NewDictionary WHERE ((OriginalField not In (SELECT OriginalField FROM NewDictionary As Tmp GROUP BY OriginalField HAVING Count(*)>1 )))";
            string sqlunion = sql1 + " UNION " + sql2;
            string sqlunionb = "(" + sqlunion + ")";
            string sql = "Select * from " + sqlunionb + "WHERE ((OriginalField not In (SELECT OriginalField FROM " + sqlunionb + " As Tmp GROUP BY OriginalField HAVING Count(*)>1 )))";
            thisAdapter = new OleDbDataAdapter(sql, thisConnection);
            System.Data.DataSet thisDataSet = new System.Data.DataSet();
            thisAdapter.Fill(thisDataSet, "WholeDictionary");
            DataTable dt = thisDataSet.Tables["WholeDictionary"];


            Dictionary<string, string> dic = new Dictionary<string, string>();
            dic.Clear();
            {
                dic = dt.Rows.Cast<DataRow>().ToDictionary(x => x[0].ToString().ToUpper(), x => x[1].ToString());
            }

            string sqlDel = "delete * from UntransDictionary";
            OleDbCommand commDel = new OleDbCommand(sqlDel, thisConnection);

            commDel.ExecuteNonQuery();

            Debug.WriteLine(System.AppDomain.CurrentDomain.BaseDirectory);

            FileStream fs = new FileStream(fehlerPath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            StreamReader fehlerTxt = new StreamReader(fs, System.Text.Encoding.Default);
            System.IO.StreamWriter fehlerunicodeTxt = new System.IO.StreamWriter(fehlerUnicodePath, false, Encoding.GetEncoding("Unicode"));
            
            string fehlerLine;
            while ((fehlerLine = fehlerTxt.ReadLine()) != null)
            {
                Line line = new Line(fehlerLine, dic);
                if (line.TransResult == Line.TranslationResult.Partial)
                {
                   string sqlInsert = "insert into UntransDictionary(OriginalField,TranslationField)values(@LineOriginalBlock,@LineTranslatedBlock)";

                    OleDbCommand comm = new OleDbCommand(sqlInsert, thisConnection);
                    OleDbParameter[] parameters = {
                    comm.Parameters.Add(new OleDbParameter("@LineOriginalBlock",OleDbType.VarChar)),
                    comm.Parameters.Add(new OleDbParameter("@LineTranslatedBlock", OleDbType.VarChar)),
                                                  };

                    parameters[0].Value = line.OriginalBlock;
                    parameters[1].Value = line.TranslatedBlock.Replace("\r", "").Replace("\n","");

                    untranslist.Add(line.TranslatedBlock.Replace("\r", ""));

                    comm.ExecuteNonQuery();

                    untransLines++;
                }

                fehlerunicodeTxt.WriteLine(line.Translation);

                fileLines++;
                if (line.Type == Line.LineType.fehler) fehlerLines++;
                if (line.TransResult == Line.TranslationResult.Full) transLines++;

            }


            sql = "select OriginalField,TranslationField from UntransDictionary order by OriginalField";
            thisAdapter = new OleDbDataAdapter(sql, thisConnection);
            thisAdapter.Fill(thisDataSet, "UntransDictionary1");
            dt = thisDataSet.Tables["UntransDictionary1"];
            this.UntransDicGrid.DataSource = dt;
            tabControl1.SelectTab(2);

            fs.Close();
            fehlerTxt.Close();
            fehlerunicodeTxt.Close();
            thisConnection.Close();


            filelines_label.Text = fileLines.ToString();
            fehlerlines_label.Text = fehlerLines.ToString();
            translines_label.Text = transLines.ToString();
            untranslines_label.Text = untransLines.ToString();
            MessageBox.Show("Translate Complete");

        }

        #endregion

        private void Form1_Load(object sender, EventArgs e)
        {
            System.IO.StreamReader configIni = new System.IO.StreamReader("config.ini");
            fehlerPath = configIni.ReadLine();
            fehlerUnicodePath = configIni.ReadLine();
            FehlerPathBox.Text = fehlerPath;
            FehlerUnicodePathBox.Text = fehlerUnicodePath;
            configIni.Close();

            Update_AllDataGrids();

        }

        private void Update_AllDataGrids()
        {
            OleDbConnection thisConnection = new OleDbConnection(@"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=dictionary.accdb;Persist Security Info=False");


            string sql = "select OriginalField,TranslationField from BasicDictionary order by OriginalField";
            thisAdapter = new OleDbDataAdapter(sql, thisConnection);
            System.Data.DataSet thisDataSet = new System.Data.DataSet();
            thisAdapter.Fill(thisDataSet, "BasicDictionary1");
            DataTable dt = thisDataSet.Tables["BasicDictionary1"];
            this.BasicDicGrid.DataSource = dt;

            BasicDicGrid.EndEdit();


            sql = "select OriginalField,TranslationField from NewDictionary order by OriginalField";
            thisAdapter = new OleDbDataAdapter(sql, thisConnection);
            thisAdapter.Fill(thisDataSet, "NewDictionary1");
            dt = thisDataSet.Tables["NewDictionary1"];
            this.NewDicGrid.DataSource = dt;

            NewDicGrid.EndEdit();


            sql = "select OriginalField,TranslationField from UntransDictionary";
            thisAdapter = new OleDbDataAdapter(sql, thisConnection);
            thisAdapter.Fill(thisDataSet, "UnTransDictionary1");
            dt = thisDataSet.Tables["UnTransDictionary1"];
            this.UntransDicGrid.DataSource = dt;

            thisConnection.Close();
            UntransDicGrid.EndEdit();
        }
 

        private void BasicDic_Update_Click(object sender, EventArgs e)
        {
            //check empty key
            for (int i = 0; i < BasicDicGrid.Rows.Count - 1; i++)
            {
                if (BasicDicGrid.Rows[i].Cells[0].Value == null || BasicDicGrid.Rows[i].Cells[0].Value.ToString() == "")
                {
                    MessageBox.Show("Empty key");
                    BasicDicGrid.CurrentCell = BasicDicGrid.Rows[i].Cells[1];
                    return;
                }
                else
                {
                    BasicDicGrid.Rows[i].Cells[0].Value = Regex.Replace(BasicDicGrid.Rows[i].Cells[0].Value.ToString(), @"\b\s+\b", " ").Trim(' ');
                }
            }

            BasicDicGrid.EndEdit();
            string sql = "select OriginalField,TranslationField from BasicDictionary order by OriginalField";
            OleDbConnection thisConnection = new OleDbConnection(@"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=dictionary.accdb;Persist Security Info=False");


            OleDbDataAdapter da = new OleDbDataAdapter(sql, thisConnection);

            OleDbCommandBuilder bld = new OleDbCommandBuilder(da);
            thisAdapter.UpdateCommand = bld.GetUpdateCommand();



            DataTable dt = (DataTable)BasicDicGrid.DataSource;
          //  dt.AcceptChanges();
 
            try
            {
                da.Update(dt);
            }
            catch (OleDbException)
            {
                MessageBox.Show("Duplicate keys");
            }


            thisConnection.Close(); 
        }
 

        private void NewDic_Update_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < NewDicGrid.Rows.Count - 1; i++)
            {
                if (NewDicGrid.Rows[i].Cells[0].Value == null || NewDicGrid.Rows[i].Cells[0].Value.ToString() == "")
                {
                    MessageBox.Show("Empty key");
                    NewDicGrid.CurrentCell = NewDicGrid.Rows[i].Cells[1];
                    return;
                }
                else
                {
                    NewDicGrid.Rows[i].Cells[0].Value = Regex.Replace(NewDicGrid.Rows[i].Cells[0].Value.ToString(), @"\b\s+\b", " ").Trim(' ');
                }
            }
            NewDicGrid.EndEdit();
            string sql = "select OriginalField,TranslationField from NewDictionary order by OriginalField";
            OleDbConnection thisConnection = new OleDbConnection(@"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=dictionary.accdb;Persist Security Info=False");
           
            
            OleDbDataAdapter da = new OleDbDataAdapter(sql, thisConnection);

            OleDbCommandBuilder bld = new OleDbCommandBuilder(da);
            thisAdapter.UpdateCommand = bld.GetUpdateCommand();

            DataTable dt = (DataTable)NewDicGrid.DataSource;

            try
            {
               da.Update(dt);
            }
            catch (OleDbException)
            {
                MessageBox.Show("Duplicate keys");
            }


            thisConnection.Close(); 
        }


        public void DataGridViewEnableCopy(DataGridView p_Data)
        {
            Clipboard.SetData(DataFormats.Text, p_Data.GetClipboardContent());
        }

        public void DataGirdViewCellPaste(DataGridView p_Data)
        {

            string pasteText = Clipboard.GetText();
            if (string.IsNullOrEmpty(pasteText))
                return;
            string[] lines = pasteText.Split('\n');
            foreach (string line in lines) {
                if (string.IsNullOrEmpty(line.Trim('\t', ' ')))
                    continue;

                string[] vals = (line.Trim('\t')).Split('\t');
                ((DataTable)p_Data.DataSource).Rows.Add(vals);
            }

        }

        public void DataGridViewEnablePaste(DataGridView p_Data)
        {
            if (p_Data == null)
                return;
            p_Data.KeyDown += new KeyEventHandler(p_Data_KeyDown);
        }

        public void p_Data_KeyDown(object sender, KeyEventArgs e)
        {
            if (Control.ModifierKeys == Keys.Control && e.KeyCode == Keys.V)
            {
                if (sender != null && sender.GetType() == typeof(DataGridView))

                    DataGirdViewCellPaste((DataGridView)sender);
            }
        }

        private void Simplify_Click(object sender, EventArgs e)
        {
            Debug.WriteLine("untranslines:-----\n");
            Dictionary<string, int> untranswords = new Dictionary<string, int>();
            foreach(string lst in untranslist){
                string lstl = lst.ToLower();
                Regex rgx = new Regex(@"[\u4E00-\u9FA50-9.]*([a-z -]+)[\u4E00-\u9FA50-9.]*([a-z -]+)?[\u4E00-\u9FA50-9.]*([a-z -]+)?[\u4E00-\u9FA50-9.]*");
                Match match = rgx.Match(lstl);
                Debug.WriteLine(match.Groups.Count);
                Debug.WriteLine(lstl);
                for (int i = 1; i < match.Groups.Count; i++) {
                    string s = match.Groups[i].Value;
                    if (s.Replace(" ","") != "") {
                        string str = Regex.Replace(s, @"(^\s*)|(\s*$)", "");
                        if(!untranswords.ContainsKey(str)){
                            untranswords.Add(str,1);
                        }
                        else {
                            untranswords[str] = untranswords[str] + 1;
                        }
                    }
                }
            }

            Dictionary<string, int> sorteddic = untranswords.OrderByDescending(p => p.Value).ToDictionary(p => p.Key, o => o.Value);
            foreach (KeyValuePair<string, int> kp in sorteddic) {
                Debug.WriteLine(kp.Key + "\t" + kp.Value);
            }
        }

  
        private void FehlerPathSelect_Click_1(object sender, EventArgs e)
        {
            OpenFileDialog fileName = new OpenFileDialog();
            fileName.InitialDirectory = Application.StartupPath;
            fileName.Filter = "txt files (*.txt)|*.txt";
            fileName.RestoreDirectory = true;
            if(fileName.ShowDialog()==DialogResult.OK)
            {
                fehlerPath = fileName.FileName.ToString();
                FehlerPathBox.Text = fehlerPath;
            }
            System.IO.StreamWriter configIni = new System.IO.StreamWriter("config.ini");
            configIni.WriteLine(fehlerPath);
            configIni.WriteLine(fehlerUnicodePath);
            configIni.Close();

        }

        private void FehlerUnicodePathSelect_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileName = new OpenFileDialog();
            fileName.InitialDirectory = Application.StartupPath;
            fileName.Filter = "txt files (*.txt)|*.txt";
            fileName.RestoreDirectory = true;
            if (fileName.ShowDialog() == DialogResult.OK)
            {
                fehlerUnicodePath = fileName.FileName.ToString();
                FehlerUnicodePathBox.Text = fehlerUnicodePath;
            }
            System.IO.StreamWriter configIni = new System.IO.StreamWriter("config.ini");
            configIni.WriteLine(fehlerPath);
            configIni.WriteLine(fehlerUnicodePath);
            configIni.Close();
        }

        private void UntransDicGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str1 = "   站8turn table can 没有turn to 位this 位    ";
            string str2 = "站8turn table can 没有be locked";
            string str3 = "站8turn table can 没有位";
            Regex rgx = new Regex(@"[\u4E00-\u9FA50-9]*([a-z ]+)[\u4E00-\u9FA50-9]*([a-z ]+)?[\u4E00-\u9FA50-9]*([a-z ]+)?[\u4E00-\u9FA50-9]*");
            Match match = rgx.Match(str1);

            string str = Regex.Replace(str1, @"(^\s*)|(\s*$)", "");
            Debug.WriteLine(str);
            

        }





    }
}
    