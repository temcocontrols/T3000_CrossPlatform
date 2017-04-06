namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class VariablesForm : Form
    {
        public List<ValuedPoint> Points { get; set; }
        public List<CustomDigitalUnitsPoint> CustomUnits { get; private set; }

        public VariablesForm(List<ValuedPoint> points, List<CustomDigitalUnitsPoint> customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();
            view.ColumnHandles[AutoManualColumn.Name] = 
                DataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[UnitsColumn.Name] = EditUnitsColumn;

            //Show points
            view.Rows.Clear();

            //Fix for auto-filled column exception
            view.SuspendLayout();

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
                ++i;
            }

            //Fix for auto-filled column exception
            view.ResumeLayout();

            ValidateView();
        }

        #region Utilities

        public static void SetCellErrorMessage(DataGridViewCell cell, bool isValidated, string message)
        {
            cell.ToolTipText = isValidated ? string.Empty : message;
            cell.ErrorText = cell.ToolTipText;
            cell.Style.BackColor = ColorConstants.GetValidationColor(isValidated);
        }

        public static bool ValidateRowValue(DataGridViewRow row,
            string valueColumn, string unitsColumn,
            List<CustomDigitalUnitsPoint> customUnits = null)
        {
            var cell = row.Cells[valueColumn];
            var isValidated = true;
            var message = string.Empty;
            try
            {
                var unitsCell = row.Cells[unitsColumn];
                var units = UnitsNamesConstants.UnitsFromName(
                    (string)unitsCell.Value, customUnits);
                new VariableValue((string)cell.Value, units, customUnits);
            }
            catch (Exception exception)
            {
                message = exception.Message;
                isValidated = false;
            }

            SetCellErrorMessage(cell, isValidated, message);

            return isValidated;
        }

        public static bool ValidateRowColumnString(DataGridViewRow row, 
            string columnName, int length)
        {
            var cell = row.Cells[columnName];
            var description = (string)cell.Value;
            var isValidated = description.Length <= length;
            var message = $"Description too long. Maximum is {length} symbols. " +
                               $"Current length: {description.Length}. " +
                               $"Please, delete {description.Length - length} symbols.";

            SetCellErrorMessage(cell, isValidated, message);

            return isValidated;
        }

        public bool ValidateRow(DataGridViewRow row)
        {
            if (!ValidateRowValue(row, ValueColumn.Name,
                UnitsColumn.Name, CustomUnits))
            {
                return false;
            }

            if (!ValidateRowColumnString(row, DescriptionColumn.Name, 21))
            {
                return false;
            }

            if (!ValidateRowColumnString(row, LabelColumn.Name, 9))
            {
                return false;
            }

            return true;
        }

        public bool ValidateView()
        {
            foreach (DataGridViewRow row in view.Rows)
            {
                if (!ValidateRow(row))
                {
                    return false;
                }
            }

            return true;
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
            if (!ValidateView())
            {
                MessageBoxUtilities.ShowWarning(Resources.VariablesFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

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
            DialogResult = DialogResult.Cancel;
            Close();
        }

        #endregion

        #region Callbacks

        private void view_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (!DataGridViewUtilities.RowIndexIsValid(e.RowIndex, view))
                {
                    return;
                }

                var row = view.Rows[e.RowIndex];
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == UnitsColumn.Index)
                {
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
                }
                else if (e.ColumnIndex == ValueColumn.Index)
                {
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
                }
                ValidateRow(row);
            }
            catch (Exception) { }
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

                    ValidateRow(row);
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void view_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            if (!DataGridViewUtilities.RowIndexIsValid(e.RowIndex, view))
            {
                return;
            }

            try
            {
                ValidateRow(view.Rows[e.RowIndex]);
            }
            catch(Exception) { }
        }

        #endregion

    }
}
