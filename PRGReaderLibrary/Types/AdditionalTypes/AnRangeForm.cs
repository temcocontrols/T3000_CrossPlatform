namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 2 + 13 + 6 + 1 = 22 bytes
    /// </summary>
    public class AnRangeForm
    {
        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort Range { get; set; }

        /// <summary>
        /// Size: SizeConstants.SIZE_TEXT_RANGE(13) bytes
        /// </summary>
        public string RangeText { get; set; }

        /// <summary>
        /// Size: SizeConstants.SIZE_TEXT_UNITS(6) bytes
        /// </summary>
        public string AUnits { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Value { get; set; }
    }
}