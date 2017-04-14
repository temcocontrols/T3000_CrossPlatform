namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
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
            view.Rows.Add(Points.Count);
            for (var i = 0; i < Points.Count; ++i)
            {
                var point = Points[i];
                var row = view.Rows[i];
                row.SetValue(InputColumn, $"IN{i + 1}");
                row.SetValue(PanelColumn, "?");
                SetRow(row, point);
            }

            view.Validate();
        }

        private void SetRow(DataGridViewRow row, InputPoint point)
        {
            if (row == null || point == null)
            {
                return;
            }

            row.SetValue(DescriptionColumn, point.Description);
            row.SetValue(AutoManualColumn, point.AutoManual);
            row.SetValue(ValueColumn, point.Value.ToString());
            row.SetValue(UnitsColumn, point.Value.Unit);
            row.SetValue(RangeColumn, point.Value.Value);
            row.SetValue(RangeTextColumn, point.Value.Unit);
            row.SetValue(CalibrationColumn, point.CalibrationL);
            row.SetValue(SignColumn, point.CalibrationSign);
            row.SetValue(FilterColumn, point.Filter);
            row.SetValue(StatusColumn, point.Status);
            row.SetValue(JumperColumn, point.Jumper);
            row.SetValue(LabelColumn, point.Label);
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e) =>
            SetRow(view.CurrentRow, new InputPoint());

        private VariableValue GetVariableValue(DataGridViewRow row) =>
            TViewUtilities.GetVariableValue(row, ValueColumn, UnitsColumn, RangeColumn, CustomUnits);

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
                    point.Value = GetVariableValue(row);
                    point.CalibrationL = row.GetValue<double>(CalibrationColumn);
                    point.CalibrationSign = row.GetValue<Sign>(SignColumn);
                    point.Filter = row.GetValue<int>(FilterColumn);
                    point.Status = row.GetValue<InputStatus>(StatusColumn);
                    point.Jumper = row.GetValue<Jumper>(JumperColumn);
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
        
        #region User input handles



        #endregion
    }
}
