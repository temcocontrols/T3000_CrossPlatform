namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class GraphicPoint : Version, IBinaryObject
    {
        public int LabelStatus { get; set; }
        public long SerialNumber { get; set; }
        public int ScreenIndex { get; set; }
        public int LabelIndex { get; set; }
        public int MainPanel { get; set; }
        public int SubPanel { get; set; }
        public int PointType { get; set; }
        public int PointNumber { get; set; }
        public int PointX { get; set; }
        public int PointY { get; set; }
        public long ClrTxt { get; set; }
        public int DisplayType { get; set; }
        public int IconSize { get; set; }
        public int IconPlace { get; set; }
        public string IconName1 { get; set; } = string.Empty;
        public string IconName2 { get; set; } = string.Empty;
        public byte[] Unused { get; set; }

        public GraphicPoint(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 240;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 70;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 70 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public GraphicPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    LabelStatus = bytes.ToByte(0 + offset);
                    SerialNumber = bytes.ToUInt32(1 + offset);
                    ScreenIndex = bytes.ToByte(5 + offset);
                    LabelIndex = bytes.ToUInt16(6 + offset);
                    MainPanel = bytes.ToByte(8 + offset);
                    SubPanel = bytes.ToByte(9 + offset);
                    PointType = bytes.ToByte(10 + offset);
                    PointNumber = bytes.ToByte(11 + offset);
                    PointX = bytes.ToUInt16(12 + offset);
                    PointY = bytes.ToUInt16(14 + offset);
                    ClrTxt = bytes.ToUInt32(16 + offset);
                    DisplayType = bytes.ToByte(20 + offset);
                    IconSize = bytes.ToByte(21 + offset);
                    IconPlace = bytes.ToByte(22 + offset);
                    IconName1 = bytes.GetString(23 + offset, 20).ClearBinarySymvols();
                    IconName2 = bytes.GetString(43 + offset, 20).ClearBinarySymvols();
                    Unused = bytes.ToBytes(63 + offset, 7);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 70 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.Add((byte)LabelStatus);
                    bytes.AddRange(((uint)SerialNumber).ToBytes());
                    bytes.Add((byte)ScreenIndex);
                    bytes.AddRange(((ushort)LabelIndex).ToBytes());
                    bytes.Add((byte)MainPanel);
                    bytes.Add((byte)SubPanel);
                    bytes.Add((byte)PointType);
                    bytes.Add((byte)PointNumber);
                    bytes.AddRange(((ushort)PointX).ToBytes());
                    bytes.AddRange(((ushort)PointY).ToBytes());
                    bytes.AddRange(((uint)ClrTxt).ToBytes());
                    bytes.Add((byte)DisplayType);
                    bytes.Add((byte)IconSize);
                    bytes.Add((byte)IconPlace);
                    bytes.AddRange(IconName1.ToBytes(20));
                    bytes.AddRange(IconName2.ToBytes(20));
                    bytes.AddRange((Unused ?? new byte[7]).ToBytes(0, 7));
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}