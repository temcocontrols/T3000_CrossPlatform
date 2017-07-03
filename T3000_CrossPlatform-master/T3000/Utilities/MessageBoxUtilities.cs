namespace T3000
{
    using Properties;
    using System;
    using System.Windows.Forms;

    public static class MessageBoxUtilities
    {
        public static void ShowException(Exception exception) =>
            MessageBox.Show(string.Format(
                Resources.Exception, exception.Message,
#if DEBUG
    exception.StackTrace
#else
    ""
#endif
                ), 
                Resources.ExceptionTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);

        public static void ShowWarning(string message) =>
            MessageBox.Show(string.Format(
                Resources.Warning, message),
                Resources.WarningTitle, MessageBoxButtons.OK, MessageBoxIcon.Warning);

    }
}
