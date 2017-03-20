namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 1 + 12 + 12 = 25 bytes
    /// </summary>
    public class UnitsElement
    {
        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Direct { get; set; }

        /// <summary>
        /// Size: 12 bytes
        /// </summary>
        public string DigitalUnitsOff { get; set; }

        /// <summary>
        /// Size: 12 bytes
        /// </summary>
        public string DigitalUnitsOn { get; set; }
    }
}