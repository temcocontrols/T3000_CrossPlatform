namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 2 + 3 + 3 = 38 bytes
    /// </summary>
    public class StrWeeklyRoutinePoint : BasePoint
    {
        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - off, false - on
        /// </summary>
        public bool Override_1_value { get; set; }

        /// <summary>
        /// Size: 1 bit. false - off, false - on
        /// </summary>
        public bool Override_2_value { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Off { get; set; }

        /// <summary>
        /// Size: 11 bits
        /// </summary>
        public byte[] Unused { get; set; }

        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point Override_1 { get; set; }

        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point Override_2 { get; set; }
    }
}