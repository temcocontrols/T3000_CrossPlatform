namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class Prg
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
        public FileVersionEnum FileVersion { get; set; }
        public IList<byte[]> Infos { get; set; } = new List<byte[]>();
        public IList<PrgData> PrgDatas { get; set; } = new List<PrgData>();
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
        public IList<StrVariablePoint> Variables { get; set; } = new List<StrVariablePoint>();

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

        #region Binary data
        
        public byte[] RawData { get; protected set; }

        private void FromDosFormat(byte[] bytes)
        {
            DateTime = bytes.GetString(0, 26);
            Signature = bytes.GetString(26, 4);
            if (!Signature.Equals(Constants.Signature, StringComparison.Ordinal))
            {
                throw new Exception($"Data is corrupted. {this.PropertiesText()}");
            }

            PanelNumber = bytes.ToUInt16(30);
            NetworkNumber = bytes.ToUInt16(32);
            Version = bytes.ToUInt16(34);
            MiniVersion = bytes.ToUInt16(36);
            Reserved = bytes.ToBytes(38, 32);
            if (Version < 210 || Version == 0x2020)
            {
                throw new Exception($"Data not loaded. Data version less than 2.10. {this.PropertiesText()}");
            }

            Length = bytes.Length;
            Coef = ((Length * 1000L) / 20000L) * 1000L +
                (((Length * 1000L) % 20000L) * 1000L) / 20000L;
            //float coef = (float)length/20.;

            //Main block
            var offset = 70;
            //var l = MaxConstants.MAX_TBL_BANK;
            var maxPrg = 0;
            var maxGrp = 0;

            for (var i = BlocksEnum.OUT; i <= BlocksEnum.UNIT; ++i)
            {
                if (i == BlocksEnum.DMON)
                {
                    continue;
                }

                if (i == BlocksEnum.AMON)
                {
                    if (Version < 230 && MiniVersion >= 230)
                    {
                        throw new Exception($"Versions conflict! {this.PropertiesText()}");
                    }
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == BlocksEnum.ALARMM)
                {
                    if (Version < 216)
                    {
                        var size = bytes.ToUInt16(offset);
                        offset += 2;
                        var count = bytes.ToUInt16(offset);
                        offset += 2;
                        for (var j = 0; j < count; ++j)
                        {
                            var data = bytes.ToBytes(offset, size);
                            offset += size;
                            Infos.Add(data);
                        }
                        continue;
                    }
                }
                else
                {
                    var count = bytes.ToUInt16(offset);
                    offset += 2;
                    var size = bytes.ToUInt16(offset);
                    offset += 2;

                    if (i == BlocksEnum.PRG)
                    {
                        maxPrg = count;
                    }
                    if (i == BlocksEnum.GRP)
                    {
                        maxGrp = count;
                    }
                    //if (count == info[i].str_size)
                    {
                        // fread(info[i].address, nitem, l, h);
                    }
                    for (var j = 0; j < count; ++j)
                    {
                        var data = bytes.ToBytes(offset, size);
                        offset += size;
                        switch (i)
                        {
                            case BlocksEnum.VAR:
                                Variables.Add(new StrVariablePoint(data, 0, FileVersion));
                                break;

                            default:
                                Infos.Add(data);
                                break;
                        }
                    }
                    //Console.WriteLine(string.Join(Environment.NewLine,
                    //    prg.Alarms.Select(c=>new string(c)).Where(c => !string.IsNullOrWhiteSpace(c))));
                    //offset += size * count + 2;
                }
            }

            //var l = Math.Min(maxPrg, tbl_bank[PRG]);
            for (var i = 0; i < maxPrg; ++i)
            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                //var data = 
                bytes.ToBytes(offset, size);
                offset += size;

                //var prgData = PRGData.FromBytes(data);
                //if (!prgData.IsEmpty)
                {
                    //prg.PrgDatas.Add(prgData);
                }
            }

            foreach (var data in PrgDatas)
            {
                //Console.WriteLine(data.PropertiesText());
            }

            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                //prg.WrTimes = reader.ReadBytes(size);
                for (var j = 0; j < size; j += SizeConstants.WR_ONE_DAY_SIZE * MaxConstants.MAX_WR)
                {
                    var list = new List<WrOneDay>();
                    for (var k = 0; k < SizeConstants.WR_ONE_DAY_SIZE; ++k)
                    {
                        var data = bytes.ToBytes(offset, MaxConstants.MAX_WR);
                        offset += MaxConstants.MAX_WR;
                        list.Add(WrOneDay.FromBytes(data));
                    }

                    WrTimes.Add(list);
                }
            }

            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                for (var j = 0; j < size; j += SizeConstants.AR_DATES_SIZE)
                {
                    var data = bytes.ToBytes(offset, SizeConstants.AR_DATES_SIZE);
                    offset += SizeConstants.AR_DATES_SIZE;
                    ArDates.Add(data);
                }
            }

            {
                //var size = 
                bytes.ToUInt16(offset);
                offset += 2;
            }

            for (var i = 0; i < maxGrp; ++i)
            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                var data = bytes.ToBytes(offset, size);
                offset += size;

                GrpDatas.Add(data);
            }

            {
                //var size = bytes.ToUInt16(offset);
                offset += 2;

                for (var j = 0; j < MaxConstants.MAX_ICON_NAME_TABLE; ++j)
                {
                    //var data = bytes.ToBytes(offset, SizeConstants.ICON_NAME_TABLE_SIZE);
                    offset += SizeConstants.ICON_NAME_TABLE_SIZE;
                    //prg.IconNameTable.Add(data);
                }
            }

            RawData = bytes;
        }

        private void FromCurrentFormat(byte[] bytes)
        {
            Version = bytes.ToByte(3);

            var offset = 3;
            offset += CurrentVersionConstants.BAC_INPUT_ITEM_COUNT*CurrentVersionConstants.BAC_INPUT_ITEM_SIZE;
            offset += CurrentVersionConstants.BAC_OUTPUT_ITEM_COUNT * CurrentVersionConstants.BAC_OUTPUT_ITEM_SIZE;

            //Get all variables
            for (var i = 0; i < CurrentVersionConstants.BAC_VARIABLE_ITEM_COUNT; ++i)
            {
                var data = bytes.ToBytes(offset, CurrentVersionConstants.BAC_VARIABLE_ITEM_SIZE);
                offset += CurrentVersionConstants.BAC_VARIABLE_ITEM_SIZE;

                Variables.Add(new StrVariablePoint(data, 0, FileVersion));
            }

            RawData = bytes;
        }

        public Prg(byte[] bytes)
        {
            FileVersion = PrgUtilities.GetFileVersion(bytes);
            if (FileVersion == FileVersionEnum.Unsupported)
            {
                throw new Exception($@"Data is corrupted or unsupported. First 100 bytes:
{bytes.GetString(0, Math.Min(100, bytes.Length))}");
            }

            switch (FileVersion)
            {
                case FileVersionEnum.Dos:
                    FromDosFormat(bytes);
                    break;

                case FileVersionEnum.Current:
                    FromCurrentFormat(bytes);
                    break;

                default:
                    throw new NotImplementedException("This version not implemented");
            }
        }

        public byte[] ToDosFormat()
        {
            var bytes = new List<byte>();

            bytes.AddRange(DateTime.ToBytes(26));
            bytes.AddRange(Signature.ToBytes(4));
            bytes.AddRange(PanelNumber.ToBytes());
            bytes.AddRange(NetworkNumber.ToBytes());
            bytes.AddRange(Version.ToBytes());
            bytes.AddRange(MiniVersion.ToBytes());
            bytes.AddRange(Reserved);

            var offset = bytes.Count;
            for (var i = BlocksEnum.OUT; i <= BlocksEnum.UNIT; ++i)
            {
                if (i == BlocksEnum.DMON)
                {
                    continue;
                }

                if (i == BlocksEnum.AMON)
                {
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == BlocksEnum.ALARMM)
                {
                    if (Version < 216)
                    {
                        var size = RawData.ToUInt16(offset);
                        offset += 2;
                        bytes.AddRange(size.ToBytes());
                        var count = RawData.ToUInt16(offset);
                        offset += 2;
                        bytes.AddRange(count.ToBytes());
                        for (var j = 0; j < count; ++j)
                        {
                            var data = RawData.ToBytes(offset, size);
                            offset += size;
                            bytes.AddRange(data);
                        }
                        continue;
                    }
                }
                else
                {
                    var count = RawData.ToUInt16(offset);
                    offset += 2;
                    bytes.AddRange(count.ToBytes());
                    var size = RawData.ToUInt16(offset);
                    offset += 2;
                    bytes.AddRange(size.ToBytes());
                    for (var j = 0; j < count; ++j)
                    {
                        var data = RawData.ToBytes(offset, size);
                        offset += size;
                        switch (i)
                        {
                            case BlocksEnum.VAR:
                                bytes.AddRange(Variables[j].ToBytes(FileVersion));
                                break;

                            default:
                                bytes.AddRange(data);
                                break;
                        }
                    }
                }
            }

            //Append raw data from file.
            bytes.AddRange(RawData.ToBytes(bytes.Count, RawData.Length - bytes.Count));

            return bytes.ToArray();
        }

        public byte[] ToCurrentFormat()
        {
            var bytes = new List<byte>();
            
            bytes.AddRange(RawData.ToBytes(0, 3));
            bytes.AddRange(RawData.ToBytes(bytes.Count, CurrentVersionConstants.BAC_INPUT_ITEM_COUNT * CurrentVersionConstants.BAC_INPUT_ITEM_SIZE));
            bytes.AddRange(RawData.ToBytes(bytes.Count, CurrentVersionConstants.BAC_OUTPUT_ITEM_COUNT * CurrentVersionConstants.BAC_OUTPUT_ITEM_SIZE));
            foreach (var variable in Variables)
            {
                bytes.AddRange(variable.ToBytes(FileVersion));
            }
            bytes.AddRange(RawData.ToBytes(bytes.Count));

            return bytes.ToArray();
        }

        public byte[] ToBytes()
        {
            switch (FileVersion)
            {
                case FileVersionEnum.Dos:
                    return ToDosFormat();

                case FileVersionEnum.Current:
                    return ToCurrentFormat();

                default:
                    throw new NotImplementedException("This version not implemented");
            }
        }

        #endregion

        public static Prg Load(string path) => PrgReader.Read(path);
        public void Save(string path) => PrgWriter.Write(this, path);
    }
}