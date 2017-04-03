namespace PRGReaderLibrary
{
    /// <summary>
    /// Size: 5 + 2 + 8 + 1 + 59 + 5 + 1 + 4 + 1 + 6 * 1 + 2 = 94 bytes
    /// </summary>
    public class AlarmPoint
    {
        /// <summary>
        /// Size: 5 bytes
        /// </summary>
        public NetPoint Point { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Modem { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Printer { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Alarm { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Restored { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Acknowledged { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool DDelete { get; set; }

        /// <summary>
        /// Size: 2 bits
        /// </summary>
        public byte Type { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte CondType { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public byte Level { get; set; }

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public ulong Time { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Count { get; set; }

        /// <summary>
        /// Size: SizeConstants.ALARM_MESSAGE_SIZE(58) + 1 = 59 bytes
        /// </summary>
        public string Message { get; set; }

        /// <summary>
        /// Size: 5 bytes
        /// </summary>
        public byte[] None { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public PanelType PanelType { get; set; }

        /// <summary>
        /// Size: 4 bits
        /// </summary>
        public PanelType DestPanelType { get; set; }

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public uint Id { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte Prg { get; set; }

        /// <summary>
        /// Size: 1 byte. 1-32, panel alarm originated from
        /// </summary>
        public byte AlarmPanel { get; set; }

        /// <summary>
        /// Size: 1 byte. Panel# to send alarm to, 255 = all
        /// </summary>
        public byte Where1 { get; set; }

        /// <summary>
        /// Size: 1 byte. Panel# to send alarm to, 0 = none
        /// </summary>
        public byte Where2 { get; set; }

        /// <summary>
        /// Size: 1 byte. Panel# to send alarm to, 0 = none
        /// </summary>
        public byte Where3 { get; set; }

        /// <summary>
        /// Size: 1 byte. Panel# to send alarm to, 0 = none
        /// </summary>
        public byte Where4 { get; set; }

        /// <summary>
        /// Size: 1 byte. Panel# to send alarm to, 0 = none
        /// </summary>
        public byte Where5 { get; set; }

        /// <summary>
        /// Size: 1 bit. Panel# to send alarm to, 255 = all
        /// </summary>
        public bool WhereState1 { get; set; }

        /// <summary>
        /// Size: 1 bit. Panel# to send alarm to, 255 = all
        /// </summary>
        public bool WhereState2 { get; set; }

        /// <summary>
        /// Size: 1 bit. Panel# to send alarm to, 255 = all
        /// </summary>
        public bool WhereState3 { get; set; }

        /// <summary>
        /// Size: 1 bit. Panel# to send alarm to, 255 = all
        /// </summary>
        public bool WhereState4 { get; set; }

        /// <summary>
        /// Size: 1 bit. Panel# to send alarm to, 255 = all
        /// </summary>
        public bool WhereState5 { get; set; }

        /// <summary>
        /// Size: 2 bits
        /// </summary>
        public byte ChangeFlag { get; set; }

        /// <summary>
        /// Size: 1 bit
        /// </summary>
        public bool Original { get; set; }

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte No { get; set; }
    }
}