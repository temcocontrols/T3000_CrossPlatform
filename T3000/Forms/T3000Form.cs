namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using Utilities;
    using System;
    using System.IO;
    using System.Linq;
    using System.Windows.Forms;
    public partial class T3000Form : Form
    {
        private Prg _prg; 
        public Prg Prg
        {
            get { return _prg; }
          
            private set { _prg = value; }
        }

        public string PrgPath { get; private set; }
        public bool IsOpened => Prg != null;



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
                Prg = Prg.Load(path);

                

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

                if (Prg.FileVersion != FileVersion.Current)
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

                Prg.Save(path);
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
                Prg.Save(path);
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

                Prg.Upgrade(FileVersion.Current);
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

                var form = new InputsForm(Prg.Inputs, Prg.CustomUnits);
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

                var form = new OutputsForm(Prg.Outputs, Prg.CustomUnits);
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

                var form = new VariablesForm(Prg.Variables, Prg.CustomUnits);
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

                var form = new ControllersForm(Prg.Controllers, Prg.CustomUnits);
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
                var f = new VariablesForm(Prg.Variables, Prg.CustomUnits);
                var f2 = new ProgramsForm(ref _prg, PrgPath );
                var form = new ScreensForm(Prg.Screens);
                form.Prg = Prg;
                form.PointsP=Prg.Programs;
                form.CodesP = Prg.ProgramCodes;
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

                var form = new SchedulesForm(Prg.Schedules, Prg.ScheduleCodes);
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

                var form = new HolidaysForm(Prg.Holidays, Prg.HolidayCodes);
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
    }
}