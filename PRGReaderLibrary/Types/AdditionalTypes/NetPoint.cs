namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 3 + 2 = 5 bytes
    /// </summary>
    public class NetPoint : T3000Point
    {
        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort Network { get; set; }
    }
}