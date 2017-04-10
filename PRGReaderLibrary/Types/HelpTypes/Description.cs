namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class DescriptionPoint : Version, IBinaryObject
    {
        public string Description { get; set; }

        public DescriptionPoint(string description = "", FileVersion version = FileVersion.Current)
            : base(version)
        {
            Description = description;
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Dos:
                case FileVersion.Current:
                    return 21;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 21 bytes
        /// FileVersion.Dos - Need 21 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public DescriptionPoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                case FileVersion.Dos:
                    Description = bytes.GetString(ref offset, 21).ClearBinarySymvols();
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            var size = GetSize(FileVersion);
            if (offset != size)
            {
                throw new OffsetException(offset, size);
            }
        }

        /// <summary>
        /// FileVersion.Current - 21 bytes
        /// FileVersion.Dos - 21 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                case FileVersion.Dos:
                    bytes.AddRange(Description.ToBytes(21));
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            var size = GetSize(FileVersion);
            if (bytes.Count != size)
            {
                throw new OffsetException(bytes.Count, size);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}