using System.Windows.Forms;

namespace FastColoredTextBoxNS
{
    public partial class frmIdentifierInfo : Form
    {
        public frmIdentifierInfo()
        {
            InitializeComponent();
        }

        private void frmIdentifierInfo_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Escape) //Close form with ESC
            {
                e.Handled = true;
                Close();
            }
        }
    }
}
