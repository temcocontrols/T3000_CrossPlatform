namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class InputsForm : Form
    {
        public List<InputPoint> Points { get; set; }
        public CustomUnits CustomUnits { get; private set; }

        public InputsForm(List<InputPoint> points, CustomUnits customUnits = null)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }
            Points = points;
            CustomUnits = customUnits;

            InitializeComponent();

            //User input
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(SignColumn, TViewUtilities.EditEnum<Sign>);
            view.AddEditHandler(StatusColumn, TViewUtilities.EditEnum<InputStatus>);
            view.AddEditHandler(JumperColumn, TViewUtilities.EditEnum<Jumper>);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);

            //Cell changed
            view.AddChangedHandler(UnitsColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);
            view.AddChangedHandler(ValueColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);

            //Formating
            view.AddFormating(SignColumn, o => ((Sign)o).GetName());
            view.AddFormating(JumperColumn, o => ((Jumper)o).GetName());
            view.AddFormating(UnitsColumn, o => ((Unit)o).GetUnitName(CustomUnits));
            view.AddFormating(RangeTextColumn, o => ((Unit)o).GetRange(CustomUnits));

            //Show points

            view.Rows.Clear();

            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    $"IN{i + 1}",
                    "?",
                    point.Description,
                    point.AutoManual,
                    point.Value.ToString(),
                    point.Value.Unit,
                    point.Value.Value,
                    point.Value.Unit,
                    point.CalibrationL,
                    point.CalibrationSign,
                    point.Filter,
                    point.Status,
                    point.Jumper,
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
            row.Cells[UnitsColumn.Name].Value = Unit.Unused;
            row.Cells[RangeColumn.Name].Value = 0;
            row.Cells[RangeTextColumn.Name].Value = Unit.Unused;
            row.Cells[CalibrationColumn.Name].Value = 0;
            row.Cells[SignColumn.Name].Value = Sign.Positive;
            row.Cells[FilterColumn.Name].Value = 0;
            row.Cells[StatusColumn.Name].Value = InputStatus.Normal;
            row.Cells[JumperColumn.Name].Value = Jumper.Thermistor;
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
                        row.GetValue<Unit>(UnitsColumn),
                        CustomUnits, range);
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
                    point.CalibrationSign = (Sign)row.Cells[SignColumn.Name].Value;
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



        #endregion
    }
}
