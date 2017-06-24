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
        public LinkLabel()
        {
            InitializeComponent();
        }

        private void LinkLabel_Load(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            // open file dialog
            OpenFileDialog open = new OpenFileDialog();
            // image filters
            open.Filter = "Image Files(*.jpg; *.jpeg; *.gif; *.bmp)|*.jpg; *.jpeg; *.gif; *.bmp";
            if (open.ShowDialog() == DialogResult.OK)
            {
                // display image in picture box
                pictureBox1.Image = new Bitmap(open.FileName);
                // image file path
                Path = open.FileName;
            }
        }

        public string TextLabel { get; set; }
        public string Path { get; set; }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK; //cierra el formulario
            this.Close();

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            TextLabel = textBox1.Text;
        }
    }
}
