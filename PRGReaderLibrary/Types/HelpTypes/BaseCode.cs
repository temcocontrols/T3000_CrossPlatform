namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class BaseCode : Version
    {
        public int Count { get; }
        public byte[] Code { get; set; }

        public BaseCode(int count, FileVersion version = FileVersion.Current)
            : base(version)
        {
            Count = count;
        }

        #region Binary data

        /// <summary>
        /// FileVersion.Current - need $Count$ bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public BaseCode(byte[] bytes, int count, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Count = count;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    Code = bytes.ToBytes(0 + offset, Count);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }
        }

        /// <summary>
        /// FileVersion.Current - $Count$ bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Code ?? new byte[Count]);
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            return bytes.ToArray();
        }

        #endregion

    }
}
