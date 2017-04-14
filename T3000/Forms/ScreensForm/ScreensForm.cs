namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Reflection;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class ScreensForm : Form
    {
        public List<ScreenPoint> Points { get; set; }

        public ScreensForm(List<ScreenPoint> points)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;

            InitializeComponent();

            //User input handles
            view.AddEditHandler(ModeColumn, TViewUtilities.EditEnum<TextGraphic>);
            view.AddEditHandler(PictureColumn, EditPictureColumn);
            view.AddEditHandler(ScreenColumn, EditScreenColumn);

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.AddValidation(RefreshColumn, TViewUtilities.ValidateInteger);
            view.AddValidation(CountColumn, TViewUtilities.ValidateInteger);

            //Cell changed handles
            view.AddChangedHandler(ModeColumn, TViewUtilities.ChangeEnabled,
                PictureColumn.Name, ModeColumn.Name);

            //Show points
            view.Rows.Clear();
            var i = 0;
            foreach (var point in Points)
            {
                view.Rows.Add(new object[] {
                    i + 1,
                    point.Description,
                    point.Label,
                    point.PictureFile,
                    0,
                    point.GraphicMode,
                    point.RefreshTime
                });
                ++i;
            }

            view.SendChanged(ModeColumn);
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
            row.Cells[LabelColumn.Name].Value = string.Empty;
            row.Cells[PictureColumn.Name].Value = string.Empty;
            row.Cells[ModeColumn.Name].Value = TextGraphic.Text;
            row.Cells[RefreshColumn.Name].Value = 0;
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
                    point.Label = (string)row.Cells[LabelColumn.Name].Value;
                    point.PictureFile = (string)row.Cells[PictureColumn.Name].Value;
                    point.GraphicMode = (TextGraphic)row.Cells[ModeColumn.Name].Value;
                    point.RefreshTime = (int)row.Cells[ModeColumn.Name].Value;
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

        private void EditScreenColumn(object sender, EventArgs e, params object[] arguments)
        {
            try
            {
                var path = view.CurrentRow.GetValue<string>(PictureColumn);
                var form = new EditScreenForm(path);
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

        private void EditPictureColumn(object sender, EventArgs e, params object[] arguments)
        {
            try
            {
                var dialog = new OpenFileDialog();
                dialog.Filter = $"{Resources.ImageFiles} (*.jpg, *.jpeg, *.jpe, *.jfif, *.png) | *.jpg; *.jpeg; *.jpe; *.jfif; *.png|" +
                                $"{Resources.AllFiles} (*.*)|*.*";
                dialog.Title = Resources.SelectImageFile;
                dialog.InitialDirectory = Assembly.GetExecutingAssembly().Location;
                if (dialog.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                var row = view.CurrentRow;
                var cell = row.Cells[PictureColumn.Name];
                cell.Value = dialog.FileName;
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }
        
        #endregion

    }
}
