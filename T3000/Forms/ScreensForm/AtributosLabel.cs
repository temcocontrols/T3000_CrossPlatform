using System;
using System.Collections.Generic;
using System.Drawing;
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

        private Point xy;
        private int __type;
        private int __link;

        public AtributosLabel(Label param_lbl,String param_lbl_name,String param_lbl_text,Point param_xy,int param_type)
        {
           
            Lbl = param_lbl;
            Lbl_name = param_lbl_name;
            Lbl_text = param_lbl_text;

            Xy = param_xy;
            Type = param_type;

            Lbl.Location =Xy;
            Lbl.Text = Lbl_text;
            Lbl.Name = Lbl_name;
            Lbl.BackColor = Color.Transparent;
            //lbl.ForeColor = Color.Black;
           // lbl.Enabled = true;
            //lbl.BorderStyle = BorderStyle.Fixed3D;
            Lbl.Size = new System.Drawing.Size(200, 40);
            Lbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));


        }

        public AtributosLabel(Label param_lbl, String param_lbl_name, String param_lbl_text, String param_prev_path, String param_next_path, Point param_xy, int param_type,int param_link)
        {

            Lbl = param_lbl;
            Lbl_name = param_lbl_name;
            Lbl_text = param_lbl_text;
            Prev_path = param_prev_path;
            Next_path = param_next_path;
            Xy = param_xy;
            Type = param_type;
            Link = param_link;

            Lbl.Location = Xy;
            Lbl.Text = Lbl_text;
            Lbl.Name = Lbl_name;
            Lbl.BackColor = Color.Transparent;
            Lbl.Size = new System.Drawing.Size(200, 40);
            Lbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));


        }

        public Label Lbl { get => lbl; set => lbl = value; }
        public string Lbl_name { get => lbl_name; set => lbl_name = value; }
        public string Lbl_text { get => lbl_text; set => lbl_text = value; }
        public Point Xy { get => xy; set => xy = value; }
        public int Type { get => __type; set => __type = value; }
        public int Link { get => __link; set => __link = value; }
    }
}
