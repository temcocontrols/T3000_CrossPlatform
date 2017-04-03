namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 11 + 1 + 4 = 16 bytes
    /// </summary>
    public class View
    {
        /// <summary>
        /// Size: 11 bytes
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte OnOff { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int TimeRange { get; set; }
    }
}