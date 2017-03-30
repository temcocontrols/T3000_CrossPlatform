namespace PRGReaderLibrary
{
    public class Version
    {
        public FileVersionEnum FileVersion { get; set; }

        public Version(FileVersionEnum version)
        {
            FileVersion = version;
        }
    }
}
