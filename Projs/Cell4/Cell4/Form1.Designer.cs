﻿namespace Cell4
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
            this.ResetBtn = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.MessageTextBox = new System.Windows.Forms.TextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.AutoRollChk = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.ForceFreeChk = new System.Windows.Forms.RadioButton();
            this.ForceNGChk = new System.Windows.Forms.RadioButton();
            this.ForceGoodChk = new System.Windows.Forms.RadioButton();
            this.sysGridView = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.sysGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // ResetBtn
            // 
            this.ResetBtn.Location = new System.Drawing.Point(444, 269);
            this.ResetBtn.Name = "ResetBtn";
            this.ResetBtn.Size = new System.Drawing.Size(106, 58);
            this.ResetBtn.TabIndex = 0;
            this.ResetBtn.Text = "复位";
            this.ResetBtn.UseVisualStyleBackColor = true;
            this.ResetBtn.Click += new System.EventHandler(this.ResetBtn_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(601, 37);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(106, 53);
            this.button3.TabIndex = 3;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // MessageTextBox
            // 
            this.MessageTextBox.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MessageTextBox.Location = new System.Drawing.Point(24, 22);
            this.MessageTextBox.Multiline = true;
            this.MessageTextBox.Name = "MessageTextBox";
            this.MessageTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.MessageTextBox.Size = new System.Drawing.Size(470, 322);
            this.MessageTextBox.TabIndex = 4;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(31, 15);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(564, 376);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.AutoRollChk);
            this.tabPage1.Controls.Add(this.MessageTextBox);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(556, 350);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "状态信息";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // AutoRollChk
            // 
            this.AutoRollChk.AutoSize = true;
            this.AutoRollChk.Checked = true;
            this.AutoRollChk.CheckState = System.Windows.Forms.CheckState.Checked;
            this.AutoRollChk.Location = new System.Drawing.Point(500, 328);
            this.AutoRollChk.Name = "AutoRollChk";
            this.AutoRollChk.Size = new System.Drawing.Size(48, 16);
            this.AutoRollChk.TabIndex = 5;
            this.AutoRollChk.Text = "滚动";
            this.AutoRollChk.UseVisualStyleBackColor = true;
            this.AutoRollChk.CheckedChanged += new System.EventHandler(this.AutoRollChk_CheckedChanged);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.ForceFreeChk);
            this.tabPage2.Controls.Add(this.ForceNGChk);
            this.tabPage2.Controls.Add(this.ForceGoodChk);
            this.tabPage2.Controls.Add(this.ResetBtn);
            this.tabPage2.Controls.Add(this.sysGridView);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(556, 350);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "状态数据";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // ForceFreeChk
            // 
            this.ForceFreeChk.AutoSize = true;
            this.ForceFreeChk.Checked = true;
            this.ForceFreeChk.Location = new System.Drawing.Point(460, 128);
            this.ForceFreeChk.Name = "ForceFreeChk";
            this.ForceFreeChk.Size = new System.Drawing.Size(83, 16);
            this.ForceFreeChk.TabIndex = 3;
            this.ForceFreeChk.TabStop = true;
            this.ForceFreeChk.Text = "Free Force";
            this.ForceFreeChk.UseVisualStyleBackColor = true;
            this.ForceFreeChk.Click += new System.EventHandler(this.ForceFreeChk_Click);
            // 
            // ForceNGChk
            // 
            this.ForceNGChk.AutoSize = true;
            this.ForceNGChk.Location = new System.Drawing.Point(460, 211);
            this.ForceNGChk.Name = "ForceNGChk";
            this.ForceNGChk.Size = new System.Drawing.Size(71, 16);
            this.ForceNGChk.TabIndex = 2;
            this.ForceNGChk.Text = "Force NG";
            this.ForceNGChk.UseVisualStyleBackColor = true;
            this.ForceNGChk.Click += new System.EventHandler(this.ForceNGChk_Click);
            // 
            // ForceGoodChk
            // 
            this.ForceGoodChk.AutoSize = true;
            this.ForceGoodChk.Location = new System.Drawing.Point(460, 172);
            this.ForceGoodChk.Name = "ForceGoodChk";
            this.ForceGoodChk.Size = new System.Drawing.Size(83, 16);
            this.ForceGoodChk.TabIndex = 1;
            this.ForceGoodChk.Text = "Force Good";
            this.ForceGoodChk.UseVisualStyleBackColor = true;
            this.ForceGoodChk.Click += new System.EventHandler(this.ForceGoodChk_Click);
            // 
            // sysGridView
            // 
            this.sysGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.sysGridView.Location = new System.Drawing.Point(24, 27);
            this.sysGridView.Name = "sysGridView";
            this.sysGridView.RowTemplate.Height = 23;
            this.sysGridView.Size = new System.Drawing.Size(414, 300);
            this.sysGridView.TabIndex = 0;
            this.sysGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.sysGridView_DataError);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(601, 96);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(106, 53);
            this.button1.TabIndex = 6;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(735, 403);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.button3);
            this.Name = "Form1";
            this.Text = "U盘组装测试";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.sysGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ResetBtn;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.DataGridView sysGridView;
        private System.Windows.Forms.Button button1;
        public System.Windows.Forms.TextBox MessageTextBox;
        private System.Windows.Forms.CheckBox AutoRollChk;
        private System.Windows.Forms.RadioButton ForceFreeChk;
        private System.Windows.Forms.RadioButton ForceNGChk;
        private System.Windows.Forms.RadioButton ForceGoodChk;

    }
}

