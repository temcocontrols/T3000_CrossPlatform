namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 4 + 1 + 1 + 1 + 1 + 2 = 40 bytes
    /// </summary>
    public class StrOutPoint : BasePoint
    {
        /// <summary>
        /// Size: 4 bytes. Long?
        /// </summary>
        public float Value { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Digital
        /// </summary>
        public bool IsAnalog { get; set; }

        /// <summary>
        /// Size: 3 bits. 0-5
        /// </summary>
        public byte AccessLevel { get; set; }

        /// <summary>
        /// Size: 1 bit. false - off
        /// </summary>
        public bool Control { get; set; }

        /// <summary>
        /// Size: 1 bit. false - off
        /// </summary>
        public bool DigitalControl { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Decommissioned { get; set; }

        /// <summary>
        /// Size: 1 byte. output_range_equate
        /// </summary>
        public byte Range { get; set; }

        /// <summary>
        /// Size: 1 byte. if analog then low
        /// </summary>
        public byte MDelLow { get; set; }

        /// <summary>
        /// Size: 1 byte. if analog then high
        /// </summary>
        public byte SDelHigh { get; set; }

        /// <summary>
        /// Size: 2 bytes. Seconds, minutes
        /// </summary>
        public byte[] DelayTimer { get; set; }
    }
}