namespace T3000.Controls.Improved
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

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

    }
}
