namespace T3000.Forms
{
    using FastColoredTextBoxNS;
    using System;
    using System.Collections.Generic;
    using System.Windows.Forms;

    public partial class ProgramEditorForm : Form
    {
        public string Code { get; set; }

        public ProgramEditorForm(string code)
        {
            InitializeComponent();

            Code = code;

            editTextBox.Grammar = new T3000Grammar();
            editTextBox.Text = Code;

            var items = new List<AutocompleteItem>();
            var keywords = new[]
            {
                "REM",
                "IF"
            };
            foreach (var item in keywords)
                items.Add(new AutocompleteItem(item) { ImageIndex = 1 });

            var snippets = new[]{ 
                "if(^)\n{\n}", 
                "if(^)\n{\n}\nelse\n{\n}",
                "for(^;;)\n{\n}", "while(^)\n{\n}",
                "do${\n^}while();",
                "switch(^)\n{\n\tcase : break;\n}"
            };
            foreach (var item in snippets)
                items.Add(new SnippetAutocompleteItem(item) { ImageIndex = 1 });

            //set as autocomplete source
            autocompleteMenu.Items.SetAutocompleteItems(items);
        }


        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            try
            {
                Code = editTextBox.Text;
            }
            catch (Exception)// exception)
            {
                //MessageBoxUtilities.ShowException(exception);
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
