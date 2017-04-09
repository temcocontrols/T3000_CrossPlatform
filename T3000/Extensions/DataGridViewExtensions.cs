namespace T3000
{
    using System.Windows.Forms;

    public static class DataGridViewExtensions
    {
        public static T GetValue<T>(this DataGridViewRow row, DataGridViewColumn column) =>
            (T)row.Cells[column.Name].Value;

        public static void SetValue<T>(this DataGridViewRow row, DataGridViewColumn column, T value = default(T)) =>
            row.Cells[column.Name].Value = value;

        /// <summary>
        /// Returns null if index not valid
        /// </summary>
        /// <param name="view"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        public static DataGridViewRow GetRow(this DataGridView view, int index)
        {
            if (!TViewUtilities.RowIndexIsValid(index, view))
            {
                return null;
            }

            return view.Rows[index];
        }
    }
}
