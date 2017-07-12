namespace PRGReaderLibrary
{
    using System.Linq;
    using System.Collections.Generic;

    public class MonitorPoint : Version, IBinaryObject
    {
        public string Label { get; set; } = string.Empty;
        public List<NetPoint> Inputs { get; set; } = new List<NetPoint>();
        public List<int> Ranges { get; set; } = new List<int>();
        public int Second { get; set; }
        public int Minute { get; set; }
        public int Hour { get; set; }
        public int MaxTimeLength { get; set; }
        public int InputsCount { get; set; }
        public int AnalogInputsCount { get; set; }
        public int Status { get; set; }
        public int NextSampleTime { get; set; }

        public MonitorPoint(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 12;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 104;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 104 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public MonitorPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Label = bytes.GetString(ref offset, 9).ClearBinarySymvols();
                    for (var i = 0; i < 14; ++i)
                    {
                        var data = bytes.ToBytes(ref offset, 5);
                        Inputs.Add(new NetPoint(data, 0, FileVersion));
                    }
                    for (var i = 0; i < 14; ++i)
                    {
                        Ranges.Add(bytes.ToByte(ref offset));
                    }
                    Second = bytes.ToByte(ref offset);
                    Minute = bytes.ToByte(ref offset);
                    Hour = bytes.ToByte(ref offset);
                    MaxTimeLength = bytes.ToByte(ref offset);
                    InputsCount = bytes.ToByte(ref offset);
                    AnalogInputsCount = bytes.ToByte(ref offset);
                    Status = bytes.ToByte(ref offset);
                    NextSampleTime = bytes.ToInt32(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 104 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Label.ToBytes(9));
                    for (var i = 0; i < 14; ++i)
                    {
                        var input = Inputs.ElementAtOrDefault(i) ?? new NetPoint();
                        input.FileVersion = FileVersion;

                        bytes.AddRange(input.ToBytes());
                    }
                    for (var i = 0; i < 14; ++i)
                    {
                        var range = Ranges.ElementAtOrDefault(i);
                        bytes.Add((byte)range);
                    }
                    bytes.Add((byte)Second);
                    bytes.Add((byte)Minute);
                    bytes.Add((byte)Hour);
                    bytes.Add((byte)MaxTimeLength);
                    bytes.Add((byte)InputsCount);
                    bytes.Add((byte)AnalogInputsCount);
                    bytes.Add((byte)Status);
                    bytes.AddRange(((int)NextSampleTime).ToBytes());
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