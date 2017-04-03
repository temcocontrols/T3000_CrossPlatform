namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 4 + 480 = 484 bytes
    /// </summary>
    public class PasswordStruct
    {
        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int Index { get; set; }

        /// <summary>
        /// Size: SizeConstants.MAX_PASSW(10) * 48 = 480
        /// </summary>
        public IList<PasswordPoint> Passwords { get; set; } = new List<PasswordPoint>();
    }
}