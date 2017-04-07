namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class VariablesForm : Form
    {
        public List<ValuedPoint> Points { get; set; }
        public List<CustomDigitalUnitsPoint> CustomUnits { get; private set; }

        public VariablesForm(List<ValuedPoint> points, List<CustomDigitalUnitsPoint> customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();

            //User input handles
            view.ColumnHandles[AutoManualColumn.Name] =
                DataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[UnitsColumn.Name] = EditUnitsColumn;

            //Validation
            view.ValidationHandles[DescriptionColumn.Name] = DataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[DescriptionColumn.Name] = new object[] { 21 };
            view.ValidationHandles[LabelColumn.Name] = DataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[LabelColumn.Name] = new object[] { 9 };
            view.ValidationHandles[ValueColumn.Name] = DataGridViewUtilities.ValidateRowValue;
            view.ValidationArguments[ValueColumn.Name] =
                new object[] { ValueColumn.Name, UnitsColumn.Name, CustomUnits };
            view.ValidationHandles[UnitsColumn.Name] = view.ValidationHandles[ValueColumn.Name];
            view.ValidationArguments[UnitsColumn.Name] = view.ValidationArguments[ValueColumn.Name];

            //Show points

            view.Rows.Clear();

            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    i + 1,
                    point.Description,
                    point.AutoManual,
                    point.Value.ToString(),
                    point.Value.Units.GetOffOnName(point.Value.CustomUnits),
                    point.Label
                });
                ++i;
            }
            view.Validate();
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e)
        {
            var row = view.CurrentRow;
            if (row == null)
            {
                return;
            }

            row.Cells[DescriptionColumn.Name].Value = string.Empty;
            row.Cells[LabelColumn.Name].Value = string.Empty;
            row.Cells[UnitsColumn.Name].Value = Units.Unused.GetOffOnName();
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
            row.Cells[ValueColumn.Name].Value = "0";
        }

        private void Save(object sender, EventArgs e)
        {
            if (!view.Validate())
            {
                MessageBoxUtilities.ShowWarning(Resources.VariablesFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

            try
            {
                var i = 0;
                foreach (DataGridViewRow row in view.Rows)
                {
                    if (i >= Points.Count)
                    {
                        break;
                    }

                    var point = Points[i];
                    point.Description = (string)row.Cells[DescriptionColumn.Name].Value;
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
                    point.Value = new VariableValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        CustomUnits);
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
                    ++i;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
                DialogResult = DialogResult.None;
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region Callbacks

        private void view_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (!DataGridViewUtilities.RowIndexIsValid(e.RowIndex, view))
                {
                    return;
                }

                var row = view.Rows[e.RowIndex];
                //Set AutoManual to Manual, if user changed units
                if (e.ColumnIndex == UnitsColumn.Index)
                {
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
                }
                else if (e.ColumnIndex == ValueColumn.Index)
                {
                    row.Cells[AutoManualColumn.Name].Value = AutoManual.Manual;
                }
                view.ValidateRow(row);
            }
            catch (Exception) { }
        }

        #endregion

        #region User input handles

        private void EditUnitsColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                var currentUnits = UnitsNamesConstants.UnitsFromName(
                    (string)row.Cells[UnitsColumn.Name].Value, CustomUnits);
                var form = new SelectUnitsForm(currentUnits, CustomUnits);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                var newValue = UnitsUtilities.ConvertValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        form.SelectedUnits,
                        CustomUnits, form.CustomUnits);
                CustomUnits = form.CustomUnits;
                view.ValidationArguments[UnitsColumn.Name] =
                    new object[] { ValueColumn.Name, UnitsColumn.Name, CustomUnits };
                view.ValidationArguments[ValueColumn.Name] = 
                    view.ValidationArguments[UnitsColumn.Name];
                var newUnits = form.SelectedUnits.GetOffOnName(CustomUnits);

                row.Cells[UnitsColumn.Name].Value = newUnits;
                row.Cells[ValueColumn.Name].Value = newValue;
                view.ValidateRow(row);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

    }
}
