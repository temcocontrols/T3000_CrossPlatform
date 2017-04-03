namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 9 + 96 = 105 bytes
    /// </summary>
    public class StrTblPoint
    {
        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        public string Label { get; set; }

        /// <summary>
        /// Size: SizeConstants.TBL_POINT_TABLE_SIZE(16) * 6 = 96
        /// </summary>
        public IList<TblPoint> Table { get; set; } = new List<TblPoint>();
    }
}