namespace PRGReaderLibrary
{
    public class InoutPoint : ValuedPoint
    {
        public int Decommissioned { get; set; }
        public bool SubId { get; set; }
        public bool SubProduct { get; set; }
        public double SubNumber { get; set; }

        public InoutPoint(string description = "", string label = "",
            FileVersion version = FileVersion.Current)
            : base(description, label, version)
        { }

        #region Binary data

        public static double SubNumberFromByte(byte value) =>
            value.ToBoolean() ? 1.0 : 0.1;

        public static byte SubNumberToByte(double value) =>
            (value == 1.0).ToByte();

        public InoutPoint(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        { }

        #endregion
    }
}
