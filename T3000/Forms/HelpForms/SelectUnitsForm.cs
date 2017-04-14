namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Linq;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class SelectUnitsForm : Form
    {
        public Unit SelectedUnit { get; private set; } = Unit.Unused;
        public bool IsValidated { get; private set; } = true;
        public CustomUnits CustomUnits { get; set; } = null;
        public Func<Unit, bool> AnalogPredicate { get; private set; }
        public Dictionary<Unit, UnitsNames> AnalogDictionary { get; private set; }

        public SelectUnitsForm(
            Unit selectedUnit = Unit.Unused, 
            CustomUnits customUnits = null, 
            Func<Unit, bool> analogPredicate = null)
        {
            InitializeComponent();

            SelectedUnit = selectedUnit;
            CustomUnits = customUnits;
            AnalogPredicate = analogPredicate;

            UpdateUnits();
        }

        private List<Unit> NumberedUnits = new List<Unit>();

        private int ToNumber(Unit unit)
        {
            if (!NumberedUnits.Contains(unit))
            {
                NumberedUnits.Add(unit);
            }
            
            return NumberedUnits.IndexOf(unit) + 1;
        }

        private Unit ToUnits(int number) =>
            NumberedUnits[number - 1];

        public void UpdateUnits()
        {
            try
            {
                analogUnitsListBox.Items.Clear();
                AnalogDictionary = UnitsNamesUtilities.GetNames(CustomUnits);
                if (AnalogPredicate != null)
                {
                    AnalogDictionary = AnalogDictionary
                        .Where(pair => AnalogPredicate(pair.Key))
                        .ToDictionary(pair => pair.Key, pair => pair.Value);
                }
                foreach (var name in AnalogDictionary)
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
                    SelectedUnit = SelectedUnit.PrevValue();
                    ShowSelectedItem();
                    break;

                case Keys.S:
                case Keys.Down:
                case Keys.PageDown:
                case Keys.VolumeDown:
                    SelectedUnit = SelectedUnit.NextValue();
                    ShowSelectedItem();
                    break;

                case Keys.Left:
                case Keys.A:
                    for (var i = 0; i < maxItemsInColumn; ++i)
                    {
                        SelectedUnit = SelectedUnit.PrevValue();
                    }
                    ShowSelectedItem();
                    break;

                case Keys.Right:
                case Keys.D:
                    for (var i = 0; i < maxItemsInColumn; ++i)
                    {
                        SelectedUnit = SelectedUnit.NextValue();
                    }
                    ShowSelectedItem();
                    break;
            }
        }

        public void ShowSelectedItem()
        {
            numberTextBox.Text = ToNumber(SelectedUnit).ToString();
            messageLabel.Text = string.Format(Resources.SelectUnitsFormSelectedUnits, SelectedUnit.GetOffOnName(CustomUnits));
            if (SelectedUnit.IsAnalog())
            {
                analogUnitsListBox.SelectedIndex = ToNumber(SelectedUnit) - 1;
                digitalUnitsListBox.SelectedIndex = -1;
            }
            else
            {
                digitalUnitsListBox.SelectedIndex = SelectedUnit - Unit.DigitalUnused;
                analogUnitsListBox.SelectedIndex = -1;
            }
        }

        private void analogUnitsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (analogUnitsListBox.SelectedIndex == -1 ||
                analogUnitsListBox.SelectedIndex == (int)SelectedUnit)
            {
                return;
            }

            try
            {
                if (digitalUnitsListBox.SelectedIndex != -1)
                    digitalUnitsListBox.SelectedIndex = -1;

                var selectedIndex = analogUnitsListBox.SelectedIndex;
                SelectedUnit = ToUnits(selectedIndex + 1);
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
                digitalUnitsListBox.SelectedIndex == (SelectedUnit - Unit.DigitalUnused))
            {
                return;
            }

            try
            {
                if (analogUnitsListBox.SelectedIndex != -1)
                    analogUnitsListBox.SelectedIndex = -1;

                var selectedIndex = digitalUnitsListBox.SelectedIndex;
                SelectedUnit = (Unit.DigitalUnused + selectedIndex);
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
                    SelectedUnit = units;
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
