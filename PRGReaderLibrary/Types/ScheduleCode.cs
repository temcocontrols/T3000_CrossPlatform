namespace PRGReaderLibrary
{
    public class ScheduleCode : BaseCode, IBinaryObject
    {
        public ScheduleCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(144, version)
        {
            Code = code;
        }

        #region Binary data

        /// <summary>
        /// FileVersion.Current - need 144 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ScheduleCode(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, 144, offset, version)
        {}

        /// <summary>
        /// FileVersion.Current - 144 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes() => base.ToBytes();

        #endregion

    }
}
