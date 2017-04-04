namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class TableValue : Version, IBinaryObject
    {
        public int Value { get; set; }
        public int Units { get; set; }

        public TableValue(int value = 0, int units = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            Value = value;
            Units = Units;
        }

        public override int GetHashCode() => Value.GetHashCode() ^ Units.GetHashCode();
        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 6 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public TableValue(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Value = bytes.ToUInt16(0 + offset);
                    Units = bytes.ToInt32(2 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 6 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(((ushort)Value).ToBytes());
                    bytes.AddRange(((int)Units).ToBytes());
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}