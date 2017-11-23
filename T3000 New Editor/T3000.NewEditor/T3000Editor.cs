using System;
using System.Windows.Forms;
using Irony.Parsing;
using T3000.Forms;

namespace T3000.NewEditor
{
    /// <summary>
    /// Defines new Editor for Code Control Basic
    /// </summary>
    public partial class T3000Editor : UserControl, IProgramEditor
    {
         ProgramEditorForm _pc = new ProgramEditorForm();

        /// <summary>
        /// Default constructor
        /// </summary>
        public T3000Editor()
        {
            InitializeComponent();
            Dock = DockStyle.Fill;

            editTextBox.Grammar = new T3000Grammar();
            editTextBox.SetParser(new LanguageData(editTextBox.Grammar));
            
        }

        /// <summary>
        /// Set Code (plain text) for editTextBox
        /// </summary>
        /// <param name="code">plain text ControlBasic code</param>
        public void SetCode(string code)
        {
            _pc.SetCode(code);
            editTextBox.Text = code;
        }

        private void cmdSettings_Click(object sender, EventArgs e)
        {
            EditSettings();
            
        }

        private void EditSettings()
        {
            
            SettingsBag.SelectedObject = editTextBox;
            SettingsBag.Top = editTextBox.Top;
            SettingsBag.Height = editTextBox.Height;
            SettingsBag.Left = editTextBox.Width - SettingsBag.Width;

            SettingsBag.Visible = !SettingsBag.Visible;

        }

    }
}
