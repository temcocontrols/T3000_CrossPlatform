namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 bytes
    /// </summary>
    public class BasePoint : DescriptionPoint
    {
        public string Label {
            get { return LabelRaw.ClearBinarySymvols(); }
            set { LabelRaw = value.AddBinarySymvols(9); }
        }

        public BasePoint(string description = "", string label = "", FileVersion version = FileVersion.Current)
            : base(description, version)
        {
            Label = label;
        }

        #region Binary data

        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        protected string LabelRaw { get; set; }

        public BasePoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            LabelRaw = bytes.GetString(21 + offset, 9);
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(base.ToBytes());
            bytes.AddRange(LabelRaw.ToBytes(9));

            return bytes.ToArray();
        }

        #endregion
    }
}