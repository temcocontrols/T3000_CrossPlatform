namespace T3000.Forms
{
    //using PRGReaderLibrary;
    using System;
    using System.IO;
    using System.Drawing;
    using System.Windows.Forms;
    using System.Collections.Generic;
    //using T3000.Forms.ScreensForm;

    public partial class EditScreenForm : Form
    {
        public List<AtributosLabel> ListLabels = new List<AtributosLabel>();
        public int counter = 0;
        public EditScreenForm(string path = null)
        {
            InitializeComponent();
            //this.MouseClick += EditScreenForm_MouseClick;
            this.KeyDown += EditScreenForm_KeyDown;
           
            if (path != null && File.Exists(path))
            {
                BackgroundImage = Image.FromFile(path);
            }

            //for (var i = 0; i < 24; ++i)
            //{
            //    var x = i % 2;
            //    var y = i / 2;
            //    var width = (Width - 10)/2;
            //    var height = (Height - 80) / 12;

            //    var button = new Button();
            //    button.FlatStyle = FlatStyle.Flat;
            //    button.FlatAppearance.BorderSize = 0;
            //    button.BackColor = Color.Transparent;
            //    button.Left = 5 + x * width;
            //    button.Top = 5 + y * height;
            //    button.Size = new Size(width, height);
            //    button.TextAlign = ContentAlignment.MiddleLeft;
            //    button.Text = $"{i}. ";

            //    Controls.Add(button);
            //}
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
        private void EditScreenForm_KeyDown(object send, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Insert && this.lockCheckBox.Checked)
            {
                ListLabels.Add(new AtributosLabel(new Label(), "Etiqueta " + counter, "Etiqueta " + counter, "null", "null", new Point(GetRandomNumber(1, 800), GetRandomNumber(1, 800))));


                this.Controls.Add(ListLabels[counter].Lbl);
                Init(ListLabels[counter].Lbl,counter);
                counter++;
            }
        }


        #endregion

        private void lockCheckBox_CheckedChanged(object sender, EventArgs e)
        {

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
                        ListLabels[param].Next_path = frmlink.Path;

                    }
                }
               
            };
            control.DoubleClick += handler4;


            EventHandler handler5 = (sender, e) =>
            {
                if (!this.lockCheckBox.Checked)
                {
                    EditScreenForm frmedit = new EditScreenForm(ListLabels[param].Next_path);
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

    }
}
