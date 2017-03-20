namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 11 + 2 + 4 + 4 + 2 + 2 + 2 + 1 + 2 + 2 = 32 bytes
    /// </summary>
    public class StrGrpElement
    {
        /// <summary>
        /// Size: 11 bytes
        /// </summary>
        public PointInfo PointInfo { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool ShowPoint { get; set; }

        /// <summary>
        /// Size: 7 bits
        /// </summary>
        public byte IconNameIndex { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte NrElement { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint HighLimit { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint LowLimit { get; set; }

        /// <summary>
        /// Size: 10 bits
        /// </summary>
        public ushort GraphicYCoordinate { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte OffLowColor { get; set; }

        /// <summary>
        /// Size: 2 bits
        /// </summary>
        public byte TypeIcon { get; set; }

        /// <summary>
        /// Size: 10 bits
        /// </summary>
        public ushort GraphicXCoordinate { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte OnHighColor { get; set; }

        /// <summary>
        /// Size: 1 bits
        /// </summary>
        public bool DisplayPointName { get; set; }

        /// <summary>
        /// Size: 1 bits
        /// </summary>
        public bool DefaultIcon { get; set; }

        /// <summary>
        /// Size: 7 bits
        /// </summary>
        public byte TextXCoordinate { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Modify { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Point present
        /// </summary>
        public bool PointAbsent { get; set; }

        /// <summary>
        /// Size: 2 bits
        /// </summary>
        public byte WherePoint { get; set; }

        /// <summary>
        /// Size: 5 bits
        /// </summary>
        public byte TextYCoordinate { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public sbyte BackgroundIcon { get; set; }

        /// <summary>
        /// Size: 10 bits
        /// </summary>
        public ushort XIcon { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte TextPlace { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool TextPresent { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool IconPresent { get; set; }

        /// <summary>
        /// Size: 10 bits
        /// </summary>
        public ushort YIcon { get; set; }

        /// <summary>
        /// Size: 2 bits
        /// </summary>
        public byte TextSize { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte NormalColor { get; set; }
    }
}