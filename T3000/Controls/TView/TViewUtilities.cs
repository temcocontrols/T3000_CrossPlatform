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

        public static void EditEnum<T>(object sender, EventArgs e, params object[] arguments) where T
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

        public static void EditBoolean(object sender, EventArgs e, params object[] arguments)
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

        public static void EditUnitsColumn(object sender, EventArgs e, params object[] arguments)
        {
            if (arguments.Length < 5)
            {
                throw new ArgumentException("Objects less than 5", nameof(arguments));
            }

            try
            {
                var valueColumnName = (string)arguments[0];
                var unitsColumnName = (string)arguments[1];
                var rangeColumnName = (string)arguments[2];
                var customUnits = (CustomUnits)arguments[3];
                var predicate = (Func<Unit, bool>)arguments[4];
                var rangeTextColumnName = arguments.Length >= 6 ? (string)arguments[5] : null; //Optional

                var view = (TView)sender;
                var row = view.CurrentRow;
                var value = GetVariableValue(row, valueColumnName, unitsColumnName, rangeColumnName, customUnits);
                var form = new Forms.SelectUnitsForm(value.Unit, value.CustomUnits, predicate);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                var newValue = value.ConvertValue(form.SelectedUnit, form.CustomUnits);
                customUnits = form.CustomUnits;

                view.ChangeValidationArguments(
                    unitsColumnName, valueColumnName, unitsColumnName, customUnits);
                view.ChangeValidationArguments(
                    unitsColumnName, valueColumnName, unitsColumnName, customUnits);

                view.ChangeEditArguments(
                    unitsColumnName, valueColumnName, unitsColumnName, rangeColumnName, 
                    customUnits, predicate, rangeTextColumnName);

                row.SetValue(unitsColumnName, form.SelectedUnit);
                row.SetValue(valueColumnName, newValue);
                row.SetValue(rangeColumnName, form.SelectedUnit);
                if (rangeTextColumnName != null)
                {
                    row.SetValue(rangeTextColumnName, form.SelectedUnit);
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
            if (arguments.Length < 3)
            {
                throw new ArgumentException("Objects less than 3", nameof(arguments));
            }

            var valueColumn = (string)arguments[0];
            var unitsColumn = (string)arguments[1];
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

        public static bool ValidateString(DataGridViewCell cell, object[] arguments)
        {
            if (arguments.Length < 1)
            {
                throw new ArgumentException("Object less 1", nameof(arguments));
            }

            var length = (int)arguments[0];
            var description = (string)cell.Value ?? "";
            var isValidated = description.Length <= length;
            var message = $"Description too long. Maximum is {length} symbols. " +
                               $"Current length: {description.Length}. " +
                               $"Please, delete {description.Length - length} symbols.";

            SetCellErrorMessage(cell, isValidated, message);

            return isValidated;
        }

        public static bool ValidateInteger(DataGridViewCell cell, object[] arguments)
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
                    int.Parse((string) cell.Value);
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

        public static bool ValidateDouble(DataGridViewCell cell, object[] arguments)
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
                var view = (TView)sender;
                var row = view.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var columnName = (string)arguments[0];
                var value = arguments[1];

                row.SetValue(columnName, value);
            }
            catch (Exception) { }
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

                var columnName = (string)arguments[0];
                var valueColumnName = (string)arguments[1];

                var value = row.GetValue<int>(valueColumnName);
                row.Cells[columnName].Enable(value != 0);
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

        #endregion

        #region Other

        public static VariableValue GetVariableValue(DataGridViewRow row,
            string valueName, string unitsName, string rangeName,
            CustomUnits customUnits) =>
            new VariableValue(
                        row.GetValue<string>(valueName),
                        row.GetValue<Unit>(unitsName),
                        customUnits,
                        row.GetValue<int>(rangeName));

        public static VariableValue GetVariableValue(DataGridViewRow row,
            DataGridViewColumn value,
            DataGridViewColumn units,
            DataGridViewColumn range,
            CustomUnits customUnits) =>
            GetVariableValue(row, value.Name, units.Name, range.Name, customUnits);

        #endregion
    }
}
