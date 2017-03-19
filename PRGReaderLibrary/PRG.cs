namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class PRG
    {
        public string DateTime { get; set; }
        public string Signature { get; set; }
        public ushort PanelNumber { get; set; }
        public ushort NetworkNumber { get; set; }
        public ushort Version { get; set; }
        public ushort MiniVersion { get; set; }
        public byte[] Reserved { get; set; }
        public long Lenght { get; set; }
        public long Coef { get; set; }
        public IList<char[]> Infos { get; set; } = new List<char[]>();
        public IList<PRGData> PrgDatas { get; set; } = new List<PRGData>();
        public IList<IList<WrOneDay>> WrTimes { get; set; } = new List<IList<WrOneDay>>();
        public IList<byte[]> ArDates { get; set; } = new List<byte[]>();
        public IList<byte[]> GrpDatas { get; set; } = new List<byte[]>();
        public byte[] IconNameTable { get; set; }

        public static PRG Load(string path) => PRGReader.Read(path);

        public override string ToString() => StringUtilities.ObjectToString(this);
    }
}