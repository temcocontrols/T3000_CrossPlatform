namespace T3000.Forms
{
    using System;
    using System.Drawing;
    using System.Windows.Forms;

    public class AtributosLabel
    {
        
        private Label lbl;
        private string lbl_name;
        private string lbl_text;
        private string prev_path,next_path;
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
            lbl.BackColor = Color.Transparent;
            //lbl.ForeColor = Color.Black;
           // lbl.Enabled = true;
            //lbl.BorderStyle = BorderStyle.Fixed3D;
            lbl.Size = new System.Drawing.Size(200, 40);
            lbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));


        }

        public Label Lbl
        {
            get { return lbl; }
            set { lbl = value; }
        }

        public string Lbl_name {
            get { return lbl_name; }
            set { lbl_name = value; }
        }

        public string Lbl_text {
            get { return lbl.Name; }
            set { lbl.Name = value; }
        }

        public string Prev_path {
            get { return prev_path; }
            set { prev_path = value; }
        }

        public string Next_path {
            get { return next_path; }
            set { next_path = value; }
        }

        public Point Xy {
            get { return xy; }
            set { xy = value; }
        }
    }
}
