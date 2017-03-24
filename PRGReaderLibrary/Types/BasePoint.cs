namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 30 bytes
    /// </summary>
    public class BasePoint
    {
        /// <summary>
        /// Size: 21 bytes
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        public string Label { get; set; }

        public BasePoint() {}

        public BasePoint(byte[] bytes, int offset = 0)
        {
            Description = bytes.GetString(0 + offset, 21);
            Label = bytes.GetString(21 + offset, 9);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            bytes.AddRange(Description.ToBytes(21));
            bytes.AddRange(Label.ToBytes(9));

            return bytes.ToArray();
        }
    }
}