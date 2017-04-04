namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;

    public class TablePoint : Version, IBinaryObject
    {
        public string Name { get; set; }
        public List<TableValue> Values { get; set; } = new List<TableValue>();

        public TablePoint(string name = "", List<TableValue> values = null,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Name = name;
            Values = values ?? Values;
        }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 5;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 105;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 105 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public TablePoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Name = bytes.GetString(0 + offset, 9).ClearBinarySymvols();
                    for (int i = 0; i < 16; ++i)
                    {
                        Values.Add(new TableValue(bytes.ToBytes(9 + i * 6 + offset, 6), 0, FileVersion));
                    }
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 105 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Name.ToBytes(9));
                    for (int i = 0; i < 16; ++i)
                    {
                        var value = Values.ElementAtOrDefault(i) ?? new TableValue();
                        value.FileVersion = FileVersion;
                        bytes.AddRange(value.ToBytes());
                    }
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}