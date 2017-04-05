namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class VariablePoint : ValuedPoint, IBinaryObject
    {
        public VariablePoint(string description = "", string label = "", 
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        {}

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 128;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 39;

                case FileVersion.Dos:
                    return 36;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 39 bytes
        /// FileVersion.Dos - Need 36 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
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
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            Value = new VariableValue(valueRaw, units);
        }

        /// <summary>
        /// FileVersion.Current - 39 bytes
        /// FileVersion.Dos - 36 bytes
        /// </summary>
        /// <returns></returns>
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
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}