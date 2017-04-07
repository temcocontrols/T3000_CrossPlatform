namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class OutputPoint : InoutPoint, IBinaryObject
    {
        public int LowVoltage { get; set; }
        public int HighVoltage { get; set; }
        public SwitchStatus HwSwitchStatus { get; set; }
        public OffOn DigitalControl { get; set; }
        public int PwmPeriod { get; set; }

        public OutputPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 64;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 45;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 45 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public OutputPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
        {
            FileVersion = version;

            int valueRaw;
            Units units;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Description = bytes.GetString(0 + offset, 19).ClearBinarySymvols();
                    LowVoltage = bytes.ToByte(19 + offset);
                    HighVoltage = bytes.ToByte(20 + offset);
                    Label = bytes.GetString(21 + offset, 9).ClearBinarySymvols();
                    valueRaw = bytes.ToInt32(30 + offset);
                    AutoManual = (AutoManual)bytes.ToByte(34 + offset);
                    DigitalAnalog = (DigitalAnalog)bytes.ToByte(35 + offset);
                    HwSwitchStatus = (SwitchStatus)bytes.ToByte(36 + offset);
                    Control = (OffOn)bytes.ToByte(37 + offset);
                    DigitalControl = (OffOn)bytes.ToByte(38 + offset);
                    Decommissioned = bytes.ToByte(39 + offset);
                    units = UnitsFromByte(bytes.ToByte(40 + offset), DigitalAnalog);
                    SubId = bytes.ToBoolean(41 + offset);
                    SubProduct = bytes.ToBoolean(42 + offset);
                    SubNumber = SubNumberFromByte(bytes.ToByte(43 + offset));
                    PwmPeriod = bytes.ToByte(44 + offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            Value = new VariableValue(valueRaw, units);
        }

        /// <summary>
        /// FileVersion.Current - 45 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Description.ToBytes(19));
                    bytes.Add((byte)LowVoltage);
                    bytes.Add((byte)HighVoltage);
                    bytes.AddRange(Label.ToBytes(9));
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)DigitalAnalog);
                    bytes.Add((byte)HwSwitchStatus);
                    bytes.Add((byte)Control);
                    bytes.Add((byte)DigitalControl);
                    bytes.Add((byte)Decommissioned);
                    bytes.Add(ToByte(Value.Units, DigitalAnalog));
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add(SubNumberToByte(SubNumber));
                    bytes.Add((byte)PwmPeriod);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion

    }
}