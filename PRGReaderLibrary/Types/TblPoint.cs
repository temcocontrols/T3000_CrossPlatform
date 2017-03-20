namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 6 bytes
    /// </summary>
    public class TblPoint
    {
        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort Value { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public UnitsEnum Unit { get; set; }
    }
}