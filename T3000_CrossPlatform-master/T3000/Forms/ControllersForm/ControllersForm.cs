namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class ControllersForm : Form
    {
        public List<ControllerPoint> Points { get; set; }
        public CustomUnits CustomUnits { get; private set; }

        public ControllersForm(List<ControllerPoint> points, CustomUnits customUnits = null)
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
            view.AddEditHandler(ActionColumn, TViewUtilities.EditEnum<DirectReverse>);
            view.AddEditHandler(TimeColumn, TViewUtilities.EditEnum<Periodicity>);

            //Cell changed handles
            view.AddChangedHandler(UnitsColumn, TViewUtilities.ChangeValue,
                AutoManualColumn, AutoManual.Manual);
            view.AddChangedHandler(ValueColumn, TViewUtilities.ChangeValue,
                AutoManualColumn, AutoManual.Manual);

            //Formating
            view.AddFormating(ActionColumn, o => ((DirectReverse)o).GetName());

            //Show points
            view.Rows.Clear();
            view.Rows.Add(Points.Count);
            for (var i = 0; i < Points.Count; ++i)
            {
                var point = Points[i];
                var row = view.Rows[i];
                row.SetValue(NumberColumn, $"{i + 1}");
                SetRow(row, point);
            }

            //Validation
            view.Validate();
        }

        private void SetRow(DataGridViewRow row, ControllerPoint point)
        {
            if (row == null || point == null)
            {
                return;
            }

            row.SetValue(NumberColumn, point.Input.Number);
            row.SetCell(ValueColumn, TViewUtilities.GetValueCellForUnit(
                    point.Value.ToString(),
                    point.Unit));
            row.SetValue(UnitsColumn, point.Unit);
            row.SetValue(AutoManualColumn, point.AutoManual);
            row.SetValue(OutputColumn, "x.x %");
            row.SetValue(SetPointColumn, "");
            row.SetValue(SetValueColumn, "");
            row.SetValue(UnitsColumn, "");
            row.SetValue(ActionColumn, point.Action);
            row.SetValue(PropColumn, point.Proportional);
            row.SetValue(IntColumn, 0);
            row.SetValue(TimeColumn, point.Periodicity);
            row.SetValue(DerColumn, 0.0);
            row.SetValue(BiasColumn, point.Bias);
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e) =>
            SetRow(view.CurrentRow, new ControllerPoint());

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
                    point.Input.Number = row.GetValue<int>(NumberColumn);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
                    //point.Value = TViewUtilities.GetVariableValue(row, ValueColumn, UnitsColumn, RangeColumn, CustomUnits);
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
