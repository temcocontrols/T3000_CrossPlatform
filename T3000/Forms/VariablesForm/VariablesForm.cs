using System.Drawing;

namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class VariablesForm : Form
    {
        public Prg Prg { get; private set; }

        public static IList<UnitsNameItem> GetOffOnNames(List<UnitsElement> customUnits = null)
        {
            var names = new List<UnitsNameItem>();
            foreach (Units units in Enum.GetValues(typeof(Units)))
            {
                names.Add(new UnitsNameItem(units, units.GetOffOnName(customUnits)));
            }

            return names;
        }

        public VariablesForm(Prg prg)
        {
            if (prg == null)
            {
                throw new ArgumentNullException(nameof(prg));
            }

            InitializeComponent();

            Prg = prg;

            AutoManualColumn.ValueType = typeof(AutoManual);
            AutoManualColumn.DataSource = Enum.GetValues(typeof(AutoManual));
        }

        public void CheckRow(int row)
        {
            var cell = prgView.Rows[row].Cells["ValueColumn"];
            var isValidated = true;
            cell.ToolTipText = string.Empty;
            cell.ErrorText = string.Empty;
            try
            {
                var unitsCell = prgView.Rows[row].Cells["UnitsColumn"];
                var units = UnitsNamesConstants.UnitsFromName((string)unitsCell.Value, Prg.Units);
                new VariableVariant((string) cell.Value, units, Prg.Units);
            }
            catch (Exception exception)
            {
                cell.ToolTipText = exception.Message;
                cell.ErrorText = exception.Message;
                isValidated = false;
            }

            cell.Style.BackColor = isValidated ? Color.LightGreen : Color.MistyRose;

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
                    variable.Value.ToString(), variable.Value.Units.GetOffOnName(variable.Value.CustomUnits), variable.Label
                });
                CheckRow(prgView.RowCount - 1);
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

                    var variable = prg.Variables[i];
                    variable.Description = (string)row.Cells["DescriptionColumn"].Value;
                    variable.Label = (string)row.Cells["LabelColumn"].Value;
                    variable.Value = new VariableVariant(
                        (string)row.Cells["ValueColumn"].Value,
                        UnitsNamesConstants.UnitsFromName((string)row.Cells["UnitsColumn"].Value, Prg.Units), prg.Units);
                    variable.AutoManual = (AutoManual)row.Cells["AutoManualColumn"].Value;
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
                    CheckRow(e.RowIndex);
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
                    //TODO: Add FromCustomUnits and ToCustomUnits in ConvertValue
                    var form = new SelectUnitsForm(Units.OffOn, Prg.Units);
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        var row = prgView.CurrentRow;
                        Prg.Units = form.CustomUnits;
                        var convertedValue = UnitsUtilities.ConvertValue(
                            (string) row.Cells["ValueColumn"].Value,
                            UnitsNamesConstants.UnitsFromName((string) row.Cells["UnitsColumn"].Value, Prg.Units),
                            form.SelectedUnits,
                            form.CustomUnits);
                        row.Cells["UnitsColumn"].Value = form.SelectedUnits.GetOffOnName(Prg.Units);
                        row.Cells["ValueColumn"].Value = convertedValue;
                        prgView.EndEdit();
                        CheckRow(e.RowIndex);
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
            CheckRow(e.RowIndex);
        }
    }
}
