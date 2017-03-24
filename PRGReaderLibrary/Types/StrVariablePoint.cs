namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 + 4 + 1 + 1 = 36
    /// </summary>
    public class StrVariablePoint : BasePoint
    {
        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public bool Value { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Digital
        /// </summary>
        public bool IsAnalog { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool IsControl { get; set; }

        /// <summary>
        /// Size: 5 bit
        /// </summary>
        public byte Unused { get; set; }

        /// <summary>
        /// Size: 1 byte. variable_range_equate
        /// </summary>
        public UnitsEnum Units { get; set; }

        #region Binary data

        public byte[] RawData { get; protected set; }

        //public StrVariablePoint() {}

        public StrVariablePoint(byte[] bytes, int offset = 0) : base(bytes, offset)
        {
            Value = bytes.ToBoolean(30 + offset);
            IsManual = bytes.ToBoolean(30 + offset);
            Units = (UnitsEnum)bytes[35 + offset];

            RawData = bytes.ToBytes(30 + offset, 6);
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            bytes.AddRange(base.ToBytes());
            //bytes.AddRange(Value.ToBytes());
            //bytes.AddRange(IsManual.ToBytes());

            //Append raw data.
            bytes.AddRange(RawData.ToBytes(bytes.Count, RawData.Length - bytes.Count));

            return bytes.ToArray();
        }

        #endregion
    }
}