namespace T3000
{
    using System;
    using System.Windows.Forms;
    using PRGReaderLibrary;

    public partial class VariablesForm : Form
    {
        private PRG prg { get; set; }

        public VariablesForm()
        {
            InitializeComponent();
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = ".PRG files (*.prg)|*.prg|All files (*.*)|*.*";
            dialog.Title = "Please select an .PRG file";
            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            try
            {
                var path = dialog.FileName;
                LoadPrg(path);
                ShowCurrentFile(path);
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }

        private void LoadPrg(string path)
        {
            prg = PRG.Load(path);
            for (var i = 0; i < prg.Vars.Count; ++i)
            {
                var variable = prg.Vars[i];
                prgView.Rows.Add(new object[]
                {
                    i, variable.Description, variable.Label, variable.IsManual
                });
            }
        }

        private void ShowException(Exception exception)
        {
            currentLabel.Text = "Exception:";
            currentFileLabel.Text = exception.Message;
        }

        private void ShowCurrentFile(string path)
        {
            currentLabel.Text = "Current:";
            currentFileLabel.Text = path;
        }
    }
}
