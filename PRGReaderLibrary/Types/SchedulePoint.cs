namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class SchedulePoint : BasePoint, IBinaryObject
    {
        public Control Control { get; set; }
        public AutoManual AutoManual { get; set; }
        public Control Override1Control { get; set; }
        public Control Override2Control { get; set; }
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

        public static int GetSize(FileVersion version = FileVersion.Current)
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
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Control = (Control)bytes.ToByte(30 + offset);
                    AutoManual = (AutoManual)bytes.ToByte(31 + offset);
                    Override1Control = (Control)bytes.ToByte(32 + offset);
                    Override2Control = (Control)bytes.ToByte(33 + offset);
                    Off = bytes.ToByte(34 + offset);
                    Unused = bytes.ToByte(35 + offset);
                    Override1Point = new T3000Point(bytes.ToBytes(36 + offset, 3), 0, FileVersion);
                    Override2Point = new T3000Point(bytes.ToBytes(39 + offset, 3), 0, FileVersion);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
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

            return bytes.ToArray();
        }

        #endregion
    }
}