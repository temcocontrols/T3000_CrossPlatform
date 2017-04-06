namespace T3000
{
    using System;
    using System.Windows.Forms;

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
    }
}
