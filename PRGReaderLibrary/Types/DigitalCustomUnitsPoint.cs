namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class DigitalCustomUnitsPoint : Version, IBinaryObject
    {
        public bool Direct { get; set; }
        public string DigitalUnitsOff { get; set; }
        public string DigitalUnitsOn { get; set; }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(DigitalUnitsOff) &&
            string.IsNullOrWhiteSpace(DigitalUnitsOn);

        public DigitalCustomUnitsPoint(bool direct = false,
            string digitalUnitsOff = "",
            string digitalUnitsOn = "",
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Direct = direct;
            DigitalUnitsOff = digitalUnitsOff;
            DigitalUnitsOn = digitalUnitsOn;
        }

        #region Binary data

        public DigitalCustomUnitsPoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Dos:
                case FileVersion.Current:
                    Direct = bytes.ToByte(0 + offset).ToBoolean();
                    DigitalUnitsOff = bytes.GetString(1 + offset, 12).ClearBinarySymvols();
                    DigitalUnitsOn = bytes.GetString(13 + offset, 12).ClearBinarySymvols();
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
                case FileVersion.Dos:
                case FileVersion.Current:
                    bytes.Add(Direct.ToByte());
                    bytes.AddRange(DigitalUnitsOff.ToBytes(12));
                    bytes.AddRange(DigitalUnitsOn.ToBytes(12));
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}