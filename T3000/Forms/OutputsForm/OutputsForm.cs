namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
    using System.Drawing;
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
            view.AddEditAction(ValueColumn, TViewUtilities.EditValue,
                UnitsColumn, RangeColumn, CustomUnits);
            view.AddEditAction(UnitsColumn, TViewUtilities.EditUnitsColumn, 
                ValueColumn, UnitsColumn, RangeColumn,
                CustomUnits, new Func<Unit, bool>(unit => unit.IsOutputAnalog()),
                RangeTextColumn);
            view.AddEditHandler(StatusColumn, TViewUtilities.EditEnum<OffOn>);

            //Value changed handles
            view.AddChangedHandler(StatusColumn, TViewUtilities.ChangeColor, 
                Color.Red, Color.Blue);

            //Formating
            view.AddFormating(UnitsColumn, o => ((Unit)o).GetUnitName(CustomUnits));
            view.AddFormating(RangeTextColumn, o => ((Unit)o).GetRange(CustomUnits));

            //Show points
            view.Rows.Clear();
            view.Rows.Add(Points.Count);
            for (var i = 0; i < Points.Count; ++i)
            {
                var point = Points[i];
                var row = view.Rows[i];
                row.SetValue(OutputColumn, $"OUT{i + 1}");
                row.SetValue(PanelColumn, "?");
                SetRow(row, point);
            }

            //Value changed handles
            view.AddChangedHandler(UnitsColumn, TViewUtilities.ChangeValue,
                AutoManualColumn, AutoManual.Manual);
            view.AddChangedHandler(ValueColumn, TViewUtilities.ChangeValue,
                AutoManualColumn, AutoManual.Manual);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.AddValidation(LowVColumn, TViewUtilities.ValidateInteger);
            view.AddValidation(HighVColumn, TViewUtilities.ValidateInteger);
            view.AddValidation(PWMPeriodColumn, TViewUtilities.ValidateInteger);
            view.Validate();
        }

        private void SetRow(DataGridViewRow row, OutputPoint point)
        {
            if (row == null || point == null)
            {
                return;
            }

            row.SetValue(DescriptionColumn, point.Description);
            row.SetValue(AutoManualColumn, point.AutoManual);
            row.SetValue(HOASwitchColumn, point.HwSwitchStatus);
            row.SetCell(ValueColumn, TViewUtilities.GetValueCellForUnit(
                    point.Value.ToString(),
                    point.Value.Unit));
            row.SetValue(UnitsColumn, point.Value.Unit);
            row.SetValue(RangeColumn, point.Value.Value);
            row.SetValue(RangeTextColumn, point.Value.Unit);
            row.SetValue(LowVColumn, point.LowVoltage);
            row.SetValue(HighVColumn, point.HighVoltage);
            row.SetValue(PWMPeriodColumn, point.PwmPeriod);
            row.SetValue(StatusColumn, point.Control);
            row.SetValue(LabelColumn, point.Label);
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e) =>
            SetRow(view.CurrentRow, new OutputPoint());

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
                for (var i = 0; i < view.RowCount && i < Points.Count; ++i)
                {
                    var point = Points[i];
                    var row = view.Rows[i];
                    point.Description = row.GetValue<string>(DescriptionColumn);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
                    point.HwSwitchStatus = row.GetValue<SwitchStatus>(HOASwitchColumn);
                    point.LowVoltage = row.GetValue<int>(LowVColumn);
                    point.HighVoltage = row.GetValue<int>(HighVColumn);
                    point.PwmPeriod = row.GetValue<int>(PWMPeriodColumn);
                    point.Control = row.GetValue<OffOn>(StatusColumn);
                    point.Value = TViewUtilities.GetVariableValue(row, ValueColumn, UnitsColumn, RangeColumn, CustomUnits);
                    point.Label = row.GetValue<string>(LabelColumn);
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
