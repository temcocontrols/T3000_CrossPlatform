namespace T3000.Forms
{
    using PRGReaderLibrary;
    using System;
    using System.Windows.Forms;

    /// <summary>
    /// This form need for Unix(Combobox not worked correctly on Unix)
    /// </summary>
    public partial class SelectAutoManualForm : Form
    {
        public AutoManual Selected { get; private set; }

        public SelectAutoManualForm(AutoManual selected = AutoManual.Automatic)
        {
            InitializeComponent();

            Selected = selected;
            try
            {
                listBox.Items.Clear();
                var i = 0;
                foreach (var name in Enum.GetNames(typeof(AutoManual)))
                {
                    listBox.Items.Add($"{i + 1}. {name}");
                    ++i;
                }
                listBox.SelectedIndex = (int) selected;
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }

        private void listBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                Save(sender, e);
            }
        }

        private void Save(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Cancel(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedIndex == -1 ||
                listBox.SelectedIndex == (int)Selected)
            {
                return;
            }

            try
            {
                var selectedIndex = listBox.SelectedIndex;
                Selected = (AutoManual)selectedIndex;
            }
            catch (Exception exception)
            {
                MessageBoxUtilities.ShowException(exception);
            }
        }
    }
}
