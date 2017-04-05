namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class Settings : Version, IBinaryObject
    {
        public byte[] Ip { get; set; }
        public byte[] SubNet { get; set; }
        public byte[] Gate { get; set; }
        public byte[] Mac { get; set; }
        public TcpType TcpType { get; set; }
        public int MiniType { get; set; }
        public int Debug { get; set; }
        public ProInfo ProInfo { get; set; }
        public int Com0Config { get; set; }
        public int Com1Config { get; set; }
        public int Com2Config { get; set; }
        public int RefreshFlashTimer { get; set; }
        public NoYes PlugNPlay { get; set; }
        /// <summary>
        /// write 88
        /// </summary>
        public int ResetDefault { get; set; }
        public int ComBaudRate0 { get; set; }
        public int ComBaudRate1 { get; set; }
        public int ComBaudRate2 { get; set; }
        public NoDisableEnable UserNameMode { get; set; }
        public NoYes EnableCustomerUnit { get; set; }
        public UsbMode UsbMode { get; set; }
        public int NetworkNumber { get; set; }
        public int PanelType { get; set; }
        public string PanelName { get; set; }
        public NoYes EnablePanelName { get; set; }
        public int PabelNumber { get; set; }
        public string DynDNSUser { get; set; }
        public string DynDNSPassword { get; set; }
        public string DynDNSDomain { get; set; }
        public NoDisableEnable DynDNSMode { get; set; }
        public DynDNSProvider DynDNSProvider { get; set; }
        public int DynDNSUpdateTime { get; set; }
        public NoDisableEnable SntpMode { get; set; }
        public int TimeZone { get; set; }
        public long SerialNumber { get; set; }
        public UNTime UpdateDynDNS { get; set; }
        public int MstpNetworkNumber { get; set; }
        public int BBMDEn { get; set; }
        public int SdExist { get; set; } // 1 -no    2- yes
        public int ModbusPort { get; set; }
        public int ModbusId { get; set; }
        public long ObjectInstance { get; set; }
        public long TimeUpdateSince1970 { get; set; }
        public int TimeZoneSummerDaytime { get; set; }
        public string SntpServer { get; set; }
        public int ZegbeeExist { get; set; }

        public Settings(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 1;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 400;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - Need 400 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public Settings(byte[] bytes, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            switch (FileVersion)
            {
                case FileVersion.Current:
                    Ip = bytes.ToBytes(0 + offset, 4);
                    SubNet = bytes.ToBytes(4 + offset, 4);
                    Gate = bytes.ToBytes(8 + offset, 4);
                    Mac = bytes.ToBytes(12 + offset, 6);
                    TcpType = (TcpType)bytes.ToByte(18 + offset);
                    MiniType = bytes.ToByte(19 + offset);
                    Debug = bytes.ToByte(20 + offset);
                    ProInfo = new ProInfo(bytes.ToBytes(21 + offset, 17), 0, FileVersion);
                    Com0Config = bytes.ToByte(38 + offset);
                    Com1Config = bytes.ToByte(39 + offset);
                    Com2Config = bytes.ToByte(40 + offset);
                    RefreshFlashTimer = bytes.ToByte(41 + offset);
                    PlugNPlay = (NoYes)bytes.ToByte(42 + offset);
                    ResetDefault = bytes.ToByte(43 + offset);
                    ComBaudRate0 = bytes.ToByte(44 + offset);
                    ComBaudRate1 = bytes.ToByte(45 + offset);
                    ComBaudRate2 = bytes.ToByte(46 + offset);
                    UserNameMode = (NoDisableEnable)bytes.ToByte(47 + offset);
                    EnableCustomerUnit = (NoYes)bytes.ToByte(48 + offset);
                    UsbMode = (UsbMode)bytes.ToByte(49 + offset);
                    NetworkNumber = bytes.ToByte(50 + offset);
                    PanelType = bytes.ToByte(51 + offset);
                    PanelName = bytes.GetString(52 + offset, 20).ClearBinarySymvols();
                    EnablePanelName = (NoYes)bytes.ToByte(72 + offset);
                    PabelNumber = bytes.ToByte(73 + offset);
                    DynDNSUser = bytes.GetString(74 + offset, 32).ClearBinarySymvols();
                    DynDNSPassword = bytes.GetString(106 + offset, 32).ClearBinarySymvols();
                    DynDNSDomain = bytes.GetString(138 + offset, 32).ClearBinarySymvols();
                    DynDNSMode = (NoDisableEnable)bytes.ToByte(170 + offset);
                    DynDNSProvider = (DynDNSProvider)bytes.ToByte(171 + offset);
                    DynDNSUpdateTime = bytes.ToUInt16(172 + offset);
                    SntpMode = (NoDisableEnable)bytes.ToByte(174 + offset);
                    TimeZone = bytes.ToInt16(175 + offset);
                    SerialNumber = bytes.ToUInt32(177 + offset);
                    UpdateDynDNS = new UNTime(bytes.ToBytes(181 + offset, 10), 0, FileVersion);
                    MstpNetworkNumber = bytes.ToUInt16(191 + offset);
                    BBMDEn = bytes.ToByte(193 + offset);
                    SdExist = bytes.ToByte(194 + offset);
                    ModbusPort = bytes.ToUInt16(195 + offset);
                    ModbusId = bytes.ToByte(197 + offset);
                    ObjectInstance = bytes.ToUInt32(198 + offset);
                    TimeUpdateSince1970 = bytes.ToUInt32(202 + offset);
                    TimeZoneSummerDaytime = bytes.ToByte(206 + offset);
                    SntpServer = bytes.GetString(207 + offset, 30).ClearBinarySymvols();
                    ZegbeeExist = bytes.ToByte(237 + offset);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }
        }

        /// <summary>
        /// FileVersion.Current - 400 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            ProInfo.FileVersion = FileVersion;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Ip.ToBytes(0, 4));
                    bytes.AddRange(SubNet.ToBytes(0, 4));
                    bytes.AddRange(Gate.ToBytes(0, 4));
                    bytes.AddRange(Mac.ToBytes(0, 6));
                    bytes.Add((byte)TcpType);
                    bytes.Add((byte)MiniType);
                    bytes.Add((byte)Debug);
                    bytes.AddRange(ProInfo.ToBytes());
                    bytes.Add((byte)Com0Config);
                    bytes.Add((byte)Com1Config);
                    bytes.Add((byte)Com2Config);
                    bytes.Add((byte)RefreshFlashTimer);
                    bytes.Add((byte)PlugNPlay);
                    bytes.Add((byte)ResetDefault);
                    bytes.Add((byte)ComBaudRate0);
                    bytes.Add((byte)ComBaudRate1);
                    bytes.Add((byte)ComBaudRate2);
                    bytes.Add((byte)UserNameMode);
                    bytes.Add((byte)EnableCustomerUnit);
                    bytes.Add((byte)UsbMode);
                    bytes.Add((byte)NetworkNumber);
                    bytes.Add((byte)PanelType);
                    bytes.AddRange(PanelName.ToBytes(20));
                    bytes.Add((byte)EnablePanelName);
                    bytes.Add((byte)PabelNumber);
                    bytes.AddRange(DynDNSUser.ToBytes(32));
                    bytes.AddRange(DynDNSPassword.ToBytes(32));
                    bytes.AddRange(DynDNSDomain.ToBytes(32));
                    bytes.Add((byte)DynDNSMode);
                    bytes.Add((byte)DynDNSProvider);
                    bytes.AddRange(((ushort)DynDNSUpdateTime).ToBytes());
                    bytes.Add((byte)SntpMode);
                    bytes.AddRange(((short)TimeZone).ToBytes());
                    bytes.AddRange(((uint)SerialNumber).ToBytes());
                    bytes.AddRange(UpdateDynDNS.ToBytes());
                    bytes.AddRange(((ushort)MstpNetworkNumber).ToBytes());
                    bytes.Add((byte)BBMDEn);
                    bytes.Add((byte)SdExist);
                    bytes.AddRange(((ushort)ModbusPort).ToBytes());
                    bytes.Add((byte)ModbusId);
                    bytes.AddRange(((uint)ObjectInstance).ToBytes());
                    bytes.AddRange(((uint)TimeUpdateSince1970).ToBytes());
                    bytes.Add((byte)TimeZoneSummerDaytime);
                    bytes.AddRange(SntpServer.ToBytes(30));
                    bytes.Add((byte)ZegbeeExist);
                    bytes.AddRange(new byte[162]);
                    break;

                default:
                    throw new NotImplementedException("File version is not implemented");
            }

            return bytes.ToArray();
        }

        #endregion
    }
}