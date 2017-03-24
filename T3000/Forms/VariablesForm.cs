namespace T3000
{
    using System;
    using System.Windows.Forms;
    using PRGReaderLibrary;
    using Utilities;

    public partial class VariablesForm : Form
    {
        private PRG Prg { get; set; }
        private string PrgPath { get; set; }
        private bool IsOpened => prgView.Enabled;

        public VariablesForm()
        {
            InitializeComponent();

            Units.ValueType = typeof(UnitsEnum);
            Units.DataSource = Enum.GetValues(typeof(UnitsEnum));
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
                    i, variable.Description, variable.Label, variable.IsManual, variable.Units
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
                variable.Units = (UnitsEnum)row.Cells["Units"].Value;
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

        private void prgView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            //Set IsManual to true, if user changed units
            if (e.ColumnIndex == prgView.Columns["Units"]?.Index &&
                e.RowIndex >= 0 && e.RowIndex < prgView.RowCount)
            {
                var row = prgView.Rows[e.RowIndex];
                row.Cells["IsManual"].Value = true;
            }
        }

        private void englishToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "en-EU");

        private void germanToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "de-DE");

        private void chineseToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "zh");
    }
}
