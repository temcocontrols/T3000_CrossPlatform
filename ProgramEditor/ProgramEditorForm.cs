namespace T3000.Forms
{
    using FastColoredTextBoxNS;
    using System;
    using System.Linq;
    using System.Collections.Generic;
    using System.Windows.Forms;
    using Irony.Parsing;


    public partial class ProgramEditorForm : Form
    {
        public string Code { get; set; }
        Grammar _grammar;
        LanguageData _language;
        Parser _parser;

        public ProgramEditorForm()
        {
            InitializeComponent();

            editTextBox.Grammar = new T3000Grammar();
            //LRUIZ :: Enable a new set of grammar, language and parser, to get Program Code Errors
            _grammar = new T3000Grammar();
            _language = new LanguageData(_grammar);
            _parser = new Parser(_language);
            //LRUIZ

            var items = new List<AutocompleteItem>();
            var keywords = new List<string>()
            {
                "REM",
                "IF",
                "IF-",
                "IF+",
                "THEN",
                "ELSE",
                "TIME-ON"
            };
            keywords.AddRange(T3000Grammar.Functions);

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
            //autocompleteMenu.Items.SetAutocompleteItems(items);
        }

        public ProgramEditorForm(string code) : this()
        {
            SetCode(code);
        }

        private string RemoveInitialNumbers(string text)
        {
            var lines = text.ToLines();
            for (var i = 0; i < lines.Count; ++i)
            {
                var words = lines[i].Split(' ');
                if (words.Length < 2)
                {
                    continue;
                }

                words = words.Skip(1).ToArray();
                lines[i] = string.Join(' '.ToString(), words);
            }

            return string.Join(Environment.NewLine, lines);
        }

        private string AddInitialNumbers(string text)
        {
            var lines = text.ToLines();
            for (var i = 0; i < lines.Count; ++i)
            {
                lines[i] = $"{(i + 1) * 10} {lines[i]}";
            }

            return string.Join(Environment.NewLine, lines);
        }

        private void SetCode(string code)
        {
            Code = code;
            //editTextBox.Text = RemoveInitialNumbers(code);
            editTextBox.Text = Code;
            

            
        }


        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            try
            {
                Code = AddInitialNumbers(editTextBox.Text);
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

        private void cmdClear_Click(object sender, EventArgs e)
        {
            SetCode("");
        }



    }
}