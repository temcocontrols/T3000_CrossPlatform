namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class EditScreenView : Form
    {
        public EditScreenView()
        {
            InitializeComponent();

            //User input handles
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(DisplayColumn, TViewUtilities.EditEnum<ScreenDisplay>);
            view.AddEditHandler(DisplayColorColumn, TViewUtilities.EditColor);
            view.AddEditHandler(HighColorColumn, TViewUtilities.EditColor);
            view.AddEditHandler(LowColorColumn, TViewUtilities.EditColor);

            //Formating
            view.AddFormating(DisplayColumn, o => ((ScreenDisplay) o).GetName());

            //Value changed handles
            view.AddChangedHandler(DisplayColorColumn, TViewUtilities.ValueColor);
            view.AddChangedHandler(HighColorColumn, TViewUtilities.ValueColor);
            view.AddChangedHandler(LowColorColumn, TViewUtilities.ValueColor);

            view.Rows.Clear();
            view.Rows.Add(1);
            SetRow(view.Rows[0]);
        }

        private void SetRow(DataGridViewRow row)
        {
            if (row == null)
            {
                return;
            }

            row.SetValue(LabelColumn, "Label");
            row.SetValue(DescriptionColumn, "Description");
            row.SetValue(AutoManualColumn, AutoManual.Automatic);
            row.SetValue(ValueColumn, "Value");
            row.SetValue(HighLimitColumn, 1.0);
            row.SetValue(LowLimitColumn, 0.0);
            row.SetValue(DisplayColorColumn, Color.Black);
            row.SetValue(HighColorColumn, Color.Blue);
            row.SetValue(LowColorColumn, Color.Red);
            row.SetValue(DisplayColumn, ScreenDisplay.Char8);
        }

        public enum ScreenDisplay
        {
            [Name("8 char")] Char8,
            [Name("20 char")] Char20,
            Value,
            Icon,
            [Name("Icon/8 char")] IconAndChar8,
            [Name("Icon/20 char")] IconAndChar20,
            [Name("Icon/Value")] IconAndValue
        }
    }
}
