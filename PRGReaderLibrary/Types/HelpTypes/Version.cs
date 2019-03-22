namespace PRGReaderLibrary
{
    public class Version
    {
        public FileVersion FileVersion { get; set; }

        public Version(FileVersion version)
        {
            FileVersion = version;
        }

        public Version() {; }

        protected void CheckSize(int size, int needSize)
        {
            if (size != needSize)
            {
                throw new OffsetException(size, needSize);
            }
        }

        protected void CheckOffset(int offset, int size) =>
            CheckSize(offset, size);
    }
}
