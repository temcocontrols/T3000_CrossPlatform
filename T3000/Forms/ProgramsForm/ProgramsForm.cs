namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Reflection;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class ProgramsForm : Form
    {
        public List<ProgramPoint> Points { get; set; }

        public ProgramsForm(List<ProgramPoint> points)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;

            InitializeComponent();

            //User input handles
            view.ColumnHandles[StatusColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[AutoManualColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[RunStatusColumn.Name] =
                TDataGridViewUtilities.EditEnumColumn<NormalCom>;

            //Validation
            view.ValidationHandles[DescriptionColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[DescriptionColumn.Name] = new object[] { 21 };
            view.ValidationHandles[LabelColumn.Name] = TDataGridViewUtilities.ValidateRowColumnString;
            view.ValidationArguments[LabelColumn.Name] = new object[] { 9 };
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
                    point.Length,
                    point.NormalCom,
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
                    point.Length = (int)row.Cells[SizeColumn.Name].Value;
                    point.NormalCom = (NormalCom)row.Cells[RunStatusColumn.Name].Value;
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

        #region Handles

        #endregion

    }
}
