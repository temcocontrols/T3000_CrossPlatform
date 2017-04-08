namespace T3000.Controls
{
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Windows.Forms;
    using MultipleMonthCalendarControls;
    using System.Collections.Generic;

    public partial class MultipleMonthCalendar : UserControl
    {
        #region Properties

        private int _dimensionX = 1;
        [Description("Dimension X value"), Category("MultipleMonthCalendar")]
        public int DimensionX {
            get { return _dimensionX; }
            set {
                _dimensionX = value;
                InitializeMonths();

                Invalidate();
            }
        }

        private int _dimensionY = 1;
        [Description("Dimension Y value"), Category("MultipleMonthCalendar")]
        public int DimensionY {
            get { return _dimensionY; }
            set {
                _dimensionY = value;
                InitializeMonths();

                Invalidate();
            }
        }

        private DateTime _startDate = DateTime.Today;
        [Description("Start date"), Category("MultipleMonthCalendar")]
        public DateTime StartDate {
            get { return _startDate; }
            set {
                _startDate = value;
                UpdateMonths();
                Invalidate();
            }
        }

        #endregion

        #region Utilities

        public static int GetCalendarCount(MultipleMonthCalendar calendar) =>
            calendar.DimensionX*calendar.DimensionY;

        public static int MonthDiff(DateTime time1, DateTime time2) =>
            (time2.Year - time1.Year) * 12 + time2.Month - time1.Month;

        public static int MonthLength(int year, int month) =>
            DateTime.DaysInMonth(year, month);

        public static bool IsDateEquals(DateTime time1, DateTime time2) =>
            time1.Year == time2.Year &&
            time1.Month == time2.Month &&
            time1.Day == time2.Day;

        /// <summary>
        /// Copies timestamp part only
        /// </summary>
        public static DateTime CopyTime(DateTime from, DateTime to) =>
            new DateTime(to.Year, to.Month, to.Day, from.Hour, from.Minute, from.Second);

        /// <summary>
        /// Copies date part only
        /// </summary>
        public static DateTime CopyDate(DateTime from, DateTime to) =>
            new DateTime(from.Year, from.Month, from.Day, to.Hour, to.Minute, to.Second);

        public static int CompareMonths(DateTime date1, DateTime date2)
        {
            var monthDate1 = new DateTime(date1.Year, date1.Month, 1);
            var monthDate2 = new DateTime(date2.Year, date2.Month, 1);

            return DateTime.Compare(monthDate1, monthDate2);
        }

        public static int CompareDate(DateTime date1, DateTime date2)
        {
            var monthDate1 = new DateTime(date1.Year, date1.Month, date1.Day);
            var monthDate2 = new DateTime(date2.Year, date2.Month, date2.Day);

            return DateTime.Compare(monthDate1, monthDate2);
        }

        /// <summary>
        /// Adds/subtracts 'months' from date
        /// </summary>
        /// <param name="date"></param>
        /// <param name="months"></param>
        /// <returns></returns>
        public static DateTime GetMonth(DateTime date, int months)
        {
            var m = date.Month + months;

            var newYear = date.Year + (m > 0 ? (m - 1) / 12 : m / 12 - 1);
            var newMonth = date.Month + ( m > 0 ? (m - 1) % 12 + 1 : 12 + m % 12 );

            /* fix moving from last day in a month */
            var length = MonthLength(newYear, newMonth);

            return new DateTime(newYear, newMonth, date.Day > length ? length : date.Day);
        }

        public static DateTime GetNextMonth(DateTime date) => GetMonth(date, 1);
        public static DateTime GetPrevMonth(DateTime date) => GetMonth(date, -1);
        
        #endregion

        #region Months

        private List<MonthControl> Months = new List<MonthControl>();
        private void InitializeMonths()
        {
            var currentMonthLength = GetCalendarCount(this);
            if (currentMonthLength == Months.Count)
            {
                return;
            }

            Controls.Clear();
            Months.Clear();

            for (var i = 0; i < currentMonthLength; ++i)
            {
                var month = new MonthControl();
                Controls.Add(month);
                Months.Add(month);
            }
            ResizeMonths();
            UpdateMonths();
        }

        private void ResizeMonths()
        {
            var width = (Width - 10) / (1.0 * DimensionX);
            var heigth = (Height - 10) / (1.0 * DimensionY);
            var size = new Size(Convert.ToInt32(width), Convert.ToInt32(heigth));
            for (var i = 0; i < Months.Count; ++i)
            {
                var month = Months[i];
                var x = i % DimensionX;
                var y = i / DimensionX;

                month.Left = 5 + x * size.Width;
                month.Top = 5 + y * size.Height;
                month.Size = size;
            }
        }

        private void UpdateMonths()
        {
            for (var i = 0; i < Months.Count; ++i)
            {
                var month = Months[i];

                month.Date = GetMonth(StartDate, i);
            }
        }

        #endregion

        #region Overrided

        protected override void OnResize(EventArgs e)
        {
            ResizeMonths();

            base.OnResize(e);
        }

        #endregion

        public MultipleMonthCalendar()
        {
            InitializeComponent();
            InitializeMonths();

            ResizeRedraw = true;
        }
    }
}
