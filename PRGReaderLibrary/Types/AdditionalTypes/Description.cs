namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 21 bytes
    /// </summary>
    public class DescriptionPoint : Version
    {
        public string Description {
            get { return DescriptionRaw.ClearBinarySymvols(); }
            set { DescriptionRaw = value.AddBinarySymvols(21); }
        }

        public DescriptionPoint(string description = "", FileVersion version = FileVersion.Current)
            : base(version)
        {
            Description = description;
        }

        #region Binary data

        /// <summary>
        /// Size: 21 bytes
        /// </summary>
        protected string DescriptionRaw { get; set; }

        public DescriptionPoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            DescriptionRaw = bytes.GetString(0 + offset, 21);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(DescriptionRaw.ToBytes(21));

            return bytes.ToArray();
        }

        #endregion
    }
}