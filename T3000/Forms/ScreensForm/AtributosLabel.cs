using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace T3000.Forms
{

    public class AtributosLabel
    {
        
        private Label lbl;
        private String lbl_name;
        private String lbl_text;
        private String path;
        private Point xy;
        private int __type;
        private int __link;
        private int id;
        private PictureBox thumb;

        public AtributosLabel(Label param_lbl,String param_lbl_name,String param_lbl_text,Point param_xy,int param_type,int param_id,int param_link)
        {
            Link = param_link;
            Id = param_id;
            Lbl = param_lbl;
            Lbl_name = param_lbl_name;
            Lbl_text = param_lbl_text;

            Xy = param_xy;
            Type = param_type;
            Thumb = new PictureBox();
            Thumb.BackColor = Color.Transparent;
            switch (param_type)
            {
                case 0:
                    Thumb.Image = Bitmap.FromHicon(new Icon(Properties.Resources.ProgramsIcon, new Size(75, 75)).Handle);
                    break;
                case 2:
                    Thumb.Image = Bitmap.FromHicon(new Icon(Properties.Resources.VariablesIcon, new Size(75, 75)).Handle);
                    break;
            }
            


            // Set the size of the PictureBox control.
            Thumb.Size = new System.Drawing.Size(75, 75);

            //Set the SizeMode to center the image.
            Thumb.SizeMode = PictureBoxSizeMode.StretchImage;
            Thumb.Location = new Point(param_xy.X, param_xy.Y - 77);
            //Thumb.Visible = true;

            Lbl.Location =Xy;
            Lbl.Text = Lbl_text;
            Lbl.ForeColor = Color.Magenta;
            Lbl.Name = Lbl_name;
            Lbl.BackColor = Color.Transparent; 
            Lbl.Enabled = true;
            //lbl.ForeColor = Color.Black;
            // lbl.Enabled = true;
            Lbl.BorderStyle = BorderStyle.None;
            Lbl.AutoSize = true;
            Lbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));


        }

        public AtributosLabel(Label param_lbl, String param_lbl_name, String param_lbl_text, Point param_xy, int param_type,int param_link,String param_path, int param_id)
        {
            Thumb = new PictureBox();
            Thumb.BackColor = Color.Transparent;
            if (param_path != null && File.Exists(param_path))
            {
                Thumb.Image = new Bitmap(param_path);
            }
            else
            {
                Thumb.Image = null;
            }
            
             // Set the size of the PictureBox control.
            Thumb.Size = new System.Drawing.Size(80, 80);

            //Set the SizeMode to center the image.
            Thumb.SizeMode = PictureBoxSizeMode.StretchImage;
            Thumb.Location = new Point(param_xy.X, param_xy.Y-82);
            Thumb.Visible = true;


            Id = param_id;
            Lbl = param_lbl;
            Lbl.ForeColor = Color.Magenta;
            Lbl_name = param_lbl_name;
            Lbl_text = param_lbl_text;
            Path = param_path;
            Xy = param_xy;
            Type = param_type;
            Link = param_link;

            Lbl.Location = Xy;
            Lbl.Text = Lbl_text;
            Lbl.Name = Lbl_name;
            Lbl.BackColor = Color.Transparent;
            Lbl.AutoSize = true;
            Lbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));


        }

        public Label Lbl { get {return  lbl; } set {lbl = value; } }
        public string Lbl_name { get { return lbl_name; } set { lbl_name = value; } }
        public string Lbl_text { get { return lbl_text; } set { lbl_text = value; } }
        public Point Xy { get { return xy; } set { xy = value; } }
        public int Type { get { return __type; } set { __type = value; } }
        public int Link { get { return __link; } set {__link = value; }}
        public string Path { get { return path; } set { path = value; } }
        public int Id { get { return id; } set { id = value; } }
        public PictureBox Thumb { get { return thumb; } set { thumb = value; } }
    }
}
