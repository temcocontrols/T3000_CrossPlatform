namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class InputPoint : InoutPoint, IBinaryObject
    {
        public int Filter { get; set; }
        public Sign CalibrationSign { get; set; }
        public double CalibrationH { get; set; }
        public double CalibrationL { get; set; }

        public InputPoint(string description = "", string label = "",
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
                    return 46;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 46 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public InputPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            int valueRaw;
            Units units;

            byte filterRaw;
            bool calibrationSignRaw;
            byte calibrationHRaw;
            byte calibrationLRaw;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    valueRaw = bytes.ToInt32(30 + offset);
                    filterRaw = bytes.ToByte(34 + offset);
                    Decommissioned = bytes.ToByte(35 + offset);
                    SubId = bytes.ToBoolean(36 + offset);
                    SubProduct = bytes.ToBoolean(37 + offset);
                    Control = (OffOn)bytes.ToByte(38 + offset);
                    AutoManual = (AutoManual)bytes.ToByte(39 + offset);
                    DigitalAnalog = (DigitalAnalog)bytes.ToByte(40 + offset);
                    calibrationSignRaw = bytes.ToBoolean(41 + offset);
                    SubNumber = SubNumberFromByte(bytes.ToByte(42 + offset));
                    calibrationHRaw = bytes.ToByte(43 + offset);
                    calibrationLRaw = bytes.ToByte(44 + offset);
                    units = UnitsFromByte(bytes.ToByte(45 + offset), DigitalAnalog);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
            
            Value = new VariableValue(valueRaw, units);

            Filter = (int)Math.Pow(2, filterRaw);
            CalibrationSign = calibrationSignRaw ? Sign.Negative : Sign.Positive;
            CalibrationH = calibrationHRaw / 10.0;
            CalibrationL = calibrationLRaw / 10.0;
        }

        /// <summary>
        /// FileVersion.Current - 46 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            var calibrationSignRaw = CalibrationSign == Sign.Negative;
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
                    bytes.Add((byte)Control);
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)DigitalAnalog);
                    bytes.Add(calibrationSignRaw.ToByte());
                    bytes.Add(SubNumberToByte(SubNumber));
                    bytes.Add(calibrationHRaw);
                    bytes.Add(calibrationLRaw);
                    bytes.Add(ToByte(Value.Units, DigitalAnalog));
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion

    }
}