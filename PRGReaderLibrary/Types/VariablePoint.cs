namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class VariablePoint : UnitsPoint
    {
        public VariablePoint(string description = "", string label = "", 
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(description, label, version, customUnits)
        {}

        /// <summary>
        /// Size: 38 + 1 = 39
        /// </summary>
        #region Binary data
            
        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected byte UnusedRaw { get; set; } = 2; //TODO: WTF
        
        public VariablePoint(byte[] bytes, int offset = 0, 
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(bytes, offset, version, customUnits)
        {
            switch (FileVersion)
            {
                case FileVersion.Dos:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    AutoManualRaw = bytes.GetBit(0, 34 + offset);
                    DigitalAnalogRaw = bytes.GetBit(1, 34 + offset);
                    ControlRaw = bytes.GetBit(2, 34 + offset);
                    UnitsRaw = bytes[35 + offset];
                    break;

                case FileVersion.Current:
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
                case FileVersion.Dos:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(new[] { AutoManualRaw, DigitalAnalogRaw, ControlRaw }.ToBits());
                    bytes.Add(UnitsRaw);
                    break;

                case FileVersion.Current:
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