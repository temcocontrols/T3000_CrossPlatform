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

            //User input handles
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(SignColumn, EditSignColumn);
            view.AddEditHandler(StatusColumn, TViewUtilities.EditEnum<InputStatus>);
            view.AddEditHandler(JumperColumn, EditJumperColumn);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);

            //Cell changed handles
            view.AddChangedHandler(UnitsColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);
            view.AddChangedHandler(ValueColumn, TViewUtilities.ChangeValue,
                AutoManualColumn.Name, AutoManual.Manual);

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
                    point.Value.Unit.GetOffOnName(customUnits),
                    point.Value.Value,
                    point.Value.Unit.IsDigital()
                    ? $"0 -> {point.Value.Value / 100.0}"
                    : "",
                    point.CalibrationL,
                    point.CalibrationSign.GetName(),
                    point.Filter,
                    point.Status,
                    point.Jumper.GetName(),
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
            row.Cells[UnitsColumn.Name].Value = Unit.Unused.GetOffOnName();
            row.Cells[RangeColumn.Name].Value = 0;
            row.Cells[CalibrationColumn.Name].Value = 0;
            row.Cells[SignColumn.Name].Value = Sign.Positive;
            row.Cells[FilterColumn.Name].Value = 0;
            row.Cells[StatusColumn.Name].Value = InputStatus.Normal;
            row.Cells[JumperColumn.Name].Value = Jumper.Thermistor.GetName();
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
                        UnitsNamesUtilities.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
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

        private void EditSignColumn(object sender, EventArgs e)
        {
            try
            {
                var view = (Controls.TView)sender;
                var cell = view.CurrentCell;
                var text = (string) cell.Value;
                var sign = text.Equals(Sign.Positive.GetName()) 
                    ? Sign.Positive : Sign.Negative;
                var nextValue = sign.NextValue();
                cell.Value = nextValue.GetName();

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void EditJumperColumn(object sender, EventArgs e)
        {
            try
            {
                var view = (Controls.TView)sender;
                var cell = view.CurrentCell;
                var text = (string)cell.Value;

                var jumper = Jumper.Thermistor;
                if (text.Equals(Jumper.To10V.GetName()))
                {
                    jumper = Jumper.To10V;
                }
                else if (text.Equals(Jumper.To5V.GetName()))
                {
                    jumper = Jumper.To5V;
                }
                else if (text.Equals(Jumper.To20Ma.GetName()))
                {
                    jumper = Jumper.To20Ma;
                }

                var nextValue = jumper.NextValue();
                cell.Value = nextValue.GetName();

                view.ValidateCell(cell);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

    }
}
