namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 2 bytes
    /// </summary>
    public class Time
    {
        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Minutes { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Hours { get; set; }

        public static Time FromBytes(byte[] data, int offset = 0)
        {
            var time = new Time();
            time.Minutes = data[0 + offset];
            time.Hours = data[1 + offset];

            return time;
        }
    }

    /// <summary>
    /// Size: 2 + 2 = 4 bytes
    /// </summary>
    public class OnOffTime
    {

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public Time OnTime { get; set; }

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public Time OffTime { get; set; }

        public static OnOffTime FromBytes(byte[] data, int offset = 0)
        {
            var time = new OnOffTime();
            time.OnTime = Time.FromBytes(data, 0);
            time.OffTime = Time.FromBytes(data, 2);

            return time;
        }
    }

    /// <summary>
    /// Size: 4 + 4 + 4 + 4 = 16 bytes
    /// </summary>
    public class WrOneDay
    {

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public OnOffTime time1 { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public OnOffTime time2 { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public OnOffTime time3 { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
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
    }
}