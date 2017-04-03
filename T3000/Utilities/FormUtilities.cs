namespace T3000
{
    using System.Windows.Forms;

    public static class FormUtilities
    {
        public static bool RowIndexIsValid(int index, DataGridView view) =>
            index >= 0 && index < view.RowCount;
    }
}
