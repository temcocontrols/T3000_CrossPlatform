namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class ProgramsForm : Form
    {
        public List<ProgramPoint> Points { get; set; }
        public List<ProgramCode> Codes { get; set; }

        public ProgramsForm(List<ProgramPoint> points, List<ProgramCode> codes)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            Codes = codes;

            InitializeComponent();

            //User input handles
            view.AddEditHandler(StatusColumn, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(RunStatusColumn, TViewUtilities.EditEnum<NormalCom>);
            view.AddEditHandler(CodeColumn, EditCodeColumn);

            //Value changed handles
            view.AddChangedHandler(StatusColumn, TViewUtilities.ChangeColor, Color.Red, Color.Blue);

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
                    point.Label,
                    $"Length: {codes[i].Code.GetString().ClearBinarySymvols().Length}"
                });
                ++i;
            }

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.AddValidation(SizeColumn, TViewUtilities.ValidateInteger);
            view.Validate();

            //For apply changed handlers
            view.SendChanged(StatusColumn);
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e)
        {
            var row = view.CurrentRow;

            if (row == null)
            {
                return;
            }

            row.SetValue(DescriptionColumn, string.Empty);
            row.SetValue(StatusColumn, OffOn.Off);
            row.SetValue(AutoManualColumn, AutoManual.Automatic);
            row.SetValue(SizeColumn, 0);
            row.SetValue(RunStatusColumn, NormalCom.Normal);
            row.SetValue(LabelColumn, string.Empty);
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
                for (var i = 0; i < view.Rows.Count; ++i)
                {
                    if (i >= Points.Count)
                    {
                        break;
                    }

                    var row = view.Rows[i];
                    var point = Points[i];
                    point.Description = row.GetValue<string>(DescriptionColumn);
                    point.Control = row.GetValue<OffOn>(StatusColumn);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
                    point.Length = row.GetValue<int>(SizeColumn);
                    point.NormalCom = row.GetValue<NormalCom>(RunStatusColumn);
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

        private void EditCodeColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                var index = row.GetValue<int>(NumberColumn) - 1;
                var form = new EditCodeForm(Codes[index]);
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
