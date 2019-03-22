namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public enum InputStatus
    {
        Normal,
        Open,
        Shorted
    }

    public class InputPoint : InoutPoint, IBinaryObject
    {
        public int Filter { get; set; }
        public Sign CalibrationSign { get; set; }
        public double CalibrationH { get; set; }
        public double CalibrationL { get; set; }

        public InputStatus Status { get; set; }
        public Jumper Jumper { get; set; }

        public InputPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }
        
        public static byte ToByte(Unit unit, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (byte)(unit - Unit.InputAnalogUnused)
            : (byte)(unit - 106);

        public static Unit UnitFromByte(byte value, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? value + Unit.InputAnalogUnused
            : (Unit)(value + 106);

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
                    return size + 16;

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
            offset += InoutPoint.GetSize(FileVersion);

            int valueRaw;
            Unit unit;

            byte filterRaw;
            byte calibrationHRaw;
            byte calibrationLRaw;
            byte decomRaw;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    valueRaw = bytes.ToInt32(ref offset);
                    filterRaw = bytes.ToByte(ref offset);
                    decomRaw = bytes.ToByte(ref offset);
                    SubId = bytes.ToBoolean(ref offset);
                    SubProduct = bytes.ToBoolean(ref offset);
                    Control = (OffOn)bytes.ToByte(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    DigitalAnalog = (DigitalAnalog)bytes.ToByte(ref offset);
                    CalibrationSign = (Sign)bytes.ToByte(ref offset);
                    SubNumber = SubNumberFromByte(bytes.ToByte(ref offset));
                    calibrationHRaw = bytes.ToByte(ref offset);
                    calibrationLRaw = bytes.ToByte(ref offset);
                    unit = UnitFromByte(bytes.ToByte(ref offset), DigitalAnalog);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
            
            Value = new VariableValue(valueRaw, unit);

            Filter = (int)Math.Pow(2, filterRaw);
            CalibrationH = calibrationHRaw / 10.0;
            CalibrationL = calibrationLRaw / 10.0;

            //Status
            var statusIndex = decomRaw % 16;
            if (statusIndex >= (int) InputStatus.Normal &&
                statusIndex <= (int) InputStatus.Shorted)
            {
                Status = (InputStatus) statusIndex;
            }
            else
            {
                Status = InputStatus.Normal;
            }

            //Jumper
            var jumperIndex = decomRaw / 16;
            if (jumperIndex >= (int)Jumper.Thermistor &&
                jumperIndex <= (int)Jumper.To10V)
            {
                Jumper = (Jumper)jumperIndex;
            }
            else
            {
                Jumper = jumperIndex == 4
                    ? (Jumper)4 //TODO: Fix for T3DemoRev6.prg
                    : Jumper.Thermistor;
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 46 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            var calibrationHRaw = Convert.ToByte(CalibrationH * 10.0);
            var calibrationLRaw = Convert.ToByte(CalibrationL * 10.0);
            var decommissionedRaw = ((int)Status) + ((int)Jumper * 16);

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add((byte)Math.Log(Filter, 2));
                    bytes.Add((byte)decommissionedRaw);
                    bytes.Add(SubId.ToByte());
                    bytes.Add(SubProduct.ToByte());
                    bytes.Add((byte)Control);
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)DigitalAnalog);
                    bytes.Add((byte)CalibrationSign);
                    bytes.Add(SubNumberToByte(SubNumber));
                    bytes.Add(calibrationHRaw);
                    bytes.Add(calibrationLRaw);
                    bytes.Add(ToByte(Value.Unit, DigitalAnalog));
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