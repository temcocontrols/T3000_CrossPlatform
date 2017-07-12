namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;

    public partial class EditCustomUnitsForm : Form
    {
        public CustomUnits CustomUnits { get; private set; }

        public EditCustomUnitsForm(CustomUnits customUnits)
        {
            InitializeComponent();

            CustomUnits = customUnits;

            //User input handles
            digitalView.AddEditHandler(DirectColumn, TViewUtilities.EditBoolean);

            digitalView.Rows.Clear();
            digitalView.Rows.Add(CustomUnits.Digital.Count);
            for (var i = 0; i < CustomUnits.Digital.Count; ++i)
            {
                var point = CustomUnits.Digital[i];
                var row = digitalView.Rows[i];
                row.SetValue(NumberColumn, $"{i + 1}");
                row.SetValue(OffNameColumn, point.DigitalUnitsOff);
                row.SetValue(OnNameColumn, point.DigitalUnitsOn);
                row.SetValue(DirectColumn, point.Direct);
            }

            //Validation
            digitalView.AddValidation(OffNameColumn, TViewUtilities.ValidateString, 12);
            digitalView.AddValidation(OnNameColumn, TViewUtilities.ValidateString, 12);
            digitalView.Validate();

            analogView.Rows.Clear();
            analogView.Rows.Add(CustomUnits.Analog.Count);
            for (var i = 0; i < CustomUnits.Analog.Count; ++i)
            {
                var point = CustomUnits.Analog[i];
                var row = analogView.Rows[i];
                row.SetValue(AnalogNumberColumn, $"{i + 1}");
                row.SetValue(NameColumn, point.Name);
            }

            //Validation
            analogView.AddValidation(NameColumn, TViewUtilities.ValidateString, 20);
            analogView.Validate();
        }

        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            if (!analogView.Validate() || !digitalView.Validate())
            {
                MessageBoxUtilities.ShowWarning(Resources.EditCustomUnitsFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

            try
            {
                for (var i = 0; i < analogView.RowCount && i < CustomUnits.Analog.Count; ++i)
                {
                    var point = CustomUnits.Analog[i];
                    var row = analogView.Rows[i];
                    point.Name = row.GetValue<string>(NameColumn);
                }
                for (var i = 0; i < digitalView.RowCount && i < CustomUnits.Digital.Count; ++i)
                {
                    var point = CustomUnits.Digital[i];
                    var row = digitalView.Rows[i];
                    point.DigitalUnitsOff = row.GetValue<string>(OffNameColumn);
                    point.DigitalUnitsOn = row.GetValue<string>(OnNameColumn);
                    point.Direct = row.GetValue<bool>(DirectColumn);
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
