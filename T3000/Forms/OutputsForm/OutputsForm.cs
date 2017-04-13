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
        public CustomUnits CustomUnits { get; private set; }

        public OutputsForm(List<OutputPoint> points, CustomUnits customUnits = null)
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
            view.AddEditHandler(HOASwitchColumn, TViewUtilities.EditEnum<SwitchStatus>);

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
                    $"OUT{i + 1}",
                    "?",
                    point.Description,
                    point.AutoManual,
                    point.HwSwitchStatus,
                    point.Value.ToString(),
                    point.Value.Units.GetOffOnName(point.Value.CustomUnits),
                    point.Value.Value,
                    point.Value.Units.IsDigital()
                    ? $"0 -> {point.Value.Value / 100.0}"
                    : "",
                    point.LowVoltage,
                    point.HighVoltage,
                    point.PwmPeriod,
                    point.Control,
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

            row.SetValue(DescriptionColumn, string.Empty);
            row.SetValue(AutoManualColumn, AutoManual.Automatic);
            row.SetValue(HOASwitchColumn, SwitchStatus.Off);
            row.SetValue(ValueColumn, "0");
            row.SetValue(UnitsColumn, Units.Unused.GetOffOnName());
            row.SetValue(RangeColumn, 0);
            row.SetValue(LowVColumn, 0);
            row.SetValue(HighVColumn, 0);
            row.SetValue(PWMPeriodColumn, 0);
            row.SetValue(LabelColumn, string.Empty);
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
                    var range = row.GetValue<int>(RangeColumn);
                    point.Description = row.GetValue<string>(DescriptionColumn);
                    point.Value = new VariableValue(
                        row.GetValue<string>(ValueColumn),
                        UnitsNamesUtilities.UnitsFromName(
                            row.GetValue<string>(UnitsColumn), CustomUnits),
                        CustomUnits, range);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
                    point.HwSwitchStatus = row.GetValue<SwitchStatus>(HOASwitchColumn);
                    point.Label = row.GetValue<string>(LabelColumn);
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

    }
}
