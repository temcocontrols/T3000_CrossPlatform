namespace T3000
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public static class DataGridViewUtilities
    {
        public static bool RowIndexIsValid(int index, DataGridView view) =>
            index >= 0 && index < view.RowCount;


        public static void EditEnumColumn<T>(object sender, EventArgs e) where T
            : struct, IConvertible
        {
            try
            {
                if (!typeof(T).IsEnum)
                {
                    throw new ArgumentException("T must be an enumerated type");
                }

                var view = (DataGridView)sender;
                var cell = view.CurrentCell;
                cell.Value = EnumUtilities.NextValue((T)cell.Value);
                view.EndEdit();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #region Validation

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

        #endregion
    }
}
