namespace PRGReaderLibrary
{
    using System.Collections.Generic;

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

        public static Time FromBytes(byte[] bytes, int offset = 0)
        {
            var time = new Time();
            time.Minutes = bytes[0 + offset];
            time.Hours = bytes[1 + offset];

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

        public static OnOffTime FromBytes(byte[] bytes, int offset = 0)
        {
            var time = new OnOffTime();
            time.OnTime = Time.FromBytes(bytes, 0);
            time.OffTime = Time.FromBytes(bytes, 2);

            return time;
        }
    }

    /// <summary>
    /// Size: 16 bytes
    /// </summary>
    public class WrOneDay
    {
        /// <summary>
        /// Size: 4 * 4 = 16 bytes
        /// </summary>
        public IList<OnOffTime> Times { get; set; } = new List<OnOffTime>();

        public static WrOneDay FromBytes(byte[] bytes, int offset = 0)
        {
            var day = new WrOneDay();
            for (var i = 0; i < 4; ++i)
            {
                day.Times.Add(OnOffTime.FromBytes(bytes, 4 * i));
            }

            return day;
        }
    }
}