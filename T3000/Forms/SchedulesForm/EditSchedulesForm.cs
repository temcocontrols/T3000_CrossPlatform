namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;

    public partial class EditSchedulesForm : Form
    {
        public EditSchedulesForm()
        {
            InitializeComponent();
        }


        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            try
            {
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
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
