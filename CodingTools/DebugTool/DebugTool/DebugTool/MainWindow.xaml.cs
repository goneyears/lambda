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
using OPCLib;
using VariablesLib;
using System.Diagnostics;
using System.Text.RegularExpressions;
namespace DebugTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            //OPCInitial();
        }
        
        OPCClient oc = new OPCClient();
        private void OPCInitial()
        {
            List<string> ls = new List<string>();
            ls = oc.GetLocalServer();
            oc.ConnectServer(ls[0], "");
            oc.AddAllItems();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {

            //oc.WriteItem("axc3050.opc_rejectparts_quant", "23");
            //foreach (string n in oc.OPCItemNames) {
            //    Debug.WriteLine("keys");
            //    Debug.WriteLine(n);
            //}
            

            Debug.WriteLine(oc.OPCItemNames.Count);

            Output ot = new Output("AXC3050.OPC_M_Change_Shift", oc);
            ot.SetValue(true);
            Input it = new Input("AXC3050.OPC_M_Change_Shift", oc);
            Debug.Write(it.GetValue().ToString());




            //object o = new object();
            //o = oc.ReadItem("AXC3050.OPC_RejectParts_Quant");
            
            //Debug.WriteLine(o.GetType());

             
        } 

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            string s = "AXC3050.OUT_x+2-Y1/4";
            string r = Variable.Recognize(s);
            Debug.WriteLine(r);
        }

        private void GenerateBtn_Click(object sender, RoutedEventArgs e)
        {
            string str = "1232dd234";
            Match match = Regex.Match(str, @"[0-9]+[a-z]+([0-9]+)");
            Match match1 = Regex.Match(str, @"^[a-z]+$");
            Debug.WriteLine(match.Success);
            Debug.WriteLine(match1.Success);
            Debug.WriteLine(match.Groups[1].Value);
        }

        private void TestCylinderBtn_Click(object sender, RoutedEventArgs e)
        {
            
        }
    }
}
