namespace ParameterGenerate
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
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.FehlerUnicodePathBox = new System.Windows.Forms.TextBox();
            this.FehlerPathBox = new System.Windows.Forms.TextBox();
            this.FehlerUnicodeBtn = new System.Windows.Forms.Button();
            this.FehlerSelectBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(57, 26);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(83, 41);
            this.button1.TabIndex = 0;
            this.button1.Text = "READ";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(57, 94);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(83, 41);
            this.button2.TabIndex = 1;
            this.button2.Text = "GEN";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // FehlerUnicodePathBox
            // 
            this.FehlerUnicodePathBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.FehlerUnicodePathBox.Location = new System.Drawing.Point(57, 228);
            this.FehlerUnicodePathBox.Name = "FehlerUnicodePathBox";
            this.FehlerUnicodePathBox.Size = new System.Drawing.Size(127, 13);
            this.FehlerUnicodePathBox.TabIndex = 28;
            // 
            // FehlerPathBox
            // 
            this.FehlerPathBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.FehlerPathBox.Location = new System.Drawing.Point(57, 173);
            this.FehlerPathBox.Name = "FehlerPathBox";
            this.FehlerPathBox.Size = new System.Drawing.Size(127, 13);
            this.FehlerPathBox.TabIndex = 27;
            // 
            // FehlerUnicodeBtn
            // 
            this.FehlerUnicodeBtn.Location = new System.Drawing.Point(30, 223);
            this.FehlerUnicodeBtn.Name = "FehlerUnicodeBtn";
            this.FehlerUnicodeBtn.Size = new System.Drawing.Size(21, 23);
            this.FehlerUnicodeBtn.TabIndex = 26;
            this.FehlerUnicodeBtn.Text = "O";
            this.FehlerUnicodeBtn.UseVisualStyleBackColor = true;
            this.FehlerUnicodeBtn.Click += new System.EventHandler(this.FehlerUnicodeBtn_Click);
            // 
            // FehlerSelectBtn
            // 
            this.FehlerSelectBtn.Location = new System.Drawing.Point(30, 168);
            this.FehlerSelectBtn.Name = "FehlerSelectBtn";
            this.FehlerSelectBtn.Size = new System.Drawing.Size(21, 23);
            this.FehlerSelectBtn.TabIndex = 25;
            this.FehlerSelectBtn.Text = "I";
            this.FehlerSelectBtn.UseVisualStyleBackColor = true;
            this.FehlerSelectBtn.Click += new System.EventHandler(this.FehlerSelectBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(200, 276);
            this.Controls.Add(this.FehlerUnicodePathBox);
            this.Controls.Add(this.FehlerPathBox);
            this.Controls.Add(this.FehlerUnicodeBtn);
            this.Controls.Add(this.FehlerSelectBtn);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox FehlerUnicodePathBox;
        private System.Windows.Forms.TextBox FehlerPathBox;
        private System.Windows.Forms.Button FehlerUnicodeBtn;
        private System.Windows.Forms.Button FehlerSelectBtn;
    }
}

