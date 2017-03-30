namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class Prg
    {
        public FileVersion FileVersion { get; set; }
        public string DateTime { get; set; }
        public string Signature { get; set; }
        public ushort PanelNumber { get; set; }
        public ushort NetworkNumber { get; set; }
        public ushort Version { get; set; }
        public ushort MiniVersion { get; set; }
        public byte[] Reserved { get; set; }
        public long Length { get; set; }
        public long Coef { get; set; }
        public IList<PrgData> PrgDatas { get; set; } = new List<PrgData>();
        public IList<byte[]> GrpDatas { get; set; } = new List<byte[]>();

        #region Main data

        public IList<InfoTable> Info { get; set; } = new List<InfoTable>();
        public IList<StrOutPoint> Outputs { get; set; } = new List<StrOutPoint>();
        public IList<StrInPoint> Inputs { get; set; } = new List<StrInPoint>();
        public IList<StrVariablePoint> Variables { get; set; } = new List<StrVariablePoint>();
        public IList<StrControllerPoint> Controllers { get; set; } = new List<StrControllerPoint>();
        public IList<StrMonitorPoint> AnalogMonitors { get; set; } = new List<StrMonitorPoint>();
        public IList<StrMonitorWorkData> MonitorWorkData { get; set; } = new List<StrMonitorWorkData>();
        public IList<StrWeeklyRoutinePoint> WeeklyRoutines { get; set; } = new List<StrWeeklyRoutinePoint>();
        public IList<IList<WrOneDay>> WrTimes { get; set; } = new List<IList<WrOneDay>>();
        public IList<StrAnnualRoutinePoint> AnnualRoutines { get; set; } = new List<StrAnnualRoutinePoint>();
        public IList<StrProgramPoint> Programs { get; set; } = new List<StrProgramPoint>();
        public byte[] ProgramCodes { get; set; }
        public IList<ControlGroupPoint> ControlGroups { get; set; } = new List<ControlGroupPoint>();
        public IList<ControlGroupElements> ControlGroupElements { get; set; } = new List<ControlGroupElements>();
        public IList<StationPoint> LocalStations { get; set; } = new List<StationPoint>();
        public PasswordStruct Passwords { get; set; } = new PasswordStruct();
        public IList<AlarmPoint> Alarms { get; set; } = new List<AlarmPoint>();
        public IList<AlarmSetPoint> AlarmsSet { get; set; } = new List<AlarmSetPoint>();
        public IList<StrArrayPoint> Arrays { get; set; } = new List<StrArrayPoint>();
        public IList<StrTblPoint> CustomTab { get; set; } = new List<StrTblPoint>();
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

            for (var i = Blocks.OUT; i <= Blocks.UNIT; ++i)
            {
                if (i == Blocks.DMON)
                {
                    continue;
                }

                if (i == Blocks.AMON)
                {
                    if (Version < 230 && MiniVersion >= 230)
                    {
                        throw new Exception($"Versions conflict! {this.PropertiesText()}");
                    }
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == Blocks.ALARMM)
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
                            //Alarms.Add(data);
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

                    if (i == Blocks.PRG)
                    {
                        maxPrg = count;
                    }
                    if (i == Blocks.GRP)
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
                            case Blocks.VAR:
                                Variables.Add(new StrVariablePoint(data, 0, FileVersion));
                                break;

                            default:
                                //Unknown.Add(data);
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

            //Get all inputs
            for (var i = 0; i < CurrentVersionRev6Constants.BAC_INPUT_ITEM_COUNT; ++i)
            {
                var size = CurrentVersionRev6Constants.BAC_INPUT_ITEM_SIZE;
                var data = bytes.ToBytes(offset, size);
                offset += size;

                //Inputs.Add(new StrInputPoint(data, 0, FileVersion));
            }

            //Get all outputs
            for (var i = 0; i < CurrentVersionRev6Constants.BAC_OUTPUT_ITEM_COUNT; ++i)
            {
                var size = CurrentVersionRev6Constants.BAC_OUTPUT_ITEM_SIZE;
                var data = bytes.ToBytes(offset, size);
                offset += size;

                //Outputs.Add(new StrOutputPoint(data, 0, FileVersion));
            }

            //Get all variables
            for (var i = 0; i < CurrentVersionRev6Constants.BAC_VARIABLE_ITEM_COUNT; ++i)
            {
                var size = CurrentVersionRev6Constants.BAC_VARIABLE_ITEM_SIZE;
                var data = bytes.ToBytes(offset, size);
                offset += size;

                Variables.Add(new StrVariablePoint(data, 0, FileVersion));
            }

            RawData = bytes;
        }

        public Prg(byte[] bytes)
        {
            FileVersion = FileVersionUtilities.GetFileVersion(bytes);
            if (FileVersion == FileVersion.Unsupported)
            {
                throw new Exception($@"Data is corrupted or unsupported. First 100 bytes:
{bytes.GetString(0, Math.Min(100, bytes.Length))}");
            }

            switch (FileVersion)
            {
                case FileVersion.Dos:
                    FromDosFormat(bytes);
                    break;

                case FileVersion.Current:
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
            for (var i = Blocks.OUT; i <= Blocks.UNIT; ++i)
            {
                if (i == Blocks.DMON)
                {
                    continue;
                }

                if (i == Blocks.AMON)
                {
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == Blocks.ALARMM)
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
                            case Blocks.VAR:
                                bytes.AddRange(Variables[j].ToBytes());
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
            bytes.AddRange(RawData.ToBytes(bytes.Count, CurrentVersionRev6Constants.BAC_INPUT_ITEM_COUNT * CurrentVersionRev6Constants.BAC_INPUT_ITEM_SIZE));
            bytes.AddRange(RawData.ToBytes(bytes.Count, CurrentVersionRev6Constants.BAC_OUTPUT_ITEM_COUNT * CurrentVersionRev6Constants.BAC_OUTPUT_ITEM_SIZE));
            foreach (var variable in Variables)
            {
                bytes.AddRange(variable.ToBytes());
            }
            bytes.AddRange(RawData.ToBytes(bytes.Count));

            return bytes.ToArray();
        }

        public byte[] ToBytes()
        {
            switch (FileVersion)
            {
                case FileVersion.Dos:
                    return ToDosFormat();

                case FileVersion.Current:
                    return ToCurrentFormat();

                default:
                    throw new NotImplementedException("This version not implemented");
            }
        }

        #endregion

        public void Upgrade(FileVersion version = FileVersion.Current)
        {
            FileVersion = version;
            foreach (var variable in Variables)
            {
                variable.FileVersion = version;
            }
        }

        public static Prg Load(string path) => PrgReader.Read(path);
        public void Save(string path) => PrgWriter.Write(this, path);
    }
}