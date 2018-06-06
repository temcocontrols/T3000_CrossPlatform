namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using Utilities;
    using System;
    using System.IO;
    using System.Linq;
    using System.Windows.Forms;
    using System.Diagnostics;

    public partial class T3000Form : Form, ILoadMessages
    {
        private Prg _prg ; 
        public Prg PRG
        {
            get { return _prg; }
          
            private set { _prg = value; }
        }

        public string PrgPath { get; private set; }
        public bool IsOpened => PRG != null;



        public T3000Form()
        {
            InitializeComponent();
            //LRUIZ: AutoExpand treeBuildingView
            //TODO: Add dynamically nodes to tree Building View
            treeBuildingView.ExpandAll();
            treeBuildingView.FullRowSelect = true;
        }

        #region File

        private void LoadPrg(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = $"{Resources.PrgFiles}|*.prg;*.prog|{Resources.AllFiles} (*.*)|*.*";
            dialog.Title = Resources.SelectPrgFile;
            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            try
            {
                var path = dialog.FileName;

                
                PrgPath = path;
                //Reset progress bar and label
                ResetLoadPrgBar(0);


                PRG = Prg.Load(path,this);
                

                statusLabel.Text = string.Format(Resources.CurrentFile, path);

                //File menu
                savePRGToolStripMenuItem.Enabled = true;
                saveAsToolStripMenuItem.Enabled = true;
                upgradeMenuItem.Enabled = true;

                //Control menu
                inputsMenuItem.Enabled = true;
                outputsMenuItem.Enabled = true;
                variablesMenuItem.Enabled = true;
                programsMenuItem.Enabled = true;
                controllersMenuItem.Enabled = true;
                screensMenuItem.Enabled = true;
                schedulesMenuItem.Enabled = true;
                holidaysMenuItem.Enabled = true;

                //Buttons tool strip
                inputsButton.Enabled = true;
                outputsButton.Enabled = true;
                variablesButton.Enabled = true;
                programsButton.Enabled = true;
                controllersButton.Enabled = true;
                screensButton.Enabled = true;
                schedulesButton.Enabled = true;
                holidaysButton.Enabled = true;

                if (PRG.FileVersion != FileVersion.Current)
                {
                    upgradeMenuItem.Visible = true;
                }
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void SavePrg(object sender, EventArgs e)
        {
            if (!IsOpened)
            {
                statusLabel.Text = Resources.FileIsNotOpen;
                return;
            }

            try
            {
                var path = PrgPath;

                PRG.Save(path);
                statusLabel.Text = string.Format(Resources.Saved, path);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void SaveAsPrg(object sender, EventArgs e)
        {
            if (!IsOpened)
            {
                statusLabel.Text = Resources.FileIsNotOpen;
                return;
            }

            var dialog = new SaveFileDialog();
            dialog.Filter = $"{Resources.PrgFiles}|*.prg;*.prog|{Resources.AllFiles} (*.*)|*.*";
            dialog.Title = Resources.SavePrgFile;
            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            var path = dialog.FileName;
            try
            {
                PRG.Save(path);
                statusLabel.Text = string.Format(Resources.Saved, path);
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void Upgrade(object sender, EventArgs e)
        {
            if (!IsOpened)
            {
                statusLabel.Text = Resources.FileIsNotOpen;
                return;
            }

            try
            {
                var path = PrgPath;

                PRG.Upgrade(FileVersion.Current);
                statusLabel.Text = string.Format(Resources.Upgraded, path);

                upgradeMenuItem.Visible = false;
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void Exit(object sender, EventArgs e)
        {
            if (IsOpened)
            {
                var result = MessageBox.Show(Resources.SaveBeforeExit,
                    Resources.SaveBeforeExitTitle,
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                if (result == DialogResult.Cancel)
                {
                    return;
                }
                else if (result == DialogResult.Yes)
                {
                    SavePrg(sender, e);
                }
            }

            Close();
        }

        #endregion

        #region Control

        private bool CheckIsOpened()
        {
            if (!IsOpened)
            {
                MessageBoxUtilities.ShowWarning(Resources.FileIsNotOpen);
                return false;
            }

            return true;
        }

        private void ShowInputs(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new InputsForm(PRG.Inputs, PRG.CustomUnits);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowOutputs(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new OutputsForm(PRG.Outputs, PRG.CustomUnits);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowVariables(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new VariablesForm(PRG.Variables, PRG.CustomUnits);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowControllers(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new ControllersForm(PRG.Controllers, PRG.CustomUnits);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowPrograms(object sender, EventArgs e)
        {
            ShowPrograms();
        }

        private void ShowPrograms()
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new ProgramsForm(ref _prg, PrgPath);

                form.MdiParent = this;
                form.Show();

            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowScreens(object sender, EventArgs e)
        {
            
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }
                var f = new VariablesForm(PRG.Variables, PRG.CustomUnits);
                var f2 = new ProgramsForm(ref _prg, PrgPath );
                var form = new ScreensForm(PRG.Screens);
                form.Prg = PRG;
                form.PointsP=PRG.Programs;
                form.CodesP = PRG.ProgramCodes;
                form.PrgPath = PrgPath;

                form.Vars = f.Vars;
                form.Progs = f2.Progs;
                
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowSchedules(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new SchedulesForm(PRG.Schedules, PRG.ScheduleCodes);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void ShowHolidays(object sender, EventArgs e)
        {
            try
            {
                if (!CheckIsOpened())
                {
                    return;
                }

                var form = new HolidaysForm(PRG.Holidays, PRG.HolidayCodes);
                form.Show();
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        #endregion

        #region Language

        private void SelectEnglish(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, string.Empty);

        private void SelectGerman(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "de-DE");

        private void SelectChinese(object sender, EventArgs e) =>
            RuntimeLocalizer.ChangeCulture(this, "zh-Hant");

        #endregion

        private void T3000Form_KeyUp(object sender, KeyEventArgs e)
        {
            if ((Control.ModifierKeys & Keys.Alt) == Keys.Alt)
            {
                switch (e.KeyCode)
                {
                    case Keys.P:
                        ShowPrograms();
                        break;
                }
            }
            e.Handled = true;
        }

        public void ResetLoadPrgBar(int newvalue)
        {
            this.LoadProgressBar.Value = newvalue;
            this.LoadPartName.Text = "";
        }


        public void TickLoadPrgBar()
        {
            this.LoadProgressBar.PerformStep();
        }

        public void PassMessage(int counter, string theMessage)
        {
            LoadPartName.Text = "";
            this.LoadPartName.Text = $"Parts({counter}) => Loaded {theMessage}";
            this.LoadProgressBar.Value = counter;

            Debug.WriteLine(this.LoadPartName.Text);
            Application.DoEvents();


            System.Threading.Thread.Sleep(50);

        }
    }
}
