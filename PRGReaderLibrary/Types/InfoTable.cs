namespace PRGReaderLibrary
{
    public class InfoTable
    {
        public string Address { get; set; } //char*
        public ushort StringSize { get; set; }
        public ushort MaxPoints { get; set; }
        public string Name { get; set; } //char*
    }
}