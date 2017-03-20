namespace PRGReaderLibrary
{

    /* 21+9+2+1+1 = 34 bytes*/
    public class StrProgramPoint
    {
        public string Description { get; set; }   // (21 bytes; string)*/
        public string Label { get; set; }         // (9 bytes; string)*/
        public ushort Bytes { get; set; }             // (2 bytes; size in bytes of program)*/
        public bool Enabled { get; set; }// = 1;    // (1 bit; 0=off; 1=on)*/
        public bool IsManual { get; set; }// = 1;    // (1 bit; 0=auto; 1=manual)*/
        public bool IsComProgram { get; set; }// = 1;      // (1 bit; 0=normal , 1=com program)*/
        public short ErrorCode { get; set; }// = 5;      // (1 bit; 0=normal end, 1=too long in program)*/
        public byte Unused { get; set; }                // because of mini's

    }
}