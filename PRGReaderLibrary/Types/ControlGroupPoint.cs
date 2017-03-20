namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 30 + 11 + 1 + 2 + 4 = 46 bytes
    /// </summary>
    public class ControlGroupPoint : BasePoint
    {
        /// <summary>
        /// Size: 11 bytes
        /// </summary>
        public string PictureFile { get; set; }

        /// <summary>
        /// Size: 1 byte. Refresh time
        /// </summary>
        public byte UpdateTime { get; set; }

        /// <summary>
        /// Size: 1 byte. false - TextMode
        /// </summary>
        public bool IsGraphicMode { get; set; }

        /// <summary>
        /// Size: 1 byte. 1 group displayed on screen 
        /// </summary>
        public bool State { get; set; }

        /// <summary>
        /// Size: 14 bytes
        /// </summary>
        public byte[] XCurGrp { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int YCurGrp { get; set; }
    }
}