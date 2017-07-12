namespace T3000.Forms
{
    //using PRGReaderLibrary;
    using System;

    using System.IO;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;
    using System.Data.SQLite;
    using System.Data;

    //using T3000.Forms.ScreensForm;

    public partial class EditScreenForm : Form
    {
        public DataGridView Dgv { get; set; }
        public DataGridView Vars { get; set; }
        public int Prfileid { get; set; }
        public int Screenid { get; set; }
        public Panel pnl;
        public Point p;
        public TextBox txb;
        public DataGridViewColumn PictureColumn { get; private set; }
        public Boolean status = false;
        public List<AtributosLabel> ListLabels = new List<AtributosLabel>();
        public int counter = 0;
        public int index_ = 0,temp_i=0;
        public EditScreenForm(int pr_id,int row_id, string path = null)
        {
            
            InitializeComponent();
            Prfileid = pr_id;
            Screenid = row_id;
            pnl = new Panel();
            txb = new TextBox();
            //###### Textbox properties #######
            txb.Width = 314;
            txb.Height = 44;
            txb.Location = new Point(54, 12);
            txb.Multiline = true;
            txb.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.45F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            txb.BackColor = SystemColors.Control;
            //###### Panel properties #######
            pnl.Width = 387;
            pnl.Height = 69;
            pnl.BorderStyle = BorderStyle.None;
            pnl.BackColor = SystemColors.Control;
            //###### Label properties #######
            Label lblpoint = new Label();
            lblpoint.Width = 50;
            lblpoint.Height = 18;
            lblpoint.Location = new Point(4, 25);
            lblpoint.Text = "Point:";
            lblpoint.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));

            pnl.Controls.Add(lblpoint);
            pnl.Controls.Add(txb);
            pnl.Paint += pnl_Paint;
            txb.KeyDown += new KeyEventHandler(txb_KeyDown); txb.Focus();
            //this.MouseClick += EditScreenForm_MouseClick;
            this.KeyDown += EditScreenForm_KeyDown;
           
            if (path != null && File.Exists(path))
            {
               BackgroundImage = Image.FromFile(path);
               
            }
            
            LoadPoint lp = new LoadPoint(Prfileid, Screenid);
            DataTable dt = lp.Tb;
            // MessageBox.Show(dt.Rows[0]["lbl_name"].ToString());
            for (int i=0;i<dt.Rows.Count;i++)
            {
                ListLabels.Add(new AtributosLabel(new Label(), dt.Rows[i]["lbl_name"].ToString(), dt.Rows[i]["lbl_text"].ToString(), new Point(int.Parse(dt.Rows[i]["point_x"].ToString()), int.Parse(dt.Rows[i]["point_y"].ToString())), int.Parse(dt.Rows[i]["type"].ToString())));
                this.Controls.Add(ListLabels[counter].Lbl);
                Init(ListLabels[counter].Lbl, counter);
                counter++;
            }
            

        }

        private void pnl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Red,
            e.ClipRectangle.Left,
            e.ClipRectangle.Top,
            e.ClipRectangle.Width - 1,
            e.ClipRectangle.Height - 1);
            base.OnPaint(e);
        }

        #region Buttons

        private void Save(object sender, EventArgs e)
        {
            try
            {
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

        private void Cancel(object sender, EventArgs e)
        {
            Close();
        }


        //private void EditScreenForm_MouseClick(object sender,MouseEventArgs e)
        //{
        //    ListLabels.Add(new AtributosLabel(new Label(), "Etiqueta " + counter, "Etiqueta " + counter,"null", "null", e.Location));


        //    this.Controls.Add(ListLabels[counter].Lbl);

        //    counter++;
        //}

            //############## ENTER EN TEXTBOX ##################
        private void txb_KeyDown(object sender, KeyEventArgs e)
        {


            switch (e.KeyCode)
            {
                case (Keys.Enter):
                    this.Controls.Remove(pnl);
                   
                    status = false;
                    if (txb.Text.ToLower().Contains("prg"))
                    {
                        string[] result;
                        string[] stringSeparators = new string[] { "prg" };
                        result = txb.Text.Split(stringSeparators, StringSplitOptions.None);
                        if (IsNumeric(result[1]) && int.Parse(result[1])>0 && int.Parse(result[1])<=16)
                        {
                            int temp;
                            temp = int.Parse(result[1]);
                            ListLabels.Add(new AtributosLabel(new Label(), Dgv.Rows[temp-1].Cells[2].Value.ToString(), Dgv.Rows[temp-1].Cells[2].Value.ToString(), p,0));
                            InsertPoint ist = new InsertPoint();
                            ist.Insert_point(Prfileid, Dgv.Rows[temp - 1].Cells[2].Value.ToString(), Dgv.Rows[temp - 1].Cells[2].Value.ToString(),Screenid,p.X,p.Y,0);
                            this.Controls.Add(ListLabels[counter].Lbl);
                            Init(ListLabels[counter].Lbl, counter);
                            counter++;
                        }
                        else
                        {
                            MessageBox.Show("Error no contiene prg #");
                        }

                    }
                    else
                    {
                       //*****************
                        if (searchVars(txb.Text.ToUpper()))
                        {
                            ListLabels.Add(new AtributosLabel(new Label(), Vars.Rows[temp_i].Cells[6].Value.ToString(), Vars.Rows[temp_i].Cells[6].Value.ToString(), p,1));
                            InsertPoint ist = new InsertPoint();
                            ist.Insert_point(Prfileid, Vars.Rows[temp_i].Cells[6].Value.ToString(), Vars.Rows[temp_i].Cells[6].Value.ToString(), Screenid, p.X, p.Y, 1);
                            this.Controls.Add(ListLabels[counter].Lbl);
                            Init(ListLabels[counter].Lbl, counter);
                            counter++;
                            txb.Text =txb.Text.Replace("\r\n", "");
                            txb.Text = "";
                            txb.Clear();

                        }
                        else
                        {
                            
                            MessageBox.Show(Vars.RowCount.ToString());
                        }

                    }

                    break;
                case (Keys.Escape):
                    this.Controls.Remove(pnl);
                    status = false;
                    break;

            }
        }
        
        private Boolean searchVars(String TBox)
        {
            Boolean flag = false;
            int indice = 0;
            //MessageBox.Show("Error no contiene prg #");
            while (!flag && indice < Vars.RowCount)
            {
                Console.WriteLine(indice.ToString()+" -- " +TBox+ " -- "+ Vars.Rows[indice].Cells[6].Value.ToString().ToUpper());
                if (TBox.Trim().Equals(Vars.Rows[indice].Cells[6].Value.ToString().Trim().ToUpper()))
                {
                    flag = true;
                    temp_i = indice;

                }
                indice++;
            }
            return flag;
        }
        //###################### KEY EVENTS #############################
        private void EditScreenForm_KeyDown(object send, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Insert && this.lockCheckBox.Checked)
            {

                //MessageBox.Show(Vars.RowCount.ToString());

                if (!status)
                {
                    status = true;//Textbox visible
                    
                    p = Cursor.Position;
                    pnl.Location = p; //posicion del panel
                    this.Controls.Add(pnl);                    
                    txb.Focus();                     
                    txb.Select();

                    
                }

            }
            if ((e.KeyCode == Keys.PageUp) || (e.KeyCode == Keys.PageDown))
            {
                int courow = Dgv.RowCount-1;
                
                switch (e.KeyCode)
                {
                    case (Keys.PageUp):
                        if (index_==courow)
                        {
                            index_ = 0;
                        }
                        else
                        {
                            index_++;
                        }
                        
                        break;
                    case (Keys.PageDown):
                        if (index_ == 0)
                        {
                            index_ = courow;
                        }
                        else
                        {
                            index_--;
                        }
                        
                        break;

                       
                }
              
                    try
                    {
                        var name = Dgv.Rows[index_].Cells[3].Value.ToString();
                        var building = "Default_Building";
                        var path = GetFullPathForPicture(name, building);
                       
                    if (path != null && File.Exists(path))
                    {
                        BackgroundImage = Image.FromFile(path);

                    }
                    else
                    {
                        BackgroundImage = null;
                    }
                }
                    catch (Exception exception)
                    {
                        MessageBoxUtilities.ShowException(exception);
                    }
               
                    

                

                
             
                



            }
        }

        private string GetFullPathForPicture(string name, string building) =>
             Path.Combine("Database", "Buildings", building, "image", name);


        #endregion

        private void lockCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (this.lockCheckBox.Checked)
            {
                this.Cursor = Cursors.Cross;
            }
            else
            {
                this.Cursor = Cursors.Default;
            }
            
        }

        public enum Direction
        {
            Any,
            Horizontal,
            Vertical
        }

        public  void Init(Control control,int param)
        {
            Init(control, Direction.Any,param);
        }



        public  void Init(Control control, Direction direction,int param)
        {
            Init(control, control, direction,param);
        }



        public  void Init(Control control, Control container, Direction direction,int param)
        {


            bool Dragging = false;
            Point DragStart = Point.Empty;
            MouseEventHandler handler = (sender, e) =>
            {
                Dragging = true;
                DragStart = new Point(e.X, e.Y);
                control.Capture = true;
            };
            control.MouseDown +=handler;

            MouseEventHandler handler2 = (sender, e) =>
            {
                Dragging = false;
                control.Capture = false;
            };
            control.MouseUp += handler2;

            MouseEventHandler handler3 = (sender, e) =>
            {
                if (Dragging && this.lockCheckBox.Checked)
                {
                    if (direction != Direction.Vertical)
                        container.Left = Math.Max(0, e.X + container.Left - DragStart.X);
                    if (direction != Direction.Horizontal)
                        container.Top = Math.Max(0, e.Y + container.Top - DragStart.Y);
                }
            };
            control.MouseMove += handler3;

            EventHandler handler4 = (sender, e) =>
            {
                if (this.lockCheckBox.Checked)
                {
                    LinkLabel frmlink = new LinkLabel();
                    if (frmlink.ShowDialog() == DialogResult.OK)
                    {
                        control.Text = frmlink.TextLabel;
                        ListLabels[param].Lbl_text = frmlink.TextLabel;
                        

                    }
                }
               
            };
            control.DoubleClick += handler4;


            EventHandler handler5 = (sender, e) =>
            {
                if (!this.lockCheckBox.Checked)
                {
                    EditScreenForm frmedit = new EditScreenForm(Prfileid,Screenid,"");
                    frmedit.Show();
                }

            };
            control.Click += handler5;

        }


        //Function to get random number
        private static readonly Random getrandom = new Random();
        private static readonly object syncLock = new object();
        public static int GetRandomNumber(int min, int max)
        {
            lock (syncLock)
            { // synchronize
                return getrandom.Next(min, max);
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
