namespace PRGReaderLibrary
{
    public class Version
    {
        public FileVersion FileVersion { get; set; }

        public Version(FileVersion version)
        {
            FileVersion = version;
        }

        protected void CheckOffset(int offset, int size)
        {
            if (offset != size)
            {
                throw new OffsetException(offset, size);
            }
        }

        protected void CheckSize(int size, int needSize)
        {
            if (size != needSize)
            {
                throw new OffsetException(size, needSize);
            }
        }
    }
}
