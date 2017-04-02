namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class UnitsPoint : BasePoint
    {
        public List<UnitsElement> CustomUnits { get; set; }

        private VariableVariant _value;
        public VariableVariant Value {
            get {
                _value = _value ?? new VariableVariant(ValueRaw, (Units)UnitsRaw, CustomUnits);
                return _value;
            }
            set {
                _value = value;
                _value.CustomUnits = CustomUnits;
                ValueRaw = value.Value;
                UnitsRaw = (byte)value.Units;
            }
        }

        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public Control Control { get; set; }

        public UnitsPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(description, label, version)
        {
            CustomUnits = customUnits;
        }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(Description) &&
            string.IsNullOrWhiteSpace(Label);

        #region Binary data

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        protected uint ValueRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected byte UnitsRaw { get; set; }

        public UnitsPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(bytes, offset, version)
        {
            CustomUnits = customUnits;
        }
        #endregion
    }
}