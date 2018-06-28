using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;


namespace ExceptionHandling
{
    public partial class frmException : Form
    {
        public Exception ExceptionObject { get; set; }
        public string CustomMessage { get; set; }
        public bool ShowTrace { get; set; } = false;


        public frmException(Exception ex, string customMsg = null, bool showTrace = true)
        {
           InitializeComponent();
            ExceptionObject = ex;
            CustomMessage = customMsg?.ToString();
            ShowTrace = showTrace;
            lblCustomMessage.Text =  (customMsg == null ? ex?.Message.ToString():customMsg?.ToString());
            if (showTrace)
                txtExceptionDetail.Text = ex?.Message.ToString() + System.Environment.NewLine + ex.StackTrace.ToString();
        }


        /// <summary>
        /// Closes the form
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdAccept_Click(object sender, EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// Copies exception details to clipboard
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdCopy_Click(object sender, EventArgs e)
        {
            string copyText = string.Format("{0}{1}{1}{2}{1}{3}",CustomMessage?.ToString(),System.Environment.NewLine,
               ExceptionObject.Message.ToString(),ExceptionObject.StackTrace.ToString());
            Clipboard.Clear();
            Clipboard.SetText(copyText);
            
            Close();
        }

        /// <summary>
        /// Writes exception details to file in the same folder than executable application.
        /// Opens de newly created file.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdSaveToFile_Click(object sender, EventArgs e)
        {
            string copyText = string.Format("# {0}{1}{1}## {2}{1}{3}", CustomMessage?.ToString(), System.Environment.NewLine,
               ExceptionObject.Message.ToString(), ExceptionObject.StackTrace.ToString());
            //Save this text to a file
            string path = Application.StartupPath + "\\" + String.Format("T3000Exception-{0}{1}{2}{3}{4}.txt",DateTime.Now.Year,DateTime.Now.Month.ToString("00"),DateTime.Now.Day.ToString("00"),DateTime.Now.Hour.ToString("00"),DateTime.Now.Minute.ToString("00"));
            File.WriteAllText(path, copyText);
            //MessageBox.Show("Exception details written to file: " + path);
            ProcessStartInfo psi = new ProcessStartInfo(path);
            psi.UseShellExecute = true;
            Process.Start(psi);

            Close();
        }
    }
}
