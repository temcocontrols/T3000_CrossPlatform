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

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            var size = BasePoint.GetSize(version);
            switch (version)
            {
                case FileVersion.Current:
                    return size + 7;

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
            offset += BasePoint.GetSize(FileVersion);

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Length = bytes.ToUInt16(ref offset);
                    Control = (OffOn)bytes.ToByte(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    NormalCom = (NormalCom)bytes.ToByte(ref offset);
                    ErrorCode = bytes.ToByte(ref offset);
                    Unused = bytes.ToByte(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
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

            CheckSize(bytes.Count, GetSize(FileVersion));

            return bytes.ToArray();
        }

        #endregion
    }
}