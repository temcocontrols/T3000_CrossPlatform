namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;

    public partial class InputsForm : Form
    {
        public Prg Prg { get; private set; }

        public InputsForm(Prg prg)
        {
            if (prg == null)
            {
                throw new ArgumentNullException(nameof(prg));
            }

            InitializeComponent();

            Prg = prg;
        }

        public new void Show()
        {
            var prg = Prg;

            prgView.Rows.Clear();
            var i = 0;
            foreach (var input in prg.Inputs)
            {
                prgView.Rows.Add(new object[] {
                    i + 1, input.Description, input.AutoManual,
                    input.Value.ToString(), input.Value.Units.GetOffOnName(input.Value.CustomUnits), input.Label
                });
                VariablesForm.CheckRow(prgView.Rows[prgView.RowCount - 1], prg);
                ++i;
            }

            base.Show();
        }

        private void Save(object sender, EventArgs e)
        {
            var prg = Prg;

            try
            {
                var i = 0;
                foreach (DataGridViewRow row in prgView.Rows)
                {
                    if (i >= prg.Variables.Count)
                    {
                        break;
                    }

                    var input = prg.Inputs[i];
                    input.Description = (string)row.Cells["DescriptionColumn"].Value;
                    input.Label = (string)row.Cells["LabelColumn"].Value;
                    input.Value = new VariableVariant(
                        (string)row.Cells["ValueColumn"].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells["UnitsColumn"].Value, 
                            Prg.CustomUnits), 
                        prg.CustomUnits);
                    input.AutoManual = (AutoManual)row.Cells["AutoManualColumn"].Value;
                    ++i;
                }
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

        private void prgView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (e.RowIndex >= prgView.RowCount ||
                    e.RowIndex < 0)
                {
                    return;
                }

                var row = prgView.Rows[e.RowIndex];
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == UnitsColumn.Index)
                {
                    row.Cells["AutoManualColumn"].Value = AutoManual.Manual;
                }

                if (e.ColumnIndex == ValueColumn.Index)
                {
                    VariablesForm.CheckRow(row, Prg);
                    row.Cells["AutoManualColumn"].Value = AutoManual.Manual;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        private void clearSelectedRowButton_Click(object sender, EventArgs e)
        {
            var row = prgView.CurrentRow;

            if (row == null)
            {
                return;
            }

            row.Cells["DescriptionColumn"].Value = string.Empty;
            row.Cells["LabelColumn"].Value = string.Empty;
            row.Cells["UnitsColumn"].Value = Units.Unused.GetOffOnName();
            row.Cells["AutoManualColumn"].Value = AutoManual.Automatic;
            row.Cells["ValueColumn"].Value = "0";
        }

        private void prgView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var senderGrid = (DataGridView)sender;

            //UnitsColumn button click
            if (senderGrid.Columns[e.ColumnIndex] is DataGridViewButtonColumn &&
                e.RowIndex >= 0 && e.RowIndex < prgView.RowCount &&
                prgView.CurrentCell.ColumnIndex == UnitsColumn.Index)
            {
                try
                {
                    var row = prgView.CurrentRow;
                    var currentUnits = UnitsNamesConstants.UnitsFromName(
                        (string)row.Cells["UnitsColumn"].Value, Prg.CustomUnits);
                    var form = new SelectUnitsForm(currentUnits, Prg.CustomUnits);
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        var convertedValue = UnitsUtilities.ConvertValue(
                            (string)row.Cells["ValueColumn"].Value,
                            UnitsNamesConstants.UnitsFromName(
                                (string)row.Cells["UnitsColumn"].Value, Prg.CustomUnits),
                            form.SelectedUnits,
                            Prg.CustomUnits,
                            form.CustomUnits
                            );
                        Prg.CustomUnits = form.CustomUnits;
                        row.Cells["UnitsColumn"].Value = form.SelectedUnits.GetOffOnName(
                            Prg.CustomUnits);
                        row.Cells["ValueColumn"].Value = convertedValue;
                        prgView.EndEdit();
                        VariablesForm.CheckRow(row, Prg);
                    }
                }
                catch (Exception exception)
                {
                    MessageBoxUtilities.ShowException(exception);
                }
            }

            //AutoManualColumn button click
            if (senderGrid.Columns[e.ColumnIndex] is DataGridViewButtonColumn &&
                e.RowIndex >= 0 && e.RowIndex < prgView.RowCount &&
                prgView.CurrentCell.ColumnIndex == AutoManualColumn.Index)
            {
                try
                {
                    var row = prgView.CurrentRow;
                    var current = (AutoManual)row.Cells["AutoManualColumn"].Value;
                    var form = new SelectAutoManualForm(current);
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        row.Cells["AutoManualColumn"].Value = form.Selected;
                        prgView.EndEdit();
                    }
                }
                catch (Exception exception)
                {
                    MessageBoxUtilities.ShowException(exception);
                }
            }
        }

        private void prgView_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            if (e.RowIndex < 0 ||
                e.RowIndex >= prgView.RowCount)
            {
                return;
            }

            VariablesForm.CheckRow(prgView.Rows[e.RowIndex], Prg);
        }
    }
}
