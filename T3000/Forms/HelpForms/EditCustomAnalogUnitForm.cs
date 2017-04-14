namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;

    public partial class EditCustomAnalogUnitForm : Form
    {
        public CustomAnalogUnitsPoint Point { get; set; }

        public EditCustomAnalogUnitForm(CustomAnalogUnitsPoint point)
        {
            InitializeComponent();

            Point = point;

            nameTextBox.Text = point.Name;

            ValidateName(this, EventArgs.Empty);
        }

        public static bool IsValid(string name)
        {
            //if (string.IsNullOrWhiteSpace(name))
            //{
            //    return false;
            //}

            return true;
        }

        private void ValidateName(object sender, EventArgs e)
        {
            var isValidated = IsValid(nameTextBox.Text);
            nameTextBox.BackColor = ColorConstants.GetValidationColor(isValidated);
        }

        #region Button

        private void Save(object sender, EventArgs e)
        {
            if (!IsValid(nameTextBox.Text))
            {
                MessageBoxUtilities.ShowWarning(Resources.EditCustomUnitsFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

            Point.Name = nameTextBox.Text;

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
