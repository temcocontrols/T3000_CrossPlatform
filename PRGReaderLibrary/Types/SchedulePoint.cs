namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class SchedulePoint : BasePoint, IBinaryObject
    {
        public OffOn Control { get; set; }
        public AutoManual AutoManual { get; set; }
        public OffOn Override1Control { get; set; }
        public OffOn Override2Control { get; set; }
        public int Off { get; set; }
        public int Unused { get; set; }
        public T3000Point Override1Point { get; set; } = new T3000Point();
        public T3000Point Override2Point { get; set; } = new T3000Point();

        public SchedulePoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 8;

                case FileVersion.Dos:
                    return 16;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 42;

                case FileVersion.Dos:
                    return 9;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - need 42 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public SchedulePoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            offset += BasePoint.GetSize(FileVersion);
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Control = (OffOn)bytes.ToByte(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    Override1Control = (OffOn)bytes.ToByte(ref offset);
                    Override2Control = (OffOn)bytes.ToByte(ref offset);
                    Off = bytes.ToByte(ref offset);
                    Unused = bytes.ToByte(ref offset);
                    var T3000PointSize = T3000Point.GetSize(FileVersion);
                    Override1Point = new T3000Point(bytes.ToBytes(ref offset, T3000PointSize), 0, FileVersion);
                    Override2Point = new T3000Point(bytes.ToBytes(ref offset, T3000PointSize), 0, FileVersion);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 42 bytes
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
                    bytes.Add((byte)Override1Control);
                    bytes.Add((byte)Override2Control);
                    bytes.Add((byte)Off);
                    bytes.Add((byte)Unused);
                    bytes.AddRange(Override1Point.ToBytes());
                    bytes.AddRange(Override2Point.ToBytes());
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