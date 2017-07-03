namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class ControllerPoint : Version, IBinaryObject
    {
        public T3000Point Input { get; set; } = new T3000Point();
        public int InputValue { get; set; }
        public int Value { get; set; }
        public T3000Point SetPoint { get; set; } = new T3000Point();
        public float SetPointValue { get; set; }
        public Unit Unit { get; set; }
        public AutoManual AutoManual { get; set; }
        public DirectReverse Action { get; set; }
        public Periodicity Periodicity { get; set; }
        public int IsSample { get; set; }
        public int PropHigh { get; set; }
        public int Proportional { get; set; }

        /// <summary>
        /// 0 - 255
        /// </summary>
        public int Reset { get; set; }

        /// <summary>
        /// 0 - 100
        /// </summary>
        public int Bias { get; set; }

        /// <summary>
        /// 0 - 2.00
        /// </summary>
        public double Rate { get; set; }


        public ControllerPoint(FileVersion version = FileVersion.Current)
            : base(version)
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
                    return 28;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 28 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ControllerPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Input = new T3000Point(bytes.ToBytes(ref offset, 3), 0, FileVersion);
                    InputValue = bytes.ToInt32(ref offset);
                    Value = bytes.ToInt32(ref offset);
                    SetPoint = new T3000Point(bytes.ToBytes(ref offset, 3), 0, FileVersion);
                    SetPointValue = bytes.ToFloat(ref offset);
                    Unit = (Unit)bytes.ToByte(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    Action = (DirectReverse) bytes.ToByte(ref offset);
                    Periodicity = (Periodicity)bytes.ToByte(ref offset);
                    IsSample = bytes.ToByte(ref offset);
                    PropHigh = bytes.ToByte(ref offset);
                    Proportional = bytes.ToByte(ref offset);
                    Reset = bytes.ToByte(ref offset);
                    Bias = bytes.ToByte(ref offset);
                    Rate = bytes.ToByte(ref offset) / 100.0;
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 28 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            Input.FileVersion = FileVersion;
            SetPoint.FileVersion = FileVersion;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Input.ToBytes());
                    bytes.AddRange(InputValue.ToBytes());
                    bytes.AddRange(Value.ToBytes());
                    bytes.AddRange(SetPoint.ToBytes());
                    bytes.AddRange(SetPointValue.ToBytes());
                    bytes.Add((byte)Unit);
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)Action);
                    bytes.Add((byte)Periodicity);
                    bytes.Add((byte)IsSample);
                    bytes.Add((byte)PropHigh);
                    bytes.Add((byte)Proportional);
                    bytes.Add((byte)Reset);
                    bytes.Add((byte)Bias);
                    bytes.Add(Convert.ToByte(Rate * 100.0));
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