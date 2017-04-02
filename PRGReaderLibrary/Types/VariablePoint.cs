namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class VariablePoint : UnitsPoint
    {
        public VariablePoint(string description = "", string label = "", 
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        {}

        #region Binary data
        
        public VariablePoint(byte[] bytes, int offset = 0, 
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            uint valueRaw;
            Units units;

            switch (FileVersion)
            {
                case FileVersion.Dos:
                    valueRaw = bytes.ToUInt32(30 + offset);
                    AutoManual = AutoManualFromByte(bytes.GetBit(0, 34 + offset).ToByte());
                    DigitalAnalog = DigitalAnalogFromByte(bytes.GetBit(1, 34 + offset).ToByte());
                    Control = ControlFromByte(bytes.GetBit(2, 34 + offset).ToByte());
                    units = (Units)bytes.ToByte(35 + offset);
                    break;

                case FileVersion.Current:
                    valueRaw = bytes.ToUInt32(30 + offset);
                    AutoManual = AutoManualFromByte(bytes.ToByte(34 + offset));
                    DigitalAnalog = DigitalAnalogFromByte(bytes.ToByte(35 + offset));
                    Control = ControlFromByte(bytes.ToByte(36 + offset));
                    //37 byte is unused
                    units = UnitsFromByte(bytes.ToByte(38 + offset), DigitalAnalog);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            Value = new VariableVariant(valueRaw, units);
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Dos:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add(new[] {
                        ToByte(AutoManual).ToBoolean(),
                        ToByte(DigitalAnalog).ToBoolean(),
                        ToByte(Control).ToBoolean() }.ToBits());
                    bytes.Add((byte)Value.Units);
                    break;

                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add(ToByte(AutoManual));
                    bytes.Add(ToByte(DigitalAnalog));
                    bytes.Add(ToByte(Control));
                    bytes.Add(2); //TODO: WTF (it equals 2)??
                    bytes.Add(ToByte(Value.Units, DigitalAnalog));
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}