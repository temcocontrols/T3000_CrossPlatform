namespace T3000
{
    using System;
    using System.Windows.Forms;
    using PRGReaderLibrary;

    public partial class VariablesForm : Form
    {
        public Prg Prg { get; private set; }

        public VariablesForm(Prg prg)
        {
            if (prg == null)
            {
                throw new ArgumentNullException(nameof(prg));
            }

            InitializeComponent();

            Prg = prg;

            UnitsColumn.DataSource = UnitsNamesConstants.GetOffOnNames(prg.Units);
            UnitsColumn.DisplayMember = "Text";
            UnitsColumn.ValueMember = "Value";

            AutoManualColumn.ValueType = typeof(AutoManual);
            AutoManualColumn.DataSource = Enum.GetValues(typeof(AutoManual));
        }

        public new void Show()
        {
            var prg = Prg;

            prgView.Rows.Clear();
            var i = 0;
            foreach (var variable in prg.Variables)
            {
                prgView.Rows.Add(new object[] {
                    i + 1, variable.Description, variable.AutoManual,
                    variable.Value.ToString(), variable.Value.Units, variable.Label
                });
                //or set manual if editing
                prgView.Rows[prgView.RowCount - 1].Cells["ValueColumn"].ReadOnly = 
                    variable.AutoManual == AutoManual.Automatic;
                ++i;
            }

            base.Show();
        }

        private void Save(object sender, EventArgs e)
        {
            var prg = Prg;

            var i = 0;
            foreach (DataGridViewRow row in prgView.Rows)
            {
                if (i >= prg.Variables.Count)
                {
                    break;
                }

                var variable = prg.Variables[i];
                variable.Description = (string)row.Cells["DescriptionColumn"].Value;
                variable.Label = (string)row.Cells["LabelColumn"].Value;
                variable.Value = new VariableVariant(
                    (string)row.Cells["ValueColumn"].Value, 
                    (Units)row.Cells["UnitsColumn"].Value, prg.Units);
                variable.AutoManual = (AutoManual)row.Cells["AutoManualColumn"].Value;
                ++i;
            }

            Close();
        }

        private void prgView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == prgView.Columns["UnitsColumn"]?.Index)
                {
                    var row = prgView.Rows[e.RowIndex];
                    row.Cells["AutoManualColumn"].Value = AutoManual.Manual;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void prgView_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (prgView.CurrentCell.ColumnIndex == prgView.Columns["UnitsColumn"]?.Index &&
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
                if (e.Cell.ColumnIndex == prgView.Columns["UnitsColumn"]?.Index)
                {
                    var row = prgView.Rows[e.Cell.RowIndex];
                    row.Cells["ValueColumn"].Value = UnitsUtilities.ConvertValue(
                        (string) row.Cells["ValueColumn"].Value,
                        (Units) row.Cells["UnitsColumn"].Value,
                        (Units) row.Cells["UnitsColumn"].Value);
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }
    }
}
