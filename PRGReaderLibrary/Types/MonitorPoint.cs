using System.Linq;

namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class MonitorPoint : Version, IBinaryObject
    {
        public string Label { get; set; }
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
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 104;

                default:
                    throw new NotImplementedException("File version is not implemented");
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
                    Label = bytes.GetString(0 + offset, 9).ClearBinarySymvols();
                    for (var i = 0; i < 14; ++i)
                    {
                        var data = bytes.ToBytes(9 + i*5 + offset, 5);
                        Inputs.Add(new NetPoint(data, 0, FileVersion));
                    }
                    for (var i = 0; i < 14; ++i)
                    {
                        Ranges.Add(bytes.ToByte(79 + i + offset));
                    }
                    Second = bytes.ToByte(93 + offset);
                    Minute = bytes.ToByte(94 + offset);
                    Hour = bytes.ToByte(95 + offset);
                    MaxTimeLength = bytes.ToByte(96 + offset);
                    InputsCount = bytes.ToByte(97 + offset);
                    AnalogInputsCount = bytes.ToByte(98 + offset);
                    Status = bytes.ToByte(99 + offset);
                    NextSampleTime = bytes.ToInt32(100 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
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
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}