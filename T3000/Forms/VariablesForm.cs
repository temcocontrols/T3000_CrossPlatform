namespace T3000
{
    using System;
    using System.Windows.Forms;
    using PRGReaderLibrary;

    public partial class VariablesForm : Form
    {
        private PRG Prg { get; set; }
        private string PrgPath { get; set; }
        private bool IsOpened => prgView.Enabled;

        public VariablesForm()
        {
            InitializeComponent();
        }

        private void LoadPrg(string path)
        {
            PrgPath = path;
            Prg = PRG.Load(path);

            prgView.Rows.Clear();
            var i = 0;
            foreach (var variable in Prg.Variables)
            {
                prgView.Rows.Add(new object[]
                {
                    i, variable.Description, variable.Label, variable.IsManual
                });
                ++i;
            }
        }

        private void SavePrg(string path)
        {
            var i = 0;
            foreach (DataGridViewRow row in prgView.Rows)
            {
                if (i >= Prg.Variables.Count)
                {
                    break;
                }

                var variable = Prg.Variables[i];
                variable.Description = row.Cells["Description"].ToString();
                variable.Label = row.Cells["Label"].ToString();
                variable.IsManual = (bool)row.Cells["IsManual"].Value;
                ++i;
            }
            Prg.Save(path);
        }

        private void ShowException(Exception exception) => 
            statusLabel.Text = $"Exception: {exception.Message}{exception.StackTrace}";

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
                statusLabel.Text = $"Current file: {path}";
                prgView.Enabled = true;
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            if (Prg == null || PrgPath == null)
            {
                statusLabel.Text = $"File isn't open";
                return;
            } 

            try
            {
                var path = PrgPath;
                SavePrg(path);
                statusLabel.Text = $"Saved: {path}";
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }
    }
}
