namespace fehlertranslater
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
            this.translate_btn = new System.Windows.Forms.Button();
            this.filelines_label = new System.Windows.Forms.Label();
            this.fehlerlines_label = new System.Windows.Forms.Label();
            this.translines_label = new System.Windows.Forms.Label();
            this.untranslines_label = new System.Windows.Forms.Label();
            this.BasicDic_Update = new System.Windows.Forms.Button();
            this.NewDic_Update = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Simplify = new System.Windows.Forms.Button();
            this.FehlerSelectBtn = new System.Windows.Forms.Button();
            this.FehlerUnicodeBtn = new System.Windows.Forms.Button();
            this.FehlerPathBox = new System.Windows.Forms.TextBox();
            this.FehlerUnicodePathBox = new System.Windows.Forms.TextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.BasicDicGrid = new System.Windows.Forms.DataGridView();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.NewDicGrid = new System.Windows.Forms.DataGridView();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.UntransDicGrid = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BasicDicGrid)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NewDicGrid)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UntransDicGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // translate_btn
            // 
            this.translate_btn.Location = new System.Drawing.Point(27, 229);
            this.translate_btn.Name = "translate_btn";
            this.translate_btn.Size = new System.Drawing.Size(112, 36);
            this.translate_btn.TabIndex = 0;
            this.translate_btn.Text = "Translate";
            this.translate_btn.UseVisualStyleBackColor = true;
            this.translate_btn.Click += new System.EventHandler(this.translate_btn_Click);
            // 
            // filelines_label
            // 
            this.filelines_label.AutoSize = true;
            this.filelines_label.Location = new System.Drawing.Point(146, 81);
            this.filelines_label.Name = "filelines_label";
            this.filelines_label.Size = new System.Drawing.Size(13, 13);
            this.filelines_label.TabIndex = 1;
            this.filelines_label.Text = "0";
            // 
            // fehlerlines_label
            // 
            this.fehlerlines_label.AutoSize = true;
            this.fehlerlines_label.Location = new System.Drawing.Point(146, 113);
            this.fehlerlines_label.Name = "fehlerlines_label";
            this.fehlerlines_label.Size = new System.Drawing.Size(13, 13);
            this.fehlerlines_label.TabIndex = 2;
            this.fehlerlines_label.Text = "0";
            // 
            // translines_label
            // 
            this.translines_label.AutoSize = true;
            this.translines_label.Location = new System.Drawing.Point(146, 144);
            this.translines_label.Name = "translines_label";
            this.translines_label.Size = new System.Drawing.Size(13, 13);
            this.translines_label.TabIndex = 3;
            this.translines_label.Text = "0";
            // 
            // untranslines_label
            // 
            this.untranslines_label.AutoSize = true;
            this.untranslines_label.Location = new System.Drawing.Point(146, 176);
            this.untranslines_label.Name = "untranslines_label";
            this.untranslines_label.Size = new System.Drawing.Size(13, 13);
            this.untranslines_label.TabIndex = 4;
            this.untranslines_label.Text = "0";
            // 
            // BasicDic_Update
            // 
            this.BasicDic_Update.Location = new System.Drawing.Point(6, 372);
            this.BasicDic_Update.Name = "BasicDic_Update";
            this.BasicDic_Update.Size = new System.Drawing.Size(100, 36);
            this.BasicDic_Update.TabIndex = 9;
            this.BasicDic_Update.Text = "BasicUpdate";
            this.BasicDic_Update.UseVisualStyleBackColor = true;
            this.BasicDic_Update.Click += new System.EventHandler(this.BasicDic_Update_Click);
            // 
            // NewDic_Update
            // 
            this.NewDic_Update.Location = new System.Drawing.Point(6, 372);
            this.NewDic_Update.Name = "NewDic_Update";
            this.NewDic_Update.Size = new System.Drawing.Size(100, 36);
            this.NewDic_Update.TabIndex = 11;
            this.NewDic_Update.Text = "NewUpdate";
            this.NewDic_Update.UseVisualStyleBackColor = true;
            this.NewDic_Update.Click += new System.EventHandler(this.NewDic_Update_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 81);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "File Lines:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 113);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Fehler Lines:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 144);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(88, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "Translated Lines:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 176);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Untranslated Lines:";
            // 
            // Simplify
            // 
            this.Simplify.Location = new System.Drawing.Point(6, 373);
            this.Simplify.Name = "Simplify";
            this.Simplify.Size = new System.Drawing.Size(100, 35);
            this.Simplify.TabIndex = 18;
            this.Simplify.Text = "Simplify";
            this.Simplify.UseVisualStyleBackColor = true;
            this.Simplify.Click += new System.EventHandler(this.Simplify_Click);
            // 
            // FehlerSelectBtn
            // 
            this.FehlerSelectBtn.Location = new System.Drawing.Point(27, 364);
            this.FehlerSelectBtn.Name = "FehlerSelectBtn";
            this.FehlerSelectBtn.Size = new System.Drawing.Size(39, 36);
            this.FehlerSelectBtn.TabIndex = 19;
            this.FehlerSelectBtn.Text = "F";
            this.FehlerSelectBtn.UseVisualStyleBackColor = true;
            this.FehlerSelectBtn.Click += new System.EventHandler(this.FehlerPathSelect_Click_1);
            // 
            // FehlerUnicodeBtn
            // 
            this.FehlerUnicodeBtn.Location = new System.Drawing.Point(27, 419);
            this.FehlerUnicodeBtn.Name = "FehlerUnicodeBtn";
            this.FehlerUnicodeBtn.Size = new System.Drawing.Size(39, 36);
            this.FehlerUnicodeBtn.TabIndex = 21;
            this.FehlerUnicodeBtn.Text = "FU";
            this.FehlerUnicodeBtn.UseVisualStyleBackColor = true;
            this.FehlerUnicodeBtn.Click += new System.EventHandler(this.FehlerUnicodePathSelect_Click);
            // 
            // FehlerPathBox
            // 
            this.FehlerPathBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.FehlerPathBox.Location = new System.Drawing.Point(72, 374);
            this.FehlerPathBox.Name = "FehlerPathBox";
            this.FehlerPathBox.Size = new System.Drawing.Size(127, 13);
            this.FehlerPathBox.TabIndex = 23;
            // 
            // FehlerUnicodePathBox
            // 
            this.FehlerUnicodePathBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.FehlerUnicodePathBox.Location = new System.Drawing.Point(72, 429);
            this.FehlerUnicodePathBox.Name = "FehlerUnicodePathBox";
            this.FehlerUnicodePathBox.Size = new System.Drawing.Size(127, 13);
            this.FehlerUnicodePathBox.TabIndex = 24;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(259, 25);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(529, 447);
            this.tabControl1.TabIndex = 25;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.BasicDicGrid);
            this.tabPage1.Controls.Add(this.BasicDic_Update);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(521, 421);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "基础字典";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // BasicDicGrid
            // 
            this.BasicDicGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.BasicDicGrid.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.BasicDicGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.BasicDicGrid.Location = new System.Drawing.Point(-4, 0);
            this.BasicDicGrid.Name = "BasicDicGrid";
            this.BasicDicGrid.Size = new System.Drawing.Size(525, 353);
            this.BasicDicGrid.TabIndex = 0;
            this.BasicDicGrid.KeyDown += new System.Windows.Forms.KeyEventHandler(this.p_Data_KeyDown);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.NewDicGrid);
            this.tabPage2.Controls.Add(this.NewDic_Update);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(521, 421);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "新增字典";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // NewDicGrid
            // 
            this.NewDicGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.NewDicGrid.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.NewDicGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.NewDicGrid.Location = new System.Drawing.Point(0, 0);
            this.NewDicGrid.Name = "NewDicGrid";
            this.NewDicGrid.Size = new System.Drawing.Size(520, 353);
            this.NewDicGrid.TabIndex = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.UntransDicGrid);
            this.tabPage3.Controls.Add(this.Simplify);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(521, 421);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "未翻译词";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // UntransDicGrid
            // 
            this.UntransDicGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.UntransDicGrid.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.UntransDicGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.UntransDicGrid.Location = new System.Drawing.Point(0, 0);
            this.UntransDicGrid.Name = "UntransDicGrid";
            this.UntransDicGrid.Size = new System.Drawing.Size(524, 353);
            this.UntransDicGrid.TabIndex = 0;
            this.UntransDicGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.UntransDicGrid_CellContentClick);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(163, 292);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 36);
            this.button1.TabIndex = 26;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(848, 545);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.FehlerUnicodePathBox);
            this.Controls.Add(this.FehlerPathBox);
            this.Controls.Add(this.FehlerUnicodeBtn);
            this.Controls.Add(this.FehlerSelectBtn);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.untranslines_label);
            this.Controls.Add(this.translines_label);
            this.Controls.Add(this.fehlerlines_label);
            this.Controls.Add(this.filelines_label);
            this.Controls.Add(this.translate_btn);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.BasicDicGrid)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.NewDicGrid)).EndInit();
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.UntransDicGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button translate_btn;
        private System.Windows.Forms.Label filelines_label;
        private System.Windows.Forms.Label fehlerlines_label;
        private System.Windows.Forms.Label translines_label;
        private System.Windows.Forms.Label untranslines_label;
        private System.Windows.Forms.Button BasicDic_Update;
        private System.Windows.Forms.Button NewDic_Update;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button Simplify;
        private System.Windows.Forms.Button FehlerSelectBtn;
        private System.Windows.Forms.Button FehlerUnicodeBtn;
        private System.Windows.Forms.TextBox FehlerPathBox;
        private System.Windows.Forms.TextBox FehlerUnicodePathBox;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.DataGridView BasicDicGrid;
        private System.Windows.Forms.DataGridView NewDicGrid;
        private System.Windows.Forms.DataGridView UntransDicGrid;
        private System.Windows.Forms.Button button1;

    }
}

