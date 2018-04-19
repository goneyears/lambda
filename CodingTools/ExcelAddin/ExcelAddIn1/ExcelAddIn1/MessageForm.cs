using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ExcelAddIn1
{
    public partial class MessageForm : Form
    {
        public MessageForm(string name)
        {
            InitializeComponent();
            MessageGrid.Width = this.Width - 10;
            MessageGrid.Height = this.Height - 20;
            this.Text = name;
        }

        public void ShowMessage(DataTable dt){

            SetDataGridViewAppearance(MessageGrid);
         
            MessageGrid.DataSource = dt;
 
        }

        private void SetDataGridViewAppearance(DataGridView dataGridView)
        {
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;

            dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells; 

        }

        private void MessageForm_Resize(object sender, EventArgs e)
        {
            MessageGrid.Width = this.Width-20;
            MessageGrid.Height = this.Height-50;
        }


    }
}
