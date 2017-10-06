using PRGReaderLibrary;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace T3000.Forms
{
    public partial class LinkLabel : Form
    {
        
        private int _pos;
        private String _label;
        private String _description;
        private String _mode;
        private String _value;
        private int _type;
        public Boolean flag { get; set; }
        public DataGridView dgv { get; set; }
        public int id { get; set; }

        Prg _prg;
        public Prg Prg
        {
            get { return _prg; }
            set { _prg = value; }
        }
        public string PrgPath { get; set; }
        public List<ProgramPoint> PointsP { get; set; }
        public List<ProgramCode> CodesP { get; set; }

        public LinkLabel(int pos,String label,String description,String mode,String value,int type)
        {
            InitializeComponent();
            Pos = pos;
            Label = label;
            Description = description;
            Mode = mode;
            Value = value;
            Type = type;
            textBox1.Enabled = false;

            textBox2.MouseClick += textBox2_Click;
            textBox1.KeyDown += textBox1_KeyDown;
        }

        public int Pos { get { return _pos; } set { _pos = value; } }
        public string Label { get { return _label; } set { _label = value; } }
        public string Description { get { return _description; } set { _description = value; } }
        public string Mode { get { return _mode; } set { _mode = value; } }
        public string Value { get { return _value; } set { _value = value; } }
        public int Type { get { return _type; } set { _type = value; } }

        private void LinkLabel_Load(object sender, EventArgs e)
        {
             
            
            switch (Type)
            {
                case 0:
                    this.label2.Text = (Pos + 1).ToString() + "-PRG" + (Pos + 1).ToString();
                    this.label3.Text = Description;
                    textBox2.ReadOnly = true;
                    textBox1.ReadOnly = true;
                    textBox1.MouseClick += textBox1_ClickPrg;
                    break;
                case 1:
                    this.label2.Text = (Pos + 1).ToString() + "-GRP" + (Pos + 1).ToString();
                    this.label3.Text = Description;
                    textBox2.Enabled = false;
                    break;
                case 2:
                    this.label2.Text = (Pos+1).ToString() + "-VAR" + (Pos+1).ToString();
                    this.label3.Text = Description.Replace(Value, "");
                    textBox2.ReadOnly = true;
                    textBox1.ReadOnly = true;
                    textBox1.MouseClick += textBox1_ClickVars;
                    
                    break;
            }
            
            this.label1.Text = Label;

            this.textBox1.Text = Value;
            this.textBox2.Text = Mode;
        }

        //private void textBox1_DoubleClick(object sender, MouseEventArgs e)
        //{
        //    int x, y;
        //    x = e.Location.X;
        //    y = e.Location.Y;
        //    if ((x>=138 && x<=220) && (y>=34 && y<=54) )
        //    {
        //        textBox1.Enabled = true;
        //        MessageBox.Show("Text entro");
        //    }
        //    else if ((x >= 324 && x <= 406) && (y >= 34 && y <= 54))
        //    {
        //        textBox2.Enabled = true;
        //        MessageBox.Show(textBox1.Enabled.ToString());
        //    }
            
        //}

        private void textBox2_Click(object sender, MouseEventArgs e)
        {
            textBox2.Text=((textBox2.Text.Equals("Automatic"))?"Manual":"Automatic");
            Boolean flag= ((textBox2.Text.Equals("Automatic")) ? false : true);
            
            
            if (Type==0)
            {
                textBox1.Enabled = flag;
                var form = new ProgramsForm(ref _prg, PrgPath );
                dgv.Rows[Pos].Cells[3].Value = ((AutoManual)dgv.Rows[Pos].Cells[3].Value).NextValue();
                form.ExternalSaveAutomanual(Pos, dgv.Rows[Pos]);
            }
            else if (Type ==2)
            {
                Regex Val = new Regex(@"^[+-]?\d+(\.\d+)?$");
                if (IsNumeric(textBox1.Text) || Val.IsMatch(textBox1.Text))
                {
                    textBox1.Enabled = flag;
                    textBox1.ReadOnly = false;
                }
                else
                {
                    textBox1.Enabled = flag;
                    textBox1.ReadOnly = true;
                }
                var form = new VariablesForm(Prg.Variables, Prg.CustomUnits);
                dgv.Rows[Pos].Cells[2].Value = ((AutoManual)dgv.Rows[Pos].Cells[2].Value).NextValue();
                form.ExternalSaveAutomanual(Pos, dgv.Rows[Pos]);
            }
           


        }

        private void textBox1_ClickPrg(object sender, MouseEventArgs e)
        {
           
           textBox1.Text = ((textBox1.Text.Equals("On")) ? "Off" : "On");
            //var form = new ProgramsForm(PointsP, CodesP);
            var form = new ProgramsForm(ref _prg, PrgPath);
            dgv.Rows[Pos].Cells[2].Value = ((OffOn)dgv.Rows[Pos].Cells[2].Value).NextValue();
            form.ExternalSaveValue(Pos, dgv.Rows[Pos]);


        }

        private void textBox1_ClickVars(object sender, MouseEventArgs e)
        {


            Regex Val = new Regex(@"^[+-]?\d+(\.\d+)?$");
            if (IsNumeric(textBox1.Text) || Val.IsMatch(textBox1.Text))
            {
                textBox1.Enabled = true;
                


            }
            else
            {
                if (textBox1.Text.ToLower().Contains("on") || textBox1.Text.ToLower().Contains("off"))
                {
                    dgv.Rows[Pos].Cells[3].Value = ((textBox1.Text.Equals("On")) ? "Off" : "On");
                }
                else if (textBox1.Text.ToLower().Contains("yes") || textBox1.Text.ToLower().Contains("no"))
                {
                    dgv.Rows[Pos].Cells[3].Value = ((textBox1.Text.Equals("Yes")) ? "No" : "Yes");

                }



                textBox1.Text = dgv.Rows[Pos].Cells[3].Value.ToString();
                var form = new VariablesForm(Prg.Variables, Prg.CustomUnits);

                form.ExternalSaveValue(Pos, dgv.Rows[Pos]);


                UpdatePoint up = new UpdatePoint();
                if (up.Update_point(id, dgv.Rows[Pos].Cells[1].Value.ToString() + " " + textBox1.Text))
                {
                    Console.WriteLine("Name Update Success");
                }
                else
                {
                    Console.WriteLine("Error");
                }
                Prg.Save(PrgPath);
                MessageBox.Show("Saved");
                flag = true;
                DialogResult = DialogResult.OK;
                


            }








        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case (Keys.Enter):
                    Regex Val = new Regex(@"^[+-]?\d+(\.\d+)?$");
                    if (IsNumeric(textBox1.Text) || Val.IsMatch(textBox1.Text))
                    {

                        dgv.Rows[Pos].Cells[3].Value = textBox1.Text;
                        var form = new VariablesForm(Prg.Variables, Prg.CustomUnits);

                        form.ExternalSaveValue(Pos, dgv.Rows[Pos]);

                        UpdatePoint up = new UpdatePoint();
                        if (up.Update_point(id, dgv.Rows[Pos].Cells[1].Value.ToString() + " " + textBox1.Text))
                        {
                            Console.WriteLine("Name Update Success");
                        }
                        else
                        {
                            Console.WriteLine("Error");
                        }
                        Prg.Save(PrgPath);
                        MessageBox.Show("Saved");
                        flag = true;
                        DialogResult = DialogResult.OK;
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show("Invalid parameter");
                    }
                    break;
            }
        }
            public static bool IsNumeric(object Expression)
        {
            double retNum;

            bool isNum = Double.TryParse(Convert.ToString(Expression), System.Globalization.NumberStyles.Any, System.Globalization.NumberFormatInfo.InvariantInfo, out retNum);
            return isNum;
        }

    }
}