namespace T3000.Forms
{
    using System;
    using System.Windows.Forms;

    public partial class ProgramEditorForm : Form
    {
        public string Code { get; set; }

        public ProgramEditorForm(string code)
        {
            InitializeComponent();

            Code = code;

            editTextBox.Grammar = new T3000Grammar();
            editTextBox.Text = Code;
        }


        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            try
            {
                Code = editTextBox.Text;
            }
            catch (Exception)// exception)
            {
                //MessageBoxUtilities.ShowException(exception);
                DialogResult = DialogResult.None;
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        #endregion
    }
}
