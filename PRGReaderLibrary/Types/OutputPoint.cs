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
            bool autoManualRaw;
            bool digitalAnalogRaw;
            byte hwSwitchStatusRaw;
            bool controlRaw;
            bool digitalControlRaw;
            byte unitsRaw;
            bool subNumberRaw;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Description = bytes.GetString(0 + offset, 19).ClearBinarySymvols();
                    LowVoltage = bytes.ToInt32(19);
                    HighVoltage = bytes.ToInt32(20);
                    Label = bytes.GetString(21 + offset, 9).ClearBinarySymvols();
                    valueRaw = bytes.ToUInt32(30 + offset);
                    autoManualRaw = bytes.ToBoolean(34 + offset);
                    digitalAnalogRaw = bytes.ToBoolean(35 + offset);
                    hwSwitchStatusRaw = bytes.ToByte(36 + offset);
                    controlRaw = bytes.ToBoolean(37 + offset);
                    digitalControlRaw = bytes.ToBoolean(38 + offset);
                    Decommissioned = bytes.ToByte(39 + offset);
                    unitsRaw = digitalAnalogRaw
                        ? bytes.ToByte(40 + offset)
                        : (byte)(bytes.ToByte(40 + offset) + 100);
                    SubId = bytes.ToBoolean(41 + offset);
                    SubProduct = bytes.ToBoolean(42 + offset);
                    subNumberRaw = bytes.ToBoolean(43 + offset);
                    PwmPeriod = bytes.ToByte(44 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            //to static methods
            Value = new VariableVariant(valueRaw, (Units)unitsRaw);
            AutoManual = autoManualRaw ? AutoManual.Manual : AutoManual.Automatic;
            DigitalAnalog = digitalAnalogRaw ? DigitalAnalog.Analog : DigitalAnalog.Digital;
            HwSwitchStatus = hwSwitchStatusRaw == 2
                ? SwitchStatus.Hand
                : hwSwitchStatusRaw == 1
                    ? SwitchStatus.Auto
                    : SwitchStatus.Off;
            Control = controlRaw ? Control.On : Control.Off;
            DigitalControl = digitalControlRaw ? Control.On : Control.Off;
            SubNumber = subNumberRaw ? 1.0 : 0.1;
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            var autoManualRaw = AutoManual == AutoManual.Manual;
            var digitalAnalogRaw = DigitalAnalog == DigitalAnalog.Analog;
            var hwSwitchStatusRaw = (byte)(HwSwitchStatus == SwitchStatus.Hand
                ? 2
                : HwSwitchStatus == SwitchStatus.Auto
                    ? 1
                    : 0);
            var controlRaw = Control == Control.On;
            var digitalControlRaw = DigitalControl == Control.On;
            var unitsRaw = (byte)Value.Units;
            var subNumberRaw = SubNumber == 1.0;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Description.AddBinarySymvols(19).ToBytes(19));
                    bytes.Add((byte)LowVoltage);
                    bytes.Add((byte)HighVoltage);
                    bytes.AddRange(Label.AddBinarySymvols(9).ToBytes(9));
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add(autoManualRaw.ToByte());
                    bytes.Add(digitalAnalogRaw.ToByte());
                    bytes.Add(hwSwitchStatusRaw);
                    bytes.Add(controlRaw.ToByte());
                    bytes.Add(digitalControlRaw.ToByte());
                    bytes.Add((byte)Decommissioned);
                    bytes.Add(digitalAnalogRaw ? unitsRaw : (byte)(unitsRaw - 100));
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add(subNumberRaw.ToByte());
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