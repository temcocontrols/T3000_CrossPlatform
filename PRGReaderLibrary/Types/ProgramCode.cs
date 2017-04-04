﻿namespace PRGReaderLibrary
{
    public class ProgramCode : BaseCode, IBinaryObject
    {
        public ProgramCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(2000, version)
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
            : base(bytes, 2000, offset, version)
        {}

        /// <summary>
        /// FileVersion.Current - 2000 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes() => base.ToBytes();

        #endregion

    }
}
