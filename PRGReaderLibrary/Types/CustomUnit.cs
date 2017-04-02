namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class CustomUnit
    {
        public bool Direct { get; set; }
        public string DigitalUnitsOff { get; set; }
        public string DigitalUnitsOn { get; set; }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(DigitalUnitsOff) &&
            string.IsNullOrWhiteSpace(DigitalUnitsOn);

        public CustomUnit(bool direct = false, 
            string digitalUnitsOff = "", 
            string digitalUnitsOn = "", 
            FileVersion version = FileVersion.Current)
        {
            Direct = direct;
            DigitalUnitsOff = digitalUnitsOff;
            DigitalUnitsOn = digitalUnitsOn;
        }

        #region Binary data

        public CustomUnit(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
        {
            Direct = bytes.ToByte(0 + offset).ToBoolean();
            DigitalUnitsOff = bytes.GetString(1 + offset, 12).ClearBinarySymvols();
            DigitalUnitsOn = bytes.GetString(13 + offset, 12).ClearBinarySymvols();
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.Add(Direct.ToByte());
            bytes.AddRange(DigitalUnitsOff.ToBytes(12));
            bytes.AddRange(DigitalUnitsOn.ToBytes(12));

            return bytes.ToArray();
        }

        #endregion
    }
}