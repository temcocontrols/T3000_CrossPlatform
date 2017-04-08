namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class HolidaysForm : Form
    {
        public List<HolidayPoint> Points { get; set; }
        public List<HolidayCode> Codes { get; set; }

        public HolidaysForm(List<HolidayPoint> points, List<HolidayCode> codes)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            Codes = codes;

            InitializeComponent();

            //User input handles
            view.ColumnHandles[StatusColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[AutoManualColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[RunStatusColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<NormalCom>;
            view.ColumnHandles[CodeColumn.Name] = EditCodeColumn;

            //Validation
            view.ValidationHandles[DescriptionColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[DescriptionColumn.Name] = new object[] { 21 }; //Max description length
            view.ValidationHandles[LabelColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[LabelColumn.Name] = new object[] { 9 }; //Max label length
            view.ValidationHandles[SizeColumn.Name] = TDataGridViewUtilities.ValidateRowColumnInteger;

            //Show points
            view.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    i + 1,
                    point.Description,
                    point.Control,
                    point.AutoManual,
                    0,
                    0,
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
            row.Cells[StatusColumn.Name].Value = OffOn.Off;
            row.Cells[AutoManualColumn.Name].Value = AutoManual.Automatic;
            row.Cells[SizeColumn.Name].Value = 0;
            row.Cells[RunStatusColumn.Name].Value = NormalCom.Normal;
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
                    point.Control = (OffOn)row.Cells[StatusColumn.Name].Value;
                    point.AutoManual = (AutoManual)row.Cells[AutoManualColumn.Name].Value;
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
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

    }
}
