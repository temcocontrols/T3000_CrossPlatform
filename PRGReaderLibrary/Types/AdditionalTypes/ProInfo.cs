namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class ProInfo : Version, IBinaryObject
    {
        public int HardwareRev { get; set; }
        public int Firmware0RevMain { get; set; }
        public int Firmware0RevSub { get; set; }

        /// <summary>
        /// PIC
        /// </summary>
        public int Firmware1Rev { get; set; }

        /// <summary>
        /// C8051
        /// </summary>
        public int Firmware2Rev { get; set; }

        /// <summary>
        /// SM5964
        /// </summary>
        public int Firmware3Rev { get; set; }

        public int BootloaderRev { get; set; }

        public byte[] Unused { get; set; }

        public ProInfo(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        public override int GetHashCode() =>
            HardwareRev.GetHashCode() ^ 
            Firmware0RevMain.GetHashCode() ^ 
            Firmware0RevSub.GetHashCode() ^
            Firmware1Rev.GetHashCode() ^
            Firmware2Rev.GetHashCode() ^
            Firmware3Rev.GetHashCode() ^
            BootloaderRev.GetHashCode();

        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 17 bytes array
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ProInfo(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    HardwareRev = bytes.ToByte(0 + offset);
                    Firmware0RevMain = bytes.ToByte(1 + offset);
                    Firmware0RevSub = bytes.ToByte(2 + offset);
                    Firmware1Rev = bytes.ToByte(3 + offset);
                    Firmware2Rev = bytes.ToByte(4 + offset);
                    Firmware3Rev = bytes.ToByte(5 + offset);
                    BootloaderRev = bytes.ToByte(6 + offset);
                    Unused = bytes.ToBytes(7 + offset, 10);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 17 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.Add((byte)HardwareRev);
                    bytes.Add((byte)Firmware0RevMain);
                    bytes.Add((byte)Firmware0RevSub);
                    bytes.Add((byte)Firmware1Rev);
                    bytes.Add((byte)Firmware2Rev);
                    bytes.Add((byte)Firmware3Rev);
                    bytes.Add((byte)BootloaderRev);
                    bytes.AddRange(Unused?.ToBytes(0, 10) ?? new byte[10]);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}