namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class SelectUnitsForm : Form
    {
        public Units SelectedUnits { get; private set; } = Units.Unused;
        public bool IsValidated { get; private set; } = true;
        public CustomUnits CustomUnits { get; set; } = null;
        public bool IsAnalogRange { get; private set; } = false;

        public SelectUnitsForm(
            Units selectedUnits = Units.Unused, 
            CustomUnits customUnits = null, 
            bool isAnalogRange = false)
        {
            InitializeComponent();

            SelectedUnits = selectedUnits;
            CustomUnits = customUnits;
            IsAnalogRange = isAnalogRange;

            UpdateUnits();
        }

        private int ToNumber(Units units) =>
            (int)(units + 1);

        private Units ToUnits(int units) =>
            (Units)(units - 1);

        public void UpdateUnits()
        {
            try
            {
                analogUnitsListBox.Items.Clear();
                var analogDictionary = IsAnalogRange 
                    ? UnitsNamesUtilities.GetAnalogRangeNames(CustomUnits)
                    : UnitsNamesUtilities.GetAnalogNames(CustomUnits);
                foreach (var name in analogDictionary)
                {
                    analogUnitsListBox.Items.Add($"{ToNumber(name.Key)}. {name.Value.OffOnName}");
                }

                digitalUnitsListBox.Items.Clear();
                foreach (var name in UnitsNamesUtilities.GetDigitalNames(CustomUnits))
                {
                    digitalUnitsListBox.Items.Add($"{ToNumber(name.Key)}. {name.Value.OffOnName}");
                }

                ShowSelectedItem();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void unitsListBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                Save(sender, e);
            }
        }

        private void Save(object sender, EventArgs e)
        {
            if (!IsValidated)
            {
                MessageBoxUtilities.ShowWarning(Resources.SelectUnitsFormNotValid);
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

        private void EditCustomUnits(object sender, EventArgs e)
        {
            var form = new EditCustomUnitsForm(CustomUnits);

            if (form.ShowDialog() == DialogResult.OK)
            {
                CustomUnits = form.CustomUnits;
                UpdateUnits();
            }
        }

        private void numberTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            var maxItemsInColumn = analogUnitsListBox.Height / analogUnitsListBox.ItemHeight;
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    Save(sender, e);
                    break;

                case Keys.W:
                case Keys.Up:
                case Keys.PageUp:
                case Keys.VolumeUp:
                    SelectedUnits = SelectedUnits.PrevValue();
                    ShowSelectedItem();
                    break;

                case Keys.S:
                case Keys.Down:
                case Keys.PageDown:
                case Keys.VolumeDown:
                    SelectedUnits = SelectedUnits.NextValue();
                    ShowSelectedItem();
                    break;

                case Keys.Left:
                case Keys.A:
                    for (var i = 0; i < maxItemsInColumn; ++i)
                    {
                        SelectedUnits = SelectedUnits.PrevValue();
                    }
                    ShowSelectedItem();
                    break;

                case Keys.Right:
                case Keys.D:
                    for (var i = 0; i < maxItemsInColumn; ++i)
                    {
                        SelectedUnits = SelectedUnits.NextValue();
                    }
                    ShowSelectedItem();
                    break;
            }
        }

        public void ShowSelectedItem()
        {
            numberTextBox.Text = ToNumber(SelectedUnits).ToString();
            messageLabel.Text = string.Format(Resources.SelectUnitsFormSelectedUnits, SelectedUnits.GetOffOnName(CustomUnits));
            if (SelectedUnits.IsAnalog())
            {
                analogUnitsListBox.SelectedIndex = (int) SelectedUnits;
                digitalUnitsListBox.SelectedIndex = -1;
            }
            else
            {
                digitalUnitsListBox.SelectedIndex = SelectedUnits - Units.DigitalUnused;
                analogUnitsListBox.SelectedIndex = -1;
            }
        }

        private void analogUnitsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (analogUnitsListBox.SelectedIndex == -1 ||
                analogUnitsListBox.SelectedIndex == (int)SelectedUnits)
            {
                return;
            }

            try
            {
                if (digitalUnitsListBox.SelectedIndex != -1)
                    digitalUnitsListBox.SelectedIndex = -1;

                var selectedIndex = analogUnitsListBox.SelectedIndex;
                SelectedUnits = (Units)selectedIndex;
                ShowSelectedItem();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void digitalUnitsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (digitalUnitsListBox.SelectedIndex == -1 ||
                digitalUnitsListBox.SelectedIndex == (SelectedUnits - Units.DigitalUnused))
            {
                return;
            }

            try
            {
                if (analogUnitsListBox.SelectedIndex != -1)
                    analogUnitsListBox.SelectedIndex = -1;

                var selectedIndex = digitalUnitsListBox.SelectedIndex;
                SelectedUnits = (Units.DigitalUnused + selectedIndex);
                ShowSelectedItem();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void numberTextBox_TextChanged(object sender, EventArgs e)
        {
            var text = numberTextBox.Text;

            int number;
            IsValidated = int.TryParse(text, out number);
            if (IsValidated)
            {
                //Valid only for correct values with name
                try
                {
                    var units = ToUnits(number);
                    units.GetOffOnName(CustomUnits);
                    SelectedUnits = units;
                    ShowSelectedItem();
                }
                catch (Exception)
                {
                    IsValidated = false;
                }
            }

            numberTextBox.BackColor = ColorConstants.GetValidationColor(IsValidated);
        }
    }
}
