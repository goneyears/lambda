using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;
using MySql.Data.MySqlClient;


using Excel = Microsoft.Office.Interop.Excel;
using System.Runtime.InteropServices;
using System.IO;
using System.Reflection;
namespace WpfApplication1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = new UnitViewModel();
        }

        string[] arrstr = {"strat", "Var1", "Var2", "Var3" };

        private void read_click(object sender, RoutedEventArgs e)
        {
            string fehlerPath = "src.st1";
            FileStream fs = new FileStream(fehlerPath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            StreamReader fehlerTxt = new StreamReader(fs, System.Text.Encoding.Unicode);
            string fehlerLine;
            string RegexStr = string.Empty;


            Regex reg = new Regex(@".*(?<varname>OUT_x(\w|\+|-)*).*");
            List<string> outvars = new List<string>();        
            while ((fehlerLine = fehlerTxt.ReadLine()) != null) {
                // RegexStr
                string line = RemoveSpecialCharacters(fehlerLine);
                Debug.WriteLine("start"+fehlerLine);
                Debug.WriteLine("start2"+line);
                Debug.WriteLine("end");
                //Match match = reg.Match(fehlerLine);
                //if (match.Groups[0].Value != "") { 
                //    string value = match.Groups["varname"].Value;
                //    outvars.Add(value);

                //    Console.WriteLine("value1的值为：{0}", value);
                //}
            }
            //reg = new Regex(@".*(?<varname>OUT_x\+(\w|\+|-)*).*");
            //List<string> OutStations = new List<string>();
            //List<string> OutNormals = new List<string>();
            //foreach (string v in outvars) {
            //    Match match = reg.Match(v);
            //    if (match.Groups[0].Value != "") {

            //        OutStations.Add(v); 
            //    }
            //    else {
            //        OutNormals.Add(v);
            //    }
            //}
            //PrintList(OutNormals);
            //PrintList(OutStations);

            //Button[] btn = new Button[1000];
            //RoutedEventHandler d1 = displocation;
            //for (int i = 0; i <OutStations.Count ; i++) {

            //    btn[i] = new Button();
            //    btn[i].Width = 120;
            //    btn[i].Height = 30;
            //    btn[i].Name = "b"+i.ToString();
            //    btn[i].Content = OutStations[i].ToString();
            //    wrp.Children.Add(btn[i]);
            //    btn[i].Click += d1;
            //}


        }
        private void PrintList(List<string> lst)
        {
            foreach (string item in lst) {
                Debug.WriteLine(item);
            }
        }

        private SQLConnector SQLc;
        private void test_regex(object sender, RoutedEventArgs e)
        {
            Debug.WriteLine("start query");
            MySqlConnection myconn = null;
            MySqlCommand mycom = null;
            //MySqlDataAdapter myrec = null;
            myconn = new MySqlConnection("Host =192.168.56.2;Database=MEPurchase;Username=root;Password=123456;Charset=utf8;");
            myconn.Open();
            mycom = myconn.CreateCommand();
            //打开excel
            //if (true) {
            Excel.Application oXL = new Excel.Application();
            Excel.Workbooks oWBs = oXL.Workbooks;
            Excel.Worksheet sht;

            Excel.Workbook oSummary = oWBs.Add(System.IO.Directory.GetCurrentDirectory() + @"\Purchaselist.xlsm");
            sht = oSummary.Worksheets[1];
            Debug.WriteLine(sht.Name);
            int columns = 29;
            string[] field = new string[columns];


            //MySqlDataAdapter adap = new MySqlDataAdapter(mycom);
            for (int i = 1; i < field.Count(); i++) {
                field[i] = ((Excel.Range)sht.Cells[1, i]).Value.ToString();
                // Debug.WriteLine(field[i]); 

            }

            int irow = 5550;
            int iprint = 1;
            string[] ctent = new string[columns];
            while (true) {
                if ((((Excel.Range)sht.Cells[irow, 1]).Value.ToString()) == "") break;
                irow++;

                iprint++;
                if (iprint == 30) {
                    Debug.WriteLine(irow);
                    iprint = 1;
                }

                string sql = string.Format(@"insert into purchaselist ({0}) values ({1});","行编号", irow);
                mycom.CommandText = sql;
                //mycom.CommandType = CommandType.Text;
                MySqlDataReader sdr;
   
                sdr = mycom.ExecuteReader();

                sdr.Close();
 
                for (int i = 2; i < field.Count(); i++) {
                    var c = ((Excel.Range)sht.Cells[irow, i]).Value;
                    if (c != null) {
                        try {
                            if (i != 17 && i != 18 && i != 19 && i != 22 && i != 26 && i != 27 && i != 28) {
                                ctent[i] = "'" + c.ToString() + "'";

                            }
                            else {
                                ctent[i] = c.ToString("yyyyMMdd");
                            }

                            sql = string.Format(@"UPDATE purchaselist SET {0}={1} WHERE 行编号={2};", field[i], ctent[i], irow);
                            mycom.CommandText = sql;
                            sdr = mycom.ExecuteReader();

                            sdr.Close();
                        }
                        catch (Exception ee){
                            Debug.WriteLine("irow: " + irow.ToString());
                            Debug.WriteLine("exception: " + ee);
                            Debug.WriteLine("field[i]: " + field[i].ToString()); 
                            ctent[i] = "'" + c.ToString() + "'";
                            Debug.WriteLine("ctent[i]: " + ctent[i].ToString());
                            sql = string.Format(@"UPDATE purchaselist SET {0}_c={1} WHERE 行编号={2};", field[i], ctent[i], irow);
                            mycom.CommandText = sql;
                            sdr = mycom.ExecuteReader();

                            sdr.Close();
                        }

                    }




                }


            }

        
            // string s = @"insert into purchaselist (物料申请单号,项目号) values (20181023,s18004)";
            //                    string sql = string.Format(@"insert into purchaselist 
            //({0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},{24},{25},{26},{27}) values
            //({28},{29},{30},{31},{32},{33},{34},{35},{36},{37},{38},{39},{40},{41},{42},{43},{44},{45},{46},{47},{48},{49},{50},{51},{52},{53},{54},{55});",
            //field[1], field[2], field[3], field[4], field[5], field[6], field[7], field[8], field[9], field[10], field[11], field[12], field[13], field[14],
            //field[15], field[16], field[17], field[18], field[19], field[20], field[21], field[22], field[23], field[24], field[25], field[26], field[27], field[28],
            //ctent[1], ctent[2], ctent[3], ctent[4], ctent[5], ctent[6], ctent[7], ctent[8], ctent[9], ctent[10], ctent[11], ctent[12], ctent[13], ctent[14],
            //ctent[15], ctent[16], ctent[17], ctent[18], ctent[19], ctent[20], ctent[21], ctent[22], ctent[23], ctent[24], ctent[25], ctent[26], ctent[27], ctent[28]
            //    );


 


            oXL.Quit();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(oXL);
            oXL = null;

        }

        public static string RemoveSpecialCharacters(string str)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < str.Length; i++) {
            if (str[i] >= '!' && str[i] <= '~') {
                sb.Append(str[i]);
            }
        }

        return sb.ToString();
}
        private void button_click(object sender, RoutedEventArgs e)
        {
            Button[] btn = new Button[5];
            RoutedEventHandler d1 = displocation;
            for (int i = 1; i < 4; i++) {

                btn[i] = new Button();
                btn[i].Width = 30;
                btn[i].Height = 20;
                btn[i].Name = "b"+i.ToString();
                wrp.Children.Add(btn[i]);
                btn[i].Click += d1;
            }

            Debug.WriteLine("dddd");
            Debug.WriteLine(button1.Height);
            Debug.WriteLine(wrp.Height);
        } 

        private void displocation(object sender, RoutedEventArgs e)
        {
            string btnName =  ((Button)sender).Name;

            string sbtnNumber = btnName.Substring(1, btnName.Length-1);
            int ibtnNumber = int.Parse(sbtnNumber);

            Debug.WriteLine(arrstr[ibtnNumber]);
            Debug.WriteLine(((Button)sender).TranslatePoint(new Point(), cvs).ToString());
        }



        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            Debug.WriteLine("start query");
            MySqlConnection myconn = null;
            MySqlCommand mycom = null;
            //MySqlDataAdapter myrec = null;
            myconn = new MySqlConnection("Host =192.168.56.2;Database=MEPurchase;Username=root;Password=123456;Charset=utf8;");
            myconn.Open();
            mycom = myconn.CreateCommand();
 
 
 
                            string sql = string.Format(@"alter table purchaselist 
                                        add 物料申请单号_c varchar(255)   after 物料申请单号                          ,
                                        add 项目号_c varchar(255)         after 项目号                                ,
                                        add 申请人_c varchar(255)         after 申请人                                ,
                                        add 订货号_c varchar(255)         after 订货号                               ,
                                        add 名称_c varchar(255)          after 名称                  ,
                                        add 规格及要求_c varchar(255)     after 规格及要求                  ,
                                        add 数量_c varchar(255)          after 数量                  ,
                                        add 单位_c varchar(255)          after 单位                  ,
                                        add 币种_c varchar(255)          after 币种                  ,
                                        add 类型_c varchar(255)          after 类型                  ,
                                        add 单价_c varchar(255)          after 单价                  ,
                                        add 合计_c varchar(255)          after 合计                  ,
                                        add 总合计_c varchar(255)         after 总合计                  ,
                                        add 供应商_c varchar(255)        after 供应商  ,
                                        add 预计到货时间_c varchar(255)   after 预计到货时间                  ,
                                        add 实际到货时间_c varchar(255)   after 实际到货时间                  ,
                                        add 领料时间_c varchar(255)       after 领料时间                  ,
                                        add 领料人_c varchar(255)         after 领料人                  ,
                                        add 领料数量_c varchar(255)       after 领料数量                  ,
                                        add 下单时间_c varchar(255)       after 下单时间                  ,
                                        add 订单号_c varchar(255)         after 订单号                  ,
                                        add ME单号_c varchar(255)        after ME单号                  ,
                                        add 备注1_c varchar(255)         after 备注1                  ,
                                        add 申请单发起时间_c varchar(255) after 申请单发起时间               ,
                                        add 申请单签完时间_c varchar(255) after 申请单签完时间              ,
                                        add 项目需求时间_c varchar(255)   after 项目需求时间  
                            
                            ");
                //string   s = "insert into purchaselist \r\n(物料申请单号, 项目号, 申请人, 项目来源, 项目类型, 订货号, 名称, 规格及要求, 数量, 单位, 币种,类型,单价,合计,总合计,供应商,预计到货时间,实际到货时间,领料时间,领料人,领料数量,下单时间,订单号,ME单号,备注1,申请单发起时间,申请单签完时间,项目需求时间) values\r\n(2014121501,G14157,郭广兴,RBUP-DC,G,'',支持费,Update BDE with database function,10,H,EUR,德方服务费,63,630,630,GermanyPC50011602,20141230,20141230,20141230,郭广兴,10,20141219,602828,'',ME141215-01,'','','');";
                mycom.CommandText = sql;
                //mycom.CommandType = CommandType.Text;
                MySqlDataReader sdr;
                try {
                    sdr = mycom.ExecuteReader();

                    sdr.Close();
                }
                catch (Exception ee){
                    Debug.WriteLine(ee);
                    Debug.WriteLine(sql);


                }
               
            //  while (sdr.Read()) {
            // Debug.WriteLine(sdr[0].ToString() + sdr[1].ToString() + sdr[2].ToString());

            //  }
            myconn.Close();
            Debug.WriteLine("query finish");

 
        }
    }
}
