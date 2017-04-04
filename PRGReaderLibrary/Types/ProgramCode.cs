namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class ProgramCode : Version, IBinaryObject
    {
        public byte[] Code { get; set; }

        public ProgramCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(version)
        {
            Code = code;
        }

        #region Binary data

        /// <summary>
        /// FileVersion.Current - need 2000 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ProgramCode(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Code = bytes.ToBytes(0 + offset, 2000);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 2000 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Code);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion

    }
}
