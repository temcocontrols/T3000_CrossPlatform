namespace T3000.Forms
{
    using PRGReaderLibrary;
    using Properties;
    using Utilities;
    using System;
    using System.Linq;
    using System.Windows.Forms;

    public partial class T3000Form : Form
    {
        public Prg Prg { get; private set; }
        public string PrgPath { get; private set; }
        public bool IsOpened => Prg != null;

        public T3000Form()
        {
            InitializeComponent();
        }

        #region File

        private void LoadPrg(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = $"{Resources.PrgFiles} (*.prg)|*.prg|{Resources.AllFiles} (*.*)|*.*";
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
                savePRGToolStripMenuItem.Enabled = true;
                saveAsToolStripMenuItem.Enabled = true;
                inputsMenuItem.Enabled = true;
                outputsMenuItem.Enabled = true;
                variablesMenuItem.Enabled = true;
                screensMenuItem.Enabled = true;
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
            dialog.Filter = $"{Resources.PrgFiles} (*.prg)|*.prg|{Resources.AllFiles} (*.*)|*.*";
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

                var form = new VariablesForm(
                    Prg.Inputs.Cast<ValuedPoint>().ToList(), 
                    Prg.CustomUnits);
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

                var form = new VariablesForm(
                    Prg.Outputs.Cast<ValuedPoint>().ToList(),
                    Prg.CustomUnits);
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

                var form = new VariablesForm(
                    Prg.Variables.Cast<ValuedPoint>().ToList(),
                    Prg.CustomUnits);
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

                var form = new ScreensForm(Prg.Screens);
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

    }
}
