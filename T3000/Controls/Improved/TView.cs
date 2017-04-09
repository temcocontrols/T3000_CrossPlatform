namespace T3000.Controls.Improved
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    using ValidationFunc =
        System.Func<System.Windows.Forms.DataGridViewCell, object[], bool>;

    public class TView : DataGridView
    {
        #region User input handles

        protected Dictionary<string, EventHandler> ColumnHandles = new Dictionary<string, EventHandler>();

        protected string ColumnIndexToName(int index) =>
            Columns[index].Name;

        protected override void OnKeyDown(KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    var cell = CurrentCell;
                    if (cell != null)
                    {
                        e.Handled = true;

                        var name = ColumnIndexToName(cell.ColumnIndex);
                        if (ColumnHandles.ContainsKey(name))
                        {
                            ColumnHandles[name]?.Invoke(this, e);
                            return;
                        }

                        BeginEdit(true);
                        return;
                    }
                    break;
            }

            base.OnKeyDown(e);
        }

        protected override void OnCellContentClick(DataGridViewCellEventArgs e)
        {
            var cell = CurrentCell;
            var name = ColumnIndexToName(cell.ColumnIndex);
            if (ColumnHandles.ContainsKey(name))
            {
                ColumnHandles[name]?.Invoke(this, e);
                return;
            }

            base.OnCellContentClick(e);
        }

        public void AddEditHandler(DataGridViewColumn column, EventHandler handler)
        {
            ColumnHandles[column.Name] = handler;
        }

        #endregion

        #region Validation

        protected Dictionary<string, ValidationFunc> ValidationHandles { get; set; } =
            new Dictionary<string, ValidationFunc>();
        protected Dictionary<string, object[]> ValidationArguments { get; set; } =
            new Dictionary<string, object[]>();

        protected override void OnCellValidating(DataGridViewCellValidatingEventArgs e)
        {
            if (!TViewUtilities.RowIndexIsValid(e.RowIndex, this))
            {
                return;
            }

            try
            {
                var cell = Rows[e.RowIndex].Cells[e.ColumnIndex];
                ValidateCell(cell);
            }
            catch (Exception) { }

            base.OnCellValidating(e);
        }

        protected override void OnCellValueChanged(DataGridViewCellEventArgs e)
        {
            base.OnCellValueChanged(e);

            if (!TViewUtilities.RowIndexIsValid(e.RowIndex, this))
            {
                return;
            }

            var cell = Rows[e.RowIndex].Cells[e.ColumnIndex];
            ValidateCell(cell);
        }

        public bool ValidateCell(DataGridViewCell cell)
        {
            var name = ColumnIndexToName(cell.ColumnIndex);
            if (ValidationHandles.ContainsKey(name))
            {
                var arguments = ValidationArguments.ContainsKey(name)
                    ? ValidationArguments[name] : null;

                return ValidationHandles[name]?.Invoke(cell, arguments) ?? true;
            }

            return true;
        }

        public bool ValidateRow(DataGridViewRow row)
        {
            var isValidated = true;
            foreach (DataGridViewCell cell in row.Cells)
            {
                isValidated &= ValidateCell(cell);
            }

            return isValidated;
        }

        public bool Validate()
        {
            var isValidated = true;
            foreach (DataGridViewRow row in Rows)
            {
                isValidated &= ValidateRow(row);
            }

            return isValidated;
        }

        public void AddValidation(DataGridViewColumn column, ValidationFunc func, params object[] arguments)
        {
            ValidationHandles[column.Name] = func;
            ValidationArguments[column.Name] = arguments;
        }

        public void ChangeValidationFunc(DataGridViewColumn column, ValidationFunc func)
        {
            ValidationHandles[column.Name] = func;
        }

        public void ChangeValidationArguments(DataGridViewColumn column, params object[] arguments)
        {
            ValidationArguments[column.Name] = arguments;
        }

        #endregion

    }
}
