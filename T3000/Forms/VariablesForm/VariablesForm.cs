namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class VariablesForm : Form
    {
        public List<VariablePoint> Points { get; set; }
        public CustomUnits CustomUnits { get; private set; }

        public VariablesForm(List<VariablePoint> points, CustomUnits customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();

            //User input handles
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(UnitsColumn, EditUnitsColumn);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.AddValidation(ValueColumn, TViewUtilities.ValidateValue, 
                ValueColumn.Name, UnitsColumn.Name, CustomUnits);
            view.AddValidation(UnitsColumn, TViewUtilities.ValidateValue,
                ValueColumn.Name, UnitsColumn.Name, CustomUnits);

            //Cell changed handles
            view.AddChangedHandler(UnitsColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);
            view.AddChangedHandler(ValueColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);

            //Formating
            view.AddFormating(UnitsColumn, o => ((Unit)o).GetOffOnName(CustomUnits));

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
                    point.Value.Unit,
                    point.Value.Value,
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
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
            row.Cells[ValueColumn.Name].Value = "0";
            row.Cells[UnitsColumn.Name].Value = Unit.Unused.GetOffOnName();
            row.Cells[RangeColumn.Name].Value = 0;
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
                    point.Description = row.GetValue<string>(DescriptionColumn);
                    point.Label = row.GetValue<string>(LabelColumn);
                    point.Value = GetVariableValue(row);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
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

        #region User input handles

        private VariableValue GetVariableValue(DataGridViewRow row) =>
            TViewUtilities.GetVariableValue(row, ValueColumn, UnitsColumn, RangeColumn, CustomUnits);

        private void EditUnitsColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                var value = GetVariableValue(row);
                var form = new SelectUnitsForm(value.Unit, value.CustomUnits);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                var newValue = value.ConvertValue(form.SelectedUnit, form.CustomUnits);
                CustomUnits = form.CustomUnits;

                view.ChangeValidationArguments(
                    UnitsColumn, ValueColumn.Name, UnitsColumn.Name, CustomUnits);
                view.ChangeValidationArguments(
                    ValueColumn, ValueColumn.Name, UnitsColumn.Name, CustomUnits);

                row.SetValue(UnitsColumn, form.SelectedUnit);
                row.SetValue(ValueColumn, newValue);
                //row.SetValue(RangeColumn, newValue.Va);

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
