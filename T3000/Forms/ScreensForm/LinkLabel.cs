using PRGReaderLibrary;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
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
        public DataGridView dgv { get; set; }
        public Prg Prg { get; set; }
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

        }

        public int Pos { get => _pos; set => _pos = value; }
        public string Label { get => _label; set => _label = value; }
        public string Description { get => _description; set => _description = value; }
        public string Mode { get => _mode; set => _mode = value; }
        public string Value { get => _value; set => _value = value; }
        public int Type { get => _type; set => _type = value; }

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
            
                textBox1.Enabled = flag;
         var form = new ProgramsForm(PointsP, CodesP);
            form.ExternalSaveAutomanual(Pos,dgv.Rows[Pos]);


        }

        private void textBox1_ClickPrg(object sender, MouseEventArgs e)
        {
           
           textBox1.Text = ((textBox1.Text.Equals("On")) ? "Off" : "On");
            var form = new ProgramsForm(PointsP, CodesP);
            form.ExternalSaveValue(Pos, dgv.Rows[Pos]);







        }

    }
}
