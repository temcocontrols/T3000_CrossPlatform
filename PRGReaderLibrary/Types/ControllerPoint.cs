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
        public Units Units { get; set; }
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
                    Input = new T3000Point(bytes.ToBytes(0 + offset, 3), 0, FileVersion);
                    InputValue = bytes.ToInt32(3 + offset);
                    Value = bytes.ToInt32(7 + offset);
                    SetPoint = new T3000Point(bytes.ToBytes(11 + offset, 3), 0, FileVersion);
                    SetPointValue = bytes.ToFloat(14 + offset);
                    Units = (Units)bytes.ToByte(18 + offset);
                    AutoManual = ValuedPoint.AutoManualFromByte(bytes.ToByte(19 + offset));
                    Action = (DirectReverse) bytes.ToByte(20 + offset);
                    Periodicity = (Periodicity)bytes.ToByte(21 + offset);
                    IsSample = bytes.ToByte(22 + offset);
                    PropHigh = bytes.ToByte(23 + offset);
                    Proportional = bytes.ToByte(24 + offset);
                    Reset = bytes.ToByte(25 + offset);
                    Bias = bytes.ToByte(26 + offset);
                    Rate = bytes.ToByte(27 + offset) / 100.0;
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
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
                    bytes.Add((byte)Units);
                    bytes.Add(ValuedPoint.ToByte(AutoManual));
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

            return bytes.ToArray();
        }

        #endregion

    }
}