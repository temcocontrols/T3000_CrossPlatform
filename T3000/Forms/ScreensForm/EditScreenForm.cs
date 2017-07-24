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
    using PRGReaderLibrary;

    //using T3000.Forms.ScreensForm;

    public partial class EditScreenForm : Form
    {
        public DataGridView Dgv { get; set; }
        public DataGridView Vars { get; set; }
        public DataGridView Progs { get; set; }
        public int Prfileid { get; set; }
        public int Screenid { get; set; }
        public Panel pnl;
        public Point p;
        public TextBox txb;
        public DataGridViewColumn PictureColumn { get; private set; }
        public Boolean status = false;
        public List<AtributosLabel> ListLabels = new List<AtributosLabel>();
        public Prg Prg { get; set; }
        public int counter = 0;
        public int index_ = 0,temp_i=0;
        static int temp=0;
        public List<ProgramPoint> PointsP { get; set; }
        public List<ProgramCode> CodesP { get; set; }
        public EditScreenForm(int pr_id,int row_id, string path = null)
        {
            
            InitializeComponent();
            Prfileid = pr_id;
            Screenid = row_id;
            pnl = new Panel();
            txb = new TextBox();
            this.lockCheckBox.BackColor = Color.Transparent;
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


            ShowPoint();

        }


        private void ShowPoint()
        {
            LoadPoint lp = new LoadPoint(Prfileid, Screenid);
            DataTable dt = lp.Tb;
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                /*
                 types  values
                 prg    0
                 grp    1
                 vars   2

                 */

                if ( int.Parse(dt.Rows[i]["type"].ToString()) == 1)
                    ListLabels.Add(new AtributosLabel(new Label(), dt.Rows[i]["lbl_name"].ToString(), dt.Rows[i]["lbl_text"].ToString(), new Point(int.Parse(dt.Rows[i]["point_x"].ToString()), int.Parse(dt.Rows[i]["point_y"].ToString())), int.Parse(dt.Rows[i]["type"].ToString()), int.Parse(dt.Rows[i]["link"].ToString()), dt.Rows[i]["image"].ToString(), int.Parse(dt.Rows[i]["id_a"].ToString())));
                if (int.Parse(dt.Rows[i]["type"].ToString()) == 0 || int.Parse(dt.Rows[i]["type"].ToString()) == 2)
                    ListLabels.Add(new AtributosLabel(new Label(), dt.Rows[i]["lbl_name"].ToString(), dt.Rows[i]["lbl_text"].ToString(), new Point(int.Parse(dt.Rows[i]["point_x"].ToString()), int.Parse(dt.Rows[i]["point_y"].ToString())), int.Parse(dt.Rows[i]["type"].ToString()), int.Parse(dt.Rows[i]["id_a"].ToString()), int.Parse(dt.Rows[i]["link"].ToString())));
               // if (int.Parse(dt.Rows[i]["type"].ToString()) == 1 || int.Parse(dt.Rows[i]["type"].ToString()) == 2)
                this.Controls.Add(ListLabels[counter].Thumb);
                this.Controls.Add(ListLabels[counter].Lbl);
                Init2(ListLabels[counter].Lbl, ListLabels[counter].Thumb, counter);
                //switch (int.Parse(dt.Rows[i]["type"].ToString()))
                //{
                //    case 0:
                //        Init(ListLabels[counter].Lbl, counter);
                //        break;
                //    case 1:
                //    case 2:
                //        Init2(ListLabels[counter].Lbl, ListLabels[counter].Thumb, counter);
                //        break;
                //}


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
            /*
             types  values
             prg    0
             grp    1
             vars   2

             */

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
                          
                            temp = int.Parse(result[1]);
                            temp--;
                            InsertPoint ist = new InsertPoint();

                            ist.Insert_point(Prfileid, Progs.Rows[temp].Cells[6].Value.ToString(), Progs.Rows[temp].Cells[1].Value.ToString().Replace("PROGRAM", ""), Screenid, p.X, p.Y, 0,temp);
                            ListLabels.Add(new AtributosLabel(new Label(), Progs.Rows[temp].Cells[6].Value.ToString(), Progs.Rows[temp].Cells[1].Value.ToString().Replace("PROGRAM", ""), p, 0, ist.Get_id, temp));
                            this.Controls.Add(ListLabels[counter].Lbl);
                            this.Controls.Add(ListLabels[counter].Thumb);
                            //Init(ListLabels[counter].Lbl, counter);
                            Init2(ListLabels[counter].Lbl, ListLabels[counter].Thumb, counter);
                            txb.Text = txb.Text.Replace("\r\n", "");
                            txb.Text = "";
                            txb.Clear();
                            counter++;
                        }
                        else 
                        {
                            MessageBox.Show("Please insert the screen #");
                        }

                    }
                   else if (txb.Text.ToLower().Contains("grp"))
                    {
                        string[] result;
                        string[] stringSeparators = new string[] { "grp" };
                        result = txb.Text.Split(stringSeparators, StringSplitOptions.None);
                        if (IsNumeric(result[1]) && int.Parse(result[1]) > 0 && int.Parse(result[1]) <= 16)
                        {
                            
                            temp = int.Parse(result[1]);
                            temp--;
                            string name = Dgv.Rows[temp].Cells[3].Value.ToString();
                            var building = "Default_Building";
                            string path = GetFullPathForPicture(name, building);
                            InsertPoint ist = new InsertPoint();
                            ist.Insert_point(Prfileid, Dgv.Rows[temp].Cells[2].Value.ToString(), Dgv.Rows[temp].Cells[2].Value.ToString(), Screenid, p.X, p.Y, 1,temp, path);
                            ListLabels.Add(new AtributosLabel(new Label(), Dgv.Rows[temp].Cells[2].Value.ToString(), Dgv.Rows[temp].Cells[2].Value.ToString(), p, 1, temp, path,ist.Get_id));
                            this.Controls.Add(ListLabels[counter].Thumb);
                            this.Controls.Add(ListLabels[counter].Lbl);
                            Init2(ListLabels[counter].Lbl, ListLabels[counter].Thumb, counter);
                            txb.Text = txb.Text.Replace("\r\n", "");
                            txb.Text = "";
                            txb.Clear();
                            counter++;
                        }
                        else
                        {
                            MessageBox.Show("Please insert the screen #");
                        }

                    }
                    else
                    {
                       //*****************
                        if (searchVars(txb.Text.ToUpper()))
                        {
                            InsertPoint ist = new InsertPoint();
                            ist.Insert_point(Prfileid, Vars.Rows[temp_i].Cells[6].Value.ToString(),Vars.Rows[temp_i].Cells[1].Value.ToString()+" "+ Vars.Rows[temp_i].Cells[3].Value.ToString() , Screenid, p.X, p.Y, 2, temp_i);
                            ListLabels.Add(new AtributosLabel(new Label(), Vars.Rows[temp_i].Cells[6].Value.ToString(), Vars.Rows[temp_i].Cells[1].Value.ToString() + " " + Vars.Rows[temp_i].Cells[3].Value.ToString(), p,2,ist.Get_id, temp_i));
                            
                            this.Controls.Add(ListLabels[counter].Lbl);
                            this.Controls.Add(ListLabels[counter].Thumb);
                            Init2(ListLabels[counter].Lbl, ListLabels[counter].Thumb, counter);
                            counter++;
                            txb.Text =txb.Text.Replace("\r\n", "");
                            txb.Text = "";
                            txb.Clear();

                        }
                        else
                        {
                            
                            MessageBox.Show("Variable not found");
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

                Screenid = index_;
                for (int x = 0; x < counter; x++)
                {
                  
                    this.Controls.Remove(ListLabels[x].Thumb);
                    this.Controls.Remove(ListLabels[x].Lbl);
                }
                counter = 0;
                ListLabels = new List<AtributosLabel>();
                ShowPoint();











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
        /*
                Function to move elements (only labels)

                     */
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

                    UpdatePoint up = new UpdatePoint();
                    if (up.Update_point(ListLabels[param].Id, container.Location.X, container.Location.Y))
                    {
                        Console.WriteLine("Update Success");
                    }
                    else
                    {
                        Console.WriteLine("Error");
                    }
                }
            };
            control.MouseMove += handler3;

            EventHandler handler4 = (sender, e) =>
            {
                if (this.lockCheckBox.Checked)
                {
                    //LinkLabel frmlink = new LinkLabel();
                    //if (frmlink.ShowDialog() == DialogResult.OK)
                    //{
                    //    control.Text = frmlink.TextLabel;
                    //    ListLabels[param].Lbl_text = frmlink.TextLabel;


                    //}

                    switch (ListLabels[param].Type)
                    {

                        case 0:
                            MessageBox.Show(CodesP.Count.ToString());
                            LinkLabel frmlink0 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, Progs.Rows[ListLabels[param].Link].Cells[2].Value.ToString(), Progs.Rows[ListLabels[param].Link].Cells[3].Value.ToString(), ListLabels[param].Type);
                            frmlink0.dgv = Progs;
                            frmlink0.Prg = Prg;
                            frmlink0.CodesP = CodesP;
                            
                            frmlink0.PointsP = PointsP;
                            frmlink0.Show();
                            break;

                        case 1:
                            LinkLabel frmlink1 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, (ListLabels[param].Link+1).ToString()+"GRP"+ (ListLabels[param].Link + 1).ToString(), "AUTO", ListLabels[param].Type);
                            
                            frmlink1.Show();
                            
                            break;

                        case 2:
                            LinkLabel frmlink2 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, Vars.Rows[ListLabels[param].Link].Cells[2].Value.ToString(), Vars.Rows[ListLabels[param].Link].Cells[3].Value.ToString(), ListLabels[param].Type);
                            frmlink2.dgv = Vars;
                            frmlink2.CodesP = CodesP;
                            MessageBox.Show(CodesP.Count.ToString());
                            frmlink2.PointsP = PointsP;
                            frmlink2.Prg = Prg;
                            frmlink2.Show();
                            break;
                    }
                    
                   
                }
               
            };


            control.DoubleClick += handler4;


            EventHandler handler5 = (sender, e) =>
            {
                if (!this.lockCheckBox.Checked && (ListLabels[param].Type==1|| ListLabels[param].Type == 0))
                {
                //EditScreenForm frmedit = new EditScreenForm(Prfileid,Screenid,"");
                //frmedit.Show();
               
                    try
                    {
                        var name = Dgv.Rows[ListLabels[param].Link].Cells[3].Value.ToString();
                        var building = "Default_Building";
                        var path = GetFullPathForPicture(name, building);
                        index_ = ListLabels[param].Link;
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
                    Screenid = ListLabels[param].Link;
                    for (int x = 0; x < counter; x++)
                    {
                        if(ListLabels[x].Type == 1 || ListLabels[x].Type==2)
                            this.Controls.Remove(ListLabels[x].Thumb);
                        this.Controls.Remove(ListLabels[x].Lbl);
                    }
                    counter = 0;
                    ListLabels = new List<AtributosLabel>();
                    ShowPoint();


                }

            };
            control.Click += handler5;

            EventHandler handler6 = (sender, e) =>
            {
                if (this.lockCheckBox.Checked)
                {

                    ///
                    
                }

            };

            control.Click += handler6;

        }
        /*End function to move elements (only labels)
                             */

        /*function to move elements (labels & Picturebox)
                             */
        public void Init2(Control control1,Control control2, int param)
        {
            Init2(control1,control2, Direction.Any, param);
        }



        public void Init2(Control control1, Control control2, Direction direction, int param)
        {
            Init2(control1, control1,control2,control2, direction, param);
        }



        public void Init2(Control control1, Control container1, Control control2, Control container2, Direction direction, int param)
        {


            bool Dragging = false;
            Point DragStart = Point.Empty;
            MouseEventHandler handler = (sender, e) =>
            {
                Dragging = true;
                DragStart = new Point(e.X, e.Y);
                control1.Capture = true;
                control2.Capture = true;
            };
            control1.MouseDown += handler;
            control2.MouseDown += handler;

            MouseEventHandler handler2 = (sender, e) =>
            {
                Dragging = false;
                control1.Capture = false;
                control2.Capture = false;
            };
            control1.MouseUp += handler2;
            control2.MouseUp += handler2;

            MouseEventHandler handler3 = (sender, e) =>
            {
                if (Dragging && this.lockCheckBox.Checked)
                {
                    if (direction != Direction.Vertical)
                        container1.Left = Math.Max(0, e.X + container1.Left - DragStart.X); container2.Left = Math.Max(0, e.X + container2.Left - DragStart.X);
                    if (direction != Direction.Horizontal)
                        container1.Top = Math.Max(0, e.Y + container1.Top - DragStart.Y); container2.Top = Math.Max(0, e.Y + container2.Top - DragStart.Y);

                    UpdatePoint up = new UpdatePoint();
                    if (up.Update_point(ListLabels[param].Id, container1.Location.X,container1.Location.Y))
                    {
                        Console.WriteLine("Update Success");
                    }
                    else
                    {
                        Console.WriteLine("Error");
                    }
                   
                }
            };
            control1.MouseMove += handler3;
            control2.MouseMove += handler3;

            MouseEventHandler handler4 = (sender, e) =>
            {
                if(e.Button== MouseButtons.Right)
                {
                    if (this.lockCheckBox.Checked)
                    {
                        switch (ListLabels[param].Type)
                        {

                            case 0:
                                LinkLabel frmlink0 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, Progs.Rows[ListLabels[param].Link].Cells[3].Value.ToString(), Progs.Rows[ListLabels[param].Link].Cells[2].Value.ToString(), ListLabels[param].Type);
                                frmlink0.dgv = Progs;
                                frmlink0.Prg = Prg;
                                frmlink0.CodesP = CodesP;

                                frmlink0.PointsP = PointsP;
                                frmlink0.Show();
                                break;

                            case 1:
                                LinkLabel frmlink1 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, (ListLabels[param].Link + 1).ToString() + "GRP" + (ListLabels[param].Link + 1).ToString(), "AUTO", ListLabels[param].Type);
                                frmlink1.Show();
                                break;

                            case 2:
                                LinkLabel frmlink2 = new LinkLabel(ListLabels[param].Link, ListLabels[param].Lbl_name, ListLabels[param].Lbl_text, Vars.Rows[ListLabels[param].Link].Cells[2].Value.ToString(), Vars.Rows[ListLabels[param].Link].Cells[3].Value.ToString(), ListLabels[param].Type);
                                frmlink2.dgv = Vars;
                                frmlink2.Prg = Prg;
                                frmlink2.Show();
                                break;
                        }
                    }
                }
                
               

            };

            /************Right Click*******************/
            control1.MouseClick += handler4;
            control2.MouseClick += handler4;

            


            EventHandler handler5 = (sender, e) =>
            {
                if (!this.lockCheckBox.Checked && ListLabels[param].Type == 1)
                {
                    //EditScreenForm frmedit = new EditScreenForm(Prfileid,Screenid,"");
                    //frmedit.Show();
                    try
                    {
                        var name = Dgv.Rows[ListLabels[param].Link].Cells[3].Value.ToString();
                        var building = "Default_Building";
                        var path = GetFullPathForPicture(name, building);
                        index_ = ListLabels[param].Link;
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
                    Screenid = ListLabels[param].Link;
                    for (int x = 0; x < counter; x++)
                    {
                        
                        this.Controls.Remove(ListLabels[x].Thumb);
                        this.Controls.Remove(ListLabels[x].Lbl);
                    }
                    counter = 0;
                    ListLabels = new List<AtributosLabel>();
                    ShowPoint();

                }

            };
            control1.Click += handler5;
            control2.Click += handler5;

            EventHandler handler6 = (sender, e) =>
            {
                if (this.lockCheckBox.Checked)
                {

                    ///

                }

            };

            control1.Click += handler6;

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
