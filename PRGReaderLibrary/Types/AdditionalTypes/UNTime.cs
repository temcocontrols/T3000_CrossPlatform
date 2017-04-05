namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class UNTime : Version, IBinaryObject
    {
        public int Second { get; set; }
        public int Minute { get; set; }
        public int Hour { get; set; }
        public int Day { get; set; }
        public DayOfWeek DayOfWeek { get; set; }
        public int Month { get; set; }
        public int Year { get; set; }
        public int DayOfYear { get; set; }
        public bool IsDst { get; set; }

        public UNTime(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        public override int GetHashCode() =>
            Second.GetHashCode() ^
            Minute.GetHashCode() ^ 
            Hour.GetHashCode() ^
            Day.GetHashCode() ^
            DayOfWeek.GetHashCode() ^
            Month.GetHashCode() ^
            Year.GetHashCode() ^
            DayOfYear.GetHashCode() ^
            IsDst.GetHashCode();

        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();

        #region Binary data

        /// <summary>
        /// FileVersion.Current - Need 10 bytes array
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public UNTime(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Second = bytes.ToByte(0 + offset);
                    Minute = bytes.ToByte(1 + offset);
                    Hour = bytes.ToByte(2 + offset);
                    Day = bytes.ToByte(3 + offset);
                    DayOfWeek = (DayOfWeek)bytes.ToByte(4 + offset);
                    Month = bytes.ToByte(5 + offset);
                    Year = bytes.ToByte(6 + offset);
                    DayOfYear = bytes.ToUInt16(7 + offset);
                    IsDst = bytes.ToBoolean(9 + offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - 10 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.Add((byte)Second);
                    bytes.Add((byte)Minute);
                    bytes.Add((byte)Hour);
                    bytes.Add((byte)Day);
                    bytes.Add((byte)DayOfWeek);
                    bytes.Add((byte)Month);
                    bytes.Add((byte)Year);
                    bytes.AddRange(((ushort)DayOfYear).ToBytes());
                    bytes.Add(IsDst.ToByte());
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}