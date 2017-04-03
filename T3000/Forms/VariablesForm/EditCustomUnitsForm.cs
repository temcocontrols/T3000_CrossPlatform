namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class EditCustomUnitsForm : Form
    {
        public static string Separator { get; } = "/";

        public List<CustomUnitPoint> CustomUnits { get; private set; }
        public bool IsValidated { get; private set; } = true;

        public EditCustomUnitsForm(List<CustomUnitPoint> customUnits)
        {
            InitializeComponent();

            CustomUnits = customUnits;
            customUnitsTextBox.Text = ToText(CustomUnits);

            Validate(this, EventArgs.Empty);
        }

        private void Preview(string text)
        {
            previewListBox.Items.Clear();
            var i = 0;
            foreach (var name in ToUnitsNames(text))
            {
                previewListBox.Items.Add($"{i + 1}. {name.OffOnName}");
                ++i;
            }
        }

        private static string[] ToLines(string text) => 
            text.Split(Environment.NewLine.ToCharArray());

        /// <summary>
        /// Returns items list of valid lines
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        private static List<UnitsNames> ToUnitsNames(string text)
        {
            var names = new List<UnitsNames>();

            var lines = ToLines(text);
            foreach (var line in lines)
            {
                if (string.IsNullOrWhiteSpace(line) ||
                    !UnitsNames.ValidateSeparatoredString(line, Separator))
                {
                    continue;
                }

                names.Add(new UnitsNames(line, Separator));
            }

            return names;
        }

        public static string ToText(List<CustomUnitPoint> customUnits)
        {
            if (customUnits == null)
            {
                return string.Empty;
            }

            var text = string.Empty;
            foreach (var unit in customUnits)
            {
                if (unit.IsEmpty)
                {
                    continue;
                }

                text += $"{unit.DigitalUnitsOff}{Separator}{unit.DigitalUnitsOn}{Environment.NewLine}";
            }

            return text;
        }

        public static List<CustomUnitPoint> ToCustomUnits(string text)
        {
            var units = new List<CustomUnitPoint>();
            var names = ToUnitsNames(text);
            foreach (var name in names)
            {
                units.Add(new CustomUnitPoint(false, name.OffName, name.OnName));
            }

            return units;
        }

        public static bool IsValid(string text)
        {
            var lines = ToLines(text);
            foreach (var line in lines)
            {
                if (string.IsNullOrWhiteSpace(line))
                {
                    continue;
                }

                if (!UnitsNames.ValidateSeparatoredString(line, Separator))
                {
                    return false;
                }
            }

            return true;
        }

        private void Validate(object sender, EventArgs e)
        {
            var text = customUnitsTextBox.Text;
            IsValidated = IsValid(text);
            customUnitsTextBox.BackColor = IsValidated ? Color.LightGreen : Color.MistyRose;
            Preview(text);
        }

        private void Save(object sender, EventArgs e)
        {
            if (!IsValidated)
            {
                MessageBoxUtilities.ShowWarning(Resources.EditCustomUnitsFormNotValid);
                DialogResult = DialogResult.None;
                return;
            }

            var text = customUnitsTextBox.Text;
            CustomUnits = ToCustomUnits(text);

            DialogResult = DialogResult.OK;
            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }
    }
}
