namespace PRGReaderLibrary
{
    public class PRGType
    {
        public int Size { get; set; }
        public byte[] Data { get; set; }
        public string Name { get; set; }
        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}