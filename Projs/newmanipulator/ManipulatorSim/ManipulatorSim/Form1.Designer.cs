namespace ManipulatorSim
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.RealCycle = new System.Windows.Forms.Timer(this.components);
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.emgbtn = new System.Windows.Forms.Button();
            this.stopbtn = new System.Windows.Forms.Button();
            this.startbtn = new System.Windows.Forms.Button();
            this.gripbtn = new System.Windows.Forms.Button();
            this.releasebtn = new System.Windows.Forms.Button();
            this.downbtn = new System.Windows.Forms.Button();
            this.forwardbtn = new System.Windows.Forms.Button();
            this.backbtn = new System.Windows.Forms.Button();
            this.upbtn = new System.Windows.Forms.Button();
            this.stepchk = new System.Windows.Forms.RadioButton();
            this.continuouschk = new System.Windows.Forms.RadioButton();
            this.singlechk = new System.Windows.Forms.RadioButton();
            this.homechk = new System.Windows.Forms.RadioButton();
            this.manualchk = new System.Windows.Forms.RadioButton();
            this.shapeContainer2 = new Microsoft.VisualBasic.PowerPacks.ShapeContainer();
            this.DClight = new Microsoft.VisualBasic.PowerPacks.OvalShape();
            this.ovalShape1 = new Microsoft.VisualBasic.PowerPacks.OvalShape();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.vstick1 = new System.Windows.Forms.PictureBox();
            this.beam1 = new System.Windows.Forms.PictureBox();
            this.setwrokpiece = new System.Windows.Forms.Button();
            this.errortext1 = new System.Windows.Forms.Label();
            this.errortext = new System.Windows.Forms.Label();
            this.workpiece1 = new System.Windows.Forms.PictureBox();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.level = new System.Windows.Forms.PictureBox();
            this.shapeContainer1 = new Microsoft.VisualBasic.PowerPacks.ShapeContainer();
            this.lineShape5 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape4 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape3 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.upright2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.downleft2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.leftup = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape1 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.upleft2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.uplimitpic = new System.Windows.Forms.PictureBox();
            this.forwardlimitpic = new System.Windows.Forms.PictureBox();
            this.downlimitpic = new System.Windows.Forms.PictureBox();
            this.backlimitpic = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Others_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Temperature_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Connection_lbl = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.vstick1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.beam1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.workpiece1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.level)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.uplimitpic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.forwardlimitpic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.downlimitpic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.backlimitpic)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // RealCycle
            // 
            this.RealCycle.Enabled = true;
            this.RealCycle.Interval = 50;
            this.RealCycle.Tick += new System.EventHandler(this.RealCycle_Tick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.emgbtn);
            this.groupBox2.Controls.Add(this.stopbtn);
            this.groupBox2.Controls.Add(this.startbtn);
            this.groupBox2.Controls.Add(this.gripbtn);
            this.groupBox2.Controls.Add(this.releasebtn);
            this.groupBox2.Controls.Add(this.downbtn);
            this.groupBox2.Controls.Add(this.forwardbtn);
            this.groupBox2.Controls.Add(this.backbtn);
            this.groupBox2.Controls.Add(this.upbtn);
            this.groupBox2.Controls.Add(this.stepchk);
            this.groupBox2.Controls.Add(this.continuouschk);
            this.groupBox2.Controls.Add(this.singlechk);
            this.groupBox2.Controls.Add(this.homechk);
            this.groupBox2.Controls.Add(this.manualchk);
            this.groupBox2.Controls.Add(this.shapeContainer2);
            this.groupBox2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(394, 36);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(340, 296);
            this.groupBox2.TabIndex = 22;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "操作面板";
            // 
            // emgbtn
            // 
            this.emgbtn.Location = new System.Drawing.Point(274, 214);
            this.emgbtn.Name = "emgbtn";
            this.emgbtn.Size = new System.Drawing.Size(47, 24);
            this.emgbtn.TabIndex = 34;
            this.emgbtn.Text = "急停";
            this.emgbtn.UseVisualStyleBackColor = true;
            this.emgbtn.MouseClick += new System.Windows.Forms.MouseEventHandler(this.emgbtn_MouseClick);
            // 
            // stopbtn
            // 
            this.stopbtn.Location = new System.Drawing.Point(219, 250);
            this.stopbtn.Name = "stopbtn";
            this.stopbtn.Size = new System.Drawing.Size(47, 24);
            this.stopbtn.TabIndex = 32;
            this.stopbtn.Text = "停止";
            this.stopbtn.UseVisualStyleBackColor = true;
            this.stopbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.stopbtn_MouseDown);
            this.stopbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.stopbtn_MouseUp);
            // 
            // startbtn
            // 
            this.startbtn.Location = new System.Drawing.Point(219, 179);
            this.startbtn.Name = "startbtn";
            this.startbtn.Size = new System.Drawing.Size(47, 24);
            this.startbtn.TabIndex = 31;
            this.startbtn.Text = "起动";
            this.startbtn.UseVisualStyleBackColor = true;
            this.startbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.startbtn_MouseDown);
            this.startbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.startbtn_MouseUp);
            // 
            // gripbtn
            // 
            this.gripbtn.Location = new System.Drawing.Point(152, 250);
            this.gripbtn.Name = "gripbtn";
            this.gripbtn.Size = new System.Drawing.Size(47, 24);
            this.gripbtn.TabIndex = 30;
            this.gripbtn.Text = "夹紧";
            this.gripbtn.UseVisualStyleBackColor = true;
            this.gripbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.gripbtn_MouseDown);
            this.gripbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.gripbtn_MouseUp);
            // 
            // releasebtn
            // 
            this.releasebtn.Location = new System.Drawing.Point(152, 179);
            this.releasebtn.Name = "releasebtn";
            this.releasebtn.Size = new System.Drawing.Size(47, 24);
            this.releasebtn.TabIndex = 29;
            this.releasebtn.Text = "松开";
            this.releasebtn.UseVisualStyleBackColor = true;
            this.releasebtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.releasebtn_MouseDown);
            this.releasebtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.releasebtn_MouseUp);
            // 
            // downbtn
            // 
            this.downbtn.Location = new System.Drawing.Point(59, 250);
            this.downbtn.Name = "downbtn";
            this.downbtn.Size = new System.Drawing.Size(47, 24);
            this.downbtn.TabIndex = 28;
            this.downbtn.Text = "下降";
            this.downbtn.UseVisualStyleBackColor = true;
            this.downbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.downbtn_MouseDown);
            this.downbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.downbtn_MouseUp);
            // 
            // forwardbtn
            // 
            this.forwardbtn.Location = new System.Drawing.Point(99, 214);
            this.forwardbtn.Name = "forwardbtn";
            this.forwardbtn.Size = new System.Drawing.Size(47, 24);
            this.forwardbtn.TabIndex = 27;
            this.forwardbtn.Text = "右移";
            this.forwardbtn.UseVisualStyleBackColor = true;
            this.forwardbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.forwardbtn_MouseDown);
            this.forwardbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.forwardbtn_MouseUp);
            // 
            // backbtn
            // 
            this.backbtn.Location = new System.Drawing.Point(23, 214);
            this.backbtn.Name = "backbtn";
            this.backbtn.Size = new System.Drawing.Size(47, 24);
            this.backbtn.TabIndex = 26;
            this.backbtn.Text = "左移";
            this.backbtn.UseVisualStyleBackColor = true;
            this.backbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.backbtn_MouseDown);
            this.backbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.backbtn_MouseUp);
            // 
            // upbtn
            // 
            this.upbtn.Location = new System.Drawing.Point(59, 179);
            this.upbtn.Name = "upbtn";
            this.upbtn.Size = new System.Drawing.Size(47, 24);
            this.upbtn.TabIndex = 25;
            this.upbtn.Tag = "";
            this.upbtn.Text = "上升";
            this.upbtn.UseVisualStyleBackColor = true;
            this.upbtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.upbtn_MouseDown);
            this.upbtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.upbtn_MouseUp);
            // 
            // stepchk
            // 
            this.stepchk.AutoSize = true;
            this.stepchk.Location = new System.Drawing.Point(146, 24);
            this.stepchk.Name = "stepchk";
            this.stepchk.Size = new System.Drawing.Size(50, 21);
            this.stepchk.TabIndex = 23;
            this.stepchk.Text = "单步";
            this.stepchk.UseVisualStyleBackColor = true;
            // 
            // continuouschk
            // 
            this.continuouschk.AutoSize = true;
            this.continuouschk.Location = new System.Drawing.Point(218, 85);
            this.continuouschk.Name = "continuouschk";
            this.continuouschk.Size = new System.Drawing.Size(50, 21);
            this.continuouschk.TabIndex = 22;
            this.continuouschk.Text = "连续";
            this.continuouschk.UseVisualStyleBackColor = true;
            // 
            // singlechk
            // 
            this.singlechk.AutoSize = true;
            this.singlechk.Location = new System.Drawing.Point(199, 43);
            this.singlechk.Name = "singlechk";
            this.singlechk.Size = new System.Drawing.Size(62, 21);
            this.singlechk.TabIndex = 20;
            this.singlechk.Text = "单周期";
            this.singlechk.UseVisualStyleBackColor = true;
            // 
            // homechk
            // 
            this.homechk.AutoSize = true;
            this.homechk.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.homechk.Location = new System.Drawing.Point(61, 43);
            this.homechk.Name = "homechk";
            this.homechk.Size = new System.Drawing.Size(62, 21);
            this.homechk.TabIndex = 18;
            this.homechk.Text = "回原点";
            this.homechk.UseVisualStyleBackColor = true;
            // 
            // manualchk
            // 
            this.manualchk.AutoSize = true;
            this.manualchk.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.manualchk.Checked = true;
            this.manualchk.Location = new System.Drawing.Point(55, 85);
            this.manualchk.Name = "manualchk";
            this.manualchk.Size = new System.Drawing.Size(50, 21);
            this.manualchk.TabIndex = 19;
            this.manualchk.TabStop = true;
            this.manualchk.Text = "手动";
            this.manualchk.UseVisualStyleBackColor = true;
            // 
            // shapeContainer2
            // 
            this.shapeContainer2.Location = new System.Drawing.Point(3, 19);
            this.shapeContainer2.Margin = new System.Windows.Forms.Padding(0);
            this.shapeContainer2.Name = "shapeContainer2";
            this.shapeContainer2.Shapes.AddRange(new Microsoft.VisualBasic.PowerPacks.Shape[] {
            this.DClight,
            this.ovalShape1});
            this.shapeContainer2.Size = new System.Drawing.Size(334, 274);
            this.shapeContainer2.TabIndex = 24;
            this.shapeContainer2.TabStop = false;
            // 
            // DClight
            // 
            this.DClight.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.DClight.BorderColor = System.Drawing.SystemColors.ActiveCaption;
            this.DClight.FillColor = System.Drawing.SystemColors.MenuHighlight;
            this.DClight.FillGradientColor = System.Drawing.SystemColors.ActiveCaption;
            this.DClight.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.DClight.Location = new System.Drawing.Point(278, 5);
            this.DClight.Name = "DClight";
            this.DClight.Size = new System.Drawing.Size(25, 26);
            // 
            // ovalShape1
            // 
            this.ovalShape1.Location = new System.Drawing.Point(92, 15);
            this.ovalShape1.Name = "ovalShape1";
            this.ovalShape1.Size = new System.Drawing.Size(129, 125);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.vstick1);
            this.groupBox1.Controls.Add(this.beam1);
            this.groupBox1.Controls.Add(this.setwrokpiece);
            this.groupBox1.Controls.Add(this.errortext1);
            this.groupBox1.Controls.Add(this.errortext);
            this.groupBox1.Controls.Add(this.workpiece1);
            this.groupBox1.Controls.Add(this.pictureBox4);
            this.groupBox1.Controls.Add(this.level);
            this.groupBox1.Controls.Add(this.shapeContainer1);
            this.groupBox1.Controls.Add(this.uplimitpic);
            this.groupBox1.Controls.Add(this.forwardlimitpic);
            this.groupBox1.Controls.Add(this.downlimitpic);
            this.groupBox1.Controls.Add(this.backlimitpic);
            this.groupBox1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(12, 37);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(362, 295);
            this.groupBox1.TabIndex = 23;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设备";
            // 
            // vstick1
            // 
            this.vstick1.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.vstick1.Location = new System.Drawing.Point(64, 49);
            this.vstick1.Name = "vstick1";
            this.vstick1.Size = new System.Drawing.Size(10, 28);
            this.vstick1.TabIndex = 17;
            this.vstick1.TabStop = false;
            // 
            // beam1
            // 
            this.beam1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.beam1.Location = new System.Drawing.Point(46, 19);
            this.beam1.Name = "beam1";
            this.beam1.Size = new System.Drawing.Size(47, 30);
            this.beam1.TabIndex = 16;
            this.beam1.TabStop = false;
            // 
            // setwrokpiece
            // 
            this.setwrokpiece.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setwrokpiece.Location = new System.Drawing.Point(270, 251);
            this.setwrokpiece.Name = "setwrokpiece";
            this.setwrokpiece.Size = new System.Drawing.Size(81, 31);
            this.setwrokpiece.TabIndex = 15;
            this.setwrokpiece.Text = "Place Piece";
            this.setwrokpiece.UseVisualStyleBackColor = true;
            this.setwrokpiece.Click += new System.EventHandler(this.setwrokpiece_Click);
            // 
            // errortext1
            // 
            this.errortext1.AutoSize = true;
            this.errortext1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.errortext1.ForeColor = System.Drawing.Color.Maroon;
            this.errortext1.Location = new System.Drawing.Point(31, 240);
            this.errortext1.Name = "errortext1";
            this.errortext1.Size = new System.Drawing.Size(26, 17);
            this.errortext1.TabIndex = 14;
            this.errortext1.Text = "OK";
            // 
            // errortext
            // 
            this.errortext.AutoSize = true;
            this.errortext.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.errortext.ForeColor = System.Drawing.Color.Maroon;
            this.errortext.Location = new System.Drawing.Point(31, 265);
            this.errortext.Name = "errortext";
            this.errortext.Size = new System.Drawing.Size(26, 17);
            this.errortext.TabIndex = 13;
            this.errortext.Text = "OK";
            // 
            // workpiece1
            // 
            this.workpiece1.BackColor = System.Drawing.Color.OrangeRed;
            this.workpiece1.Location = new System.Drawing.Point(54, 189);
            this.workpiece1.Name = "workpiece1";
            this.workpiece1.Size = new System.Drawing.Size(30, 11);
            this.workpiece1.TabIndex = 11;
            this.workpiece1.TabStop = false;
            this.workpiece1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.workpiece1_MouseDown);
            this.workpiece1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.workpiece1_MouseMove);
            this.workpiece1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.workpiece1_MouseUp);
            // 
            // pictureBox4
            // 
            this.pictureBox4.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.pictureBox4.BackgroundImage = global::ManipulatorSim.Properties.Resources.dash1;
            this.pictureBox4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox4.InitialImage = global::ManipulatorSim.Properties.Resources.dash1;
            this.pictureBox4.Location = new System.Drawing.Point(23, 200);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(322, 24);
            this.pictureBox4.TabIndex = 10;
            this.pictureBox4.TabStop = false;
            // 
            // level
            // 
            this.level.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.level.Location = new System.Drawing.Point(54, 75);
            this.level.Name = "level";
            this.level.Size = new System.Drawing.Size(30, 21);
            this.level.TabIndex = 7;
            this.level.TabStop = false;
            // 
            // shapeContainer1
            // 
            this.shapeContainer1.Location = new System.Drawing.Point(3, 19);
            this.shapeContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.shapeContainer1.Name = "shapeContainer1";
            this.shapeContainer1.Shapes.AddRange(new Microsoft.VisualBasic.PowerPacks.Shape[] {
            this.lineShape5,
            this.lineShape4,
            this.lineShape3,
            this.lineShape2,
            this.upright2,
            this.downleft2,
            this.leftup,
            this.lineShape1,
            this.upleft2});
            this.shapeContainer1.Size = new System.Drawing.Size(356, 273);
            this.shapeContainer1.TabIndex = 18;
            this.shapeContainer1.TabStop = false;
            // 
            // lineShape5
            // 
            this.lineShape5.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.lineShape5.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.lineShape5.Name = "lineShape5";
            this.lineShape5.X1 = 309;
            this.lineShape5.X2 = 309;
            this.lineShape5.Y1 = 153;
            this.lineShape5.Y2 = 163;
            // 
            // lineShape4
            // 
            this.lineShape4.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.lineShape4.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.lineShape4.Name = "lineShape4";
            this.lineShape4.X1 = 50;
            this.lineShape4.X2 = 50;
            this.lineShape4.Y1 = 153;
            this.lineShape4.Y2 = 163;
            // 
            // lineShape3
            // 
            this.lineShape3.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.lineShape3.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.lineShape3.Name = "lineShape3";
            this.lineShape3.X1 = 298;
            this.lineShape3.X2 = 308;
            this.lineShape3.Y1 = 163;
            this.lineShape3.Y2 = 163;
            // 
            // lineShape2
            // 
            this.lineShape2.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.lineShape2.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.lineShape2.Name = "lineShape2";
            this.lineShape2.X1 = 298;
            this.lineShape2.X2 = 308;
            this.lineShape2.Y1 = 57;
            this.lineShape2.Y2 = 57;
            // 
            // upright2
            // 
            this.upright2.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.upright2.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.upright2.Name = "upright2";
            this.upright2.X1 = 309;
            this.upright2.X2 = 309;
            this.upright2.Y1 = 57;
            this.upright2.Y2 = 67;
            // 
            // downleft2
            // 
            this.downleft2.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.downleft2.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.downleft2.Name = "downleft2";
            this.downleft2.X1 = 50;
            this.downleft2.X2 = 60;
            this.downleft2.Y1 = 163;
            this.downleft2.Y2 = 163;
            // 
            // leftup
            // 
            this.leftup.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.leftup.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.leftup.Name = "leftup";
            this.leftup.X1 = 50;
            this.leftup.X2 = 60;
            this.leftup.Y1 = 57;
            this.leftup.Y2 = 57;
            // 
            // lineShape1
            // 
            this.lineShape1.BorderColor = System.Drawing.SystemColors.ScrollBar;
            this.lineShape1.BorderWidth = 10;
            this.lineShape1.Name = "lineShape1";
            this.lineShape1.X1 = 19;
            this.lineShape1.X2 = 340;
            this.lineShape1.Y1 = 17;
            this.lineShape1.Y2 = 17;
            // 
            // upleft2
            // 
            this.upleft2.BorderColor = System.Drawing.SystemColors.ButtonShadow;
            this.upleft2.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.upleft2.Name = "upleft2";
            this.upleft2.X1 = 50;
            this.upleft2.X2 = 50;
            this.upleft2.Y1 = 57;
            this.upleft2.Y2 = 67;
            // 
            // uplimitpic
            // 
            this.uplimitpic.BackColor = System.Drawing.Color.Red;
            this.uplimitpic.Location = new System.Drawing.Point(54, 74);
            this.uplimitpic.Name = "uplimitpic";
            this.uplimitpic.Size = new System.Drawing.Size(259, 1);
            this.uplimitpic.TabIndex = 25;
            this.uplimitpic.TabStop = false;
            // 
            // forwardlimitpic
            // 
            this.forwardlimitpic.BackColor = System.Drawing.Color.Red;
            this.forwardlimitpic.Location = new System.Drawing.Point(312, 74);
            this.forwardlimitpic.Name = "forwardlimitpic";
            this.forwardlimitpic.Size = new System.Drawing.Size(1, 107);
            this.forwardlimitpic.TabIndex = 27;
            this.forwardlimitpic.TabStop = false;
            // 
            // downlimitpic
            // 
            this.downlimitpic.BackColor = System.Drawing.Color.Red;
            this.downlimitpic.Location = new System.Drawing.Point(54, 180);
            this.downlimitpic.Name = "downlimitpic";
            this.downlimitpic.Size = new System.Drawing.Size(259, 1);
            this.downlimitpic.TabIndex = 24;
            this.downlimitpic.TabStop = false;
            // 
            // backlimitpic
            // 
            this.backlimitpic.BackColor = System.Drawing.Color.Red;
            this.backlimitpic.Location = new System.Drawing.Point(53, 74);
            this.backlimitpic.Name = "backlimitpic";
            this.backlimitpic.Size = new System.Drawing.Size(1, 107);
            this.backlimitpic.TabIndex = 26;
            this.backlimitpic.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Others_MenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(746, 25);
            this.menuStrip1.TabIndex = 24;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // Others_MenuItem
            // 
            this.Others_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Temperature_MenuItem});
            this.Others_MenuItem.Name = "Others_MenuItem";
            this.Others_MenuItem.Size = new System.Drawing.Size(68, 21);
            this.Others_MenuItem.Text = "其他应用";
            // 
            // Temperature_MenuItem
            // 
            this.Temperature_MenuItem.Name = "Temperature_MenuItem";
            this.Temperature_MenuItem.Size = new System.Drawing.Size(152, 22);
            this.Temperature_MenuItem.Text = "温度调节";
            this.Temperature_MenuItem.Click += new System.EventHandler(this.Temperature_MenuItem_Click);
            // 
            // Connection_lbl
            // 
            this.Connection_lbl.AutoSize = true;
            this.Connection_lbl.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Connection_lbl.ForeColor = System.Drawing.Color.SeaGreen;
            this.Connection_lbl.Location = new System.Drawing.Point(12, 335);
            this.Connection_lbl.Name = "Connection_lbl";
            this.Connection_lbl.Size = new System.Drawing.Size(73, 17);
            this.Connection_lbl.TabIndex = 28;
            this.Connection_lbl.Text = "Connection";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(746, 353);
            this.Controls.Add(this.Connection_lbl);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Manipulator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.vstick1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.beam1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.workpiece1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.level)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.uplimitpic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.forwardlimitpic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.downlimitpic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.backlimitpic)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer RealCycle;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton homechk;
        private System.Windows.Forms.RadioButton manualchk;
        private System.Windows.Forms.RadioButton stepchk;
        private System.Windows.Forms.RadioButton continuouschk;
        private System.Windows.Forms.RadioButton singlechk;
        private Microsoft.VisualBasic.PowerPacks.ShapeContainer shapeContainer2;
        private Microsoft.VisualBasic.PowerPacks.OvalShape ovalShape1;
        private System.Windows.Forms.Button releasebtn;
        private System.Windows.Forms.Button downbtn;
        private System.Windows.Forms.Button forwardbtn;
        private System.Windows.Forms.Button backbtn;
        private System.Windows.Forms.Button upbtn;
        private System.Windows.Forms.Button stopbtn;
        private System.Windows.Forms.Button startbtn;
        private System.Windows.Forms.Button gripbtn;
        private System.Windows.Forms.Button emgbtn;
        private Microsoft.VisualBasic.PowerPacks.OvalShape DClight;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.PictureBox vstick1;
        private System.Windows.Forms.PictureBox beam1;
        private System.Windows.Forms.Button setwrokpiece;
        private System.Windows.Forms.Label errortext1;
        private System.Windows.Forms.Label errortext;
        private System.Windows.Forms.PictureBox workpiece1;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.PictureBox level;
        private Microsoft.VisualBasic.PowerPacks.ShapeContainer shapeContainer1;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape1;
        private Microsoft.VisualBasic.PowerPacks.LineShape upright2;
        private Microsoft.VisualBasic.PowerPacks.LineShape downleft2;
        private Microsoft.VisualBasic.PowerPacks.LineShape leftup;
        private System.Windows.Forms.PictureBox downlimitpic;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape5;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape3;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape2;
        private System.Windows.Forms.PictureBox forwardlimitpic;
        private System.Windows.Forms.PictureBox backlimitpic;
        private System.Windows.Forms.PictureBox uplimitpic;
        private Microsoft.VisualBasic.PowerPacks.LineShape upleft2;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape4;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Others_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Temperature_MenuItem;
        private System.Windows.Forms.Label Connection_lbl;
    }
}

