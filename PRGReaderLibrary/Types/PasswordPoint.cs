namespace PRGReaderLibrary
{
    public class PasswordPoint
    {
        public string Name { get; set; } // (16 byte s; string)
        public string Password { get; set; } // (9 byte s; string)
        public byte AccessLevel { get; set; } // (1 byte ; 0-99)
        public uint RightsAccess { get; set; }
        public byte DefaultPanel { get; set; }
        public byte DefaultGroup { get; set; }
        public long ScreenRights { get; set; } //char[8]
        public long ProgramRights { get; set; } //char[8]
    }
}