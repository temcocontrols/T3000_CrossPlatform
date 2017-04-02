namespace PRGReaderLibrary
{
    public class UnitsPoint : BasePoint
    {
        public VariableVariant Value { get; set; }
        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public Control Control { get; set; }

        public UnitsPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        {}

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(Description) &&
            string.IsNullOrWhiteSpace(Label);

        #region Binary data

        public static byte ToByte(AutoManual value) =>
            (value == AutoManual.Manual).ToByte();
        public static AutoManual AutoManualFromByte(byte value) =>
            value.ToBoolean() ? AutoManual.Manual : AutoManual.Automatic;

        public static byte ToByte(DigitalAnalog value) =>
            (value == DigitalAnalog.Analog).ToByte();
        public static DigitalAnalog DigitalAnalogFromByte(byte value) =>
            value.ToBoolean() ? DigitalAnalog.Analog : DigitalAnalog.Digital;

        public static byte ToByte(Control value) =>
            (value == Control.On).ToByte();
        public static Control ControlFromByte(byte value) =>
            value.ToBoolean() ? Control.On : Control.Off;

        public static byte ToByte(Units units, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (byte)units
            : (byte)(units - Units.DigitalUnused);
        public static Units UnitsFromByte(byte value, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (Units)value
            : value + Units.DigitalUnused;

        public UnitsPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {}

        #endregion
    }
}