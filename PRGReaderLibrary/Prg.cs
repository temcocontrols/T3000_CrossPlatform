namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
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

        public List<InputPoint> Inputs { get; set; } = new List<InputPoint>();
        public List<OutputPoint> Outputs { get; set; } = new List<OutputPoint>();
        public List<VariablePoint> Variables { get; set; } = new List<VariablePoint>();
        public List<ProgramPoint> Programs { get; set; } = new List<ProgramPoint>();
        public List<ControllerPoint> Controllers { get; set; } = new List<ControllerPoint>();
        public List<ScreenPoint> Screens { get; set; } = new List<ScreenPoint>();
        public List<GraphicPoint> Graphics { get; set; } = new List<GraphicPoint>();
        public List<UserPoint> Users { get; set; } = new List<UserPoint>();

        public List<SchedulePoint> Schedules { get; set; } = new List<SchedulePoint>();
        public List<HolidayPoint> Holidays { get; set; } = new List<HolidayPoint>();

        public List<ProgramCode> ProgramCodes { get; set; } = new List<ProgramCode>();

        public List<InfoTable> Info { get; set; } = new List<InfoTable>();
        public List<StrMonitorPoint> AnalogMonitors { get; set; } = new List<StrMonitorPoint>();
        public List<StrMonitorWorkData> MonitorWorkData { get; set; } = new List<StrMonitorWorkData>();
        public List<List<WrOneDay>> WrTimes { get; set; } = new List<List<WrOneDay>>();
        public List<ControlGroupElements> ControlGroupElements { get; set; } = new List<ControlGroupElements>();
        public List<StationPoint> LocalStations { get; set; } = new List<StationPoint>();
        public PasswordStruct Passwords { get; set; } = new PasswordStruct();
        public List<AlarmPoint> Alarms { get; set; } = new List<AlarmPoint>();
        public List<AlarmSetPoint> AlarmsSet { get; set; } = new List<AlarmSetPoint>();
        public List<StrArrayPoint> Arrays { get; set; } = new List<StrArrayPoint>();
        public List<StrTblPoint> CustomTab { get; set; } = new List<StrTblPoint>();
        public List<DigitalCustomUnitsPoint> CustomUnits { get; set; } = new List<DigitalCustomUnitsPoint>();
        public List<AnalogCustomUnitsPoint> AnalogCustomUnits { get; set; } = new List<AnalogCustomUnitsPoint>();


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
            if (!Signature.Equals(DosConstants.Signature, StringComparison.Ordinal))
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

            for (var i = PointType.OUT; i <= PointType.UNIT; ++i)
            {
                if (i == PointType.TZ)
                {
                    continue;
                }

                if (i == PointType.AMON)
                {
                    if (Version < 230 && MiniVersion >= 230)
                    {
                        throw new Exception($"Versions conflict! {this.PropertiesText()}");
                    }
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == PointType.ALARMM)
                {
                    if (Version < 216)
                    {
                        var size = bytes.ToUInt16(offset);
                        offset += 2;
                        var count = bytes.ToUInt16(offset);
                        offset += 2;
                        for (var j = 0; j < count; ++j)
                        {
                            //var data = bytes.ToBytes(offset, size);
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

                    if (i == PointType.PRG)
                    {
                        maxPrg = count;
                    }
                    if (i == PointType.GRP)
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
                            case PointType.VAR:
                                Variables.Add(new VariablePoint(data, 0, FileVersion));
                                break;

                            case PointType.UNIT:
                                CustomUnits.Add(new PRGReaderLibrary.DigitalCustomUnitsPoint(data, 0, FileVersion));
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

        private byte[] GetObject(byte[] bytes, int size, ref int offset)
        {
            var data = bytes.ToBytes(offset, size);
            offset += size;

            return data;
        }

        private IList<byte[]> GetArray(byte[] bytes, int count, int size, ref int offset)
        {
            var array = new List<byte[]>();
            for (var i = 0; i < count; ++i)
            {
                array.Add(GetObject(bytes, size, ref offset));
            }

            return array;
        }

        private void FromCurrentFormat(byte[] bytes)
        {
            Version = bytes.ToByte(3);

            var offset = 3;

            //Get all inputs
            Inputs.AddRange(GetArray(bytes, 
                Rev6Constants.InputCount,
                Rev6Constants.InputSize, ref offset)
                .Select(i => new InputPoint(i, 0, FileVersion)));

            //Get all outputs
            Outputs.AddRange(GetArray(bytes,
                Rev6Constants.OutputCount,
                Rev6Constants.OutputSize, ref offset)
                .Select(i => new OutputPoint(i, 0, FileVersion)));

            //Get all variables
            Variables.AddRange(GetArray(bytes,
                Rev6Constants.VariableCount,
                Rev6Constants.VariableSize, ref offset)
                .Select(i => new VariablePoint(i, 0, FileVersion)));

            //Get all programs
            Programs.AddRange(GetArray(bytes,
                Rev6Constants.ProgramCount,
                Rev6Constants.ProgramSize, ref offset)
                .Select(i => new ProgramPoint(i, 0, FileVersion)));

            //Get all controllers
            Controllers.AddRange(GetArray(bytes,
                Rev6Constants.ControllerCount,
                Rev6Constants.ControllerSize, ref offset)
                .Select(i => new ControllerPoint(i, 0, FileVersion)));

            //Get all screens
            Screens.AddRange(GetArray(bytes,
                Rev6Constants.ScreenCount,
                Rev6Constants.ScreenSize, ref offset)
                .Select(i => new ScreenPoint(i, 0, FileVersion)));

            //Get all graphics

            //TODO: Constants to object static Size(FileVersion) Count(FileVersion)

            Graphics.AddRange(GetArray(bytes,
                Rev6Constants.GraphicCount,
                Rev6Constants.GraphicSize, ref offset)
                .Select(i => new GraphicPoint(i, 0, FileVersion)));

            Users.AddRange(GetArray(bytes,
                Rev6Constants.UserCount,
                Rev6Constants.UserSize, ref offset)
                .Select(i => new UserPoint(i, 0, FileVersion)));

            CustomUnits.AddRange(GetArray(bytes,
                Rev6Constants.DigitalCustomUnitsCount,
                Rev6Constants.DigitalCustomUnitsSize, ref offset)
                .Select(i => new DigitalCustomUnitsPoint(i, 0, FileVersion)));

            GetArray(bytes,
                Rev6Constants.AnalogCustomRangeTableCount,
                Rev6Constants.AnalogCustomRangeTableSize, ref offset);

            GetObject(bytes, Rev6Constants.SettingSize, ref offset);

            Schedules.AddRange(GetArray(bytes,
                Rev6Constants.ScheduleCount,
                Rev6Constants.ScheduleSize, ref offset)
                .Select(i => new SchedulePoint(i, 0, FileVersion)));

            Holidays.AddRange(GetArray(bytes,
                Rev6Constants.HolidayCount,
                Rev6Constants.HolidaySize, ref offset)
                .Select(i => new HolidayPoint(i, 0, FileVersion)));

            GetArray(bytes,
                Rev6Constants.MonitorCount,
                Rev6Constants.MonitorSize, ref offset);

            GetArray(bytes,
                Rev6Constants.WeeklyRoutinesCount,
                Rev6Constants.WeeklyRoutinesSize, ref offset);

            GetArray(bytes,
                Rev6Constants.AnnualRoutinesCount,
                Rev6Constants.AnnualRoutinesSize, ref offset);

            ProgramCodes.AddRange(GetArray(bytes,
                Rev6Constants.ProgramCodeCount,
                Rev6Constants.ProgramCodeSize, ref offset)
                .Select(i => new ProgramCode(i, 0, FileVersion)));

            AnalogCustomUnits.AddRange(GetArray(bytes,
                Rev6Constants.AnalogCustomUnitsCount,
                Rev6Constants.AnalogCustomUnitsSize, ref offset)
                .Select(i => new AnalogCustomUnitsPoint(i, 0, FileVersion)));

            if (offset != bytes.Length)
            {
                throw new ArgumentException($@"Bytes lenght != offset after reading.
Offset: {offset}, Length: {bytes.Length}");
            }

            RawData = bytes;

            UpdateCustomUnits();
        }

        public void UpdateCustomUnits()
        {
            //Set CustomUnits for inputs
            foreach (var input in Inputs)
            {
                input.Value.CustomUnits = CustomUnits;
            }

            //Set CustomUnits for inputs
            foreach (var output in Outputs)
            {
                output.Value.CustomUnits = CustomUnits;
            }

            //Set CustomUnits for variables
            foreach (var variable in Variables)
            {
                variable.Value.CustomUnits = CustomUnits;
            }
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
            for (var i = PointType.OUT; i <= PointType.UNIT; ++i)
            {
                if (i == PointType.TZ)
                {
                    continue;
                }

                if (i == PointType.AMON)
                {
                    if (Version >= 230 && MiniVersion > 0)
                        continue;
                }

                if (i == PointType.ALARMM)
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
                            case PointType.VAR:
                                bytes.AddRange(Variables[j].ToBytes());
                                break;

                            case PointType.UNIT:
                                bytes.AddRange(CustomUnits[j].ToBytes());
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
            //Update if Units changed
            UpdateCustomUnits();

            var bytes = new List<byte>();

            bytes.AddRange(RawData.ToBytes(0, 3));

            //'for' instead 'foreach' for upgrade support

            for (var i = 0; i < Rev6Constants.InputCount; ++i)
            {
                var obj = Inputs.ElementAtOrDefault(i) ?? new InputPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.OutputCount; ++i)
            {
                var obj = Outputs.ElementAtOrDefault(i) ?? new OutputPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.VariableCount; ++i)
            {
                var obj = Variables.ElementAtOrDefault(i) ?? new VariablePoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.ProgramCount; ++i)
            {
                var obj = Programs.ElementAtOrDefault(i) ?? new ProgramPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.ControllerCount; ++i)
            {
                var obj = Controllers.ElementAtOrDefault(i) ?? new ControllerPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.ScreenCount; ++i)
            {
                var obj = Screens.ElementAtOrDefault(i) ?? new ScreenPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.GraphicCount; ++i)
            {
                var obj = Graphics.ElementAtOrDefault(i) ?? new GraphicPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.UserCount; ++i)
            {
                var obj = Users.ElementAtOrDefault(i) ?? new UserPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.DigitalCustomUnitsCount; ++i)
            {
                var obj = CustomUnits.ElementAtOrDefault(i) ?? new DigitalCustomUnitsPoint();
                bytes.AddRange(obj.ToBytes());
            }

            bytes.AddRange(RawData.ToBytes(bytes.Count, Rev6Constants.AnalogCustomRangeTableCount * Rev6Constants.AnalogCustomRangeTableSize));
            bytes.AddRange(RawData.ToBytes(bytes.Count, Rev6Constants.SettingSize));

            for (var i = 0; i < Rev6Constants.ScheduleCount; ++i)
            {
                var obj = Schedules.ElementAtOrDefault(i) ?? new SchedulePoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.HolidayCount; ++i)
            {
                var obj = Holidays.ElementAtOrDefault(i) ?? new HolidayPoint();
                bytes.AddRange(obj.ToBytes());
            }

            bytes.AddRange(RawData.ToBytes(bytes.Count, Rev6Constants.MonitorCount * Rev6Constants.MonitorSize));
            bytes.AddRange(RawData.ToBytes(bytes.Count, Rev6Constants.WeeklyRoutinesCount * Rev6Constants.WeeklyRoutinesSize));
            bytes.AddRange(RawData.ToBytes(bytes.Count, Rev6Constants.AnnualRoutinesCount * Rev6Constants.AnnualRoutinesSize));
            
            for (var i = 0; i < Rev6Constants.ProgramCodeCount; ++i)
            {
                var obj = ProgramCodes.ElementAtOrDefault(i) ?? new ProgramCode();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < Rev6Constants.AnalogCustomUnitsCount; ++i)
            {
                var obj = AnalogCustomUnits.ElementAtOrDefault(i) ?? new AnalogCustomUnitsPoint();
                bytes.AddRange(obj.ToBytes());
            }

            if (RawData.Length != bytes.Count)
            {
                throw new ArgumentException($@"Bytes lenght != RawData.Length after writing.
Offset: {RawData.Length}, Length: {bytes.Count}");
            }

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