namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class ProgramCode : BaseCode, IBinaryObject
    {
        public int Version { get; set; }
        public List<byte[]> Lines { get; set; } = new List<byte[]>();

        public ProgramCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(2000, version)
        {
            Code = code;
        }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 16;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 2000;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - need 2000 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ProgramCode(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, 2000, offset, version)
        {
            Version = bytes.ToInt16(ref offset);
            while (offset < 2000)
            {
                var data = bytes.ToBytes(ref offset, 5);
                var size = data[4];
                Lines.Add(bytes.ToBytes(ref offset, size));
                //data = bytes.ToBytes(ref offset, 5);
                //size = data[4];
                //bytes.ToBytes(ref offset, size);
            }
        }

        /// <summary>
        /// FileVersion.Current - 2000 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes() => base.ToBytes();

        #endregion

    }
}
