namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 2 = 32 bytes
    /// </summary>
    public class StrAnnualRoutinePoint : BasePoint
    {
        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool ManualControl { get; set; }

        /// <summary>
        /// Size: 14 bits
        /// </summary>
        public byte[] Unused { get; set; } /* (14 bits)*/

    }
}