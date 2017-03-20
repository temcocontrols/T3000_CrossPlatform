namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 3 + 3 + 4 + 8 + 8 + 8 + 8 + 8 + 4 + 1 + 4 = 59 bytes
    /// </summary>
    public class AlarmSetPoint
    {
        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point Point { get; set; }

        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point Point1 { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint Cond1 { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long WayLow { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long Low { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long Normal { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long High { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long WayHigh { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint Time { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public sbyte NrMes { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint Count { get; set; }
    }
}