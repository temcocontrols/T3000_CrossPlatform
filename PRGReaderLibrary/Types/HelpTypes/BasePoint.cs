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

        public new static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Dos:
                case FileVersion.Current:
                    return DescriptionPoint.GetSize(version) + 9;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public bool IsEmpty =>
            string.IsNullOrWhiteSpace(Description) &&
            string.IsNullOrWhiteSpace(Label);

        #region Binary data

        public BasePoint(byte[] bytes, int offset = 0, FileVersion version = FileVersion.Current)
            : base(bytes, offset, version)
        {
            offset += DescriptionPoint.GetSize(FileVersion);
            switch (FileVersion)
            {
                case FileVersion.Current:
                case FileVersion.Dos:
                    Label = bytes.GetString(ref offset, 9).ClearBinarySymvols();

                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        public new byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                case FileVersion.Dos:
                    bytes.AddRange(base.ToBytes());
                    bytes.AddRange(Label.ToBytes(9));

                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckSize(bytes.Count, GetSize(FileVersion));

            return bytes.ToArray();
        }

        #endregion
    }
}