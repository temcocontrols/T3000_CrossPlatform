namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 4 + 1 + 8 + 4 + 8 + 8 + 56 + 56 = 145 bytes
    /// </summary>
    public class StrMonitorWorkData
    {
        /// <summary>
        /// Size: 4 bytes. Modified. Initially ptr(4).
        /// </summary>
        public byte[] DataSegment { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Start { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Saved { get; set; }

        /// <summary>
        /// Size: 6 bits
        /// </summary>
        public byte Unused { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public ulong NextSampleTime { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint HeadIndex { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public ulong LastSampleTime { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public ulong LastSampleSavedTime { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_POINTS_IN_MONITOR(14) * 4 = 56 bytes
        /// </summary>
        public uint[] StartIndexDig { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_POINTS_IN_MONITOR(14) * 4 = 56 bytes
        /// </summary>
        public uint[] EndIndexDig { get; set; }
    }
}