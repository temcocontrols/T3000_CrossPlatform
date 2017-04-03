namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class ProgramPoint : BasePoint, IBinaryObject
    {
        public int Length { get; set; }
        public Control Control { get; set; }
        public AutoManual AutoManual { get; set; }
        public NormalCom NormalCom { get; set; }
        public int ErrorCode { get; set; }
        public int Unused { get; set; }

        public ProgramPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static byte ToByte(NormalCom value) =>
            (value == NormalCom.Com).ToByte();
        public static NormalCom NormalComFromByte(byte value) =>
            value.ToBoolean() ? NormalCom.Com : NormalCom.Normal;

        public ProgramPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Length = bytes.ToUInt16(30 + offset);
                    Control = ValuedPoint.ControlFromByte(bytes.ToByte(32 + offset));
                    AutoManual = ValuedPoint.AutoManualFromByte(bytes.ToByte(33 + offset));
                    NormalCom = NormalComFromByte(bytes.ToByte(34 + offset));
                    ErrorCode = bytes.ToByte(35 + offset);
                    Unused = bytes.ToByte(36 + offset);
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
                case FileVersion.Current:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(((ushort)Length).ToBytes());
                    bytes.Add(ValuedPoint.ToByte(Control));
                    bytes.Add(ValuedPoint.ToByte(AutoManual));
                    bytes.Add(ToByte(NormalCom));
                    bytes.Add((byte)ErrorCode);
                    bytes.Add((byte)Unused);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}