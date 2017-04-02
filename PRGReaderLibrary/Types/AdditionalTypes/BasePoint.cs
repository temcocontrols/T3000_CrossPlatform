namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class BasePoint : DescriptionPoint
    {
        public string Label { get; set; }

        public BasePoint(string description = "", string label = "", FileVersion version = FileVersion.Current)
            : base(description, version)
        {
            Label = label;
        }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(Description) &&
            string.IsNullOrWhiteSpace(Label);

        #region Binary data

        public BasePoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            Label = bytes.GetString(21 + offset, 9).ClearBinarySymvols();
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(base.ToBytes());
            bytes.AddRange(Label.ToBytes(9));

            return bytes.ToArray();
        }

        #endregion
    }
}