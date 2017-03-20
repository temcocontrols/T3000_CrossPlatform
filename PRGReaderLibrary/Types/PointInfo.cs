namespace PRGReaderLibrary
{
    public class PointInfo
    {
        public NetPoint Point { get; set; }
        public float Value { get; set; }
        public bool IsManual { get; set; }  // 0=auto, 1=manual
        public bool IsAnalog { get; set; }  // 0=digital, 1=analog
        public bool IsDisplayLabel { get; set; } // 0=display description, 1=display label
        public byte Security { get; set; }  // 0-3 correspond to 2-5 access level
        public bool IsDecomisioned { get; set; }  // 0=normal, 1=point decommissioned
        public Unit Unit { get; set; }
    }
}