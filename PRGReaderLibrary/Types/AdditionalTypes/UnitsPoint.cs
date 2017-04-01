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

        public AutoManual AutoManual {
            get { return AutoManualRaw ? AutoManual.Manual : AutoManual.Automatic; }
            set { AutoManualRaw = value == AutoManual.Manual; }
        }

        public DigitalAnalog DigitalAnalog {
            get { return DigitalAnalogRaw ? DigitalAnalog.Analog : DigitalAnalog.Digital; }
            set { DigitalAnalogRaw = value == DigitalAnalog.Analog; }
        }

        public Control Control {
            get { return ControlRaw ? Control.On : Control.Off; }
            set { ControlRaw = value == Control.On; }
        }

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

        /// <summary>
        /// Size: 30 + 4 + 4 = 38
        /// </summary>
        #region Binary data

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        protected uint ValueRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected bool AutoManualRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected bool DigitalAnalogRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected bool ControlRaw { get; set; }

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

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            bytes.AddRange(base.ToBytes());

            return bytes.ToArray();
        }
        #endregion
    }
}