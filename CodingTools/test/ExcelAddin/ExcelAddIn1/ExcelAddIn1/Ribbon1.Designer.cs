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
            this.button1 = this.Factory.CreateRibbonButton();
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
            this.group1.Items.Add(this.button1);
            this.group1.Label = "Purchase";
            this.group1.Name = "group1";
            // 
            // button1
            // 
            this.button1.Label = "GetPrice";
            this.button1.Name = "button1";
            this.button1.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.button1_Click);
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
        internal Microsoft.Office.Tools.Ribbon.RibbonButton button1;
    }

    partial class ThisRibbonCollection
    {
        internal ETools Ribbon1
        {
            get { return this.GetRibbon<ETools>(); }
        }
    }
}
