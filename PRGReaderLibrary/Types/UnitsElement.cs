namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class UnitsElement
    {
        public bool Direct {
            get { return DirectRaw.ToBoolean(); }
            set { DirectRaw = value.ToByte(); }
        }
        public string DigitalUnitsOff {
            get { return DigitalUnitsOffRaw.ClearBinarySymvols(); }
            set { DigitalUnitsOffRaw = value.AddBinarySymvols(12); }
        }
        public string DigitalUnitsOn {
            get { return DigitalUnitsOnRaw.ClearBinarySymvols(); }
            set { DigitalUnitsOnRaw = value.AddBinarySymvols(9); }
        }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(DigitalUnitsOff) &&
            string.IsNullOrWhiteSpace(DigitalUnitsOn);

        public UnitsElement(bool direct = false, 
            string digitalUnitsOff = "", 
            string digitalUnitsOn = "", 
            FileVersion version = FileVersion.Current)
        {
            Direct = direct;
            DigitalUnitsOff = digitalUnitsOff;
            DigitalUnitsOn = digitalUnitsOn;
        }

        /// <summary>
        /// Size: 1 + 12 + 12 = 25 bytes
        /// </summary>

        #region Binary data

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        protected byte DirectRaw { get; set; }

        /// <summary>
        /// Size: 12 bytes
        /// </summary>
        protected string DigitalUnitsOffRaw { get; set; }

        /// <summary>
        /// Size: 12 bytes
        /// </summary>
        protected string DigitalUnitsOnRaw { get; set; }

        public UnitsElement(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
        {
            DirectRaw = bytes.ToByte(0 + offset);
            DigitalUnitsOffRaw = bytes.GetString(1 + offset, 12);
            DigitalUnitsOnRaw = bytes.GetString(13 + offset, 12);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(DirectRaw.ToBytes());
            bytes.AddRange(DigitalUnitsOffRaw.ToBytes(12));
            bytes.AddRange(DigitalUnitsOnRaw.ToBytes(12));

            return bytes.ToArray();
        }

        #endregion
    }
}