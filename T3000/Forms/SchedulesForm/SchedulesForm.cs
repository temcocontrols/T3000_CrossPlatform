namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class SchedulesForm : Form
    {
        public List<SchedulePoint> Points { get; set; }
        public List<ScheduleCode> Codes { get; set; }

        public SchedulesForm(List<SchedulePoint> points, List<ScheduleCode> codes)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            Codes = codes;

            InitializeComponent();

            //User input handles
            view.AddEditHandler(OutputColumn, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(State1Column, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(State2Column, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(SchedulesColumn, EditCodeColumn);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.AddValidation(Holiday1Column, TViewUtilities.ValidateString, 9);
            view.AddValidation(Holiday2Column, TViewUtilities.ValidateString, 9);

            //Show points
            view.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    i + 1,
                    point.Description,
                    point.AutoManual,
                    point.Control,
                    "",
                    point.Override1Control,
                    "",
                    point.Override2Control,
                    point.Label,
                    $"Length: {codes[i].Code.GetString().ClearBinarySymvols().Length}"
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
            row.Cells[OutputColumn.Name].Value = OffOn.Off;
            row.Cells[Holiday1Column.Name].Value = "";
            row.Cells[State1Column.Name].Value = OffOn.Off;
            row.Cells[Holiday2Column.Name].Value = "";
            row.Cells[State2Column.Name].Value = OffOn.Off;
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
                    point.Description = (string)row.Cells[DescriptionColumn.Name].Value;
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
                    point.Control = (OffOn)row.Cells[OutputColumn.Name].Value;
                    point.Override1Control = (OffOn)row.Cells[State1Column.Name].Value;
                    point.Override2Control = (OffOn)row.Cells[State2Column.Name].Value;
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
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

        private void EditCodeColumn(object sender, EventArgs e)
        {
            try
            {
                var form = new EditSchedulesForm();
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

    }
}
