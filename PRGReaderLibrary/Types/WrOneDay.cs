namespace PRGReaderLibrary
{
    public class Time
    {
        public byte Minutes { get; set; }
        public byte Hours { get; set; }

        public static Time FromBytes(byte[] data, int offset = 0)
        {
            var time = new Time();
            time.Minutes = data[0 + offset];
            time.Hours = data[1 + offset];

            return time;
        }
    }

    public class OnOffTime
    {
        public Time OnTime { get; set; }
        public Time OffTime { get; set; }

        public static OnOffTime FromBytes(byte[] data, int offset = 0)
        {
            var time = new OnOffTime();
            time.OnTime = Time.FromBytes(data, 0);
            time.OffTime = Time.FromBytes(data, 2);

            return time;
        }
    }

    public class WrOneDay
    {
        public OnOffTime time1 { get; set; }
        public OnOffTime time2 { get; set; }
        public OnOffTime time3 { get; set; }
        public OnOffTime time4 { get; set; }

        public static WrOneDay FromBytes(byte[] data, int offset = 0)
        {
            var day = new WrOneDay();
            day.time1 = OnOffTime.FromBytes(data, 0);
            day.time2 = OnOffTime.FromBytes(data, 4);
            day.time3 = OnOffTime.FromBytes(data, 8);
            day.time4 = OnOffTime.FromBytes(data, 12);

            return day;
        }
        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}