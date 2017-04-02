namespace PRGReaderLibrary
{
    using System.Collections.Generic;
    
    public class DescriptionPoint : Version
    {
        public string Description { get; set; }

        public DescriptionPoint(string description = "", FileVersion version = FileVersion.Current)
            : base(version)
        {
            Description = description;
        }

        #region Binary data

        public DescriptionPoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            Description = bytes.GetString(0 + offset, 21).ClearBinarySymvols();
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(Description.AddBinarySymvols(21).ToBytes(21));

            return bytes.ToArray();
        }

        #endregion
    }
}