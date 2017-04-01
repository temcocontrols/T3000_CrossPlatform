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
        public List<UnitsElement> CustomUnits { get; set; } = null;

        public SelectUnitsForm(Units selectedUnits = Units.Unused, List<UnitsElement> customUnits = null)
        {
            InitializeComponent();

            SelectedUnits = selectedUnits;
            CustomUnits = customUnits;
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
                foreach (var name in UnitsNamesConstants.GetAnalogNames(CustomUnits))
                {
                    analogUnitsListBox.Items.Add($"{ToNumber(name.Key)}. {name.Value.OffOnName}");
                }

                digitalUnitsListBox.Items.Clear();
                foreach (var name in UnitsNamesConstants.GetDigitalNames(CustomUnits))
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
            if (e.KeyCode == Keys.Enter)
            {
                Save(sender, e);
            }
        }

        private void ShowSelectedItem()
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

            numberTextBox.BackColor = IsValidated ? Color.LightGreen : Color.MistyRose;
        }
    }
}
