namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class ProgramPoint : BasePoint, IBinaryObject
    {
        public int Length { get; set; }
        public OffOn Control { get; set; }
        public AutoManual AutoManual { get; set; }
        public NormalCom NormalCom { get; set; }
        public int ErrorCode { get; set; }
        public int Unused { get; set; }

        public ProgramPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
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
                    return 37;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 37 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ProgramPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Length = bytes.ToUInt16(30 + offset);
                    Control = (OffOn)bytes.ToByte(32 + offset);
                    AutoManual = (AutoManual)bytes.ToByte(33 + offset);
                    NormalCom = (NormalCom)bytes.ToByte(34 + offset);
                    ErrorCode = bytes.ToByte(35 + offset);
                    Unused = bytes.ToByte(36 + offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 37 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(((ushort)Length).ToBytes());
                    bytes.Add((byte)Control);
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)NormalCom);
                    bytes.Add((byte)ErrorCode);
                    bytes.Add((byte)Unused);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}