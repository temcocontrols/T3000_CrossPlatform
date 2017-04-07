namespace T3000.Controls.Improved
{
    using System;
    using System.Windows.Forms;
    using System.Collections.Generic;

    /// <summary>
    /// Need full implementation(not override)
    /// </summary>
    public class TMonthCalendar : MonthCalendar
    {
        public List<DateTime> SelectedDates { get; set; } = new List<DateTime>();

        private void WmDateSelected(ref Message m)
        {
            var start = new DateTime(2017, 4, 7);
            var end = new DateTime(2017, 4, 11);
            SetSelectionRange(start, end);
        }

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case 513:
                    WmDateSelected(ref m);
                    break;

                default:
                    base.WndProc(ref m);
                    break;
            }
        }
    }
}
