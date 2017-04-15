namespace PRGReaderLibrary
{
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
        public ProInfo ProInfo { get; set; } = new ProInfo();
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
        public string PanelName { get; set; } = string.Empty;
        public NoYes EnablePanelName { get; set; }
        public int PabelNumber { get; set; }
        public string DynDNSUser { get; set; } = string.Empty;
        public string DynDNSPassword { get; set; } = string.Empty;
        public string DynDNSDomain { get; set; } = string.Empty;
        public NoDisableEnable DynDNSMode { get; set; }
        public DynDNSProvider DynDNSProvider { get; set; }
        public int DynDNSUpdateTime { get; set; }
        public NoDisableEnable SntpMode { get; set; }
        public int TimeZone { get; set; }
        public long SerialNumber { get; set; }
        public UNTime UpdateDynDNS { get; set; } = new UNTime();
        public int MstpNetworkNumber { get; set; }
        public int BBMDEn { get; set; }
        public int SdExist { get; set; } // 1 -no    2- yes
        public int ModbusPort { get; set; }
        public int ModbusId { get; set; }
        public long ObjectInstance { get; set; }
        public long TimeUpdateSince1970 { get; set; }
        public int TimeZoneSummerDaytime { get; set; }
        public string SntpServer { get; set; } = string.Empty;
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
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 400;

                default:
                    throw new FileVersionNotImplementedException(version);
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
                    Ip = bytes.ToBytes(ref offset, 4);
                    SubNet = bytes.ToBytes(ref offset, 4);
                    Gate = bytes.ToBytes(ref offset, 4);
                    Mac = bytes.ToBytes(ref offset, 6);
                    TcpType = (TcpType)bytes.ToByte(ref offset);
                    MiniType = bytes.ToByte(ref offset);
                    Debug = bytes.ToByte(ref offset);
                    ProInfo = new ProInfo(bytes.ToBytes(ref offset, 17), 0, FileVersion);
                    Com0Config = bytes.ToByte(ref offset);
                    Com1Config = bytes.ToByte(ref offset);
                    Com2Config = bytes.ToByte(ref offset);
                    RefreshFlashTimer = bytes.ToByte(ref offset);
                    PlugNPlay = (NoYes)bytes.ToByte(ref offset);
                    ResetDefault = bytes.ToByte(ref offset);
                    ComBaudRate0 = bytes.ToByte(ref offset);
                    ComBaudRate1 = bytes.ToByte(ref offset);
                    ComBaudRate2 = bytes.ToByte(ref offset);
                    UserNameMode = (NoDisableEnable)bytes.ToByte(ref offset);
                    EnableCustomerUnit = (NoYes)bytes.ToByte(ref offset);
                    UsbMode = (UsbMode)bytes.ToByte(ref offset);
                    NetworkNumber = bytes.ToByte(ref offset);
                    PanelType = bytes.ToByte(ref offset);
                    PanelName = bytes.GetString(ref offset, 20).ClearBinarySymvols();
                    EnablePanelName = (NoYes)bytes.ToByte(ref offset);
                    PabelNumber = bytes.ToByte(ref offset);
                    DynDNSUser = bytes.GetString(ref offset, 32).ClearBinarySymvols();
                    DynDNSPassword = bytes.GetString(ref offset, 32).ClearBinarySymvols();
                    DynDNSDomain = bytes.GetString(ref offset, 32).ClearBinarySymvols();
                    DynDNSMode = (NoDisableEnable)bytes.ToByte(ref offset);
                    DynDNSProvider = (DynDNSProvider)bytes.ToByte(ref offset);
                    DynDNSUpdateTime = bytes.ToUInt16(ref offset);
                    SntpMode = (NoDisableEnable)bytes.ToByte(ref offset);
                    TimeZone = bytes.ToInt16(ref offset);
                    SerialNumber = bytes.ToUInt32(ref offset);
                    UpdateDynDNS = new UNTime(bytes.ToBytes(ref offset, 10), 0, FileVersion);
                    MstpNetworkNumber = bytes.ToUInt16(ref offset);
                    BBMDEn = bytes.ToByte(ref offset);
                    SdExist = bytes.ToByte(ref offset);
                    ModbusPort = bytes.ToUInt16(ref offset);
                    ModbusId = bytes.ToByte(ref offset);
                    ObjectInstance = bytes.ToUInt32(ref offset);
                    TimeUpdateSince1970 = bytes.ToUInt32(ref offset);
                    TimeZoneSummerDaytime = bytes.ToByte(ref offset);
                    SntpServer = bytes.GetString(ref offset, 30).ClearBinarySymvols();
                    ZegbeeExist = bytes.ToByte(ref offset);
                    offset += 162; //Unused
                    break;

                default:
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 400 bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            var bytes = new List<byte>();
            ProInfo.FileVersion = FileVersion;
            UpdateDynDNS.FileVersion = FileVersion;

            switch (FileVersion)
            {
                case FileVersion.Current:
                    bytes.AddRange(Ip?.ToBytes(0, 4) ?? new byte[4]);
                    bytes.AddRange(SubNet?.ToBytes(0, 4) ?? new byte[4]);
                    bytes.AddRange(Gate?.ToBytes(0, 4) ?? new byte[4]);
                    bytes.AddRange(Mac?.ToBytes(0, 6) ?? new byte[6]);
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
                    throw new FileVersionNotImplementedException(FileVersion);
            }

            CheckSize(bytes.Count, GetSize(FileVersion));

            return bytes.ToArray();
        }

        #endregion
    }
}