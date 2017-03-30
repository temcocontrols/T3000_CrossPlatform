namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 bytes
    /// </summary>
    public class BasePoint : Version
    {
        public string Description {
            get { return DescriptionRaw.ClearBinarySymvols(); }
            set { DescriptionRaw = value.AddBinarySymvols(21); }
        }

        public string Label {
            get { return LabelRaw.ClearBinarySymvols(); }
            set { LabelRaw = value.AddBinarySymvols(9); }
        }

        public BasePoint(string description = "", string label = "", FileVersion version = FileVersion.Current)
            : base(version)
        {
            Description = description;
            Label = label;
        }

        #region Binary data

        /// <summary>
        /// Size: 21 bytes
        /// </summary>
        protected string DescriptionRaw { get; set; }

        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        protected string LabelRaw { get; set; }

        public BasePoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(version)
        {
            DescriptionRaw = bytes.GetString(0 + offset, 21);
            LabelRaw = bytes.GetString(21 + offset, 9);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(DescriptionRaw.ToBytes(21));
            bytes.AddRange(LabelRaw.ToBytes(9));

            return bytes.ToArray();
        }

        #endregion
    }
}