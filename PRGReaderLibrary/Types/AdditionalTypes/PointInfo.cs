namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 5 + 4 + 1 + 1 = 11 bytes
    /// </summary>
    public class PointInfo
    {
        /// <summary>
        /// Size: 5 bytes
        /// </summary>
        public NetPoint Point { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public float Value { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool ManualControl { get; set; }  // 0=auto, 1=manual

        /// <summary>
        /// Size: 1 bit. false - Digital
        /// </summary>
        public bool IsAnalog { get; set; }

        /// <summary>
        /// Size: 3 bits. false - Display description
        /// </summary>
        public bool IsDisplayLabel { get; set; }

        /// <summary>
        /// Size: 2 bits. 0-3 correspond to 2-5 access level
        /// </summary>
        public byte Security { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool IsDecomisioned { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public Units Unit { get; set; }
    }
}