namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using System;
    using System.Linq;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;

    public partial class ChangeCustomUnitsForm : Form
    {
        public static string Separator { get; } = "/";

        public List<UnitsNames> Names { get; private set; } = new List<UnitsNames>();
        public bool IsValidated { get; private set; } = false;

        public ChangeCustomUnitsForm()
        {
            InitializeComponent();
        }

        private void Preview(string text)
        {
            previewListBox.Items.Clear();
            previewListBox.Items.AddRange(GetNames(text).Select(i => i.OffOnName).ToArray());
        }

        private static string[] ToLines(string text) => 
            text.Split(Environment.NewLine.ToCharArray());

        /// <summary>
        /// Returns items list of valid lines
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        private static List<UnitsNames> GetNames(string text)
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

                names.Add(new UnitsNames(line));
            }

            return names;
        }

        private void Validate(object sender, EventArgs e)
        {
            IsValidated = true;

            var text = customUnitsTextBox.Text;
            var lines = ToLines(text);
            foreach (var line in lines)
            {
                if (string.IsNullOrWhiteSpace(line))
                {
                    continue;
                }
                
                if (!UnitsNames.ValidateSeparatoredString(line, Separator))
                {
                    IsValidated = false;
                    break;
                }
            }

            customUnitsTextBox.BackColor = IsValidated ? Color.LightGreen : Color.MistyRose;
            Preview(text);
        }

        private void Save(object sender, EventArgs e)
        {
            if (!IsValidated)
            {
                MessageBoxUtilities.ShowWarning(Resources.ChangeCustomUnitsNotValid);
                return;
            }

            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }
    }
}
