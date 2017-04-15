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
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(ValueColumn, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(HolidaysColumn, EditCodeColumn);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);

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
                    point.Label,
                    "Edit"
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
            row.Cells[ValueColumn.Name].Value = OffOn.Off;
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
                    point.Control = (OffOn)row.Cells[ValueColumn.Name].Value;
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
                var form = new SelectHolidaysForm(Codes[index]);
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
