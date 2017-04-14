namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Windows.Forms;

    public partial class EditCustomDigitalUnitForm : Form
    {
        public CustomDigitalUnitsPoint Point { get; set; }

        public EditCustomDigitalUnitForm(CustomDigitalUnitsPoint point)
        {
            InitializeComponent();

            Point = point;

            offNameTextBox.Text = point.DigitalUnitsOff;
            onNameTextBox.Text = point.DigitalUnitsOn;

            ValidateNames(this, EventArgs.Empty);
        }

        public static bool IsValid(string name)
        {
            //if (string.IsNullOrWhiteSpace(name))
            //{
            //    return false;
            //}

            return true;
        }

        private void ValidateNames(object sender, EventArgs e)
        {
            offNameTextBox.BackColor = ColorConstants.GetValidationColor(IsValid(offNameTextBox.Text));
            onNameTextBox.BackColor = ColorConstants.GetValidationColor(IsValid(onNameTextBox.Text));
        }

        #region Button

        private void Save(object sender, EventArgs e)
        {
            if (!IsValid(offNameTextBox.Text) ||
                !IsValid(onNameTextBox.Text))
            {
                MessageBoxUtilities.ShowWarning(Resources.EditCustomUnitsFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

            Point.DigitalUnitsOff = offNameTextBox.Text;
            Point.DigitalUnitsOn = onNameTextBox.Text;

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
