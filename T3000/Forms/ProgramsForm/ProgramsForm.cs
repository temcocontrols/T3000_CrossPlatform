namespace T3000.Forms
{
    using PRGReaderLibrary;
    using PRGReaderLibrary.Extensions;
    using PRGReaderLibrary.Types.Enums.Codecs;
    using PRGReaderLibrary.Utilities;
    using Properties;
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Drawing;

    using System.Windows.Forms;

    public partial class ProgramsForm : Form
    {
        public List<ProgramPoint> Points { get; set; }
        public List<ProgramCode> Codes { get; set; }
        public DataGridView Progs { get; set; }

        private Prg _prg;
        public Prg SelectedPrg
        {
            get { return _prg; }

            set { _prg = value; }
        }

        public string PrgPath { get; private set; }


        public ProgramsForm(ref Prg  CurPRG,string Path)
        {
            SelectedPrg = CurPRG;
            PrgPath = Path;

            SetView(SelectedPrg.Programs, SelectedPrg.ProgramCodes);

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

        int Index_EditProgramCode;

        private void EditCodeColumn(object sender, EventArgs e)
        {
            try
            {
                var row = view.CurrentRow;
                Index_EditProgramCode = row.GetValue<int>(NumberColumn) - 1;
                
                var form = new ProgramEditorForm();
                form.Caption = $"Edit Code: Panel 1 - Program {Index_EditProgramCode } - Label {SelectedPrg.Programs[Index_EditProgramCode].Description}";

                Debug.WriteLine("--------------ORIGINAL CODE-------------------");
                CoderHelper.ConsolePrintBytes(Codes[Index_EditProgramCode].Code, "Original");

                Decoder DECODER = new Decoder();
                
                DECODER.SetControlPoints(SelectedPrg);
                string ProgramText = DECODER.DecodeBytes(Codes[Index_EditProgramCode].Code);

                Debug.WriteLine("--------------NEW PROGRAM TEXT-------------------");
                Debug.WriteLine(ProgramText);

                //STEP 1: create a local copy of all identifiers
                form.Identifiers = DECODER.Identifiers;

                //STEP 2: Create a local copy for Control Basic program text
                form.SetCode(ProgramText);

                //STEP 3: Override Send Event Handler and encode program into bytes.
                form.Send += Form_Send;

                //STEP 4: Who's your daddy?!!
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

            Debug.WriteLine("");
            Debug.WriteLine("---------------------DEBUG STRINGS-----------------------");
            Debug.WriteLine("");
            Debug.WriteLine($"Code:{Environment.NewLine}{e.Code}");
            Debug.WriteLine($"Tokens:{Environment.NewLine}{e.ToString()}");


            //Init a copy of controlpoints
            Encoder ENCODER = new Encoder();

            ENCODER.SetControlPoints(SelectedPrg);
            //ENCODE THE PROGRAM
            byte[] ByteEncoded = ENCODER.EncodeBytes(e.Tokens);
            var PSize = BitConverter.ToInt16(ByteEncoded, 0);
            CoderHelper.ConsolePrintBytes(ByteEncoded, "Encoded");
            MessageBox.Show($"Resource compiled succceded{System.Environment.NewLine}Total size 2000 bytes{System.Environment.NewLine}Already used {PSize} bytes.", "T3000");

           // MessageBox.Show(Encoding.UTF8.GetString(ByteEncoded), "Tokens");
            SelectedPrg.ProgramCodes[Index_EditProgramCode].Code = ByteEncoded;
            //The need of this code, means that constructor must accept byte array and fill with nulls to needSize value
            SelectedPrg.ProgramCodes[Index_EditProgramCode].Count = 2000;
            SelectedPrg.Programs[Index_EditProgramCode].Length = PSize;
            //Also that save, must recalculate and save the lenght in bytes of every programcode into program.lenght
            //Prg.Save($"{PrgPath.Substring(0,PrgPath.Length-4)}.PRG");
           

        }


        #endregion

    }

}
