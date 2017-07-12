namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class ScreenPoint : BasePoint, IBinaryObject
    {
        public string PictureFile { get; set; } = string.Empty;
       
        public int RefreshTime { get; set; }
        public TextGraphic GraphicMode { get; set; }
        public int X { get; set; }
        public int Y { get; set; }

        public ScreenPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 16; //add 16

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
                    return size + 16;   //add 16

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 46 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ScreenPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            offset += BasePoint.GetSize(FileVersion);

            switch (FileVersion)
            {
                case FileVersion.Current:
                    PictureFile = bytes.GetString(ref offset, 11).ClearBinarySymvols();
                    RefreshTime = bytes.ToByte(ref offset);
                    GraphicMode = (TextGraphic)bytes.ToByte(ref offset);
                    X = bytes.ToByte(ref offset);
                    Y = bytes.ToUInt16(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 46 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(PictureFile.ToBytes(11));
                    bytes.Add((byte)RefreshTime);
                    bytes.Add((byte)GraphicMode);
                    bytes.Add((byte)X);
                    bytes.AddRange(((ushort)Y).ToBytes());
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