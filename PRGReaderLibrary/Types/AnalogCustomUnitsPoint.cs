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
                    throw new NotImplementedException("File version is not implemented");
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
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}