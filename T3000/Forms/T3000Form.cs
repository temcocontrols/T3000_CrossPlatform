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
    using ExceptionHandling;

    public partial class T3000Form : Form, ILoadMessages
    {
        private Prg _prg;
        public Prg PRG
        {
            get { return _prg; }

            private set { _prg = value; }
        }

        public string PrgPath { get; private set; }
        public bool IsOpened => PRG != null;



        public T3000Form()
        {

            try
            {
                InitializeComponent();
                //LRUIZ: AutoExpand treeBuildingView
                //TODO: NOT MINE: Add dynamically nodes to tree Building View
                treeBuildingView.ExpandAll();
                treeBuildingView.FullRowSelect = true;
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Initializing T3000");
            }
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



                PRG = Prg.Load(path, this);



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
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Loading Program File");
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
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Saving PRG File Exception Found");
            }

        }

        private void SaveAsPrg(object sender, EventArgs e)
        {

            try
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

                PRG.Save(path);
                statusLabel.Text = string.Format(Resources.Saved, path);

            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Saving As .PRG, exception found");
            }
        }

        private void Upgrade(object sender, EventArgs e)
        {

            try
            {
                if (!IsOpened)
                {
                    statusLabel.Text = Resources.FileIsNotOpen;
                    return;
                }


                var path = PrgPath;

                PRG.Upgrade(FileVersion.Current);
                statusLabel.Text = string.Format(Resources.Upgraded, path);

                upgradeMenuItem.Visible = false;

            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Upgrading File, Exception Found!");
            }
        }

        private void Exit(object sender, EventArgs e)
        {

            try
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
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex);
            }
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
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex);
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
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, Resources.ShowProgramException);
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
                var f2 = new ProgramsForm(ref _prg, PrgPath);
                var form = new ScreensForm(PRG.Screens);
                form.Prg = PRG;
                form.PointsP = PRG.Programs;
                form.CodesP = PRG.ProgramCodes;
                form.PrgPath = PrgPath;

                form.Vars = f.Vars;
                form.Progs = f2.Progs;

                form.Show();

            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex);
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
                ExceptionHandler.Show(exception);
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
                ExceptionHandler.Show(exception);
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

            try
            {
                LoadPartName.Text = "";
                this.LoadPartName.Text = $"Parts({counter}) => Loaded {theMessage}";
                this.LoadProgressBar.Value = counter;

                Debug.WriteLine(this.LoadPartName.Text);
                Application.DoEvents();


                System.Threading.Thread.Sleep(50);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex);
            }

        }

        private void t3000EditorTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProgramEditorForm prgf = new ProgramEditorForm();
            prgf.Show();
        }
    }
}
