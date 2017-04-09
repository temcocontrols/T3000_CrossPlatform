namespace T3000.Controls
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    using ValidationFunc =
        System.Func<System.Windows.Forms.DataGridViewCell, object[], bool>;
    using CellAction =
        System.Action<object, System.Windows.Forms.DataGridViewCellEventArgs, object[]>;

    public class TView : DataGridView
    {
        public bool RowIndexIsValid(int index) =>
            index >= 0 && index < RowCount;

        public TView() : base()
        {
            CellValueChanged += OnCellValueChanged;
        }

        #region User input handles

        private Dictionary<string, EventHandler> ColumnHandles = new Dictionary<string, EventHandler>();

        private string ColumnIndexToName(int index) =>
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

        private Dictionary<string, ValidationFunc> ValidationHandles { get; set; } =
            new Dictionary<string, ValidationFunc>();
        private Dictionary<string, object[]> ValidationArguments { get; set; } =
            new Dictionary<string, object[]>();

        protected override void OnCellValidating(DataGridViewCellValidatingEventArgs e)
        {
            if (!RowIndexIsValid(e.RowIndex))
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

            if (!RowIndexIsValid(e.RowIndex))
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
                    ? ValidationArguments[name] : new object[0];

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

        #region Value changed handles

        private Dictionary<string, CellAction> ValueChangedHandles { get; set; } = 
            new Dictionary<string, CellAction>();
        private Dictionary<string, object[]> ValueChangedArguments { get; set; } =
            new Dictionary<string, object[]>();

        private void OnCellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                var row = this.GetRow(e.RowIndex);
                if (row == null)
                {
                    return;
                }

                var name = ColumnIndexToName(e.ColumnIndex);
                if (ValueChangedHandles.ContainsKey(name))
                {
                    var arguments = ValueChangedArguments.ContainsKey(name)
                        ? ValueChangedArguments[name] : new object[0];

                    ValueChangedHandles[name]?.Invoke(this, e, arguments);
                }

                ValidateRow(row);
            }
            catch (Exception) { }
        }

        public void AddChangedHandler(string columnName, CellAction handler, params object[] arguments)
        {
            ValueChangedHandles[columnName] = handler;
            ValueChangedArguments[columnName] = arguments;
        }

        public void AddChangedHandler(DataGridViewColumn column, CellAction handler, params object[] arguments) =>
            AddChangedHandler(column.Name, handler, arguments);

        public void SendChanged(DataGridViewColumn column)
        {
            foreach (DataGridViewRow row in column.DataGridView.Rows)
            {
                OnCellValueChanged(new DataGridViewCellEventArgs(column.Index, row.Index));
            }
        }

        #endregion
    }
}
