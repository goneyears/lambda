﻿namespace SQLAGV
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
            this.sysGridView = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.sysGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // sysGridView
            // 
            this.sysGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.sysGridView.Location = new System.Drawing.Point(21, 12);
            this.sysGridView.Name = "sysGridView";
            this.sysGridView.RowTemplate.Height = 23;
            this.sysGridView.Size = new System.Drawing.Size(53, 63);
            this.sysGridView.TabIndex = 0;
            this.sysGridView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.sysGridView_DataError);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(72, 251);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(89, 54);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(379, 268);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(82, 54);
            this.button2.TabIndex = 2;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(625, 408);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.sysGridView);
            this.Name = "Form1";
            this.Text = "AGV";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.sysGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView sysGridView;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;

    }
}

