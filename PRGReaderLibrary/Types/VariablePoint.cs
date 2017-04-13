namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class VariablePoint : BasePoint, IBinaryObject
    {
        public VariableValue Value { get; set; } = new VariableValue(0, 0);
        public AutoManual AutoManual { get; set; }
        public DigitalAnalog DigitalAnalog { get; set; }
        public OffOn Control { get; set; }

        public VariablePoint(string description = "", string label = "", 
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static byte ToByte(Unit unit, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (byte)unit
            : (byte)(unit - Unit.DigitalUnused);

        public static Unit UnitsFromByte(byte value, DigitalAnalog digitalAnalog) =>
            digitalAnalog == DigitalAnalog.Analog
            ? (Unit)value
            : value + Unit.DigitalUnused;

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

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            var size = BasePoint.GetSize(version);
            switch (version)
            {
                case FileVersion.Current:
                    return size + 9;

                case FileVersion.Dos:
                    return size + 6;

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
            offset += BasePoint.GetSize(FileVersion);

            int valueRaw;
            Unit unit;

            switch (FileVersion)
            {
                case FileVersion.Dos:
                    valueRaw = bytes.ToInt32(ref offset);
                    AutoManual = (AutoManual) bytes.GetBit(0, ref offset).ToByte();
                    DigitalAnalog = (DigitalAnalog)bytes.GetBit(1, ref offset).ToByte();
                    Control = (OffOn)bytes.GetBit(2, ref offset).ToByte();
                    offset += 1;//after GetBit
                    unit = (Unit)bytes.ToByte(ref offset);
                    break;

                case FileVersion.Current:
                    valueRaw = bytes.ToInt32(ref offset);
                    AutoManual = (AutoManual)bytes.ToByte(ref offset);
                    DigitalAnalog = (DigitalAnalog)bytes.ToByte(ref offset);
                    Control = (OffOn)bytes.ToByte(ref offset);
                    offset += 1;//this byte is unused
                    unit = UnitsFromByte(bytes.ToByte(ref offset), DigitalAnalog);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            Value = new VariableValue(valueRaw, unit);

            var size = GetSize(FileVersion);
            if (offset != size)
            {
                throw new OffsetException(offset, size);
            }
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
                        ((byte)AutoManual).ToBoolean(),
                        ((byte)DigitalAnalog).ToBoolean(),
                        ((byte)Control).ToBoolean() }.ToBits());
                    bytes.Add((byte)Value.Unit);
                    break;

                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Value.Value.ToBytes());
                    bytes.Add((byte)AutoManual);
                    bytes.Add((byte)DigitalAnalog);
                    bytes.Add((byte)Control);
                    bytes.Add(2); //TODO: WTF (it equals 2)??
                    bytes.Add(ToByte(Value.Unit, DigitalAnalog));
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            var size = GetSize(FileVersion);
            if (bytes.Count != size)
            {
                throw new OffsetException(bytes.Count, size);
            }

            return bytes.ToArray();
        }

        #endregion
    }
}