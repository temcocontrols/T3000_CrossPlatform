namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 1 + 4 + 2 + 4 + 1 + 17 + 2 + 17 = 48 bytes
    /// </summary>
    public class PanelInfo1
    {
        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Type { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint ActivePanelsCount { get; set; }

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort DesLength { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int Version { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Number { get; set; }

        /// <summary>
        /// Size: SizeConstants.NAME_SIZE(17) bytes
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Size: 2 bytes
        /// </summary>
        public ushort Network { get; set; }

        /// <summary>
        /// Size: SizeConstants.NAME_SIZE(17) bytes
        /// </summary>
        public string NetworkName { get; set; }
    }
}