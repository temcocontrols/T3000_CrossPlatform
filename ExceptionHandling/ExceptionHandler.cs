using System;

namespace ExceptionHandling
{
    public class ExceptionHandler
    {

        /// <summary>
        /// Creates a dialog form for exception details
        /// </summary>
        /// <param name="ex">Exception</param>
        /// <param name="customMsg">Optional Custom Message</param>
        /// <param name="showTrace">Show stack trace? Default= True</param>
        public static void Show(Exception ex, String customMsg = null, bool showTrace = true)
        {
            frmException objForm = new frmException(ex,customMsg,showTrace);
            objForm.ShowDialog();

        }

    }
}
