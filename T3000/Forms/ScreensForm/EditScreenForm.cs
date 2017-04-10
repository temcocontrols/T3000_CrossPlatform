namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.IO;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class EditScreenForm : Form
    {
        public EditScreenForm(string path = null)
        {
            InitializeComponent();

            if (path != null && File.Exists(path))
            {
                BackgroundImage = Image.FromFile(path);
            }

            for (var i = 0; i < 24; ++i)
            {
                var x = i % 2;
                var y = i / 2;
                var width = (Width - 10)/2;
                var height = (Height - 80) / 12;

                var button = new Button();
                button.FlatStyle = FlatStyle.Flat;
                button.FlatAppearance.BorderSize = 0;
                button.BackColor = Color.Transparent;
                button.Left = 5 + x * width;
                button.Top = 5 + y * height;
                button.Size = new Size(width, height);
                button.TextAlign = ContentAlignment.MiddleLeft;
                button.Text = $"{i}. ";

                Controls.Add(button);
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
