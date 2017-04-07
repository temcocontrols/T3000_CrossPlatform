namespace T3000.Controls.Improved
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    using ValidationFunc =
        System.Func<System.Windows.Forms.DataGridViewCell, object[], bool>;

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
        public Dictionary<string, object[]> ValidationArguments { get; set; } =
            new Dictionary<string, object[]>();

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

        protected override void OnCellValidating(DataGridViewCellValidatingEventArgs e)
        {
            if (!TDataGridViewUtilities.RowIndexIsValid(e.RowIndex, this))
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

            if (!TDataGridViewUtilities.RowIndexIsValid(e.RowIndex, this))
            {
                return;
            }
            var cell = Rows[e.RowIndex].Cells[e.ColumnIndex];
            ValidateCell(cell);
        }

        #endregion

    }
}
