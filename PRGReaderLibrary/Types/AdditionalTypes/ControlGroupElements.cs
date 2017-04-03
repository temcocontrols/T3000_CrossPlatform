namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 4 + 4 = 8 bytes
    /// </summary>
    public class ControlGroupElements
    {
        /// <summary>
        /// Size: 4 byte. Modified. Initially ptr(4)
        /// </summary>
        public IList<StrGrpElement> Grps { get; set; } = new List<StrGrpElement>();

        /// <summary>
        /// Size: 4 byte
        /// </summary>
        public int NumberElements => Grps.Count;
    }
}