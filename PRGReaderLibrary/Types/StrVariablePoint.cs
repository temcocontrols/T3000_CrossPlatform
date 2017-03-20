namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 4 + 1 + 1 = 36
    /// </summary>
    public class StrVariablePoint : BasePoint
    {
        /// <summary>
        /// Size: 4 bytes
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
        /// Size: 1 bit
        /// </summary>
        public bool IsControl { get; set; }

        /// <summary>
        /// Size: 5 bit
        /// </summary>
        public byte Unused { get; set; }

        /// <summary>
        /// Size: 1 byte. variable_range_equate
        /// </summary>
        public byte Range { get; set; }
    }
}