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
using System.Diagnostics;

namespace testtcpip
{
    public partial class AGVControl : Form
    {
        public AGVControl()
        {
            InitializeComponent();
        }

        TCPConnector TcpConnectorCar1;
        TCPConnector TcpConnectorCar2;
        TCPConnector TcpConnectorEM;

        AGVStatus car1Status;
        AGVStatus car2Status;
        AGVStatus EMStatus;

        Thread loginThread;



        public void AGVLogin()
        {
            while (!car1Status.logIn)
            { 
                if (car1Status.requestLogin)
                {
                    TcpConnectorCar1.SendString("adept\r\n");
                    car1Status.logIn = true;
                    Car1LoginChk.Checked = true;
                }

                Thread.Sleep(200);
            }

            while (!car2Status.logIn)
            {
                if (car2Status.requestLogin)
                {
                    TcpConnectorCar2.SendString("adept\r\n");
                    car2Status.logIn = true;
                    Car2LoginChk.Checked = true;
                }

                Thread.Sleep(200);
            }

            while (!EMStatus.logIn)
            {
                if (EMStatus.requestLogin)
                {
                    TcpConnectorEM.SendString("adept\r\n");
                    EMStatus.logIn = true;
                   // EMLoginChk.Checked = true;
                }

                Thread.Sleep(200);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            Control.CheckForIllegalCrossThreadCalls = false;

            TcpConnectorCar1 = new TCPConnector("192.168.10.107", 7171);

            TcpConnectorCar2 = new TCPConnector("192.168.10.84", 7171);

            TcpConnectorEM = new TCPConnector("192.168.10.81", 7171);

            car1Status = new AGVStatus(true,"Car1");
            car2Status = new AGVStatus(true,"Car2");
            EMStatus = new AGVStatus(false, "EM");

            TcpConnectorCar1.MessageReceived += car1Status.Analyze;
            TcpConnectorCar1.MessageReceived += SetControlObjectStatus;
            TcpConnectorCar1.MessageReceived += DisplayInformation;

            TcpConnectorCar2.MessageReceived += car2Status.Analyze;
            TcpConnectorCar2.MessageReceived += SetControlObjectStatus;
            TcpConnectorCar2.MessageReceived += DisplayInformation;

            TcpConnectorEM.MessageReceived += EMStatus.Analyze;
            TcpConnectorEM.MessageReceived += DisplayInformation;

            loginThread = new Thread(new ThreadStart(AGVLogin));
            loginThread.Start(); 
        }

        public void SetControlObjectStatus(Object sender, TCPConnector.TCPEventArgs e)
        {
            CheckBox[] chbOut = new CheckBox[7] {new CheckBox(), O1, O2, O3, O4, O5, O6 };
            for (int i = 1; i <= 3; i++)
            {
                chbOut[i].Checked = car1Status.Output[i];
            }
            for (int i = 3; i <= 6; i++)
            {
                chbOut[i].Checked = car2Status.Output[i];
            }
            CheckBox[] chbIn = new CheckBox[3] { new CheckBox(), I1, I2};
            for (int i = 1; i <= 2; i++)
            {
                chbIn[i].Checked = car1Status.Input[i];
            }

            //Position Display
            if      (!car1Status.Output[3] && !car1Status.Output[2] &&  car1Status.Output[1]) Car1PosLbl.Text = "1";
            else if (!car1Status.Output[3] &&  car1Status.Output[2] && !car1Status.Output[1]) Car1PosLbl.Text = "2";
            else if (!car1Status.Output[3] &&  car1Status.Output[2] &&  car1Status.Output[1]) Car1PosLbl.Text = "3";
            else if ( car1Status.Output[3] && !car1Status.Output[2] && !car1Status.Output[1]) Car1PosLbl.Text = "4";
            else if ( car1Status.Output[3] &&  car1Status.Output[2] &&  car1Status.Output[1]) Car1PosLbl.Text = "5";
            else  Car1PosLbl.Text = "0";

            if      (!car1Status.Output[6] && !car1Status.Output[5] &&  car1Status.Output[4]) Car2PosLbl.Text = "1";
            else if (!car1Status.Output[6] &&  car1Status.Output[5] && !car1Status.Output[4]) Car2PosLbl.Text = "2";
            else if (!car1Status.Output[6] &&  car1Status.Output[5] &&  car1Status.Output[4]) Car2PosLbl.Text = "3";
            else if ( car1Status.Output[6] && !car1Status.Output[5] && !car1Status.Output[4]) Car2PosLbl.Text = "4";
            else if ( car1Status.Output[6] &&  car1Status.Output[5] &&  car1Status.Output[4]) Car2PosLbl.Text = "5";
            else Car2PosLbl.Text = "0";

        }

        public void DisplayInformation(Object sender, TCPConnector.TCPEventArgs e)
        {

            InformationOutTxt.Text = AGVStatus.InformationOutput;
            InformationOutTxt.Focus();
            InformationOutTxt.Select(InformationOutTxt.TextLength, 0);
            InformationOutTxt.ScrollToCaret();

        }
        public class AGVStatus
        {
            public bool[] Output = new bool[7] { false, false, false, false, false, false, false };
            public bool[] Input = new bool[3] { false, false, false };
            public bool requestLogin = false;
            public bool logIn = false;
            public static string InformationOutput="";
            public enum StatusType
            {
                Error=0,
                INPUT=1,
                OUTPUT=2
            }

            private bool _analyzeIO;
            private string _deviceType;
            public AGVStatus(bool analyzeIO,string deviceType)
            {
                _analyzeIO = analyzeIO;
                _deviceType = deviceType;
            }
            public void Analyze(Object sender, TCPConnector.TCPEventArgs e)
            {
                TCPConnector TCPConncector = (TCPConnector)sender;
                //Debug.WriteLine("----start----");
                string[] sLineArray = TCPConncector.receivedMessage.Split('\r','\n');
                InformationOutput=InformationOutput+"\r\n"+_deviceType + "--->\r\n" + TCPConncector.receivedMessage;
                Debug.WriteLine("\n\n"+_deviceType + "--->\n   " + TCPConncector.receivedMessage);
                foreach (string sLine in sLineArray)
                {
                    if (IsLoginRequest(sLine))
                    {
                        requestLogin = true;
                    }
                    string[] sArray = sLine.Split(' ');
                    if (_analyzeIO)
                    {
                        if (CheckStatusType(sArray) == StatusType.INPUT)
                        {
                            AnalyzeInputs(sArray);
                        }
                        else if (CheckStatusType(sArray) == StatusType.OUTPUT)
                        {
                            AnalyzeOutputs(sArray);
                        }
                    }
   
                }

             //   Debug.WriteLine("----end----");
            }

          
            public StatusType CheckStatusType(string[] inStrArray )
            {
                if (inStrArray[0]=="Input:")
                {
                    return StatusType.INPUT;
                }
                else if (inStrArray[0] == "Output:")
                {
                    return StatusType.OUTPUT;
                }
                else
                {
                    return StatusType.Error;
                }
            }

            public bool IsLoginRequest(string str)
            {
                return (str.ToLower() == "enter password:");
            }
            public void AnalyzeInputs(string[] StrArray)
            {
                if (StrArray[2].ToLower() == "off")
                {

                    if (StrArray[1].ToLower() == "input_1") { Debug.WriteLine("input 1 is off"); Input[1] = false; }
                    if (StrArray[1].ToLower() == "input_2") { Debug.WriteLine("input 2 is off"); Input[2] = false; } 
                }
                else if (StrArray[2].ToLower() == "on")
                {
                    if (StrArray[1].ToLower() == "input_1") { Debug.WriteLine("input 1 is on"); Input[1] = true; }
                    if (StrArray[1].ToLower() == "input_2") { Debug.WriteLine("input 2 is on"); Input[2] = true; }
                }
            }

            public void AnalyzeOutputs(string[] StrArray)
            {
                if (StrArray[2].ToLower() == "off")
                {
                    if (StrArray[1].ToLower() == "output_1") { Debug.WriteLine("output 1 is off"); Output[1] = false; }
                    if (StrArray[1].ToLower() == "output_2") { Debug.WriteLine("output 2 is off"); Output[2] = false; }
                    if (StrArray[1].ToLower() == "output_3") { Debug.WriteLine("output 3 is off"); Output[3] = false; }
                    if (StrArray[1].ToLower() == "output_4") { Debug.WriteLine("output 4 is off"); Output[4] = false; }
                    if (StrArray[1].ToLower() == "output_5") { Debug.WriteLine("output 5 is off"); Output[5] = false; }
                    if (StrArray[1].ToLower() == "output_6") { Debug.WriteLine("output 6 is off"); Output[6] = false; }
                }
                else if (StrArray[2].ToLower() == "on")
                {
                    if (StrArray[1].ToLower() == "output_1") { Debug.WriteLine("output 1 is on"); Output[1] = true; }
                    if (StrArray[1].ToLower() == "output_2") { Debug.WriteLine("output 2 is on"); Output[2] = true; }
                    if (StrArray[1].ToLower() == "output_3") { Debug.WriteLine("output 3 is on"); Output[3] = true; }
                    if (StrArray[1].ToLower() == "output_4") { Debug.WriteLine("output 4 is on"); Output[4] = true; }
                    if (StrArray[1].ToLower() == "output_5") { Debug.WriteLine("output 5 is on"); Output[5] = true; }
                    if (StrArray[1].ToLower() == "output_6") { Debug.WriteLine("output 6 is on"); Output[6] = true; }
                }
            }
        }
        private void RefreshIO_Click(object sender, EventArgs e)
        { 
            TcpConnectorCar1.SendString("inputquery input_1\r\n");
            TcpConnectorCar1.SendString("inputquery input_2\r\n");

            TcpConnectorCar1.SendString("outputquery output_1\r\n");
            TcpConnectorCar1.SendString("outputquery output_2\r\n");
            TcpConnectorCar1.SendString("outputquery output_3\r\n");

            TcpConnectorCar1.SendString("outputquery output_4\r\n");
            TcpConnectorCar1.SendString("outputquery output_5\r\n");
            TcpConnectorCar1.SendString("outputquery output_6\r\n");
   
        }





        private void Car1OutOffBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_1\r\n"); 
            TcpConnectorCar1.SendString("outputoff output_3\r\n"); 
            TcpConnectorCar1.SendString("outputoff output_2\r\n");

        }

        private void Car2OutOffBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_4\r\n");
            TcpConnectorCar1.SendString("outputoff output_6\r\n");
            TcpConnectorCar1.SendString("outputoff output_5\r\n");
        }




        private void Car1GoBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("Go\r\n");
        }

        private void Car2GoBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar2.SendString("Go\r\n");
        }




        private void Car1Set1Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_3\r\n"); 
            TcpConnectorCar1.SendString("outputoff output_2\r\n");
            TcpConnectorCar1.SendString("outputon  output_1\r\n");
        }

        private void Car1Set2Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_3\r\n");
            TcpConnectorCar1.SendString("outputon  output_2\r\n");
            TcpConnectorCar1.SendString("outputoff output_1\r\n");
        }

        private void Car1Set3Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_3\r\n");
            TcpConnectorCar1.SendString("outputon  output_2\r\n");
            TcpConnectorCar1.SendString("outputon  output_1\r\n");

        }

        private void Car1Set4Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputon  output_3\r\n");
            TcpConnectorCar1.SendString("outputoff output_2\r\n");
            TcpConnectorCar1.SendString("outputoff output_1\r\n");

        }

        private void Car1Set5Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputon  output_3\r\n");
            TcpConnectorCar1.SendString("outputon  output_2\r\n");
            TcpConnectorCar1.SendString("outputon  output_1\r\n");

        }


        //-------------------------------------------------



        private void Car2Set1Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_6\r\n");
            TcpConnectorCar1.SendString("outputoff output_5\r\n");
            TcpConnectorCar1.SendString("outputon  output_4\r\n");

        }

        private void Car2Set2Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_6\r\n");
            TcpConnectorCar1.SendString("outputon  output_5\r\n");
            TcpConnectorCar1.SendString("outputoff output_4\r\n");

        }

        private void Car2Set3Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputoff output_6\r\n");
            TcpConnectorCar1.SendString("outputon  output_5\r\n");
            TcpConnectorCar1.SendString("outputon  output_4\r\n");

        }

        private void Car2Set4Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputon  output_6\r\n");
            TcpConnectorCar1.SendString("outputoff output_5\r\n");
            TcpConnectorCar1.SendString("outputoff output_4\r\n");

        }

        private void Car2Set5Btn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("outputon  output_6\r\n");
            TcpConnectorCar1.SendString("outputon  output_5\r\n");
            TcpConnectorCar1.SendString("outputon  output_4\r\n");

        }

        private void QueryStatusBtn_Click(object sender, EventArgs e)
        {

            TcpConnectorEM.SendString("qsr\r\n");
            Thread.Sleep(800);
            TcpConnectorCar1.SendString("status\r\n");
            Thread.Sleep(800);
            TcpConnectorCar2.SendString("status\r\n");

        }

        private void TxtClearBtn_Click(object sender, EventArgs e)
        {
            AGVStatus.InformationOutput = "";
            InformationOutTxt.Text = AGVStatus.InformationOutput;

            SendCmdTxt.Text = "";
        }

        private void Car1SendBtn_Click(object sender, EventArgs e)
        {

            TcpConnectorCar1.SendString(SendCmdTxt.Text+"\r\n");
        }

        private void Car2SendBtn_Click(object sender, EventArgs e)
        {

            TcpConnectorCar2.SendString(SendCmdTxt.Text + "\r\n");
        }

        private void EMSendBtn_Click(object sender, EventArgs e)
        {

            TcpConnectorEM.SendString(SendCmdTxt.Text + "\r\n");
        }

        private void Car1DockBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("Dock\r\n");

        }

        private void Car1StopBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar1.SendString("Stop\r\n");

        }

        private void Car2DockBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar2.SendString("Dock\r\n");

        }
        private void Car2StopBtn_Click(object sender, EventArgs e)
        {
            TcpConnectorCar2.SendString("Stop\r\n");

        }


    }
}
