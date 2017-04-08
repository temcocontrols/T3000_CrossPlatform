namespace T3000.Controls
{
    using System;
    using System.Windows.Forms;
    using System.ComponentModel;
    using MultipleMonthCalendarControls;

    public partial class MultipleMonthCalendar : UserControl
    {
        #region Properties
        
        [Description("Dimension X value"), Category("MultipleMonthCalendar")]
        public int DimensionX {
            get { return monthsControl.DimensionX; }
            set { monthsControl.DimensionX = value; }
        }

        [Description("Dimension Y value"), Category("MultipleMonthCalendar")]
        public int DimensionY {
            get { return monthsControl.DimensionY; }
            set { monthsControl.DimensionY = value; }
        }

        [Description("Start date"), Category("MultipleMonthCalendar")]
        public DateTime StartDate {
            get { return monthsControl.StartDate; }
            set { monthsControl.StartDate = value; }
        }
        
        #endregion

        #region Overrided

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
        }

        #endregion

        public MultipleMonthCalendar()
        {
            InitializeComponent();

            ResizeRedraw = true;

            nextButton.Click += (sender, args) => 
                monthsControl.StartDate = MonthUtilities.GetNextMonth(monthsControl.StartDate);

            prevButton.Click += (sender, args) =>
                monthsControl.StartDate = MonthUtilities.GetPrevMonth(monthsControl.StartDate);
        }
    }
}
