namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class AnalogCustomUnitsPoint : Version, IBinaryObject
    {
        public string Name { get; set; }

        public bool IsEmpty => string.IsNullOrWhiteSpace(Name);

        public AnalogCustomUnitsPoint(string name = "", 
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
        public AnalogCustomUnitsPoint(byte[] bytes, int offset = 0, 
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Name = bytes.GetString(0 + offset, 20).ClearBinarySymvols();
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
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

            return bytes.ToArray();
        }

        #endregion
    }
}