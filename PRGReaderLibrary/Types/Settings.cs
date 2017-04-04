namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class Settings : Version, IBinaryObject
    {
        public byte[] Unused { get; set; }

        public Settings(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 1;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 400;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 400 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public Settings(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Unused = bytes.ToBytes(0 + offset, 400);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 400 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Unused);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}