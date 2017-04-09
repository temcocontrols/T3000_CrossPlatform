namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class EditScreenForm : Form
    {
        public EditScreenForm(string path = null)
        {
            InitializeComponent();

            if (path != null)
            {
                imageLabel.Image = Image.FromFile(path);
            }
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
