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
        public List<CustomUnitPoint> CustomUnits { get; private set; }

        public VariablesForm(List<ValuedPoint> points, List<CustomUnitPoint> customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();

            //Show points
            prgView.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                prgView.Rows.Add(new object[] {
                    i + 1, point.Description, point.AutoManual,
                    point.Value.ToString(),
                    point.Value.Units.GetOffOnName(point.Value.CustomUnits),
                    point.Label
                });
                CheckRowValue(prgView.Rows[prgView.RowCount - 1], CustomUnits);
                ++i;
            }
        }

        #region Utilities

        public static bool RowIndexIsValid(int index, DataGridView view) =>
            index >= 0 && index < view.RowCount;

        public static void CheckRowValue(DataGridViewRow row, List<CustomUnitPoint> customUnits = null)
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

        #endregion

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e)
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
        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region Callbacks

        private void prgView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (!RowIndexIsValid(e.RowIndex, prgView))
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
                    CheckRowValue(row, CustomUnits);
                    row.Cells["AutoManualColumn"].Value = AutoManual.Manual;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void EditUnitsColumn(object sender, EventArgs e)
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
                    CheckRowValue(row, CustomUnits);
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void EditAutoManualColumn(object sender, EventArgs e)
        {
            try
            {
                var row = prgView.CurrentRow;
                var current = (AutoManual)row.Cells["AutoManualColumn"].Value;
                row.Cells["AutoManualColumn"].Value = EnumUtilities.NextValue(current);
                prgView.EndEdit();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private bool ButtonEdit(object sender, EventArgs e)
        {
            if (prgView.CurrentCell.ColumnIndex == UnitsColumn.Index)
            {
                EditUnitsColumn(sender, e);
                return true;
            }
            else if (prgView.CurrentCell.ColumnIndex == AutoManualColumn.Index)
            {
                EditAutoManualColumn(sender, e);
                return true;
            }

            return false;
        }


        private void prgView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (!(((DataGridView)sender).Columns[e.ColumnIndex] is DataGridViewButtonColumn) ||
                !RowIndexIsValid(e.RowIndex, prgView))
            {
                return;
            }

            ButtonEdit(sender, e);
        }

        private void prgView_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            if (!RowIndexIsValid(e.RowIndex, prgView))
            {
                return;
            }

            CheckRowValue(prgView.Rows[e.RowIndex], CustomUnits);
        }

        private void prgView_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    if (prgView.CurrentCell != null)
                    {
                        e.Handled = true;
                        if (!ButtonEdit(sender, e))
                        {
                            prgView.BeginEdit(true);
                        }
                    }
                    break;
            }
        }

        #endregion

    }
}
