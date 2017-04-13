namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class OutputPoint : InoutPoint, IBinaryObject
    {
        public int LowVoltage { get; set; }
        public int HighVoltage { get; set; }
        public SwitchStatus HwSwitchStatus { get; set; }
        public OffOn DigitalControl { get; set; }
        public int PwmPeriod { get; set; }

        protected int Decommissioned { get; set; }

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

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            var size = InoutPoint.GetSize(version);
            switch (version)
            {
                case FileVersion.Current:
                    return size + 15;

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
            Unit unit;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Description = bytes.GetString(ref offset, 19).ClearBinarySymvols();
                    LowVoltage = bytes.ToByte(ref offset);
                    HighVoltage = bytes.ToByte(ref offset);
                    Label = bytes.GetString(ref offset, 9).ClearBinarySymvols();
                    valueRaw = bytes.ToInt32(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    DigitalAnalog = (DigitalAnalog)bytes.ToByte(ref offset);
                    HwSwitchStatus = (SwitchStatus)bytes.ToByte(ref offset);
                    Control = (OffOn)bytes.ToByte(ref offset);
                    DigitalControl = (OffOn)bytes.ToByte(ref offset);
                    Decommissioned = bytes.ToByte(ref offset);
                    unit = VariablePoint.UnitsFromByte(bytes.ToByte(ref offset), DigitalAnalog);
                    SubId = bytes.ToBoolean(ref offset);
                    SubProduct = bytes.ToBoolean(ref offset);
                    SubNumber = SubNumberFromByte(bytes.ToByte(ref offset));
                    PwmPeriod = bytes.ToByte(ref offset);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            Value = new VariableValue(valueRaw, unit);

            var size = GetSize(FileVersion);
            if (offset != size)
            {
                throw new OffsetException(offset, size);
            }
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
                    bytes.Add(VariablePoint.ToByte(Value.Unit, DigitalAnalog));
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add(SubNumberToByte(SubNumber));
                    bytes.Add((byte)PwmPeriod);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            var size = GetSize(FileVersion);
            if (bytes.Count != size)
            {
                throw new OffsetException(bytes.Count, size);
            }

            return bytes.ToArray();
        }

        #endregion

    }
}