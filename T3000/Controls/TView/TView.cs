namespace T3000.Controls
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    using EditAction =
        System.Action<object, System.EventArgs, object[]>;
    using ValidationFunc =
        System.Func<System.Windows.Forms.DataGridViewCell, object[], bool>;
    using CellAction =
        System.Action<object, System.Windows.Forms.DataGridViewCellEventArgs, object[]>;
    using FormatingFunc =
        System.Func<object, object>;

    public class TView : DataGridView
    {
        public bool RowIndexIsValid(int index) =>
            index >= 0 && index < RowCount;

        public TView() : base()
        {
            CellValueChanged += OnCellValueChanged;
        }

        #region User input handles

        private Dictionary<string, EditAction> InputHandles = new Dictionary<string, EditAction>();
        private Dictionary<string, object[]> InputArguments { get; set; } =
            new Dictionary<string, object[]>();

        private string ColumnIndexToName(int index) =>
            Columns[index].Name;

        protected override void OnKeyDown(KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    var cell = CurrentCell;
                    if (cell != null && !cell.ReadOnly)
                    {
                        e.Handled = true;

                        var name = ColumnIndexToName(cell.ColumnIndex);
                        if (InputHandles.ContainsKey(name))
                        {
                            var arguments = InputArguments.ContainsKey(name)
                                ? InputArguments[name] : new object[0];

                            InputHandles[name]?.Invoke(this, e, arguments);
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
            if (!cell.ReadOnly && InputHandles.ContainsKey(name))
            {
                var arguments = InputArguments.ContainsKey(name)
                    ? InputArguments[name] : new object[0];

                InputHandles[name]?.Invoke(this, e, arguments);
                return;
            }

            base.OnCellContentClick(e);
        }

        public void AddEditHandler(string columnName, EditAction handler, params object[] arguments)
        {
            InputHandles[columnName] = handler;
            InputArguments[columnName] = arguments;
        }

        public void AddEditHandler(DataGridViewColumn column, 
            EditAction handler, params object[] arguments) =>
            AddEditHandler(column.Name, handler, arguments);

        public void ChangeEditHandler(string columnName, EditAction handler) =>
            InputHandles[columnName] = handler;

        public void ChangeEditHandler(DataGridViewColumn column, EditAction handler) =>
            ChangeEditHandler(column.Name, handler);

        public void ChangeEditArguments(string columnName, params object[] arguments) =>
            InputArguments[columnName] = arguments;

        public void ChangeEditArguments(DataGridViewColumn column, params object[] arguments) =>
            ChangeEditArguments(column.Name, arguments);

        #endregion

        #region Validation handles

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

        public void AddValidation(string columnName, ValidationFunc func, params object[] arguments)
        {
            ValidationHandles[columnName] = func;
            ValidationArguments[columnName] = arguments;
        }

        public void AddValidation(DataGridViewColumn column, ValidationFunc func, params object[] arguments) =>
            AddValidation(column.Name, func, arguments);

        public void ChangeValidationFunc(string columnName, ValidationFunc func) =>
            ValidationHandles[columnName] = func;

        public void ChangeValidationFunc(DataGridViewColumn column, ValidationFunc func) =>
            ChangeValidationFunc(column.Name, func);

        public void ChangeValidationArguments(string columnName, params object[] arguments) =>
            ValidationArguments[columnName] = arguments;

        public void ChangeValidationArguments(DataGridViewColumn column, params object[] arguments) =>
            ChangeValidationArguments(column.Name, arguments);

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

        #region Formatting handles

        private Dictionary<string, FormatingFunc> FormattingHandles { get; set; } =
            new Dictionary<string, FormatingFunc>();

        protected override void OnCellFormatting(DataGridViewCellFormattingEventArgs e)
        {
            if (!RowIndexIsValid(e.RowIndex))
            {
                return;
            }

            try
            {
                var cell = Rows[e.RowIndex].Cells[e.ColumnIndex];

                var name = ColumnIndexToName(e.ColumnIndex);
                if (FormattingHandles.ContainsKey(name))
                {
                    e.Value = FormattingHandles[name].Invoke(cell.Value);
                    e.FormattingApplied = true;
                    return;
                }

                ValidateCell(cell);
            }
            catch (Exception) { }

            base.OnCellFormatting(e);
        }

        public void AddFormating(DataGridViewColumn column, FormatingFunc func)
        {
            FormattingHandles[column.Name] = func;
        }

        #endregion

    }
}
