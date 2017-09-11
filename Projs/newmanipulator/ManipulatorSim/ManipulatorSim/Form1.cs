using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using S7PROSIMLib;
using System.Diagnostics;

namespace ManipulatorSim
{
    public partial class Form1 : Form
    {

        public S7ProSim ps = new S7ProSim();


        Notify worldnotify = new Notify();

        TemperatureForm tForm;
        //    ps=S7ProSim();

        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {
         // ps.StartPLCSim("C:\\Users\\Mach\\Dropbox\\Rainbow\\Personal\\Project\\Proj9\\plcsimfile\\plc1.plc");
            ps.Connect();
            ps.SetScanMode(ScanModeConstants.ContinuousScan);
            AREA = new Position(backlimitpic.Location.X,forwardlimitpic.Location.X,uplimitpic.Location.Y,downlimitpic.Location.Y );
            AREA1 = new Position(AREA.left-15,AREA.right+15, AREA.top-15, AREA.bottom+15);
            mainlevel.represent = level;
            workpiece.represent = workpiece1;
            beam.represent = beam1;
            vstick.represent = vstick1;

            worldnotify.grip += workpiece.attached;




        }
        private void setwrokpiece_Click(object sender, EventArgs e)
        {
            workpiece.BackOrigin();


        }
        #region functions
        Axis mainlevel = new Axis(54,75);
        Axis workpiece = new Axis(51,189);
        Axis beam = new Axis(46, 19);
        Axis vstick = new Axis(64, 49,27);
        r_trig rt1=new r_trig();
        Position AREA;
        Position AREA1;
        UserAction btns=new UserAction();


        bool griperror = false;

        public  object ReadPLCBit(char type,int B,int x)
            {
                object bOut=false;
                switch (type)
                {
                    case 'M':
                    case 'm':
                         ps.ReadFlagValue(B, x, PointDataTypeConstants.S7_Bit, ref bOut);
                    break;
                    case 'Q':
                    case 'q':
                         ps.ReadOutputPoint(B, x, PointDataTypeConstants.S7_Bit, ref bOut);
                    break;
                    default:
                    break;

                }

                return bOut;

            }
        public void WritePLCBit(char type,int B,int x,bool bSet)
        {
                  
                switch (type)
                {
                    case 'M':
                    case 'm':
                         ps.WriteFlagValue(B, x, bSet);
                    break;
                    case 'I':
                    case 'i':
                         ps.WriteInputPoint(B, x, bSet);
                    break;
                    default:
                    break;

                }

        }
        Move mov=new Move();
        public void ReadAllPLC()
        {
           
            mov.forward = ReadPLCBit('Q', 4, 3);
            mov.backward = ReadPLCBit('Q', 4, 4);
            mov.upward = ReadPLCBit('Q', 4, 2);
            mov.downward = ReadPLCBit('Q', 4, 0);
            mov.grip = ReadPLCBit('Q', 4, 1);

        }
        Limits lims=new Limits();
        Limits errlims = new Limits();
        public void WriteAllPLC()
        {
            WritePLCBit('I', 0, 3, lims.forward);
            WritePLCBit('I', 0, 4, lims.back);
            WritePLCBit('I', 0, 2, lims.up);
            WritePLCBit('I', 0, 1, lims.down);

            WritePLCBit('I', 1, 1, btns.forward);
            WritePLCBit('I', 0, 6, btns.back);
            WritePLCBit('I', 0, 5, btns.up);
            WritePLCBit('I', 1, 0, btns.down);

            WritePLCBit('I', 0, 7, btns.release);
            WritePLCBit('I', 1, 2, btns.grip);
            WritePLCBit('I', 2, 0, btns.manual);
            WritePLCBit('I', 2, 1, btns.home);
            WritePLCBit('I', 2, 2, btns.step);
            WritePLCBit('I', 2, 3, btns.single);
            WritePLCBit('I', 2, 4, btns.continuous);
            WritePLCBit('I', 2, 6, btns.start);
            WritePLCBit('I', 2, 7, btns.stop);


        }
        #endregion
 
   
 
        #region timer
        int itimecounter;

        //static bool needReconnect;
        private void RealCycle_Tick(object sender, EventArgs e)
        {
           
            Debug.WriteLine("ps state:" + ps.GetState());
            if (ps.GetState() == "ERROR")
            {
               // needReconnect = true;
                Connection_lbl.ForeColor = Color.Crimson;
                Connection_lbl.Text = "No Connection, Please Run PLCSIM.";
                ps.Connect();
                ps.SetScanMode(ScanModeConstants.ContinuousScan);
            }
            else if (ps.GetState() == "RUN_P")
            {
                Connection_lbl.ForeColor = Color.SeaGreen;
                Connection_lbl.Text = "Connection OK, Run_P Mode.";
            }
            else if (ps.GetState() == "RUN")
            {
                Connection_lbl.ForeColor = Color.SeaGreen;
                Connection_lbl.Text = "Connection OK, Run Mode.";
            }
            else if (ps.GetState() == "STOP")
            {
                Connection_lbl.ForeColor = Color.Goldenrod;
                Connection_lbl.Text = "Connection OK, Stop Mode";
            }
            else
            {
                Connection_lbl.Text = "PLC state check Error";
            }

             
            rt1.IN(lims.down);
#region IO Refresh

            ReadAllPLC();

            btns.manual = manualchk.Checked;
            btns.home = homechk.Checked;
            btns.step = stepchk.Checked;
            btns.single = singlechk.Checked;
            btns.continuous = continuouschk.Checked;
            WriteAllPLC();
#endregion

            //Motion
            #region Motion
            if (mov.forward.Equals(true) && !errlims.forward && !btns.emg) mainlevel.moveX(2);
            if (mov.backward.Equals(true) && !errlims.back && !btns.emg) mainlevel.moveX(-2);
            if (mov.upward.Equals(true)&& !errlims.up && !btns.emg) mainlevel.moveY(-1);
            if (mov.downward.Equals(true)&& !errlims.down && !btns.emg) mainlevel.moveY(1);
            #endregion

            #region World change
            //World Change
            #region limits
            //limit  up
            
            if (mainlevel.represent.Location.Y <= AREA.top)
            {
                lims.up = true;
                uplimitpic.Visible=true;

            }
            else
            {
                lims.up = false;
                uplimitpic.Visible=false;
            }
            errlims.up = (mainlevel.represent.Location.Y < AREA1.top) ? true : false;

                //limit down
            if (mainlevel.represent.Location.Y + mainlevel.represent.Height >= AREA.bottom)
            {
                lims.down = true;
                downlimitpic.Visible=true;

            }
            else
            {
                lims.down = false;
                downlimitpic.Visible = false;
            }
            errlims.down = (mainlevel.represent.Location.Y + mainlevel.represent.Height > AREA1.bottom) ? true : false;
                //limit back
            if (mainlevel.represent.Location.X <= AREA.left )
            {
                lims.back = true;
                backlimitpic.Visible=true;

            }
            else
            {
                lims.back = false;
                backlimitpic.Visible=false;
            }
            errlims.back = (mainlevel.represent.Location.X <= AREA1.left) ? true : false;
                //limit forward
            if (mainlevel.represent.Location.X + mainlevel.represent.Width > AREA.right)
            {
                lims.forward = true;
                forwardlimitpic.Visible=true;

            }
            else
            {
                lims.forward = false;
                forwardlimitpic.Visible=false;
            }
            errlims.forward = (mainlevel.represent.Location.X + mainlevel.represent.Width > AREA1.right) ? true : false;
            #endregion
            //alarms 
            #region alarms
            if (mov.grip.Equals(true) && rt1.Q && !workpiece.isAttached)
                griperror = true;
            else if (mov.grip.Equals(false) && !lims.down)
                griperror = false;


            if (!lims.down) itimecounter = 0;//防止有时还未延时就抓取的情况
            if (mov.grip.Equals(true))
            {
                mainlevel.represent.BackColor = SystemColors.HotTrack;
                if (lims.down)
                    itimecounter++;

                if (((itimecounter > 26) || workpiece.isAttached)&& mainlevel.nearby(workpiece)&& !griperror)
                {
                    worldnotify.EnGrip = mainlevel;
                   // workpiece.attached(mainlevel);
                }
            }
            else
            {
                mainlevel.represent.BackColor = SystemColors.ActiveCaption;
                workpiece.released(mainlevel);
                if (!lims.down) griperror = false;
            }

            #endregion
            //display
            #region display
            if (errlims.up)
                errortext1.Text = "Up Limit Error";
            if (errlims.down)
                errortext1.Text = "Down Limit Error";
            if (errlims.back)
                errortext1.Text = "Back Limit Error";
            if (errlims.forward)
                errortext1.Text = "Forward Limit Error";
            if (!errlims.up && !errlims.down && !errlims.back && !errlims.forward)
                errortext1.Text = "  ";

            if (griperror)
            {
                workpiece.released(mainlevel);
                errortext.Text = "Grip Error";
            }
            else
                errortext.Text = "  ";
            #endregion
            #region follower
            beam.followX(mainlevel);
            vstick.followX(mainlevel);
            vstick.extend(mainlevel);
            #endregion

        }
            
   
            #endregion

  
        #endregion

        #region workpiece free move
        private Point offset;
        private bool ismousedown;

        private void workpiece1_MouseDown(object sender, MouseEventArgs e)
        {
            //鼠标在框内坐标
        //    ismousedown = true;
            Point mouseLocation = new Point(Control.MousePosition.X - Location.X, Control.MousePosition.Y - 20 - Location.Y);

            offset = new Point(mouseLocation.X - workpiece1.Location.X,
                               mouseLocation.Y - workpiece1.Location.Y);

        }

        private void workpiece1_MouseMove(object sender, MouseEventArgs e)
        {
            if (ismousedown)
            {
                Point mouseLocation = new Point(Control.MousePosition.X - Location.X, Control.MousePosition.Y - 20 - Location.Y);
                workpiece1.Location = new Point(mouseLocation.X - offset.X, mouseLocation.Y - offset.Y);
            }

        }

        private void workpiece1_MouseUp(object sender, MouseEventArgs e)
        {
            ismousedown = false;
        }

        #endregion

        private void upbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.up = true;

        }

        private void upbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.up = false;
        }

        private void downbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.down = true;
        }

        private void downbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.down = false;
        }

        private void backbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.back = true;
        }

        private void backbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.back = false;

        }

        private void forwardbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.forward = true;
        }

        private void forwardbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.forward = false;
        }

        private void releasebtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.release = true;
        }

        private void releasebtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.release = false;

        }

        private void gripbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.grip = true;
        }

        private void gripbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.grip = false;
        }

        private void startbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.start = true;
        }

        private void startbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.start = false;
        }

        private void stopbtn_MouseDown(object sender, MouseEventArgs e)
        {
            btns.stop = true;
        }

        private void stopbtn_MouseUp(object sender, MouseEventArgs e)
        {
            btns.stop = false;
        }

        private void emgbtn_MouseClick(object sender, MouseEventArgs e)
        {
            btns.emg = !btns.emg;
            if (btns.emg)
            {
                DClight.FillColor = SystemColors.Control;
            }
            else
                DClight.FillColor = SystemColors.MenuHighlight;
        }

        private void Temperature_MenuItem_Click(object sender, EventArgs e)
        {
            tForm = new TemperatureForm();
            tForm.Owner = this;
            tForm.Show();
        }

 



 

    


   



    }
}
