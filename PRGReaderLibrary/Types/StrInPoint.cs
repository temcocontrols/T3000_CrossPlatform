namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 4 + 2 + 1 + 1 = 38 bytes
    /// </summary>
    public class StrInPoint : BasePoint
    {
        /// <summary>
        /// Size: 4 bytes. Long?
        /// </summary>
        public float Value { get; set; }

        /// <summary>
        /// Size: 3 bits. 0=1,1=2,2=4,3=8,4=16,5=32,6=64,7=128
        /// </summary>
        public byte Filter { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Decommissioned { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool SenOn { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool SenOff { get; set; }

        /// <summary>
        /// Size: 1 bit. false - off
        /// </summary>
        public bool Control { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Automatic
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// Size: 1 bit. false - Digital
        /// </summary>
        public bool IsAnalog { get; set; }

        /// <summary>
        /// Size: 1 bit. false - positive; true - negative
        /// </summary>
        public bool CalibrationSign { get; set; }

        /// <summary>
        /// Size: 1 bit. false - 0.1, true - 1.0
        /// </summary>
        public bool CalibrationIncrement { get; set; }

        /// <summary>
        /// Size: 5 bit
        /// </summary>
        public bool Unused { get; set; }

        /// <summary>
        /// Size: 1 byte. -256.0 to 256.0 / -25.6 to 25.6 (msb is sign)) 
        /// TODO: ? signed char - it is -127 to 127, -12.7 to 12.7 or 0.0 to 25.5
        /// </summary>
        public byte Calibration { get; set; }

        /// <summary>
        /// Size: 1 byte. input_range_equate
        /// </summary>
        public byte Range { get; set; }
    }
}