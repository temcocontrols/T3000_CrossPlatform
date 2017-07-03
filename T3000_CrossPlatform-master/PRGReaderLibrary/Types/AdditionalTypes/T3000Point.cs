namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class T3000Point : Version, IBinaryObject
    {
        public int Number { get; set; }
        public PanelType Type { get; set; }
        public int Panel { get; set; }

        public T3000Point(int number = 0,
            PanelType type = PanelType.T3000,
            int panel = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Number = number;
            Type = type;
            Panel = panel;
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 3;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public override int GetHashCode() =>
            Number.GetHashCode() ^ Type.GetHashCode() ^ Panel.GetHashCode();

        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 3 bytes array
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public T3000Point(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Number = bytes.ToByte(ref offset);
                    Type = (PanelType)bytes.ToByte(ref offset);
                    Panel = bytes.ToByte(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 3 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.Add((byte)Number);
                    bytes.Add((byte)Type);
                    bytes.Add((byte)Panel);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}