namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 17 + 17 + 1 + 4 + 4 + 1 + 1 + 4 + 15 = 64 bytes
    /// </summary>
    public class StationPoint
    {
        /// <summary>
        /// Size: SizeConstants.NAME_SIZE(17) bytes
        /// </summary>
        public string HardName { get; set; }

        /// <summary>
        /// Size: SizeConstants.NAME_SIZE(17) bytes
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public string Number { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint DesLength { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint DesckSum { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte State { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public Panels PanelType { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int Version { get; set; }

        /// <summary>
        /// Size: SizeConstants.MAX_TBL_BANK(15)
        /// </summary>
        public byte[] TblBank { get; set; }
    }
}