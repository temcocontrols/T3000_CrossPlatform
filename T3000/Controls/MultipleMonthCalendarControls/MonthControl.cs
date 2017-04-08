﻿namespace T3000.Controls.MultipleMonthCalendarControls
{
    using System;
    using System.Linq;
    using System.Drawing;
    using System.Windows.Forms;
    using System.ComponentModel;
    using System.Collections.Generic;

    public partial class MonthControl : UserControl
    {
        #region Properties

        private DateTime _date = DateTime.Today;
        [Description("Is selected"), Category("DayControl")]
        public DateTime Date {
            get { return _date; }
            set {
                _date = value;

                UpdateDays();
            }
        }

        public List<DateTime> SelectedDays =>
            Days.Where(i => i.IsSelected).Select(i => i.Date).ToList();

        #endregion

        #region Days

        private List<DayControl> Days = new List<DayControl>();
        private void UpdateDays()
        {
            var offset = (int)Date.DayOfWeek;
            for (var i = 0; i < 35; ++i)
            {
                var day = Days[i];
                if (i - offset >= 0 && i - offset < DateTime.DaysInMonth(Date.Year, Date.Month))
                {
                    day.Date = new DateTime(Date.Year, Date.Month, i - offset + 1);
                }
            }
            titleButton.Text = Date.ToString("MMMM yyyy");

            Invalidate();
        }

        private void InitializeDays()
        {
            var width = (Width - 10) / 7.0;
            var heigth = (Height - 10 - 40) / 5.0;
            var size = new Size(Convert.ToInt32(width), Convert.ToInt32(heigth));
            for (var i = 0; i < 35; ++i)
            {
                var x = i % 7;
                var y = i / 7;

                var day = new DayControl();
                day.Left = 5 + x * size.Width;
                day.Top = 45 + y * size.Height;
                day.Size = size;
                day.Click += (sender, args) => day.IsSelected = !day.IsSelected;
                Controls.Add(day);
                Days.Add(day);
            }

            Invalidate();
        }

        #endregion

        public MonthControl()
        {
            InitializeComponent();
            InitializeDays();

            Click += (sender, args) => MessageBox.Show($"SelectedDates: {SelectedDays.Count}");
        }
    }
}
