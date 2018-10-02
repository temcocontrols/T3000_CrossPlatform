using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FastColoredTextBoxNS
{
    public partial class PropertiesGrid : Form
    {
        

        public PropertiesGrid()
        {
            InitializeComponent();
            
        }

        private void PropertiesGrid_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.F4) //Closes the form
            {
                if(ModifierKeys == Keys.None)
                {
                    e.Handled = true;
                    Close();
                }
                

            }
        }
    }
}
