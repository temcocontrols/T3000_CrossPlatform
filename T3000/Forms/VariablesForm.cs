namespace T3000
{
    using System;
    using System.Windows.Forms;
    using PRGReaderLibrary;
    using Utilities;
    using Properties;

    public partial class VariablesForm : Form
    {
        private Prg Prg { get; set; }
        private string PrgPath { get; set; }
        private bool IsOpened => prgView.Enabled;

        public VariablesForm()
        {
            InitializeComponent();

            Units.DataSource = UnitsNamesConstants.GetOffOnNames();
            Units.DisplayMember = "Text";
            Units.ValueMember = "Value";

            AutoManual.ValueType = typeof(AutoManual);
            AutoManual.DataSource = Enum.GetValues(typeof(AutoManual));

            statusLabel.Text = Resources.PleaseOpenFile;
        }

        private void LoadPrg(string path)
        {
            PrgPath = path;
            Prg = Prg.Load(path);

            prgView.Rows.Clear();
            Units.DataSource = UnitsNamesConstants.GetOffOnNames(Prg.Units);
            var i = 0;
            foreach (var variable in Prg.Variables)
            {
                prgView.Rows.Add(new object[] {
                    i + 1, variable.Description, variable.AutoManual, variable.Value.ToString(), variable.Value.Units, variable.Label
                });
                if (variable.AutoManual == PRGReaderLibrary.AutoManual.Automatic)
                {
                    //or set manual if editing
                    prgView.Rows[prgView.RowCount - 1].Cells["Value"].ReadOnly = true;
                }
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
                variable.Description = (string)row.Cells["Description"].Value;
                variable.Label = (string)row.Cells["Label"].Value;
                variable.Value = new VariableVariant((string)row.Cells["Value"].Value, (Units)row.Cells["Units"].Value, Prg.Units);
                variable.AutoManual = (AutoManual)row.Cells["AutoManual"].Value;
                ++i;
            }
            Prg.Save(path);
        }

        private void ShowException(Exception exception) =>
            MessageBox.Show(string.Format(Resources.Exception, exception.Message, exception.StackTrace), "Exception: ", MessageBoxButtons.OK, MessageBoxIcon.Error);

        private void openButton_Click(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = $"{Resources.PRGFiles} (*.prg)|*.prg|{Resources.AllFiles} (*.*)|*.*";
            dialog.Title = Resources.SelectPRGFile;
            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            try
            {
                var path = dialog.FileName;
                LoadPrg(path);
                statusLabel.Text = string.Format(Resources.CurrentFile, path);
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
                statusLabel.Text = Resources.FileIsNotOpen;
                return;
            } 

            try
            {
                var path = PrgPath;
                SavePrg(path);
                statusLabel.Text = string.Format(Resources.Saved, path);
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }

        private void prgView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == prgView.Columns["Units"]?.Index)
                {
                    var row = prgView.Rows[e.RowIndex];
                    row.Cells["AutoManual"].Value = PRGReaderLibrary.AutoManual.Manual;
                }
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }

        private void englishToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, string.Empty);

        private void germanToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "de-DE");

        private void chineseToolStripMenuItem_Click(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "zh-Hant");

        private void prgView_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (prgView.CurrentCell.ColumnIndex == prgView.Columns["Units"]?.Index &&
                prgView.CurrentCell.IsInEditMode)
            {
                var currentValue = (Units)prgView.CurrentCell.Value;
                switch (e.KeyCode)
                {
                    case Keys.Up:
                        prgView.CurrentCell.Value = currentValue + 1;
                        break;

                    case Keys.Down:
                        prgView.CurrentCell.Value = currentValue - 1;
                        break;
                }
            }
        }

        private void prgView_CellContextMenuStripChanged(object sender, DataGridViewCellEventArgs e)
        {
            //MessageBox.Show("prgView_CellContextMenuStripChanged");
        }

        private void prgView_CellStateChanged(object sender, DataGridViewCellStateChangedEventArgs e)
        {
            try
            {
                //Convert value when units changed
                if (e.Cell.ColumnIndex == prgView.Columns["Units"]?.Index)
                {
                    var row = prgView.Rows[e.Cell.RowIndex];
                    row.Cells["Value"].Value = UnitsUtilities.ConvertValue(
                        (string) row.Cells["Value"].Value,
                        (Units) row.Cells["Units"].Value,
                        (Units) row.Cells["Units"].Value);
                }
            }
            catch (Exception exception)
            {
                ShowException(exception);
            }
        }
    }
}
