namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 4 + 2 + 2 + 4 = 12 bytes
    /// </summary>
    public class InfoTable
    {
        /// <summary>
        /// Size: 4 bytes. Modified. Initially ptr(4)
        /// </summary>
        public string Address { get; set; }

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort StringSize { get; set; }

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort MaxPoints { get; set; }

        /// <summary>
        /// Size: 4 bytes. Modified. Initially ptr(4)
        /// </summary>
        public string Name { get; set; }
    }
}