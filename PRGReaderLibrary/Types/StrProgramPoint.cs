namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 2 + 1 + 1 = 34 bytes
    /// </summary>
    public class StrProgramPoint : BasePoint
    {
        /// <summary>
        /// Size: 2 bytes. Size in bytes of program
        /// </summary>
        public ushort Bytes { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Normal
        /// </summary>
        public bool IsComProgram { get; set; }

        /// <summary>
        /// Size: 5 bits. 0=normal end, 1=too long in program
        /// </summary>
        public short ErrorCode { get; set; }

        /// <summary>
        /// Size: 1 byte. Because of mini's
        /// </summary>
        public byte Unused { get; set; }

    }
}