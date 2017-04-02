namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class InputPoint : UnitsPoint
    {
        public InputPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(description, label, version, customUnits)
        { }

        /// <summary>
        /// Size: 38 + 8 = 46 bytes
        /// </summary>
        #region Binary data

        /// <summary>
        /// Size: 1 bytes. Used 3 bits: 0=1,1=2,2=4,3=8,4=16,5=32,6=64,7=128
        /// </summary>
        protected byte FilterRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected byte DecommissionedRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected bool SubIdRaw { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected bool SubProductRaw { get; set; }

        /// <summary>
        /// Size: 1 byte. sign 0 = positiv 1 = negative
        /// </summary>
        protected bool CalibrationSignRaw { get; set; }

        /// <summary>
        /// Size: 1 byte. 0 = 0.1, 1 = 1.0
        /// </summary>
        protected bool SubNumberRaw { get; set; }

        /// <summary>
        /// Size: 1 byte. 5 bits - spare
        /// </summary>
        protected byte CalibrationHRaw { get; set; }

        /// <summary>
        /// Size: 1 byte. -25.6 to 25.6 / -256 to 256
        /// </summary>
        protected byte CalibrationLRaw { get; set; }

        public InputPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(bytes, offset, version, customUnits)
        {
            bool autoManualRaw;
            bool digitalAnalogRaw;
            bool controlRaw;
            switch (FileVersion)
            {
                case FileVersion.Current:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    FilterRaw = bytes.ToByte(34 + offset);
                    DecommissionedRaw = bytes.ToByte(35 + offset);
                    SubIdRaw = bytes.ToBoolean(36 + offset);
                    SubProductRaw = bytes.ToBoolean(37 + offset);
                    controlRaw = bytes.ToBoolean(38 + offset);
                    autoManualRaw = bytes.ToBoolean(39 + offset);
                    digitalAnalogRaw = bytes.ToBoolean(40 + offset);
                    CalibrationSignRaw = bytes.ToBoolean(41 + offset);
                    SubNumberRaw = bytes.ToBoolean(42 + offset);
                    CalibrationHRaw = bytes.ToByte(43 + offset);
                    CalibrationLRaw = bytes.ToByte(44 + offset);
                    UnitsRaw = digitalAnalogRaw
                        ? bytes[45 + offset]
                        : (byte)(bytes[45 + offset] + 100);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            AutoManual = autoManualRaw ? AutoManual.Manual : AutoManual.Automatic;
            DigitalAnalog = digitalAnalogRaw ? DigitalAnalog.Analog : DigitalAnalog.Digital;
            Control = controlRaw ? Control.On : Control.Off;
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            var autoManualRaw = AutoManual == AutoManual.Manual;
            var digitalAnalogRaw = DigitalAnalog == DigitalAnalog.Analog;
            var controlRaw = Control == Control.On;
            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(FilterRaw);
                    bytes.Add(DecommissionedRaw);
                    bytes.Add(SubIdRaw.ToByte());
                    bytes.Add(SubProductRaw.ToByte());
                    bytes.Add(controlRaw.ToByte());
                    bytes.Add(autoManualRaw.ToByte());
                    bytes.Add(digitalAnalogRaw.ToByte());
                    bytes.Add(CalibrationSignRaw.ToByte());
                    bytes.Add(SubNumberRaw.ToByte());
                    bytes.Add(CalibrationHRaw);
                    bytes.Add(CalibrationLRaw);
                    bytes.Add(digitalAnalogRaw ? UnitsRaw : (byte)(UnitsRaw - 100));
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion

    }
}