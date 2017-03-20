namespace PRGReaderLibrary
{
    public class PanelInfo1
    {
        public byte Type { get; set; }
        public uint ActivePanelsCount { get; set; }
        public ushort DesLength { get; set; }
        public int Version { get; set; }
        public byte Number { get; set; }
        public string Name { get; set; } //Lenght is SizeConstants.NAME_SIZE
        public ushort Network { get; set; }
        public string NetworkName { get; set; } //Lenght is SizeConstants.NAME_SIZE
    }
}