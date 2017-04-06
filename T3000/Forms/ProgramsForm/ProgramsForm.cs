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

            view.ColumnHandles[StatusColumn.Name] =
                DataGridViewUtilities.EditEnumColumn<OffOn>;
            view.ColumnHandles[AutoManualColumn.Name] =
                DataGridViewUtilities.EditEnumColumn<AutoManual>;
            view.ColumnHandles[RunStatusColumn.Name] =
                DataGridViewUtilities.EditEnumColumn<NormalCom>;

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
