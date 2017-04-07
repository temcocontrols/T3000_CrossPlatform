namespace T3000.Controls.Improved
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    using ValidationFunc =
        System.Func<System.Windows.Forms.DataGridViewCell, object, object, object, bool>;
    using ValidationArguments =
        System.Tuple<object, object, object>;

    public class TDataGridView : DataGridView
    {
        #region User input handles

        public Dictionary<string, EventHandler> ColumnHandles = new Dictionary<string, EventHandler>();

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

        #endregion

        #region Validation

        public Dictionary<string, ValidationFunc> ValidationHandles { get; set; } =
            new Dictionary<string, ValidationFunc>();
        public Dictionary<string, ValidationArguments> ValidationArguments { get; set; } =
            new Dictionary<string, ValidationArguments>();

        private bool InvokeValidationHandle(DataGridViewCell cell)
        {
            var name = ColumnIndexToName(cell.ColumnIndex);
            if (ValidationHandles.ContainsKey(name))
            {
                var arguments = ValidationArguments.ContainsKey(name)
                    ? ValidationArguments[name]
                    : new ValidationArguments(null, null, null);

                return ValidationHandles[name]?.Invoke(cell,
                    arguments.Item1, arguments.Item2, arguments.Item3) ?? true;
            }

            return true;
        }

        protected override void OnCellValidating(DataGridViewCellValidatingEventArgs e)
        {
            if (!DataGridViewUtilities.RowIndexIsValid(e.RowIndex, this))
            {
                return;
            }

            try
            {
                var cell = Rows[e.RowIndex].Cells[e.ColumnIndex];
                InvokeValidationHandle(cell);
            }
            catch (Exception) { }

            base.OnCellValidating(e);
        }

        public bool ValidateRow(DataGridViewRow row)
        {
            foreach (DataGridViewCell cell in row.Cells)
            {
                if (!InvokeValidationHandle(cell))
                {
                    return false;
                }
            }

            return true;
        }

        public bool Validate()
        {
            foreach (DataGridViewRow row in Rows)
            {
                if (!ValidateRow(row))
                {
                    return false;
                }
            }

            return true;
        }

        #endregion

    }
}
