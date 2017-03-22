namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public class PRG
    {
        public string DateTime { get; set; }
        public string Signature { get; set; }
        public ushort PanelNumber { get; set; }
        public ushort NetworkNumber { get; set; }
        public ushort Version { get; set; }
        public ushort MiniVersion { get; set; }
        public byte[] Reserved { get; set; }
        public long Length { get; set; }
        public long Coef { get; set; }
        public IList<byte[]> Infos { get; set; } = new List<byte[]>();
        public IList<PRGData> PrgDatas { get; set; } = new List<PRGData>();
        public IList<byte[]> GrpDatas { get; set; } = new List<byte[]>();

        /// <summary>
        /// Size: 216 + 1280 + 1216 + 4608 + 384 + 2352 + 
        /// 2320 + 608 + 2304 + 256 + 1088 + 128 + 1472 +
        /// 256 + 2048 + 484 + 4512 + 944 + 208 + 525 +
        /// 200 + 8 + 4 + 224 + 1 + 4 + 368 = 28018 bytes
        /// </summary>
        #region Main data

        /// <summary>
        /// Size: MaxConstants.MAX_INFOS(18) * 12 = 216 bytes
        /// </summary>
        public IList<InfoTable> Info { get; set; } = new List<InfoTable>();

        /// <summary>
        /// Size: MaxConstants.MAX_OUTS(32) * 40 = 1280 bytes
        /// </summary>
        public IList<StrOutPoint> Outputs { get; set; } = new List<StrOutPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_INS(32) * 38 = 1216 bytes
        /// </summary>
        public IList<StrInPoint> Inputs { get; set; } = new List<StrInPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_VARS(128) * 36 = 4608 bytes
        /// </summary>
        public IList<StrVariablePoint> Vars { get; set; } = new List<StrVariablePoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_CONS(16) * 24 = 384 bytes
        /// </summary>
        public IList<StrControllerPoint> Controllers { get; set; } = new List<StrControllerPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_ANALM(16) * 147 = 2352 bytes
        /// </summary>
        public IList<StrMonitorPoint> AnalogMonitors { get; set; } = new List<StrMonitorPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_ANALM(16) * 145 = 2320 bytes
        /// </summary>
        public IList<StrMonitorWorkData> MonitorWorkData { get; set; } = new List<StrMonitorWorkData>();

        /// <summary>
        /// Size: MaxConstants.MAX_WR(16) * 38 = 608 bytes
        /// </summary>
        public IList<StrWeeklyRoutinePoint> WeeklyRoutines { get; set; } = new List<StrWeeklyRoutinePoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_WR(16) * SizeConstants.WR_ONE_DAY_SIZE(9) * 16 = 2304 bytes
        /// </summary>
        public IList<IList<WrOneDay>> WrTimes { get; set; } = new List<IList<WrOneDay>>();

        /// <summary>
        /// Size: MaxConstants.MAX_AR(8) * 32 = 256 bytes
        /// </summary>
        public IList<StrAnnualRoutinePoint> AnnualRoutines { get; set; } = new List<StrAnnualRoutinePoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_PRGS(32) * 34 = 1088 bytes
        /// </summary>
        public IList<StrProgramPoint> Programs { get; set; } = new List<StrProgramPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_PRGS(32) * 4 = 128 bytes
        /// </summary>
        public byte[] ProgramCodes { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_GRPS(32) * 46 = 1472 bytes
        /// </summary>
        public IList<ControlGroupPoint> ControlGroups { get; set; } = new List<ControlGroupPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_GRPS(32) * 8 = 256 bytes
        /// </summary>
        public IList<ControlGroupElements> ControlGroupElements { get; set; } = new List<ControlGroupElements>();

        /// <summary>
        /// Size: MaxConstants.MAX_LOCAL_STATIONS(32) * 64 = 2048 bytes
        /// </summary>
        public IList<StationPoint> LocalStations { get; set; } = new List<StationPoint>();

        /// <summary>
        /// Size: 484 bytes
        /// </summary>
        public PasswordStruct Passwords { get; set; } = new PasswordStruct();

        /// <summary>
        /// Size: MaxConstants.MAX_ALARMS(48) * 94 = 4512 bytes
        /// </summary>
        public IList<AlarmPoint> Alarms { get; set; } = new List<AlarmPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_ALARMS_SET(16) * 59 = 944 bytes
        /// </summary>
        public IList<AlarmSetPoint> AlarmsSet { get; set; } = new List<AlarmSetPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_ARRAYS(16) * 13 = 208 bytes
        /// </summary>
        public IList<StrArrayPoint> Arrays { get; set; } = new List<StrArrayPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_TABS(5) * 105 = 525 bytes
        /// </summary>
        public IList<StrTblPoint> CustomTab { get; set; } = new List<StrTblPoint>();

        /// <summary>
        /// Size: MaxConstants.MAX_UNITS(8) * 25 = 200 bytes
        /// </summary>
        public IList<UnitsElement> Units { get; set; } = new List<UnitsElement>();

        /// <summary>
        /// Size: 8 bytes
        /// </summary>
        public ulong IndexHeapGrp { get; set; }

        /// <summary>
        /// Size: 4 bytes. Modified. Initially ptr(4)
        /// </summary>
        public IList<StrGrpElement> GrpElements { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_ICON_NAME_TABLE(16) * 
        /// SizeConstants.ICON_NAME_TABLE_SIZE(14) = 224 bytes
        /// </summary>
        public IList<byte[]> IconNameTable { get; set; } = new List<byte[]>();

        /// <summary>
        /// Size: 1 byte
        /// </summary>
        public byte JustLoad { get; set; } = 1;

        /// <summary>
        /// Size: 4 bytes
        /// </summary>
        public int PixVar { get; set; }

        /// <summary>
        /// Size: MaxConstants.MAX_AR(8) * SizeConstants.AR_DATES_SIZE(46) = 368 bytes
        /// </summary>
        public IList<byte[]> ArDates { get; set; } = new List<byte[]>();

        #endregion

        public byte[] RawData { get; set; }//TODO: private set when FromBytes. Base class with RawData FromBytes

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            bytes.AddRange(DateTime.ToBytes(26));
            bytes.AddRange(Signature.ToBytes(4));
            bytes.AddRange(PanelNumber.ToBytes());
            bytes.AddRange(NetworkNumber.ToBytes());
            bytes.AddRange(Version.ToBytes());
            bytes.AddRange(MiniVersion.ToBytes());
            bytes.AddRange(Reserved);

            //Append raw data from file.
            bytes.AddRange(RawData.ToBytes(bytes.Count, RawData.Length - bytes.Count));

            return bytes.ToArray();
        }

        public static PRG Load(string path) => PRGReader.Read(path);
        public void Save(string path) => PRGWriter.Write(this, path);
    }
}