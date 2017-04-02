namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class InputPoint : UnitsPoint
    {
        public int Filter { get; set; }
        public int Decommissioned { get; set; }
        public bool SubId { get; set; }
        public bool SubProduct { get; set; }
        public Sign CalibrationSign { get; set; }
        public double SubNumber { get; set; }
        public double CalibrationH { get; set; }
        public double CalibrationL { get; set; }

        public InputPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public InputPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            bool autoManualRaw;
            bool digitalAnalogRaw;
            bool controlRaw;
            uint valueRaw;
            byte unitsRaw;

            byte filterRaw;
            bool calibrationSignRaw;
            bool subNumberRaw;
            byte calibrationHRaw;
            byte calibrationLRaw;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    valueRaw = bytes.ToUInt32(30 + offset);
                    filterRaw = bytes.ToByte(34 + offset);
                    Decommissioned = bytes.ToByte(35 + offset);
                    SubId = bytes.ToBoolean(36 + offset);
                    SubProduct = bytes.ToBoolean(37 + offset);
                    controlRaw = bytes.ToBoolean(38 + offset);
                    autoManualRaw = bytes.ToBoolean(39 + offset);
                    digitalAnalogRaw = bytes.ToBoolean(40 + offset);
                    calibrationSignRaw = bytes.ToBoolean(41 + offset);
                    subNumberRaw = bytes.ToBoolean(42 + offset);
                    calibrationHRaw = bytes.ToByte(43 + offset);
                    calibrationLRaw = bytes.ToByte(44 + offset);
                    unitsRaw = digitalAnalogRaw
                        ? bytes[45 + offset]
                        : (byte)(bytes[45 + offset] + 100);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            AutoManual = autoManualRaw ? AutoManual.Manual : AutoManual.Automatic;
            DigitalAnalog = digitalAnalogRaw ? DigitalAnalog.Analog : DigitalAnalog.Digital;
            Control = controlRaw ? Control.On : Control.Off;
            Value = new VariableVariant(valueRaw, (Units)unitsRaw);

            Filter = (int)Math.Pow(2, filterRaw);
            CalibrationSign = calibrationSignRaw ? Sign.Negative : Sign.Positive;
            SubNumber = subNumberRaw ? 1.0 : 0.1;
            CalibrationH = calibrationHRaw / 10.0;
            CalibrationL = calibrationLRaw / 10.0;
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            var autoManualRaw = AutoManual == AutoManual.Manual;
            var digitalAnalogRaw = DigitalAnalog == DigitalAnalog.Analog;
            var controlRaw = Control == Control.On;
            var unitsRaw = (byte)Value.Units;

            var calibrationSignRaw = CalibrationSign == Sign.Negative;
            var subNumberRaw = SubNumber == 1.0;
            var calibrationHRaw = Convert.ToByte(CalibrationH * 10.0);
            var calibrationLRaw = Convert.ToByte(CalibrationL * 10.0);

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add((byte)Math.Log(Filter, 2));
                    bytes.Add((byte)Decommissioned);
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add(controlRaw.ToByte());
                    bytes.Add(autoManualRaw.ToByte());
                    bytes.Add(digitalAnalogRaw.ToByte());
                    bytes.Add(calibrationSignRaw.ToByte());
                    bytes.Add(subNumberRaw.ToByte());
                    bytes.Add(calibrationHRaw);
                    bytes.Add(calibrationLRaw);
                    bytes.Add(digitalAnalogRaw ? unitsRaw : (byte)(unitsRaw - 100));
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion

    }
}