namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    /// <summary>
    /// Size: 9 + 70 + 14 + 4 + 48 + 2 = 147 bytes
    /// </summary>
    public class StrMonitorPoint
    {
        /// <summary>
        /// Size: 9 bytes
        /// </summary>
        public string Label { get; set; }

        /// <summary>
        /// Size: SizeConstants.MAX_POINTS_IN_MONITOR(14) * 5 = 70 bytes
        /// </summary>
        public IList<NetPoint> Inputs { get; set; } = new List<NetPoint>();

        /// <summary>
        /// Size: SizeConstants.MAX_POINTS_IN_MONITOR(14) bytes
        /// </summary>
        public byte[] Range { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-59
        /// </summary>
        public byte SecondIntervalTime { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-59
        /// </summary>
        public byte MinuteIntervalTime { get; set; }

        /// <summary>
        /// Size: 1 byte. 0-255
        /// </summary>
        public byte HourIntervalTime { get; set; }

        /// <summary>
        /// Size: 1 byte. The length of the monitor in time units
        /// </summary>
        public byte MaxTimeLength { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_VIEWS(3) * 16 = 48 bytes
        /// </summary>
        public IList<View> Views { get; set; } = new List<View>();

        /// <summary>
        /// Size: 4 bits. Total number of points
        /// </summary>
        public byte InputsCount { get; set; }

        /// <summary>
        /// Size: 4 bits. Number of analog points
        /// </summary>
        public byte AInputsCount { get; set; }

        /// <summary>
        /// Size: 2 bits. Minutes = 0, Hours = 1, Days = 2
        /// </summary>
        public byte Unit { get; set; }

        /// <summary>
        /// Size: 2 bits. Number of views
        /// </summary>
        public byte ViewsCount { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool DataWrapped { get; set; }

        /// <summary>
        /// Size: 1 bit. Monitor status: false - OFF / true - ON
        /// </summary>
        public bool Status { get; set; }

        /// <summary>
        /// Size: 1 bit. false - No reset / true - Reset
        /// </summary>
        public bool Reset { get; set; }

        /// <summary>
        /// Size: 1 bit. false - 4 bytes data / true - 2 bytes data
        /// </summary>
        public bool Double { get; set; }
    }
}