namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 3 + 4 + 4 + 3 + 4 + 1 + 1 + 4 = 24 bytes
    /// </summary>
    public class StrControllerPoint
    {
        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point Input { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public float InputValue { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public float Value { get; set; }

        /// <summary>
        /// Size: 3 bytes
        /// </summary>
        public T3000Point SetPoint { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public float SetPointValue { get; set; }

        /// <summary>
        /// Size: 1 byte. Analog_units_equate
        /// </summary>
        public UnitsEnum Units { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - direct, true - reverse
        /// </summary>
        public bool Action { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Repeats/Hour, true - Repeats/Min
        /// </summary>
        public bool RepeatsPerMin { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Unused { get; set; }

        /// <summary>
        /// Size: 4 bits. High 4 bits of proportional bad
        /// </summary>
        public byte PropHigh { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-2000 with prop_high
        /// </summary>
        public byte Proportional { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-255
        /// </summary>
        public byte Reset { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-100
        /// </summary>
        public byte Bias { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-2.00
        /// </summary>
        public byte Rate { get; set; }
    }
}