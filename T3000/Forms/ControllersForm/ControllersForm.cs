namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using Properties;
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

            //Validation


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
                    i + 1,
                    point.Input.Number,
                    point.Value.ToString(),
                    point.Units.ToString(),
                    point.AutoManual,
                    "x.x %",
                    "",
                    "",
                    "",
                    point.Action,
                    point.Proportional,
                    0,
                    point.Periodicity,
                    0.00,
                    point.Bias
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

            row.Cells[InputColumn.Name].Value = string.Empty;
            row.Cells[ValueColumn.Name].Value = "0";
            row.Cells[UnitsColumn.Name].Value = Units.Unused.GetOffOnName();
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
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

                    var point = Points[i];/*
                    var range = (int)row.Cells[RangeColumn.Name].Value;
                    point.Description = (string)row.Cells[DescriptionColumn.Name].Value;
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
                    point.Value = new VariableValue(
                        (string)row.Cells[ValueColumn.Name].Value,
                        UnitsNamesConstants.UnitsFromName(
                            (string)row.Cells[UnitsColumn.Name].Value, CustomUnits),
                        CustomUnits, range);
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;*/
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
