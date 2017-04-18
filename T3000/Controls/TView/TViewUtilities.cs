namespace T3000
{
    using PRGReaderLibrary;
    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using Controls;

    public static class TViewUtilities
    {
        #region User input handles

        public static void EditEnum<T>(object sender, EventArgs e) where T
            : struct, IConvertible
        {
            try
            {
                if (!typeof(T).IsEnum)
                {
                    throw new ArgumentException("T must be an enumerated type");
                }

                var view = (TView)sender;
                var cell = view.CurrentCell;
                cell.Value = ((T)cell.Value).NextValue();

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        public static void EditBoolean(object sender, EventArgs e)
        {
            try
            {
                var view = (TView)sender;
                var cell = view.CurrentCell;
                cell.Value = !((bool)cell.Value);

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        public static void EditColor(object sender, EventArgs e)
        {
            try
            {
                var view = (TView)sender;
                var cell = view.CurrentCell;
                var dialog = new ColorDialog();
                dialog.Color = (Color)cell.Value;
                if (dialog.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                cell.Value = dialog.Color;

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        public static void EditValue(object sender, EventArgs e, params object[] arguments)
        {
            if (arguments.Length < 3)
            {
                throw new ArgumentException("Objects less than 3", nameof(arguments));
            }

            try
            {
                var unitsColumn = (DataGridViewColumn)arguments[0];
                var rangeColumn = (DataGridViewColumn)arguments[1];
                var customUnits = (CustomUnits)arguments[2];

                var view = (TView)sender;
                var row = view.CurrentRow;
                var cell = view.CurrentCell;
                try
                {
                    var value = GetVariableValue(row, cell.OwningColumn, unitsColumn, rangeColumn,
                        customUnits);
                    if (value.Unit.IsDigital())
                    {
                        cell.Value = value.GetInverted().ToString();
                    }
                    else
                    {
                        view.BeginEdit(false);
                    }
                }
                catch (Exception)
                {
                    view.BeginEdit(false);
                }

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        public static DataGridViewCell GetValueCellForUnit(string value, Unit unit)
        {
            var cell = unit.IsDigital()
                ? (DataGridViewCell)new DataGridViewButtonCell()
                : new DataGridViewTextBoxCell();
            cell.Value = value;

            return cell;
        }

        public static void EditUnitsColumn(object sender, EventArgs e, params object[] arguments)
        {
            if (arguments.Length < 5)
            {
                throw new ArgumentException("Objects less than 5", nameof(arguments));
            }

            try
            {
                var valueColumn = (DataGridViewColumn)arguments[0];
                var unitsColumn = (DataGridViewColumn)arguments[1];
                var rangeColumn = (DataGridViewColumn)arguments[2];
                var customUnits = (CustomUnits)arguments[3];
                var predicate = (Func<Unit, bool>)arguments[4];
                var rangeTextColumn = arguments.Length >= 6 ? (DataGridViewColumn)arguments[5] : null; //Optional

                var view = (TView)sender;
                var row = view.CurrentRow;
                var value = GetVariableValue(row, valueColumn, unitsColumn, rangeColumn, customUnits);
                var form = new Forms.SelectUnitsForm(value.Unit, value.CustomUnits, predicate);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                var newUnit = form.SelectedUnit;
                var newValue = value.ConvertValue(newUnit, form.CustomUnits);
                customUnits = form.CustomUnits;

                view.ChangeValidationArguments(
                    unitsColumn, valueColumn, unitsColumn, customUnits);
                view.ChangeValidationArguments(
                    unitsColumn, valueColumn, unitsColumn, customUnits);

                view.ChangeEditArguments(
                    unitsColumn, valueColumn, unitsColumn, rangeColumn,
                    customUnits, predicate, rangeTextColumn);

                row.SetValue(unitsColumn, newUnit);
                row.SetValue(valueColumn, newValue);
                
                if (rangeTextColumn != null)
                {
                    row.SetValue(rangeTextColumn, newUnit);
                }

                // If from analog to digital or from digital to analog
                if (value.Unit.IsDigital() != newUnit.IsDigital())
                {
                    row.SetCell(valueColumn, GetValueCellForUnit(newValue, newUnit));
                }

                view.ValidateRow(row);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

        #region Validation

        public static void SetCellErrorMessage(DataGridViewCell cell, bool isValidated, string message)
        {
            cell.ToolTipText = isValidated ? string.Empty : message;
            cell.ErrorText = cell.ToolTipText;
            cell.Style.BackColor = ColorConstants.GetValidationColor(isValidated);
        }

        public static bool ValidateValue(DataGridViewCell cell, object[] arguments)
        {
            try
            {
                if (arguments.Length < 3)
                {
                    throw new ArgumentException("Arguments less than 3", nameof(arguments));
                }

                var valueColumn = (DataGridViewColumn)arguments[0];
                var unitsColumn = (DataGridViewColumn)arguments[1];
                var customUnits = (CustomUnits)arguments[2];

                var isValidated = true;
                var message = string.Empty;
                try
                {
                    var row = cell.OwningRow;
                    new VariableValue(
                        row.GetValue<string>(valueColumn),
                        row.GetValue<Unit>(unitsColumn),
                        customUnits);
                }
                catch (Exception exception)
                {
                    message = exception.Message;
                    isValidated = false;
                }

                SetCellErrorMessage(cell, isValidated, message);

                return isValidated;
            }
            catch (Exception exception)
            {
                SetCellErrorMessage(cell, false, exception.Message);
                return false;
            }
        }

        public static bool ValidateString(DataGridViewCell cell, object[] arguments)
        {
            try
            {
                if (arguments.Length < 1)
                {
                    throw new ArgumentException("Arguments less 1", nameof(arguments));
                }

                var length = (int)arguments[0];
                var description = cell.Value == null ? "" : (string)cell.Value;
                var isValidated = description.Length <= length;
                var message = $"Description too long. Maximum is {length} symbols. " +
                              $"Current length: {description.Length}. " +
                              $"Please, delete {description.Length - length} symbols.";
                SetCellErrorMessage(cell, isValidated, message);

                return isValidated;
            }
            catch (Exception exception)
            {
                SetCellErrorMessage(cell, false, exception.Message);
                return false;
            }
        }

        public static bool ValidateInteger(DataGridViewCell cell, object[] arguments)
        {
            try
            {
                var isValidated = true;
                var message = string.Empty;

                if (cell.Value == null)
                {
                    message = $"Value is null. Please input valid value.";
                    isValidated = false;
                }
                else if (cell.Value.GetType() == typeof(string))
                {
                    try
                    {
                        int.Parse((string)cell.Value);
                    }
                    catch (Exception exception)
                    {
                        message = exception.Message;
                        isValidated = false;
                    }
                }
                else if (cell.Value.GetType() != typeof(int))
                {
                    message = $"Type is not int or string. Type: {cell.ValueType}";
                    isValidated = false;
                }

                SetCellErrorMessage(cell, isValidated, message);

                return isValidated;
            }
            catch (Exception exception)
            {
                SetCellErrorMessage(cell, false, exception.Message);
                return false;
            }
        }

        public static bool ValidateDouble(DataGridViewCell cell, object[] arguments)
        {
            try
            {
                var isValidated = true;
                var message = string.Empty;

                if (cell.Value == null)
                {
                    message = $"Value is null. Please input valid value.";
                    isValidated = false;
                }
                else if (cell.Value.GetType() == typeof(string))
                {
                    try
                    {
                        double.Parse((string)cell.Value);
                    }
                    catch (Exception exception)
                    {
                        message = exception.Message;
                        isValidated = false;
                    }
                }
                else if (cell.Value.GetType() != typeof(double))
                {
                    message = $"Type is not double or string. Type: {cell.ValueType}";
                    isValidated = false;
                }

                SetCellErrorMessage(cell, isValidated, message);

                return isValidated;
            }
            catch (Exception exception)
            {
                SetCellErrorMessage(cell, false, exception.Message);
                return false;
            }
        }

        #endregion

        #region Value changed handles

        public static void ChangeValue(object sender, DataGridViewCellEventArgs e, object[] arguments)
        {
            if (arguments.Length < 2)
            {
                throw new ArgumentException("Arguments less 2", nameof(arguments));
            }

            try
            {
                var view = (TView) sender;
                var row = view.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var column = (DataGridViewColumn) arguments[0];
                var value = arguments[1];

                row.SetValue(column, value);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        public static void ChangeEnabled(object sender, DataGridViewCellEventArgs e, object[] arguments)
        {
            if (arguments.Length < 2)
            {
                throw new ArgumentException("Arguments less 2", nameof(arguments));
            }

            try
            {
                var view = (TView)sender;
                var row = view.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var column = (DataGridViewColumn)arguments[0];
                var valueColumn = (DataGridViewColumn)arguments[1];

                var value = row.GetValue<int>(valueColumn);
                row.GetCell(column).Enable(value != 0);
            }
            catch (Exception) { }
        }

        public static void ChangeColor(object sender, DataGridViewCellEventArgs e, object[] arguments)
        {
            if (arguments.Length < 2)
            {
                throw new ArgumentException("Arguments less 2", nameof(arguments));
            }

            try
            {
                var view = (TView)sender;
                var row = view.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var colorOff = (Color)arguments[0];
                var colorOn = (Color)arguments[1];

                var cell = row.Cells[e.ColumnIndex];
                cell.Style.ForeColor = ((int)cell.Value == 0)
                    ? colorOff
                    : colorOn;
                cell.Style.SelectionForeColor = cell.Style.ForeColor;
            }
            catch (Exception) { }
        }

        public static void ValueColor(object sender, DataGridViewCellEventArgs e, object[] arguments)
        {
            try
            {
                var view = (TView)sender;
                var row = view.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var cell = row.Cells[e.ColumnIndex];
                var color = (Color)cell.Value;
                var isBrigtnesses = color.GetBrightness() < 0.5;
                var foreColor = isBrigtnesses ? Color.White : Color.Black;
                cell.Style.ForeColor = foreColor;
                cell.Style.SelectionForeColor = foreColor;
                cell.Style.BackColor = color;
                cell.Style.SelectionBackColor = color;
            }
            catch (Exception) { }
        }

        #endregion

        #region Other

        public static VariableValue GetVariableValue(DataGridViewRow row,
            DataGridViewColumn value,
            DataGridViewColumn units,
            DataGridViewColumn range,
            CustomUnits customUnits) =>
            new VariableValue(
                        row.GetValue<string>(value),
                        row.GetValue<Unit>(units),
                        customUnits,
                        row.GetValue<int>(range));

        #endregion
    }
}
