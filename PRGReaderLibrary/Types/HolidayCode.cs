namespace PRGReaderLibrary
{
    using System;

    public class HolidayCode : BaseCode, IBinaryObject
    {
        public HolidayCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(46, version)
        {
            Code = code;
        }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 4;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 46;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - need 46 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public HolidayCode(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, 46, offset, version)
        {}

        /// <summary>
        /// FileVersion.Current - 46 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes() => base.ToBytes();

        #endregion

    }
}
