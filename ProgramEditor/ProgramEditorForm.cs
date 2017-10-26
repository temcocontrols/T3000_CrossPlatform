namespace T3000.Forms
{
    using FastColoredTextBoxNS;
    using Irony;
    using Irony.Parsing;
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Forms;
    using PRGReaderLibrary;
    using PRGReaderLibrary.Types.Enums.Codecs;



    /// <summary>
    /// Delegate to event handler Send
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public delegate void SendEventHandler(object sender, SendEventArgs e);

    /// <summary>
    /// ProgramEditor Form
    /// </summary>
    public partial class ProgramEditorForm : Form
    {

        private Prg _prg;
        /// <summary>
        /// Local copy of current PRG
        /// </summary>
        public Prg Prg
        {
            get { return _prg; }

            set { _prg = value; }
        }

        /// <summary>
        /// Local copy of PrgPath
        /// </summary>
        public string PrgPath { get; set; }

        private string Code { get; set; }


        List<TokenInfo> Tokens = new List<TokenInfo>();

        int ParsingTimes = 0;

        /// <summary>
        /// Form caption
        /// </summary>
        public string Caption
        {
            get { return this.Text; }
            set { this.Text = value; }
        }

        

        Grammar _grammar;
        LanguageData _language;
        ParseTree _parseTree;
        Parser _parser;
        

        //Container of all line numbers
        List<LineInfo> Lines;
        List<JumpInfo> Jumps;
        long LastParseTime;

        /// <summary>
        /// Event Send
        /// </summary>
        public event SendEventHandler Send;

        

        /// <summary>
        /// Overridable OnSend Event Handler
        /// </summary>
        public void OnSend(SendEventArgs e)
        {

            Code = editTextBox.Text;


            if (Send != null)
            {
                Send(this,e);
            }

           
        }

        /// <summary>
        /// Default constructor of ProgramEditorForm
        /// Use: SetCode(string) to assign program code to Editor.
        /// </summary>
        public ProgramEditorForm()
        {
            InitializeComponent();

            editTextBox.Grammar = new T3000Grammar();
            editTextBox.SetParser(new LanguageData(editTextBox.Grammar));
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

            this.WindowState = FormWindowState.Maximized;

            
            
        }


        /// <summary>
        /// Get next line number
        /// </summary>
        /// <returns>new line number (string)</returns>
        string GetNextLineNumber()
        {
            
            Lines = new List<LineInfo>();
            var lines = editTextBox.Text.ToLines(StringSplitOptions.RemoveEmptyEntries);
            //Preload ALL line numbers
            for (var i = 0; i < lines.Count; i++)
            {
                var words = lines[i].Split(' ');

                var LINFO = new LineInfo(Convert.ToInt32(words[0]), (i + 1) * 10);
                this.Lines.Add(LINFO);
            }

            return (Lines.LastOrDefault().Before  + 10).ToString();

        }


        /// <summary>
        /// Try to renumber all lines and their references.
        /// Show errors as semantic ones.
        /// </summary>
        public void LinesValidator()
        {
            
            if(_parseTree == null) return;

            if (_parseTree.ParserMessages.Any()) return;

            int pos = 0;
            int col = 0;
            bool Cancel = false;
            Lines = new List<LineInfo>();
            Jumps = new List<JumpInfo>();
                       

            var lines = editTextBox.Text.ToLines( StringSplitOptions.RemoveEmptyEntries);

            //Preload ALL line numbers
            for (var i = 0; i < lines.Count; i++)
            {
                var words = lines[i].Split(' ');
                
                var LINFO = new LineInfo(Convert.ToInt32(words[0]), (i + 1) * 10);
                this.Lines.Add(LINFO);
            }

            for (var i = 0; i < lines.Count; i++)
            {
                var words = lines[i].Split(' ');
                

                for(var j=0; j< words.Count(); j++)
                {
                    JumpType type = JumpType.GOTO ;
                    int linenumber = -1;
                    int offset = 0;


                    switch (words[j])
                    {
                        case "GOTO":
                        case "GOSUB":
                        case "ON-ERROR":
                        case "ON-ALARM":
                        case "THEN":

                            switch (words[j][0])
                            {
                                case 'G':
                                    type = words[j] == "GOTO" ? JumpType.GOTO : JumpType.GOSUB; break;
                                case 'O':
                                    type = words[j] == "ON-ERROR" ? JumpType.ONERROR : JumpType.ONALARM; break;
                                case 'T':
                                    type = JumpType.THEN;break;
                            }
                    

                            offset = j + 1;
                            int BeforeLineNumber = -1;
                            if (!Int32.TryParse(words[offset],out BeforeLineNumber)) break;

                            //var BeforeLineNumber = Convert.ToInt32(words[offset]);
                            linenumber = Lines.FindIndex(k => k.Before == BeforeLineNumber );
                            if(linenumber == -1)
                            {
                                //There is a semantic error here
                                //Add error message to parser and cancel renumbering.
                                //Don't break it inmediately, to show all possible errors of this type
                                _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                    new SourceLocation(pos + words[j].Count() + 1, i , col + words[j].Count()+1), 
                                    $"Semantic Error: Line number {BeforeLineNumber.ToString()} for {words[j]} does not exist", 
                                    new ParserState("Validating Lines")));
                                ShowCompilerErrors();
                                Cancel = true;
                            }
                            JumpInfo JINFO = new JumpInfo(type, i, offset );
                            Jumps.Add(JINFO);
                            //Change reference to new linenumber
                            words[offset] = linenumber == -1? BeforeLineNumber.ToString():Lines[linenumber].ToString();
                            break;
                            
                    }//switch jumps
                     pos += words[j].Count() + 1;
                    col += words[j].Count() + 1;
                }//for words
                pos++;
                col = 0;
                //change current linenumber
                words[0] = Lines[i].ToString();
                lines[i] = string.Join(' '.ToString(), words);
                

            }//for lines
            string newcode = string.Join(Environment.NewLine, lines);
            if (Cancel) return;
            editTextBox.Text = newcode;
        }


        /// <summary>
        /// Set code to EditBox, ProgramCode is automatically parsed. 
        /// </summary>
        /// <param name="code">String contaning plain text Control Basic with numbered lines {Not Bytes Encoded Programs}</param>
        public void SetCode(string code)
        {
            Code = code;
            //editTextBox.Text = RemoveInitialNumbers(code);
            
            editTextBox.Text = Code;
           
            //LRUIZ: Parse and show syntax errors

            ParseCode(false);
            
        }

        
        private void cmdClear_Click(object sender, EventArgs e)
        {
            ClearCode();
        }

        /// <summary>
        /// Clear editBox only.
        /// If you want to update/clear the inner code, use SetCode
        /// </summary>
        public void ClearCode()
        {
            //local member Code is not cleared, to allow recovering with REFRESH (F8)
            editTextBox.Text = "";
        }


        /// <summary>
        /// Override of ToString -> GetCode
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return GetCode();
        }

        /// <summary>
        /// Get current code
        /// </summary>
        /// <returns></returns>
        public string GetCode()
        {
            Code = editTextBox.Text;
            return Code;
        }

        /// <summary>
        /// Forces parsing the code contained in EditTextBox
        /// </summary>
        public void ParseCode(bool fullParsing = false)
        {
            ClearParserOutput();
            if (_parser == null || !_parser.Language.CanParse()) return;
            _parseTree = null;
            GC.Collect(); //to avoid disruption of perf times with occasional collections
            _parser.Context.TracingEnabled = true;
            try
            {
                Stopwatch stopwatch = Stopwatch.StartNew(); //creates and start the instance of Stopwatch

                _parser.Parse(editTextBox.Text, "<source>");
                _parseTree = _parser.Context.CurrentParseTree;


                if (_parseTree.ParserMessages.Any() || _parseTree.HasErrors()) return;

                if (fullParsing) //Only do this checks in full parsing.
                {
                    LinesValidator(); // Check semantic errors on jumps and renumber lines.
                    ProcessTokens(); //Check for other semantic errors and make some changes to local list of tokens

                    if (_parseTree.ParserMessages.Any() || _parseTree.HasErrors())
                    {
                        MessageBox.Show($"{_parseTree.ParserMessages.Count()} error(s) found!{Environment.NewLine}Compiler halted.", "Semantic Errors Found!");
                        return;
                    }
                }
                

                System.Threading.Thread.Sleep(500);
                stopwatch.Stop();
                LastParseTime = stopwatch.ElapsedMilliseconds - 500;
                lblParseTime.Text = $"Parse Time: {LastParseTime}ms";

            }
            catch (Exception ex)
            {
                gridCompileErrors.Rows.Add(null, ex.Message, null);
                
                //throw;
            }
            finally
            {
                
                ShowCompilerErrors();

               
                ShowCompileStats();
               
            }
        }


        private void ClearParserOutput()
        {

            lblSrcLineCount.Text = string.Empty;
            lblSrcTokenCount.Text = "";
            lblParseTime.Text = "";
            lblParseErrorCount.Text = "";

        
            gridCompileErrors.Rows.Clear();
           
            Application.DoEvents();
        }

        private void ShowCompileStats()
        {
            lblSrcLineCount.Text = $"Lines: {editTextBox.Lines.Count()} ";
            lblSrcTokenCount.Text = $"Tokens: {_parseTree.Tokens.Count()}";
            lblParseTime.Text = $"Parse Time: {LastParseTime}ms";
            lblParseErrorCount.Text = _parseTree.HasErrors() ? $"Errors: {_parseTree.ParserMessages.Count() }" : "No Errors";

        }

        /// <summary>
        /// Updates Compile Errors Gridview
        /// </summary>
        private void ShowCompilerErrors()
        {
            gridCompileErrors.Rows.Clear();
            if (_parseTree == null || _parseTree.ParserMessages.Count == 0) return;
            foreach (var err in _parseTree.ParserMessages)
                gridCompileErrors.Rows.Add(err.Location, err, err.ParserState);
        }

        /// <summary>
        /// Allows to position over token at selected error.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gridCompileErrors_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0 || e.RowIndex >= gridCompileErrors.Rows.Count) return;
            var err = gridCompileErrors.Rows[e.RowIndex].Cells[1].Value as LogMessage;
            switch (e.ColumnIndex)
            {
                case 0: //state
                case 1: //stack top
                    ShowSourcePosition(err.Location.Position, 1);
                    break;
            }//switch
        }

        /// <summary>
        /// Shows a caret in editTextBox for a selected token
        /// </summary>
        /// <param name="position"></param>
        /// <param name="length"></param>
        private void ShowSourcePosition(int position, int length)
        {
            if (position < 0) return;
            editTextBox.SelectionStart = position;
            editTextBox.SelectionLength = length;
            //editTextBox.Select(location.Position, length);
            editTextBox.DoCaretVisible();
            editTextBox.Focus();
            
        }

        /// <summary>
        /// Parse code delayed after editing program.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void editTextBox_TextChangedDelayed(object sender, TextChangedEventArgs e)
        {
            ParseCode(false);
            
        }

        private void cmdRefresh_Click(object sender, EventArgs e)
        {
            RefreshCode();
        }

        /// <summary>
        /// Refresh, reload assigned code into editBox
        /// </summary>
        public void RefreshCode()
        {
            
            editTextBox.Text = Code;
          
        }
        private void ProgramEditorForm_KeyDown(object sender, KeyEventArgs e)
        {
            
            

            switch(e.KeyCode )
            {
                case Keys.F2:
                    SendCode(); e.Handled = true; break;
                case Keys.F4:
                    ClearCode(); e.Handled = true; break;
                case Keys.F6:
                    SaveFile(); e.Handled = true; break;
                case Keys.F7:
                    LoadFile(); e.Handled = true; break;
                case Keys.F8:
                    RefreshCode(); e.Handled = true; break;
                case Keys.F10:
                    LinesValidator(); e.Handled = true; break;
                
            }//switch.
           
        }

        private void cmdLoad_Click(object sender, EventArgs e)
        {
            
            LoadFile();
           
        }

        /// <summary>
        /// Open file dialog to load a text file into editor
        /// </summary>
        public void LoadFile()
        {
            // Create an instance of the open file dialog box.
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = "Text Files (.txt)|*.txt|All Files (*.*)|*.*";
            openFileDialog1.FilterIndex = 1;

            openFileDialog1.Multiselect = true;

            // Call the ShowDialog method to show the dialog box.
            DialogResult  userClickedOK = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (userClickedOK == DialogResult.OK )
            { 
                string text = System.IO.File.ReadAllText(openFileDialog1.FileName);
                
                editTextBox.Text = text;
               
            }
        }

        private void cmdSend_Click(object sender, EventArgs e)
        {
            SendCode();
        }




        private void SendCode()
        {
            ParseCode(true); //Performs full parsing and semantic checks
            
            if(_parseTree.HasErrors() || _parseTree.ParserMessages.Any())
            {
                MessageBox.Show("Send operation, aborted", "Error(s) found");
                return;
            }

            Code = editTextBox.Text;
            OnSend(new SendEventArgs(Code,Tokens));
            
        }

        private void cmdSave_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        /// <summary>
        /// Open File dialog to save a copy of program code into a file.
        /// </summary>
        public void SaveFile()
        {
            // Create an instance of the open file dialog box.
            SaveFileDialog openFileDialog1 = new SaveFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = "Text Files (.txt)|*.txt|All Files (*.*)|*.*";
            openFileDialog1.FilterIndex = 1;

            

            // Call the ShowDialog method to show the dialog box.
            DialogResult userClickedOK = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (userClickedOK == DialogResult.OK)
            {
                System.IO.File.WriteAllText (openFileDialog1.FileName,editTextBox.Text );
               
            }
        }


        private void cmdSettings_Click(object sender, EventArgs e)
        {
            EditSettings();
        }

        private void EditSettings()
        {
            


            SettingsBag.SelectedObject = editTextBox ;
            SettingsBag.Top = editTextBox.Top;
            SettingsBag.Height = editTextBox.Height;
            SettingsBag.Left = editTextBox.Width - SettingsBag.Width;
           
            SettingsBag.Visible = !SettingsBag.Visible ;


            ////NOT WORKING: Serialize SettingsBag;
            //IFormatter formatter = new BinaryFormatter();
            //Stream stream = new FileStream("EditorSettings.bin", FileMode.Create, FileAccess.Write, FileShare.None);
            //formatter.Serialize(stream, editTextBox  );
            //stream.Close();

            

        }

        private void ProgramEditorForm_ResizeEnd(object sender, EventArgs e)
        {
            if (SettingsBag.Visible)
            {
                SettingsBag.Top = editTextBox.Top;
                SettingsBag.Height = editTextBox.Height;
                SettingsBag.Left = editTextBox.Width - SettingsBag.Width;
            }
        }

        private void ProgramEditorForm_Resize(object sender, EventArgs e)
        {
            if (SettingsBag.Visible)
            {
                SettingsBag.Top = editTextBox.Top;
                SettingsBag.Height = editTextBox.Height;
                SettingsBag.Left = editTextBox.Width - SettingsBag.Width;
            }
        }

        private void cmdRenumber_Click(object sender, EventArgs e)
        {
            LinesValidator();
        }

        /// <summary>
        /// Pre-process tokens from parser
        /// </summary>
        private void ProcessTokens()
        {
            
            string[] excludeTokens = { "CONTROL_BASIC", "LF" };
            bool isFirstToken = true;
            var Cancel = false;

            try
            {
                Tokens = new List<TokenInfo>();

                if (_parseTree == null) return;

                //foreach (var tok in _parseTree.Tokens)
                for(var idxToken = 0; idxToken < _parseTree.Tokens.Count; idxToken++)
                {
                    var tok = _parseTree.Tokens[idxToken];
                    var tokentext = tok.Text;
                    var terminalname = tok.Terminal.Name;

                    switch (tok.Terminal.Name)
                    {
                        case "Comment":
                            //split Comments into two tokens
                            Tokens.Add(new TokenInfo("REM", "REM"));
                            Tokens.Last().Type = (short)LINE_TOKEN.REM;
                            Tokens.Last().Token = (short)LINE_TOKEN.REM;
                            var commentString = tok.Text.Substring(4).TrimEnd(' ');
                            Tokens.Add(new TokenInfo(commentString, "Comment"));
                            Tokens.Last().Type = (short)commentString.Length;
                            Tokens.Last().Token = (short)LINE_TOKEN.STRING;
                            break;

                        case "IntegerNumber":
                            //rename to LineNumber only if first token on line.

                            Tokens.Add(new TokenInfo(tokentext, isFirstToken ? "LineNumber" : terminalname));
                            break;

                        case "LocalVariable":
                            TokenInfo NewLocalVar = new TokenInfo(tokentext, terminalname);
                            NewLocalVar.Type = (short)PCODE_CONST.LOCAL_VAR;
                            NewLocalVar.Token = (short)TYPE_TOKEN.IDENTIFIER;
                            Tokens.Add(NewLocalVar);
                            break;
                        case "VARS":
                        case "INS":
                        case "OUTS":
                            TokenInfo NewPointVar = new TokenInfo(tokentext, terminalname);
                            NewPointVar.Type = (short)PCODE_CONST.POINT_VAR;
                            NewPointVar.Token = (short)TYPE_TOKEN.IDENTIFIER;
                            Tokens.Add(NewPointVar);
                            break;

                        

                        case "ASSIGN":

                            TokenInfo assignToken, last;

                            var index = Tokens.Count - 1;
                            last = Tokens[index];
                            Tokens.RemoveAt(index);
                            assignToken = new TokenInfo(tokentext, terminalname);
                            assignToken.Token = (short)LINE_TOKEN.ASSIGN;
                            //insert it before assignar var.
                            Tokens.Add(assignToken);
                            Tokens.Add(last);
                            //get the expression in postfix
                            functions = new Stack<TokenInfo>();
                            Tokens.AddRange(GetExpression(ref idxToken, ref Cancel));
                            
                            break;

                        case "Identifier":
                            //Locate Identifier and Identify Token associated ControlPoint.
                            //To include this info in TokenInfo.Type and update TokenInfo.TerminalName
                            int PointIndex = 0;
                            var TokenType = GetTypeIdentifier(tokentext, out PointIndex);
                            if (TokenType == PCODE_CONST.UNDEFINED_SYMBOL)
                            {
                                //There is a semantic error here
                                //Add error message to parser and cancel renumbering.
                                //Don't break it inmediately, to show all possible errors of this type
                                _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                    tok.Location,
                                    $"Semantic Error: Undefined Identifier: {tok.Text}",
                                    new ParserState("Validating Tokens")));
                                ShowCompilerErrors();
                                Cancel = true;
                            }
                            else
                            {
                                //Prepare token identifier to encode: Token + Index + Type
                                TokenInfo NewIdentifier = new TokenInfo(tokentext, terminalname);
                                NewIdentifier.Type = (short)TYPE_TOKEN.KEYWORD;
                                NewIdentifier.Index = (short)PointIndex;
                                NewIdentifier.Token = (short)TokenType;
                                Tokens.Add(NewIdentifier);
                            }
                            break;
                        case "Number":
                            Tokens.Add(new TokenInfo(tokentext, terminalname));
                            Tokens.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                            break;

                        default:
                            Tokens.Add(new TokenInfo(tokentext, terminalname));
                            break;
                    }
                    isFirstToken = terminalname == "LF" ? true : false;

                }
            }
            catch( Exception ex) {
                MessageBox.Show(ex.Message, "ProcessTokens()");
                ex = null;
            }


        }



        /// <summary>
        /// Returns PCODE_CONST value and Index for the especified Identifier
        /// </summary>
        /// <param name="Ident">Label of Point Identifier</param>
        /// <param name="Index">Out Index of Point Identifier</param>
        /// <returns>PCODE_CONST value and Index</returns>
        PCODE_CONST GetTypeIdentifier( string Ident, out int Index)
        {
           
            string label = "";
            try
            {
                //Is VAR?
                label = Prg.Variables.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Variables.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                }
                    

                //Is IN?
                label = Prg.Inputs.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Inputs.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                } 
                    

                //Is OUT?
                label = Prg.Outputs.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Outputs.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                }
                    

                //Is PRG?
                label = Prg.Programs.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Programs.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                }
                    

                //Is SCH?
                label = Prg.Schedules.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Schedules.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                }
                   

                //Is HOL?
                label = Prg.Holidays.Find(v => v.Label == Ident).Label ?? string.Empty;
                if (!string.IsNullOrEmpty(label))
                {
                    Index = Prg.Holidays.FindIndex(v => v.Label == Ident);
                    return PCODE_CONST.LOCAL_POINT_PRG;
                }
                    
            }
            catch
            {
                Index = -1;
                return PCODE_CONST.UNDEFINED_SYMBOL;
            }

            Index = -2;
            return PCODE_CONST.UNDEFINED_SYMBOL;
            
        }


        /// <summary>
        /// Stack of recursive examined functions, counting subexpressions
        /// </summary>
        Stack<TokenInfo> functions = new Stack<TokenInfo>();

        /// <summary>
        /// Parse tokens from infix notation into postfix (RPN)
        /// </summary>
        /// <param name="Index">Start Index</param>
        /// <param name="Cancel">Cancel processing because of at least one semantic error</param>
        /// <returns>RPN Expression, ready to be encoded</returns>
        List<TokenInfo> GetExpression(ref int Index, ref bool Cancel)
        {
            // _parseTree.Tokens.Count
            List<TokenInfo> Expr = new List<TokenInfo>();
            Stack<TokenInfo> Oper = new Stack<TokenInfo>();
            
            //Last processed token was a BEGIN EXPRESSION MARKER
            Index++; //Jump over next token.

            for (; Index < _parseTree.Tokens.Count; Index++)
            {
                var tok = _parseTree.Tokens[Index];
                var tokentext = tok.Text;
                var terminalname = tok.Terminal.Name;
                

                switch (terminalname)
                {

                    #region PARENTHESIS

                    case "(":
                        //If the incoming symbol is a left parenthesis, push it on the stack.
                        Oper.Push(new TokenInfo(tokentext, terminalname));
                        break;
                    
                    case ")":
                        //	If the incoming symbol is a right parenthesis, 
                        // pop the stack and print the operators until you see a left parenthesis. 
                        // Discard the pair of parentheses.
                        if (Oper.Count > 0)
                        {
                            while (Oper.Peek().TerminalName != "(")
                            {
                                Expr.Add(Oper.Pop());
                            }
                        }
                        if(Oper.Count >0) Oper.Pop(); //Discard left parenthesis
                        //see if those parenthesis were parts of a function call.
                        if(Oper.Count > 0 && Oper.Peek().Precedence == 200 )
                        {
                            //Function Call
                            //Add function token to expression.
                            Expr.Add(Oper.Pop());
                            if (functions.Count > 0)
                            {
                                if (Expr.Last().TerminalName == functions.Peek().TerminalName)
                                {
                                    //Add the counter into Index property of token function
                                    
                                    Expr.Last().Index = functions.Peek().Index ;
                                    functions.Pop();
                                }
                               
                            }

                        }
                        break;

                    #endregion

                    case "COMMA":
                        //Add 1 to counter of subexpressions, comma means here comes another one.
                        if (functions.Count > 0) functions.Peek().Index++;
                        //Save everything down to Left Parenthesis but don't discard it
                        if (Oper.Count > 0)
                        {
                            while (Oper.Peek().TerminalName != "(")
                            {
                                Expr.Add(Oper.Pop());
                            }
                        }

                       
                        break;

                    #region END MARKERS FOR EXPRESSION
                    case "LF":
                    case "THEN":
                    case "EOF":
                    case "REM":
                   

                        //Pop all operators remaining in stack.
                        //Return expression
                        while (Oper.Count > 0)
                        {
                            Expr.Add(Oper.Pop());
                        }
                        
                        Index--; //Get back, this token should be processed by parent function.
                        return Expr;
                    #endregion

                    #region Identifier
                    case "Identifier":
                        //Locate Identifier and Identify Token associated ControlPoint.
                        //To include this info in TokenInfo.Type and update TokenInfo.TerminalName
                        int PointIndex = 0;
                        var TokenType = GetTypeIdentifier(tokentext, out PointIndex);
                        if (TokenType == PCODE_CONST.UNDEFINED_SYMBOL)
                        {
                            //There is a semantic error here
                            //Add error message to parser and cancel renumbering.
                            //Don't break it inmediately, to show all possible errors of this type
                            _parseTree.ParserMessages.Add(new LogMessage(ErrorLevel.Error,
                                tok.Location,
                                $"Semantic Error: Undefined Identifier: {tok.Text}",
                                new ParserState("Validating Tokens")));
                            ShowCompilerErrors();
                            Cancel = true;
                        }
                        else
                        {
                            //Prepare token identifier to encode: Token + Index + Type
                            TokenInfo NewIdentifier = new TokenInfo(tokentext, terminalname);
                            NewIdentifier.Type = (short)TYPE_TOKEN.KEYWORD;
                            NewIdentifier.Index = (short)PointIndex;
                            NewIdentifier.Token = (short)TokenType;
                            Expr.Add(NewIdentifier);
                        }
                        break;

                    #endregion

                    #region OPERATORS

                    case "PLUS":
                    case "MINUS":
                    case "MUL":
                    case "DIV":
                    case "POW":
                    case "MOD":
                    case "LT":
                    case "GT":
                    case "LE":
                    case "GE":
                    case "EQ":
                    case "NE":
                    case "AND":
                    case "XOR":
                    case "OR":
                    case "NOT":
                    
                        //All operators are cast directly into token of TYPE_TOKEN and with precedence attribute.
                        //To allow further transforms by RPN Parser of Expressions
                        var op= new TokenInfo(tokentext, terminalname);
                        TYPE_TOKEN TypeToken = (TYPE_TOKEN)Enum.Parse(typeof(TYPE_TOKEN), terminalname.ToString().Trim());
                        op.Token = (short)TypeToken;
                        op.Precedence = (short)tok.KeyTerm.Precedence;

                        if(Oper.Count == 0)
                        {
                            Oper.Push(op);
                        }
                        else
                        {
                            while(Oper.Count > 0 && op.Precedence <= Oper.Peek().Precedence)
                            {
                                Expr.Add(Oper.Pop());
                            }

                            Oper.Push(op);
                        }
                        break;
                    #endregion

                    #region Number
                    case "Number":
                        Expr.Add(new TokenInfo(tokentext, terminalname));
                        Expr.Last().Token = (short)PCODE_CONST.CONST_VALUE_PRG;
                        break;
                    #endregion

                    #region FUNCTIONS
                    case "ABS":
                    case "AVG":
                    case "INTERVAL":
                    case "_INT":
                    case "LN":
                    case "LN_1":
                    case "SQR":
                    case "_Status":
                    case "MAX":
                    case "MIN":
                        //All operators are cast directly into token of TYPE_TOKEN and with precedence attribute.
                        //To allow further transforms by RPN Parser of Expressions
                        var fxToken = new TokenInfo(tokentext, terminalname);
                        FUNCTION_TOKEN tokenValue = (FUNCTION_TOKEN)Enum.Parse(typeof(FUNCTION_TOKEN), terminalname.ToString().Trim());
                        fxToken.Token = (short)tokenValue;
                        
                        //fx.Precedence = (short)tok.KeyTerm.Precedence;
                        fxToken.Precedence = 200;
                        fxToken.Index = 1; //At least one expression to count
                        if (Oper.Count == 0)
                        {
                            Oper.Push(fxToken);
                            functions.Push(fxToken);

                        }
                        else
                        {
                            while (Oper.Count > 0 && fxToken.Precedence <= Oper.Peek().Precedence)
                            {
                                Expr.Add(Oper.Pop());
                            }

                            Oper.Push(fxToken);
                            functions.Push(fxToken);

                        }
                        break;

                        #endregion
                }

            }


            //Pop All operators remaining in stack.
            while (Oper.Count > 0)
            {
                Expr.Add(Oper.Pop());
            }

            //Check: If Expr.Count < 1 then semantic error found, expected Expression.


            Index-=1;
            return Expr;
        }


    }




    /// <summary>
    /// Stores values Before and After Renumbering.
    /// </summary>
    public class LineInfo
    {
        /// <summary>
        /// Line number before renumbering
        /// </summary>
        public int Before { get; set; } 
        /// <summary>
        /// Line number after renumbering
        /// </summary>
        public int After { get; set; }
        /// <summary>
        /// Default constructor of class LineInfo
        /// </summary>
        /// <param name="b">Before value</param>
        /// <param name="a">After value</param>
        public LineInfo(int b, int a) { Before = b; After = a; }
        /// <summary>
        /// LineInfo ToString() override
        /// </summary>
        /// <returns>Line number After renumbering as a string
        /// Ready to use in line number replacements</returns>
        public override string ToString()
        {
            return After.ToString();
        }
    };

    /// <summary>
    /// Enumerates type of jumping instructions:
    /// GOTO, GOSUB, ONALARM, ONERROR, THEN
    /// </summary>
    public enum JumpType { GOTO, GOSUB, ONALARM, ONERROR, THEN };

    /// <summary>
    /// Stores Jump intructions information.
    /// Helper in renumbering.
    /// </summary>
    public class JumpInfo
    {   /// <summary>
        /// Type of  Jump Instruction: GOTO, GOSUB, ONALARM, ONERROR, THEN
        /// </summary>
        public JumpType Type { get; set; } //Type of Jump
        /// <summary>
        /// Zero based index of line in list
        /// </summary>
        public int LineIndex { get; set; } //Index of Line in Lines
        /// <summary>
        /// Offset in words count from the start of every line.
        /// </summary>
        public int Offset { get; set; } //Code Offset

        /// <summary>
        /// Default constructor for a Jump Info.
        /// </summary>
        /// <param name="t">Type of Jump</param>
        /// <param name="l">Line index</param>
        /// <param name="o">Offset - Words for start of line</param>
        public JumpInfo(JumpType t, int l, int o)
        {
            Type = t;
            LineIndex = l;
            Offset = o;
        }
    };

    /// <summary>
    /// TokeInfo stores information about a single token
    /// </summary>
    public class TokenInfo
    {
        /// <summary>
        /// Original text token from parsing
        /// </summary>
        public string Text { get; set; }
        /// <summary>
        /// Associated Terminal Name from Grammar
        /// </summary>
        public string TerminalName { get; set; }
        /// <summary>
        /// Token Type (1 Byte)
        /// Token size for Comment string
        /// </summary>
        public short Type { get; set; }
        /// <summary>
        /// Token value (1 Byte)
        /// </summary>
        public short Token { get; set; }
        /// <summary>
        /// Control Point index
        /// </summary>
        public short Index { get; set; }
        /// <summary>
        /// Operators Precedence
        /// </summary>
        public short Precedence { get; set; }

        /// <summary>
        /// Default constructor: Create Basic TokenInfo from Text and Terminal Name
        /// Expected to be fulfilled with more token info
        /// </summary>
        /// <param name="Text">Plain Text tokenizable</param>
        /// <param name="TName">Terminal Name</param>
        public TokenInfo(string Text, string TName)
        {
            this.Text = Text;
            this.TerminalName = TName;
            this.Precedence = 0;
            this.Index = 0;
            this.Type = 0;
        }

        /// <summary>
        /// TokenInfo ToString Override
        /// </summary>
        /// <returns>string formatted as ·×Text×· or ·TerminalName·
        /// ·×Text· means there is no TerminalName defined
        /// </returns>
        public override string ToString()
        {
            string result = " ";
            //result     += this.Text ?? "NULL";
            //result     += "->";
            result       += this.TerminalName ?? $"×{this.Text}";
            result       += "·";
            return result;
        }

    }

}
