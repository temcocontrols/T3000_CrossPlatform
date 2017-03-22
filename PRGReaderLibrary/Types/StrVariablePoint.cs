namespace PRGReaderLibrary
{
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

        public static StrVariablePoint FromBytes(byte[] bytes, int offset = 0)
        {
            var point = new StrVariablePoint();

            point.Description = bytes.GetString(0 + offset, 21);
            point.Label = bytes.GetString(21 + offset, 9);
            point.Value = bytes.ToBoolean(30 + offset);
            point.IsManual = bytes.ToBoolean(30 + offset);
            point.Units = (UnitsEnum)bytes[35 + offset];

            return point;
        }
    }
}