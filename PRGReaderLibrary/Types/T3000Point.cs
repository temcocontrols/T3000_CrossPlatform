namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class T3000Point : Version, IBinaryObject
    {
        public int Number { get; set; }
        public PanelType Type { get; set; }
        public int Panel { get; set; }

        public T3000Point(int number = 0,
            PanelType type = PanelType.T3000,
            int panel = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Number = number;
            Type = type;
            Panel = panel;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() != GetType())
            {
                return false;
            }

            var point = (T3000Point) obj;
            return Number == point.Number &&
                Type == point.Type &&
                Panel == point.Panel;
        }

        #region Binary data

        public static byte ToByte(PanelType value) => (byte)value;
        public static PanelType PanelTypeFromByte(byte value) => (PanelType) value;

        public T3000Point(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Number = bytes.ToByte(0 + offset);
                    Type = PanelTypeFromByte(bytes.ToByte(1 + offset));
                    Panel = bytes.ToByte(2 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.Add((byte)Number);
                    bytes.Add(ToByte(Type));
                    bytes.Add((byte)Panel);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}