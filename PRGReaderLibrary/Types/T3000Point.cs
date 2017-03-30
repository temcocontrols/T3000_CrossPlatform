namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 3 bytes
    /// </summary>
    public class T3000Point
    {
        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Number { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public Panels Type { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Panel { get; set; }
    }
}