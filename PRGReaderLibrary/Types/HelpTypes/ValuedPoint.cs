namespace PRGReaderLibrary
{
    public class ValuedPoint : BasePoint
    {
        public VariableValue Value { get; set; } = new VariableValue(0, 0);
        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public OffOn Control { get; set; }

        public ValuedPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        {}

        #region Binary data

        public static byte ToByte(AutoManual value) =>
            (value == AutoManual.Manual).ToByte();
        public static AutoManual AutoManualFromByte(byte value) =>
            value.ToBoolean() ? AutoManual.Manual : AutoManual.Automatic;

        public static byte ToByte(DigitalAnalog value) =>
            (value == DigitalAnalog.Analog).ToByte();
        public static DigitalAnalog DigitalAnalogFromByte(byte value) =>
            value.ToBoolean() ? DigitalAnalog.Analog : DigitalAnalog.Digital;

        public static byte ToByte(OffOn value) =>
            (value == OffOn.On).ToByte();
        public static OffOn ControlFromByte(byte value) =>
            value.ToBoolean() ? OffOn.On : OffOn.Off;

        public static byte ToByte(Units units, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (byte)units
            : (byte)(units - Units.DigitalUnused);
        public static Units UnitsFromByte(byte value, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (Units)value
            : value + Units.DigitalUnused;

        public ValuedPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {}

        #endregion
    }
}