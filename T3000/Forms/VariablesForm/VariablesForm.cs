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
        public List<DigitalCustomUnitsPoint> CustomUnits { get; private set; }

        public VariablesForm(List<ValuedPoint> points, List<DigitalCustomUnitsPoint> customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();

            //Show points
            view.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    i + 1,
                    point.Description,
                    point.AutoManual,
                    point.Value.ToString(),
                    point.Value.Units.GetOffOnName(point.Value.CustomUnits),
                    point.Label
                });
                CheckRowValue(view.Rows[view.RowCount - 1],
                    ValueColumn.Name, UnitsColumn.Name, CustomUnits);
                ++i;
            }
        }

        #region Utilities

        public static void CheckRowValue(DataGridViewRow row,
            string valueColumn, string unitsColumn,
            List<DigitalCustomUnitsPoint> customUnits = null)
        {
            var cell = row.Cells[valueColumn];
            var isValidated = true;
            cell.ToolTipText = string.Empty;
            cell.ErrorText = string.Empty;
            try
            {
                var unitsCell = row.Cells[unitsColumn];
                var units = UnitsNamesConstants.UnitsFromName(
                    (string)unitsCell.Value, customUnits);
                new VariableValue((string) cell.Value, units, customUnits);
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
            var row = view.CurrentRow;

            if (row == null)
            {
                return;
            }

            row.Cells[DescriptionColumn.Name].Value = string.Empty;
            row.Cells[LabelColumn.Name].Value = string.Empty;
            row.Cells[UnitsColumn.Name].Value = Units.Unused.GetOffOnName();
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
            row.Cells[ValueColumn.Name].Value = "0";
        }

        private void Save(object sender, EventArgs e)
        {
            try
            {
                var i = 0;
                foreach (DataGridViewRow row in view.Rows)
                {
                    if (i >= Points.Count)
                    {
                        break;
                    }

                    var point = Points[i];
                    point.Description = (string)row.Cells[DescriptionColumn.Name].Value;
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
                    point.Value = new VariableValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        CustomUnits);
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
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
                if (!FormUtilities.RowIndexIsValid(e.RowIndex, view))
                {
                    return;
                }

                var row = view.Rows[e.RowIndex];
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == UnitsColumn.Index)
                {
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
                }

                if (e.ColumnIndex == ValueColumn.Index)
                {
                    CheckRowValue(row, ValueColumn.Name, UnitsColumn.Name, CustomUnits);
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
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
                var row = view.CurrentRow;
                var currentUnits = UnitsNamesConstants.UnitsFromName(
                    (string)row.Cells[UnitsColumn.Name].Value, CustomUnits);
                var form = new SelectUnitsForm(currentUnits, CustomUnits);
                if (form.ShowDialog() == DialogResult.OK)
                {
                    var convertedValue = UnitsUtilities.ConvertValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        form.SelectedUnits,
                        CustomUnits, form.CustomUnits);
                    CustomUnits = form.CustomUnits;
                    row.Cells[UnitsColumn.Name].Value = form.SelectedUnits.GetOffOnName(
                        CustomUnits);
                    row.Cells[ValueColumn.Name].Value = convertedValue;
                    view.EndEdit();
                    CheckRowValue(row, ValueColumn.Name, UnitsColumn.Name, CustomUnits);
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
                var row = view.CurrentRow;
                var current = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
                row.Cells[AutoManualColumn.Name].Value = EnumUtilities.NextValue(current);
                view.EndEdit();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private bool ButtonEdit(object sender, EventArgs e)
        {
            if (view.CurrentCell.ColumnIndex == UnitsColumn.Index)
            {
                EditUnitsColumn(sender, e);
                return true;
            }
            else if (view.CurrentCell.ColumnIndex == AutoManualColumn.Index)
            {
                EditAutoManualColumn(sender, e);
                return true;
            }

            return false;
        }


        private void prgView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (!(((DataGridView)sender).Columns[e.ColumnIndex] is DataGridViewButtonColumn) ||
                !FormUtilities.RowIndexIsValid(e.RowIndex, view))
            {
                return;
            }

            ButtonEdit(sender, e);
        }

        private void prgView_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            if (!FormUtilities.RowIndexIsValid(e.RowIndex, view))
            {
                return;
            }

            CheckRowValue(view.Rows[e.RowIndex], ValueColumn.Name, UnitsColumn.Name, CustomUnits);
        }

        private void prgView_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    if (view.CurrentCell != null)
                    {
                        e.Handled = true;
                        if (!ButtonEdit(sender, e))
                        {
                            view.BeginEdit(true);
                        }
                    }
                    break;
            }
        }

        #endregion

    }
}
