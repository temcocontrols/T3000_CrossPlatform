namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class HolidayPoint : BasePoint, IBinaryObject
    {
        public OffOn Control { get; set; }
        public AutoManual AutoManual { get; set; }
        public int Unused { get; set; }

        public HolidayPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 4;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            var size = BasePoint.GetSize(version);
            switch (version)
            {
                case FileVersion.Current:
                    return size + 3;

                case FileVersion.Dos:
                    return size + 16;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - need 33 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public HolidayPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            offset += BasePoint.GetSize(FileVersion);

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Control = (OffOn)bytes.ToByte(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    Unused = bytes.ToByte(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 33 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.Add((byte)Control);
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)Unused);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckSize(bytes.Count, GetSize(FileVersion));

            return bytes.ToArray();
        }

        #endregion
    }
}