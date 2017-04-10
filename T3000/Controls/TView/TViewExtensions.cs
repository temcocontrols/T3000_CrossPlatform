namespace T3000
{
    using Controls;
    using System.Drawing;
    using System.Windows.Forms;

    public static class TViewExtensions
    {
        public static readonly Color DisabledBackColor = SystemColors.ControlDark;
        public static readonly Color DisabledForeColor = SystemColors.ControlDarkDark;
        public static readonly Color DisabledSelectionBackColor = SystemColors.ControlDark;

        public static T GetValue<T>(this DataGridViewRow row, string columnName) =>
            (T)row.Cells[columnName].Value;

        public static void SetValue<T>(this DataGridViewRow row, string columnName, T value = default(T)) =>
            row.Cells[columnName].Value = value;

        public static T GetValue<T>(this DataGridViewRow row, DataGridViewColumn column) =>
            row.GetValue<T>(column.Name);

        public static void SetValue<T>(this DataGridViewRow row, DataGridViewColumn column, T value = default(T)) =>
            row.SetValue(column.Name, value);


        /// <summary>
        /// Returns null if index not valid
        /// </summary>
        /// <param name="view"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        public static DataGridViewRow GetRow(this TView view, int index)
        {
            if (!view.RowIndexIsValid(index))
            {
                return null;
            }

            return view.Rows[index];
        }

        public static void Enable(this DataGridViewCell cell, bool enabled)
        {
            cell.ReadOnly = !enabled;
            cell.Style.BackColor = enabled
                ? cell.OwningColumn.DefaultCellStyle.BackColor
                : DisabledBackColor;
            cell.Style.ForeColor = enabled
                ? cell.OwningColumn.DefaultCellStyle.ForeColor
                : DisabledForeColor;
            cell.Style.SelectionBackColor = enabled
                ? cell.OwningColumn.DefaultCellStyle.SelectionBackColor
                : DisabledSelectionBackColor;
        }
    }
}
