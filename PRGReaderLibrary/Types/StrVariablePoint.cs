namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 + 4 + 1 + 1 = 36
    /// </summary>
    public class StrVariablePoint : BasePoint
    {
        private VariableVariant _value;
        public VariableVariant Value {
            get {
                _value = _value ?? new VariableVariant(ValueRaw, (UnitsEnum)UnitsRaw);
                return _value;
            }
            set {
                _value = value;
                ValueRaw = value.Value;
                UnitsRaw = (byte)value.Units;
            }
        }

        public AutoManualEnum AutoManual {
            get { return AutoManualRaw ? AutoManualEnum.Manual : AutoManualEnum.Automatic; }
            set { AutoManualRaw = value == AutoManualEnum.Manual; }
        }

        public DigitalAnalogEnum DigitalAnalog {
            get { return DigitalAnalogRaw ? DigitalAnalogEnum.Analog : DigitalAnalogEnum.Digital; }
            set { DigitalAnalogRaw = value == DigitalAnalogEnum.Analog; }
        }

        public ControlEnum Control {
            get { return ControlRaw ? ControlEnum.On : ControlEnum.Off; }
            set { ControlRaw = value == ControlEnum.On; }
        }

        public StrVariablePoint(string description = "", string label = "", FileVersionEnum version = FileVersionEnum.Current)
            : base(description, label, version) { }

        #region Binary data

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        protected uint ValueRaw { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        protected bool AutoManualRaw { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        protected bool DigitalAnalogRaw { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        protected bool ControlRaw { get; set; }

        /// <summary>
        /// Size: 5 bit
        /// </summary>
        protected byte UnusedRaw { get; set; } = 2; //TODO: WTF

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected byte UnitsRaw { get; set; }

        public StrVariablePoint(byte[] bytes, int offset = 0, FileVersionEnum version = FileVersionEnum.Current)
            : base(bytes, offset, version)
        {
            switch (FileVersion)
            {
                case FileVersionEnum.Dos:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    AutoManualRaw = bytes.GetBit(0, 34 + offset);
                    DigitalAnalogRaw = bytes.GetBit(1, 34 + offset);
                    ControlRaw = bytes.GetBit(2, 34 + offset);
                    UnitsRaw = bytes[35 + offset];
                    break;

                case FileVersionEnum.Current:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    AutoManualRaw = bytes.ToBoolean(34 + offset);
                    DigitalAnalogRaw = bytes.ToBoolean(35 + offset);
                    ControlRaw = bytes.ToBoolean(36 + offset);
                    UnusedRaw = bytes.ToByte(37 + offset);
                    UnitsRaw = DigitalAnalogRaw
                        ? bytes[38 + offset]
                        : (byte)(bytes[38 + offset] + 100);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersionEnum.Dos:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(new[] { AutoManualRaw, DigitalAnalogRaw, ControlRaw }.ToBits());
                    bytes.Add(UnitsRaw);
                    break;

                case FileVersionEnum.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(AutoManualRaw.ToByte());
                    bytes.Add(DigitalAnalogRaw.ToByte());
                    bytes.Add(ControlRaw.ToByte());
                    bytes.Add(UnusedRaw); //WTF (it equals 2)??
                    bytes.Add(DigitalAnalogRaw ? UnitsRaw : (byte)(UnitsRaw - 100));
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}