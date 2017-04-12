﻿namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class InoutPoint : BasePoint
    {
        public VariableValue Value { get; set; } = new VariableValue(0, 0);
        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public OffOn Control { get; set; }
        
        public CustomUnits CustomUnits { get; set; }

        public bool SubId { get; set; }
        public bool SubProduct { get; set; }
        public double SubNumber { get; set; }

        public static byte ToByte(Units units, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (byte)(units - Units.AnalogRangeUnused)
            : (byte)(units - 106);

        public static Units AnalogRangeFromByte(byte value, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? value + Units.AnalogRangeUnused
            : (Units)(value + 106);

        public InoutPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static double SubNumberFromByte(byte value) =>
            value.ToBoolean() ? 1.0 : 0.1;

        public static byte SubNumberToByte(double value) =>
            (value == 1.0).ToByte();

        public InoutPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        { }

        #endregion
    }
}
