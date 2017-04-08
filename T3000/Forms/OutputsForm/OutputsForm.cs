namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class OutputsForm : Form
    {
        public List<OutputPoint> Points { get; set; }
        public List<CustomDigitalUnitsPoint> CustomUnits { get; private set; }

        public OutputsForm(List<OutputPoint> points, List<CustomDigitalUnitsPoint> customUnits = null)
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
                TDataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[UnitsColumn.Name] = EditUnitsColumn;

            //Validation
            view.ValidationHandles[DescriptionColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[DescriptionColumn.Name] = new object[] { 21 }; //Max description length
            view.ValidationHandles[LabelColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[LabelColumn.Name] = new object[] { 9 }; //Max label length

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
                    point.Value.Value,
                    point.Value.Units.IsDigital()
                    ? $"0 -> {point.Value.Value / 100.0}"
                    : "",
                    point.PwmPeriod,
                    point.HighVoltage,
                    point.Decommissioned,
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
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
            row.Cells[ValueColumn.Name].Value = "0";
            row.Cells[UnitsColumn.Name].Value = Units.Unused.GetOffOnName();
            row.Cells[RangeColumn.Name].Value = 0;
            row.Cells[PercentsColumn.Name].Value = 0;
            row.Cells[HundredColumn.Name].Value = 0;
            row.Cells[DColumn.Name].Value = 0;
            row.Cells[LabelColumn.Name].Value = string.Empty;
        }

        private void Save(object sender, EventArgs e)
        {
            if (!view.Validate())
            {
                MessageBoxUtilities.ShowWarning(Resources.ViewNotValidated);
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
                    var range = (int)row.Cells[RangeColumn.Name].Value;
                    point.Description = (string)row.Cells[DescriptionColumn.Name].Value;
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
                    point.Value = new VariableValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        CustomUnits, range);
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
                if (!TDataGridViewUtilities.RowIndexIsValid(e.RowIndex, view))
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
