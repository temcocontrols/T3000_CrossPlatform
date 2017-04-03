namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class VariablesForm : Form
    {
        public List<ValuedPoint> Points { get; set; }
        public List<CustomUnit> CustomUnits { get; private set; }

        public VariablesForm(List<ValuedPoint> points, List<CustomUnit> customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }
            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();
        }

        public static void CheckRow(DataGridViewRow row, List<CustomUnit> customUnits = null)
        {
            var cell = row.Cells["ValueColumn"];
            var isValidated = true;
            cell.ToolTipText = string.Empty;
            cell.ErrorText = string.Empty;
            try
            {
                var unitsCell = row.Cells["UnitsColumn"];
                var units = UnitsNamesConstants.UnitsFromName(
                    (string)unitsCell.Value, customUnits);
                new VariableVariant((string) cell.Value, units, customUnits);
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
            prgView.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                prgView.Rows.Add(new object[] {
                    i + 1, point.Description, point.AutoManual,
                    point.Value.ToString(), point.Value.Units.GetOffOnName(point.Value.CustomUnits), point.Label
                });
                CheckRow(prgView.Rows[prgView.RowCount - 1], CustomUnits);
                ++i;
            }

            base.Show();
        }

        private void Save(object sender, EventArgs e)
        {
            try
            {
                var i = 0;
                foreach (DataGridViewRow row in prgView.Rows)
                {
                    if (i >= Points.Count)
                    {
                        break;
                    }

                    var point = Points[i];
                    point.Description = (string)row.Cells["DescriptionColumn"].Value;
                    point.Label = (string)row.Cells["LabelColumn"].Value;
                    point.Value = new VariableVariant(
                        (string)row.Cells["ValueColumn"].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells["UnitsColumn"].Value, CustomUnits), 
                        CustomUnits);
                    point.AutoManual = (AutoManual)row.Cells["AutoManualColumn"].Value;
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
                    CheckRow(row, CustomUnits);
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
                        (string)row.Cells["UnitsColumn"].Value, CustomUnits);
                    var form = new SelectUnitsForm(currentUnits, CustomUnits);
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        var convertedValue = UnitsUtilities.ConvertValue(
                            (string)row.Cells["ValueColumn"].Value,
                            UnitsNamesConstants.UnitsFromName(
                                (string)row.Cells["UnitsColumn"].Value, CustomUnits),
                            form.SelectedUnits,
                            CustomUnits, form.CustomUnits);
                        CustomUnits = form.CustomUnits;
                        row.Cells["UnitsColumn"].Value = form.SelectedUnits.GetOffOnName(
                            CustomUnits);
                        row.Cells["ValueColumn"].Value = convertedValue;
                        prgView.EndEdit();
                        CheckRow(row, CustomUnits);
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

            CheckRow(prgView.Rows[e.RowIndex], CustomUnits);
        }
    }
}
