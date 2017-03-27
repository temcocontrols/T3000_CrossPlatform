namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 + 4 + 1 + 1 = 36
    /// </summary>
    public class StrVariablePoint : BasePoint
    {
        /// <summary>
        /// Return correct object for value and units
        /// </summary>
        public object Value {
            get {
                return DigitalAnalog == DigitalAnalogEnum.Analog
                    ? Units == UnitsEnum.Time
                        ? (object)new TimeSpan(0,
                            (int)ValueRaw / 1000 / 60 / 60 % 24,
                            (int)ValueRaw / 1000 / 60 % 60,
                            (int)ValueRaw / 1000 % 60,
                            (int)ValueRaw % 1000
                            )
                        : ValueRaw / 1000.0F
                    : ValueRaw;
            }
            set {
                var type = value.GetType();
                if (type == typeof(bool))
                {
                    ValueRaw = ((bool)value).ToByte();
                }
                else if (type == typeof(TimeSpan))
                {
                    var time = ((TimeSpan) value);
                    ValueRaw = (uint)((time.Hours*60*60 + time.Minutes*60 + time.Seconds)*1000 + time.Milliseconds);
                }
                else
                {
                    ValueRaw = DigitalAnalog == DigitalAnalogEnum.Analog
                        ? (uint)(((float)value) * 1000)
                        : (uint)value;
                }
            }
        }

        public string ValueString {
            get {
                return DigitalAnalog == DigitalAnalogEnum.Analog
                    ? Units == UnitsEnum.Time
                        ? ((TimeSpan)Value).ToString(@"hh\:mm\:ss")
                        : ((float)Value).ToString("F3")
                    : $"{Value}";
            }
            set {
                Value = DigitalAnalog == DigitalAnalogEnum.Analog
                    ? Units == UnitsEnum.Time
                        ? (object)TimeSpan.Parse(value)
                        : float.Parse(value)
                    : (object)(value.Equals("0") ? false : true);
            }
        }

        public AutoManualEnum AutoManual
        {
            get { return AutoManualRaw ? AutoManualEnum.Manual : AutoManualEnum.Automatic; }
            set { AutoManualRaw = value == AutoManualEnum.Manual; }
        }

        /// <summary>
        ///  Units >= UnitsEnum.OffOn && Units <= UnitsEnum.LowHigh
        ///         ? DigitalAnalogEnum.Digital
        ///         : DigitalAnalogEnum.Analog;
        /// </summary>
        public DigitalAnalogEnum DigitalAnalog {
            get { return DigitalAnalogRaw ? DigitalAnalogEnum.Analog : DigitalAnalogEnum.Digital; }
            set { DigitalAnalogRaw = value == DigitalAnalogEnum.Analog; }
        }

        public ControlEnum Control
        {
            get { return ControlRaw ? ControlEnum.On : ControlEnum.Off; }
            set { ControlRaw = value == ControlEnum.On; }
        }

        public UnitsEnum Units {
            get { return (UnitsEnum)UnitsRaw; }
            set { UnitsRaw = (byte)value; }
        }

        public StrVariablePoint() { }

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

        public StrVariablePoint(byte[] bytes, int offset = 0, FileVersionEnum version = FileVersionEnum.Current) : base(bytes, offset)
        {
            switch (version)
            {
                case FileVersionEnum.Dos:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    AutoManualRaw = bytes.GetBit(0, 34 + offset);
                    DigitalAnalogRaw = bytes.GetBit(1, 34 + offset);
                    ControlRaw = bytes.GetBit(2, 34 + offset);
                    UnitsRaw = bytes[35 + offset];
                    break;

                case FileVersionEnum.Current:
                    /* For debug
                    Console.WriteLine(bytes.GetString(0 + offset, 21));
                    Console.WriteLine(bytes.GetString(21 + offset, 9));
                    Console.WriteLine(bytes.ToInt32(30 + offset));
                    Console.WriteLine(bytes.ToByte(34 + offset));
                    Console.WriteLine(bytes.ToByte(35 + offset));
                    Console.WriteLine(bytes.ToByte(36 + offset));
                    Console.WriteLine(bytes.ToByte(37 + offset));
                    Console.WriteLine(bytes.ToByte(38 + offset));
                    Console.WriteLine();
                    //*/
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    AutoManualRaw = bytes.ToByte(34 + offset) > 0;
                    DigitalAnalogRaw = bytes.ToByte(35 + offset) > 0;
                    ControlRaw = bytes.ToByte(36 + offset) > 0;
                    UnusedRaw = bytes.ToByte(37 + offset);
                    UnitsRaw = DigitalAnalogRaw
                        ? bytes[38 + offset]
                        : (byte)(bytes[38 + offset] + 100);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public byte[] ToBytes(FileVersionEnum version = FileVersionEnum.Current)
        {
            var bytes = new List<byte>();

            switch (version)
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
                    bytes.Add(UnusedRaw); //WTF 2??
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