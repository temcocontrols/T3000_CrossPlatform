namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;
    
    public partial class EditCustomUnitsForm : Form
    {
        public static string Separator { get; } = "/";

        public CustomUnits CustomUnits { get; private set; }
        public bool IsValidated { get; private set; } = true;

        public EditCustomUnitsForm(CustomUnits customUnits)
        {
            InitializeComponent();

            CustomUnits = (CustomUnits)customUnits.Clone();

            //Clear selection
            digitalListBox.SelectedIndexChanged +=
                (sender, args) =>
                {
                    if (digitalListBox.SelectedIndex != -1)
                    {
                        analogListBox.SelectedIndex = -1;
                    }
                };

            analogListBox.SelectedIndexChanged +=
                (sender, args) =>
                {
                    if (analogListBox.SelectedIndex != -1)
                    {
                        digitalListBox.SelectedIndex = -1;
                    }
                };

            Preview();
        }

        private void Preview()
        {
            analogListBox.Items.Clear();
            var i = 0;
            foreach (var name in CustomUnits.Analog)
            {
                analogListBox.Items.Add($"{i + 1}. {name.Name}");
                ++i;
            }

            digitalListBox.Items.Clear();
            i = 0;
            foreach (var name in CustomUnits.Digital)
            {
                digitalListBox.Items.Add($"{i + 1}. {name.DigitalUnitsOff}/{name.DigitalUnitsOn}");
                ++i;
            }

        }

        #region Buttons

        private void Edit(object sender, EventArgs e)
        {
            var selectedIndex = analogListBox.SelectedIndex;
            if (selectedIndex >= 0 && selectedIndex < CustomUnits.Analog.Count)
            {
                var point = CustomUnits.Analog[selectedIndex];
                var form = new EditCustomAnalogUnitForm(point);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                CustomUnits.Analog[selectedIndex] = form.Point;
            }

            selectedIndex = digitalListBox.SelectedIndex;
            if (selectedIndex >= 0 && selectedIndex < CustomUnits.Digital.Count)
            {
                var point = CustomUnits.Digital[selectedIndex];
                var form = new EditCustomDigitalUnitForm(point);
                if (form.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                CustomUnits.Digital[selectedIndex] = form.Point;
            }

            Preview();
        }

        private void Save(object sender, EventArgs e)
        {
            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        #endregion
    }
}
