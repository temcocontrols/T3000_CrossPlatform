namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 16 + 9 + 1 + 4 + 1 + 1 + 8 + 8 = 48 bytes
    /// </summary>
    public class PasswordPoint
    {
        /// <summary>
        /// Size: 16 bytes
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        public string Password { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-99
        /// </summary>
        public byte AccessLevel { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint RightsAccess { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte DefaultPanel { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte DefaultGroup { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long ScreenRights { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public long ProgramRights { get; set; }
    }
}