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

        #region Binary data
        
        public VariablePoint(byte[] bytes, int offset = 0, 
            FileVersion version = FileVersion.Current,
            List<UnitsElement> customUnits = null)
            : base(bytes, offset, version, customUnits)
        {
            bool autoManualRaw;
            bool digitalAnalogRaw;
            bool controlRaw;
            switch (FileVersion)
            {
                case FileVersion.Dos:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    autoManualRaw = bytes.GetBit(0, 34 + offset);
                    digitalAnalogRaw = bytes.GetBit(1, 34 + offset);
                    controlRaw = bytes.GetBit(2, 34 + offset);
                    UnitsRaw = bytes[35 + offset];
                    break;

                case FileVersion.Current:
                    ValueRaw = bytes.ToUInt32(30 + offset);
                    autoManualRaw = bytes.ToBoolean(34 + offset);
                    digitalAnalogRaw = bytes.ToBoolean(35 + offset);
                    controlRaw = bytes.ToBoolean(36 + offset);
                    //37 byte is unused
                    UnitsRaw = digitalAnalogRaw
                        ? bytes[38 + offset]
                        : (byte)(bytes[38 + offset] + 100);
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
                case FileVersion.Dos:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(new[] { autoManualRaw, digitalAnalogRaw, controlRaw }.ToBits());
                    bytes.Add(UnitsRaw);
                    break;

                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(ValueRaw.ToBytes());
                    bytes.Add(autoManualRaw.ToByte());
                    bytes.Add(digitalAnalogRaw.ToByte());
                    bytes.Add(controlRaw.ToByte());
                    bytes.Add(2); //TODO: WTF (it equals 2)??
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