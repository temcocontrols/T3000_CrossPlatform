namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class OutputPoint : UnitsPoint
    {
        public int LowVoltage { get; set; }
        public int HighVoltage { get; set; }
        public SwitchStatus HwSwitchStatus { get; set; }
        public Control DigitalControl { get; set; }
        public int Decommissioned { get; set; }
        public bool SubId { get; set; }
        public bool SubProduct { get; set; }
        public double SubNumber { get; set; }
        public int PwmPeriod { get; set; }

        public OutputPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public OutputPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
        {
            FileVersion = version;

            uint valueRaw;
            Units units;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Description = bytes.GetString(0 + offset, 19).ClearBinarySymvols();
                    LowVoltage = bytes.ToInt32(19);
                    HighVoltage = bytes.ToInt32(20);
                    Label = bytes.GetString(21 + offset, 9).ClearBinarySymvols();
                    valueRaw = bytes.ToUInt32(30 + offset);
                    AutoManual = AutoManualFromByte(bytes.ToByte(34 + offset));
                    DigitalAnalog = DigitalAnalogFromByte(bytes.ToByte(35 + offset));
                    HwSwitchStatus = SwitchStatusFromByte(bytes.ToByte(36 + offset));
                    Control = ControlFromByte(bytes.ToByte(37 + offset));
                    DigitalControl = ControlFromByte(bytes.ToByte(38 + offset));
                    Decommissioned = bytes.ToByte(39 + offset);
                    units = UnitsFromByte(bytes.ToByte(40 + offset), DigitalAnalog);
                    SubId = bytes.ToBoolean(41 + offset);
                    SubProduct = bytes.ToBoolean(42 + offset);
                    SubNumber = SubNumberFromByte(bytes.ToByte(43 + offset));
                    PwmPeriod = bytes.ToByte(44 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            Value = new VariableVariant(valueRaw, units);
        }

        public static SwitchStatus SwitchStatusFromByte(byte value)
        {
            switch (value)
            {
                case 2:
                    return SwitchStatus.Hand;

                case 1:
                    return SwitchStatus.Auto;

                default:
                    return SwitchStatus.Off;
            }
        }

        public static byte ToByte(SwitchStatus value)
        {
            switch (value)
            {
                case SwitchStatus.Hand:
                    return 2;

                case SwitchStatus.Auto:
                    return 1;

                default:
                    return 0;
            }
        }

        public static double SubNumberFromByte(byte value) =>
            value.ToBoolean() ? 1.0 : 0.1;

        public static byte SubNumberToByte(double value) =>
            (value == 1.0).ToByte();

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Description.ToBytes(19));
                    bytes.Add((byte)LowVoltage);
                    bytes.Add((byte)HighVoltage);
                    bytes.AddRange(Label.AddBinarySymvols(9).ToBytes(9));
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add(ToByte(AutoManual));
                    bytes.Add(ToByte(DigitalAnalog));
                    bytes.Add(ToByte(HwSwitchStatus));
                    bytes.Add(ToByte(Control));
                    bytes.Add(ToByte(DigitalControl));
                    bytes.Add((byte)Decommissioned);
                    bytes.Add(ToByte(Value.Units, DigitalAnalog));
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add(SubNumberToByte(SubNumber));
                    bytes.Add((byte)PwmPeriod);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion

    }
}