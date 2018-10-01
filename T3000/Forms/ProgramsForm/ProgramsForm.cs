namespace T3000.Forms
{
    using PRGReaderLibrary;
    using PRGReaderLibrary.Extensions;
    using PRGReaderLibrary.Types.Enums.Codecs;
    using PRGReaderLibrary.Utilities;
    using Properties;
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class ProgramsForm : Form
    {
        public List<ProgramPoint> Points { get; set; }
        public List<ProgramCode> Codes { get; set; }
        public DataGridView Progs { get; set; }

        private Prg _prg;
        public Prg Prg
        {
            get { return _prg; }

            set { _prg = value; }
        }

        public string PrgPath { get; private set; }


        public ProgramsForm(ref Prg CurPRG, string Path)
        {
            Prg = CurPRG;
            PrgPath = Path;

            SetView(Prg.Programs, Prg.ProgramCodes);

        }


        public void SetView(List<ProgramPoint> points, List<ProgramCode> codes)
        {
            if (points == null)
            {
                throw new ArgumentNullException(nameof(points));
            }

            Points = points;
            Codes = codes;

            InitializeComponent();

            //User input handles
            view.AddEditHandler(StatusColumn, TViewUtilities.EditEnum<OffOn>);
            view.AddEditHandler(AutoManualColumn, TViewUtilities.EditEnum<AutoManual>);
            view.AddEditHandler(RunStatusColumn, TViewUtilities.EditEnum<NormalCom>);
            view.AddEditHandler(CodeColumn, EditCodeColumn);

            //Value changed handles
            view.AddChangedHandler(StatusColumn, TViewUtilities.ChangeColor,
                Color.Red, Color.Blue);

            //Show points
            view.Rows.Clear();
            view.Rows.Add(Points.Count);
            for (var i = 0; i < Points.Count; ++i)
            {
                var point = Points[i];
                var row = view.Rows[i];

                //Read only
                row.SetValue(NumberColumn, i + 1);

                SetRow(row, point);
            }

            //Validation
            view.AddValidation(DescriptionColumn, TViewUtilities.ValidateString, 21);
            view.AddValidation(LabelColumn, TViewUtilities.ValidateString, 9);
            view.Validate();

            Progs = view;
        }


        private void SetRow(DataGridViewRow row, ProgramPoint point)
        {
            if (row == null || point == null)
            {
                return;
            }

            row.SetValue(DescriptionColumn, point.Description);
            row.SetValue(StatusColumn, point.Control);
            row.SetValue(AutoManualColumn, point.AutoManual);
            row.SetValue(SizeColumn, point.Length);
            row.SetValue(RunStatusColumn, point.NormalCom);
            row.SetValue(LabelColumn, point.Label);
        }

        #region Buttons

        private void ClearSelectedRow(object sender, EventArgs e) =>
            SetRow(view.CurrentRow, new ProgramPoint());

        private void Save(object sender, EventArgs e)
        {
            if (!view.Validate())
            {
                MessageBoxUtilities.ShowWarning(Resources.ViewNotValidated);
                DialogResult = DialogResult.None;
                return;
            }

            try
            {
                for (var i = 0; i < view.RowCount && i < Points.Count; ++i)
                {
                    var point = Points[i];
                    var row = view.Rows[i];
                    point.Description = row.GetValue<string>(DescriptionColumn);
                    point.Control = row.GetValue<OffOn>(StatusColumn);
                    point.NormalCom = row.GetValue<NormalCom>(RunStatusColumn);
                    point.AutoManual = row.GetValue<AutoManual>(AutoManualColumn);
                    point.Length = row.GetValue<int>(SizeColumn);
                    point.Label = row.GetValue<string>(LabelColumn);


                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
                DialogResult = DialogResult.None;
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }

        public void ExternalSaveAutomanual(int pos, DataGridViewRow erow)
        {
            try
            {
                for (var i = 0; i < view.RowCount && i < Points.Count; ++i)
                {
                    var point = Points[i];
                    var row = erow;
                    if (i == pos)
                    {
                        point.AutoManual = ((AutoManual)row.Cells[3].Value);

                    }


                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);

            }
        }
        public void ExternalSaveValue(int pos, DataGridViewRow erow)
        {
            try
            {
                for (var i = 0; i < view.RowCount && i < Points.Count; ++i)
                {
                    var point = Points[i];
                    var row = erow;
                    if (i == pos)
                    {
                        point.Control = ((OffOn)row.Cells[2].Value);

                    }


                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);

            }
        }

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region User input handles

        int Index_EditProgramCode;

        private void EditCodeColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                Index_EditProgramCode = row.GetValue<int>(NumberColumn) - 1;

                var form = new ProgramEditorForm();
                form.Caption = $"Edit Code: Panel 1 - Program {Index_EditProgramCode } - Label {Prg.Programs[Index_EditProgramCode].Description}";

                Console.WriteLine("--------------ORIGINAL CODE-------------------");
                ConsolePrintBytes(Codes[Index_EditProgramCode].Code, "Original");
                form.SetCode(Codes[Index_EditProgramCode].ToString());


                #region Create local copy of identifiers from control points
                foreach (var vars in Prg.Variables)
                    form.Identifiers.Add(vars.Label);
                foreach (var ins in Prg.Inputs)
                    form.Identifiers.Add(ins.Label, IdentifierTypes.INS);
                foreach (var outs in Prg.Outputs)
                    form.Identifiers.Add(outs.Label, IdentifierTypes.OUTS);
                foreach (var prgs in Prg.Programs)
                    form.Identifiers.Add(prgs.Label, IdentifierTypes.PRGS);
                foreach (var schs in Prg.Schedules)
                    form.Identifiers.Add(schs.Label, IdentifierTypes.SCHS);
                foreach (var hols in Prg.Holidays)
                    form.Identifiers.Add(hols.Label, IdentifierTypes.HOLS);

                #endregion


                //Override Send Event Handler and encode program into bytes.
                form.Send += Form_Send;
                form.MdiParent = this.MdiParent;

                form.Show();
                //if (form.ShowDialog() != DialogResult.OK) return;

            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void Form_Send(object sender, SendEventArgs e)
        {

            Console.WriteLine();
            Console.WriteLine("---------------------DEBUG STRINGS-----------------------");
            Console.WriteLine();
            Console.WriteLine($"Code:{Environment.NewLine}{e.Code}");
            Console.WriteLine($"Tokens:{Environment.NewLine}{e.ToString()}");


            //Inician las pruebas de codificación
            byte[] ByteEncoded = EncodeBytes(e.Tokens);
            var PSize = BitConverter.ToInt16(ByteEncoded, 0);
            ConsolePrintBytes(ByteEncoded, "Encoded");
            MessageBox.Show($"Resource compiled succceded{System.Environment.NewLine}Total size 2000 bytes{System.Environment.NewLine}Already used {PSize} bytes.", "T3000");

            // MessageBox.Show(Encoding.UTF8.GetString(ByteEncoded), "Tokens");
            Prg.ProgramCodes[Index_EditProgramCode].Code = ByteEncoded;
            //The need of this code, means that constructor must accept byte array and fill with nulls to needSize value
            Prg.ProgramCodes[Index_EditProgramCode].Count = 2000;
            Prg.Programs[Index_EditProgramCode].Length = PSize;
            //Also that save, must recalculate and save the lenght in bytes of every programcode into program.lenght
            //Prg.Save($"{PrgPath.Substring(0,PrgPath.Length-4)}.PRG");


        }




        /// <summary>
        /// Encode a ProgramCode Into Byte Array
        /// </summary>
        /// <param name="Tokens">Preprocessed list of tokens</param>
        /// <returns>byte array</returns>
        private byte[] EncodeBytes(List<EditorTokenInfo> Tokens)
        {
            var result = new List<byte>();
            byte[] prgsize = { (byte)0x00, (byte)0x00 };
            result.AddRange(prgsize);

            Stack<int> offsets = new Stack<int>();
            Stack<EditorJumpInfo> Jumps = new Stack<EditorJumpInfo>();
            List<EditorLineInfo> Lines = new List<EditorLineInfo>();

            int offset = 1; //offset is a count of total encoded bytes



            int tokenIndex = 0;
            bool isFirstToken = true;


            for (tokenIndex = 0; tokenIndex < Tokens.Count; tokenIndex++)
            {
                var token = Tokens[tokenIndex];

                switch (token.TerminalName)
                {
                    #region IF IF+ IF- THEN ELSE
                    case "IF":
                    case "IF+":
                    case "IF-":
                    case "THEN":
                    case "ELSE":
                    case "EOE":
                        result.Add((byte)token.Token);
                        offset++;

                        if (token.Token == (short)LINE_TOKEN.EOE)
                        {
                            if (offsets.Count > 0)
                            {
                                int newoffset = offset + 1;
                                int idxoffset = offsets.Pop();
                                //encode and replace
                                short NewOffSetNumber = Convert.ToInt16(newoffset);
                                byte[] byteoffset = NewOffSetNumber.ToBytes();
                                result[idxoffset] = byteoffset[0];
                                result[idxoffset + 1] = byteoffset[1];

                            }
                        }

                        break;


                    #endregion

                    #region REM COMMENTS
                    case "REM":
                    case "ASSIGN":

                        result.Add((byte)token.Token);
                        offset++;
                        break;
                    case "Comment":
                    case "PhoneNumber":
                        result.Add((byte)token.Type); //Lenght of String
                        offset++;
                        result.AddRange(token.Text.ToBytes());
                        offset += token.Type;
                        break;
                    #endregion

                    #region Special Numbers
                    case "LineNumber":
                        if (isFirstToken)
                        {
                            result.Add((byte)TYPE_TOKEN.NUMBER); //TYPE OF NEXT TOKEN: NUMBER 1 Byte
                            short LineNumber = Convert.ToInt16(token.Text);
                            result.AddRange(LineNumber.ToBytes()); //LINE NUMBER, 2 Bytes
                            Lines.Add(new EditorLineInfo(Convert.ToInt32(LineNumber), Convert.ToInt32(offset + 1)));
                            offset += 3;
                            isFirstToken = false;
                        }
                        else
                        {
                            //else: linenumber for a jump

                            short LineNumber = Convert.ToInt16(token.Text);
                            byte[] RawLineNumber = LineNumber.ToBytes();
                            RawLineNumber[1] = (byte)LINE_TOKEN.RAWLINE;
                            RawLineNumber[0] = (byte)LINE_TOKEN.RAWLINE;
                            result.AddRange(RawLineNumber);
                            Jumps.Push(new EditorJumpInfo(0, LineNumber, offset + 1));
                            offset += 2;

                        }


                        break;

                    case "OFFSET":
                        //push index of next byte for new offset.
                        offsets.Push(offset + 1);
                        short OffSetNumber = Convert.ToInt16(token.Token);
                        result.AddRange(OffSetNumber.ToBytes()); //OFFSET NUMBER, 2 Bytes
                        offset += 2;

                        break;

                    //Index and Counters: 1 Byte
                    case "ARGCOUNT":
                    case "SYSPRG":
                    case "PRG":
                    case "PANEL":

                        short IdentCount = Convert.ToInt16(token.Index);
                        byte[] bytesIdentCount = IdentCount.ToBytes();
                        result.Add(bytesIdentCount[0]); //OFFSET NUMBER, 1 Bytes
                        offset += 1;

                        break;

                    case "PRT_A":
                    case "PRT_B":
                    case "PRT_0":
                    case "ALL":
                        short prt = Convert.ToInt16(token.Token);
                        byte[] bytesPrt = prt.ToBytes();
                        result.Add(bytesPrt[0]); //OFFSET NUMBER, 1 Bytes
                        offset += 1;
                        break;

                    case "WAITCOUNTER":
                        result.Add((byte)token.Token);
                        offset++;
                        int WaitCounter = Convert.ToInt32(token.Index);
                        result.AddRange(WaitCounter.ToBytes()); //OFFSET NUMBER, 4 Bytes
                        offset += 4;

                        break;
                    #endregion

                    #region Operators, Functions and Commands
                    //OPERATORS
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
                    //FUNCTIONS
                    case "ABS":
                    case "INTERVAL":
                    case "_INT":
                    case "LN":
                    case "LN_1":
                    case "SQR":
                    case "_Status":
                    case "CONPROP":
                    case "CONRATE":
                    case "CONRESET":
                    case "TBL":
                    case "TIME":
                    case "TIME_ON":
                    case "TIME_OFF":
                    case "WR_ON":
                    case "WR_OFF":
                    case "DOY":
                    case "DOM":
                    case "DOW":
                    case "POWER_LOSS":
                    case "UNACK":
                    case "SCANS":
                    case "USER_A":
                    case "USER_B":

                    //COMMANDS
                    case "START":
                    case "STOP":
                    case "CLEAR":
                    case "RETURN":
                    case "WAIT":
                    case "HANGUP":
                    case "GOTO":
                    case "GOSUB":
                    case "ON_ERROR":
                    case "ON_ALARM":
                    case "ENABLEX":
                    case "DISABLEX":
                    case "ENDPRG":
                    case "RUN_MACRO":
                    case "CALL":
                    case "SET_PRINTER":
                    case "DECLARE":
                    case "PRINT_AT":
                    case "ALARM_AT":
                    case "PHONE":


                        result.Add((byte)token.Token);
                        offset++;
                        break;




                    //Functions with variable list of expressions, must add count of expressions as last token.
                    case "AVG":
                    case "MAX":
                    case "MIN":

                        result.Add((byte)token.Token);
                        result.Add((byte)token.Index);
                        offset += 2;
                        break;

                    case "NOT":
                        //TODO: Learn how to encode NOT operator -> tests and errors.
                        break;
                    #endregion

                    #region Identifiers: VARS, INS, OUTS, etc 3 bytes
                    case "Identifier":
                        //Encode directly: Token + Index + Type

                        result.Add((byte)token.Token);
                        result.Add((byte)token.Index);
                        result.Add((byte)token.Type);
                        offset += 3;

                        break;

                    #endregion

                    #region NUMBERS (4 BYTES ONLY)
                    case "Number":
                    case "CONNUMBER":
                    case "TABLENUMBER":
                    case "TIMER":


                        result.Add((byte)token.Token);
                        offset++;
                        //And... voilá...  trick revealed.
                        //All numbers are converted to integer 32b, multiplying by 1000.
                        //on Decoding bytes: reverse operation dividing by 1000, so if not exact
                        //floating point numbers only have 3 decimals
                        int numVal = (int)(Convert.ToSingle(token.Text) * 1000);
                        byte[] byteArray = BitConverter.GetBytes(numVal);
                        result.AddRange(byteArray);
                        offset += 4;
                        break;
                    #endregion

                    case "LF":
                        isFirstToken = true;

                        break;

                    case "EOF":
                        if ((tokenIndex + 1) == Tokens.Count)
                        {
                            //EOF: Last LF, should be replaced with xFE
                            result.Add((byte)LINE_TOKEN.EOF);
                            //No increment to offset, as EOF doesn't count on 
                        }

                        //EOL: LF, Just Ignored. Next Token should be another LineNumber
                        break;



                    default:
                        Console.WriteLine($"Token ignored and not encoded: {token.ToString()}");
                        break;

                }
                isFirstToken = token.TerminalName == "LF" ? true : false;

            }

            //Set Jumps offsets
            if (Jumps.Count > 0 && Lines.Count > 0)
            {
                while (Jumps.Count > 0)
                {
                    EditorJumpInfo NewJump = Jumps.Pop();
                    var LineIdx = Lines.FindIndex(k => k.Before == NewJump.LineIndex);
                    if (LineIdx >= 0)
                    {
                        short LineOffset = Convert.ToInt16(Lines[LineIdx].After);
                        byte[] LObytes = LineOffset.ToBytes();
                        result[NewJump.Offset] = LObytes[0];
                        result[NewJump.Offset + 1] = LObytes[1];

                    }
                    else //LineIdx is -1, not found!
                    {
                        MessageBox.Show($"Error: Line not found: {NewJump.LineIndex}");
                    }

                }

            }


            offset--;
            byte[] size = offset.ToBytes();
            result[0] = size[0];
            result[1] = size[1];

            //fill with nulls til the end of block
            while (result.Count < 2000)
            {
                result.Add((byte)0x00);
            }
            return result.ToArray();
        }




        #endregion


        /// <summary>
        /// Prints a byte array
        /// </summary>
        /// <param name="ByteEncoded">Byte array to print</param>
        /// <param name="HeaderString">Optional Header string</param>
        void ConsolePrintBytes(byte[] ByteEncoded, string HeaderString = "")
        {
            var PSize = BitConverter.ToInt16(ByteEncoded, 0);
            Console.Write(HeaderString);
            Console.Write(" Bytes = { ");
            for (var i = 0; i < PSize + 3; i++)
            {
                Console.Write($"{ByteEncoded[i]} ");

            }
            Console.WriteLine("}");
        }

    }

}