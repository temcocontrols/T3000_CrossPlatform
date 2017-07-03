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
        private String prev_path,next_path;
        private Point xy;

        public AtributosLabel(Label param_lbl,String param_lbl_name,String param_lbl_text,String param_prev_path,String param_next_path,Point param_xy)
        {
            lbl = param_lbl;
            lbl_name = param_lbl_name;
            lbl_text = param_lbl_text;
            prev_path = param_prev_path;
            next_path = param_next_path;
            xy = param_xy;

            lbl.Location =xy;
            lbl.Text = lbl_text;
            lbl.Name = lbl_name;
            lbl.BackColor = Color.White;
            lbl.ForeColor = Color.Black;
            lbl.Enabled = true;
            lbl.BorderStyle = BorderStyle.Fixed3D;
            lbl.Size = new System.Drawing.Size(60, 15);
        }

        public Label Lbl { get => lbl; set => lbl = value; }
        public string Lbl_name { get => lbl_name; set => lbl_name = value; }
        public string Lbl_text { get => lbl.Name; set => lbl.Name = value; }
        public string Prev_path { get => prev_path; set => prev_path = value; }
        public string Next_path { get => next_path; set => next_path = value; }
        public Point Xy { get => xy; set => xy = value; }
    }
}
