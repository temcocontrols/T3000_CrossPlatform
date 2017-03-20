namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 9 + 4 = 13 bytes
    /// </summary>
    public class StrArrayPoint
    {
        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        public string Label { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int Length { get; set; }
    }
}