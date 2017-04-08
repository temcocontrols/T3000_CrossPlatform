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
            view.ColumnHandles[OutputColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[AutoManualColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[State1Column.Name] =
                TDataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[State2Column.Name] =
                TDataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[SchedulesColumn.Name] = EditCodeColumn;

            //Validation
            view.ValidationHandles[DescriptionColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[DescriptionColumn.Name] = new object[] { 21 }; //Max description length
            view.ValidationHandles[LabelColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[LabelColumn.Name] = new object[] { 9 }; //Max label length
            view.ValidationHandles[Holiday1Column.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[Holiday1Column.Name] = new object[] { 9 }; //Max Holiday1 length
            view.ValidationHandles[Holiday2Column.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[Holiday2Column.Name] = new object[] { 9 }; //Max Holiday2 length

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
                var row = view.CurrentRow;
                var index = ((int)row.Cells[NumberColumn.Name].Value) - 1;
                var form = new EditSchedulesForm(Codes[index]);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                Codes[index] = form.Code;
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

    }
}
