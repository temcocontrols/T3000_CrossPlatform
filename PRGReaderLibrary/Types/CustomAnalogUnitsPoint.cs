namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class CustomAnalogUnitsPoint : Version, IBinaryObject, ICloneable
    {
        public string Name { get; set; }

        public bool IsEmpty => string.IsNullOrWhiteSpace(Name);

        public CustomAnalogUnitsPoint(string name = "", 
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Name = name;
        }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 5;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 20;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 20 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public CustomAnalogUnitsPoint(byte[] bytes, int offset = 0, 
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Name = bytes.GetString(ref offset, 20).ClearBinarySymvols();
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
        /// FileVersion.Current - 20 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Name.ToBytes(20));
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

        public object Clone() => new CustomAnalogUnitsPoint(Name, FileVersion);
    }
}