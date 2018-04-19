namespace ExcelAddIn1
{
    partial class ETools : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public ETools()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Etooltab = this.Factory.CreateRibbonTab();
            this.group1 = this.Factory.CreateRibbonGroup();
            this.GetPriceBtn = this.Factory.CreateRibbonButton();
            this.FullPriceBtn = this.Factory.CreateRibbonButton();
            this.Etooltab.SuspendLayout();
            this.group1.SuspendLayout();
            // 
            // Etooltab
            // 
            this.Etooltab.Groups.Add(this.group1);
            this.Etooltab.Label = "Etools";
            this.Etooltab.Name = "Etooltab";
            // 
            // group1
            // 
            this.group1.Items.Add(this.GetPriceBtn);
            this.group1.Items.Add(this.FullPriceBtn);
            this.group1.Label = "Purchase";
            this.group1.Name = "group1";
            // 
            // GetPriceBtn
            // 
            this.GetPriceBtn.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.GetPriceBtn.Image = global::ExcelAddIn1.Properties.Resources._16b7324e82fa1c9d9c3003f220fbc22b;
            this.GetPriceBtn.Label = "GetPrice";
            this.GetPriceBtn.Name = "GetPriceBtn";
            this.GetPriceBtn.ScreenTip = "Show every single price in comment";
            this.GetPriceBtn.ShowImage = true;
            this.GetPriceBtn.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.button1_Click);
            // 
            // FullPriceBtn
            // 
            this.FullPriceBtn.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.FullPriceBtn.Image = global::ExcelAddIn1.Properties.Resources._6c99b5afda7c785b369d0ad2259f1313;
            this.FullPriceBtn.Label = "FullPrice";
            this.FullPriceBtn.Name = "FullPriceBtn";
            this.FullPriceBtn.ShowImage = true;
            this.FullPriceBtn.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.FullPriceBtn_Click);
            // 
            // ETools
            // 
            this.Name = "ETools";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.Etooltab);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.Ribbon1_Load);
            this.Etooltab.ResumeLayout(false);
            this.Etooltab.PerformLayout();
            this.group1.ResumeLayout(false);
            this.group1.PerformLayout();

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab Etooltab;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton GetPriceBtn;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton FullPriceBtn;
    }

    partial class ThisRibbonCollection
    {
        internal ETools Ribbon1
        {
            get { return this.GetRibbon<ETools>(); }
        }
    }
}
