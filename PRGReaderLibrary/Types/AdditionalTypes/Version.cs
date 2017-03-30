namespace PRGReaderLibrary
{
    public class Version
    {
        public FileVersion FileVersion { get; set; }

        public Version(FileVersion version)
        {
            FileVersion = version;
        }
    }
}
