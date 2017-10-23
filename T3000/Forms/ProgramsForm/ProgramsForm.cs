namespace T3000.Forms
{
    using PRGReaderLibrary;
    using PRGReaderLibrary.Types.Enums.Codecs;
    using Properties;
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Text;
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


        public ProgramsForm(ref Prg  CurPRG,string Path)
        {
            Prg = CurPRG;
            PrgPath = Path;

            SetView(Prg.Programs, Prg.ProgramCodes);

        }


        public void  SetView(List<ProgramPoint> points, List<ProgramCode> codes)
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
                    if (i==pos)
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

        private int Index_EditProgramCode = 0;

        private void EditCodeColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                Index_EditProgramCode = row.GetValue<int>(NumberColumn) - 1;
                
                var form = new ProgramEditorForm();
                form.Caption = $"Edit Code: Panel 1 - Program {Index_EditProgramCode } - Label {Prg.Programs[Index_EditProgramCode].Description}";
                form.SetCode(Codes[Index_EditProgramCode].ToString());
                form.Prg = this.Prg;
                form.PrgPath = this.PrgPath;
                //Override Send Event Handler and encode program into bytes.
                form.Send += Form_Send;
                form.MdiParent = this.MdiParent ;
                
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
            //TODO: Use parse tree tokens to encode bytes and patch PRG File.
            MessageBox.Show(e.Code, "Code");
            //Utility properties to encode: e.Code, e.Tokens, e.Index, Index_EditProgramCode
            MessageBox.Show(e.ToString(), "Tokens");


            //Inician las pruebas de codificación
            byte[] ByteEncoded = EncodeBytes(e.Tokens);
            MessageBox.Show(Encoding.UTF8.GetString(ByteEncoded), "Tokens");
            Prg.ProgramCodes[Index_EditProgramCode].Code = ByteEncoded;
            //The need of this code, means that constructor must accept byte array and fill with nulls to needSize value
            Prg.ProgramCodes[Index_EditProgramCode].Count = 2000;
            Prg.Programs[Index_EditProgramCode].Length = BitConverter.ToInt16(ByteEncoded, 0);
            //Also that save, must recalculate and save the lenght in bytes of every programcode into program.lenght
            Prg.Save($"{PrgPath.Substring(0,PrgPath.Length-4)}2.PRG");
           

        }

        private byte[] EncodeBytes(List<TokenInfo> Tokens)
        {
            var result = new List<byte>();
            byte[] prgsize = { (byte) 0x00, (byte) 0x00 };
            result.AddRange(prgsize);
            
            int offset = 0;
            int tokenIndex = 0;
            bool isFirstToken = true;

            foreach (var token in Tokens)
            {
                switch(token.TerminalName)
                {
                    case "REM":
                        result.Add((byte)LINE_TOKEN.REM);
                        offset++;
                        break;
                    case "Comment":
                        token.Text = token.Text.Trim(' ');
                        var sizeNext = token.Text.Length;
                        result.Add((byte)sizeNext);
                        offset++;
                        result.AddRange(token.Text.ToBytes());
                        offset += sizeNext;
                        break;

                    case "LineNumber":
                        if (isFirstToken)
                        {
                            result.Add((byte) TYPE_TOKEN.NUMBER); //TYPE OF NEXT TOKEN: NUMBER 1 Byte
                            short LineNumber = Convert.ToInt16(token.Text);
                                result.AddRange(LineNumber.ToBytes()); //LINE NUMBER, 2 Bytes
                            offset += 3;
                        }
                        //else is a linenumber for a jump

                        break;
                    case "EOF":
                        if ((tokenIndex + 1) == Tokens.Count)
                        {
                            //EOF: Last LF, should be replaced with xFE
                            result.Add((byte) LINE_TOKEN.EOF);
                            //No increment to offset, as EOF doesn't count on 
                        }
                      
                        //EOL: LF, Just Ignored. Next Token should be another LineNumber
                        break;
                    
                }
                isFirstToken = token.TerminalName  == "LF" ? true : false;
                tokenIndex++;
                
            }
            
            byte[] size = offset.ToBytes();
            result[0] = size[0];
            result[1] = size[1];

            //fill with nulls til the end of block
            while(result.Count < 2000)
            {
                result.Add((byte)0x00);
            }
            return result.ToArray();
        }




        #endregion

    }

}