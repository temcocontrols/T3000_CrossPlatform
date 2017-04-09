namespace T3000
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;
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
                cell.Value = EnumUtilities.NextValue((T)cell.Value);

                view.ValidateCell(cell);
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
                throw new ArgumentException("Object less 3", nameof(arguments));
            }

            var valueColumn = (string)arguments[0];
            var unitsColumn = (string)arguments[1];
            var customUnits = (List<CustomDigitalUnitsPoint>)arguments[2];
            var isValidated = true;
            var message = string.Empty;
            try
            {
                var row = cell.OwningRow;
                var unitsCell = row.Cells[unitsColumn];
                var valueCell = row.Cells[valueColumn];
                var units = UnitsNamesConstants.UnitsFromName(
                    (string)unitsCell.Value, customUnits);
                new VariableValue((string)valueCell.Value, units, customUnits);
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

        #endregion

        #region Value changed handles

        public static void Change(object sender, DataGridViewCellEventArgs e, object[] arguments)
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

        #endregion
    }
}
