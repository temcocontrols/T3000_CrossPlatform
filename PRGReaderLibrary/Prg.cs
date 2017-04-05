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
        public bool IsUpgraded { get; set; } = false;

        #region Main data

        public List<InputPoint> Inputs { get; set; } = new List<InputPoint>();
        public List<OutputPoint> Outputs { get; set; } = new List<OutputPoint>();
        public List<VariablePoint> Variables { get; set; } = new List<VariablePoint>();
        public List<ProgramPoint> Programs { get; set; } = new List<ProgramPoint>();
        public List<ControllerPoint> Controllers { get; set; } = new List<ControllerPoint>();
        public List<ScreenPoint> Screens { get; set; } = new List<ScreenPoint>();
        public List<GraphicPoint> Graphics { get; set; } = new List<GraphicPoint>();
        public List<UserPoint> Users { get; set; } = new List<UserPoint>();
        public List<TablePoint> Tables { get; set; } = new List<TablePoint>();
        public Settings Settings { get; set; }
        public List<SchedulePoint> Schedules { get; set; } = new List<SchedulePoint>();
        public List<HolidayPoint> Holidays { get; set; } = new List<HolidayPoint>();
        public List<MonitorPoint> Monitors { get; set; } = new List<MonitorPoint>();
        public List<ScheduleCode> ScheduleCodes { get; set; } = new List<ScheduleCode>();
        public List<HolidayCode> HolidayCodes { get; set; } = new List<HolidayCode>();
        public List<ProgramCode> ProgramCodes { get; set; } = new List<ProgramCode>();

        public List<DigitalCustomUnitsPoint> CustomUnits { get; set; } = new List<DigitalCustomUnitsPoint>();
        public List<AnalogCustomUnitsPoint> AnalogCustomUnits { get; set; } = new List<AnalogCustomUnitsPoint>();

        #endregion

        #region Binary data


        public byte[] RawData { get; protected set; }

        private void FromDosFormat(byte[] bytes)
        {
            DateTime = bytes.GetString(0, 26);
            Signature = bytes.GetString(26, 4);
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
            }

            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                //prg.WrTimes = reader.ReadBytes(size);
                var schedulesCount = SchedulePoint.GetCount(FileVersion);
                var schedulesSize = SchedulePoint.GetSize(FileVersion);
                for (var j = 0; j < size; j += schedulesCount * schedulesCount)
                {
                    var list = new List<WrOneDay>();
                    for (var k = 0; k < schedulesCount; ++k)
                    {
                        var data = bytes.ToBytes(offset, schedulesCount);
                        offset += schedulesCount;
                        list.Add(WrOneDay.FromBytes(data));
                    }

                    //WrTimes.Add(list);
                }
            }

            {
                var size = bytes.ToUInt16(offset);
                offset += 2;
                var holidaySize = HolidayPoint.GetSize(FileVersion);
                for (var j = 0; j < size; j += holidaySize)
                {
                    var data = bytes.ToBytes(offset, holidaySize);
                    offset += holidaySize;
                    //ArDates.Add(data);
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

                //GrpDatas.Add(data);
            }

            {
                //var size = bytes.ToUInt16(offset);
                offset += 2;

                //for (var j = 0; j < MaxConstants.MAX_ICON_NAME_TABLE; ++j)
                {
                    //var data = bytes.ToBytes(offset, SizeConstants.ICON_NAME_TABLE_SIZE);
                    //offset += SizeConstants.ICON_NAME_TABLE_SIZE;
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

        private void FromCurrentFormat(byte[] bytes, int offset = 0)
        {
            Signature = bytes.GetString(0, 2);
            Version = bytes.ToByte(2);
            Length = bytes.Length;

            offset += 3;

            //Get all inputs
            Inputs.AddRange(GetArray(bytes,
                InputPoint.GetCount(FileVersion),
                InputPoint.GetSize(FileVersion), ref offset)
                .Select(i => new InputPoint(i, 0, FileVersion)));

            //Get all outputs
            Outputs.AddRange(GetArray(bytes,
                OutputPoint.GetCount(FileVersion),
                OutputPoint.GetSize(FileVersion), ref offset)
                .Select(i => new OutputPoint(i, 0, FileVersion)));

            //Get all variables
            Variables.AddRange(GetArray(bytes,
                VariablePoint.GetCount(FileVersion),
                VariablePoint.GetSize(FileVersion), ref offset)
                .Select(i => new VariablePoint(i, 0, FileVersion)));

            //Get all programs
            Programs.AddRange(GetArray(bytes,
                ProgramPoint.GetCount(FileVersion),
                ProgramPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ProgramPoint(i, 0, FileVersion)));

            //Get all controllers
            Controllers.AddRange(GetArray(bytes,
                ControllerPoint.GetCount(FileVersion),
                ControllerPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ControllerPoint(i, 0, FileVersion)));

            //Get all screens
            Screens.AddRange(GetArray(bytes,
                ScreenPoint.GetCount(FileVersion),
                ScreenPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ScreenPoint(i, 0, FileVersion)));

            //Get all graphics

            //TODO: Constants to object static Size(FileVersion) Count(FileVersion)

            Graphics.AddRange(GetArray(bytes,
                GraphicPoint.GetCount(FileVersion),
                GraphicPoint.GetSize(FileVersion), ref offset)
                .Select(i => new GraphicPoint(i, 0, FileVersion)));

            Users.AddRange(GetArray(bytes,
                UserPoint.GetCount(FileVersion),
                UserPoint.GetSize(FileVersion), ref offset)
                .Select(i => new UserPoint(i, 0, FileVersion)));

            CustomUnits.AddRange(GetArray(bytes,
                DigitalCustomUnitsPoint.GetCount(FileVersion),
                DigitalCustomUnitsPoint.GetSize(FileVersion), ref offset)
                .Select(i => new DigitalCustomUnitsPoint(i, 0, FileVersion)));

            Tables.AddRange(GetArray(bytes,
                TablePoint.GetCount(FileVersion),
                TablePoint.GetSize(FileVersion), ref offset)
                .Select(i => new TablePoint(i, 0, FileVersion)));

            Settings = new Settings(
                GetObject(bytes, Settings.GetSize(FileVersion), ref offset), 0, FileVersion);

            Schedules.AddRange(GetArray(bytes,
                SchedulePoint.GetCount(FileVersion),
                SchedulePoint.GetSize(FileVersion), ref offset)
                .Select(i => new SchedulePoint(i, 0, FileVersion)));

            Holidays.AddRange(GetArray(bytes,
                HolidayPoint.GetCount(FileVersion),
                HolidayPoint.GetSize(FileVersion), ref offset)
                .Select(i => new HolidayPoint(i, 0, FileVersion)));

            Monitors.AddRange(GetArray(bytes,
                MonitorPoint.GetCount(FileVersion),
                MonitorPoint.GetSize(FileVersion), ref offset)
                .Select(i => new MonitorPoint(i, 0, FileVersion)));

            ScheduleCodes.AddRange(GetArray(bytes,
                ScheduleCode.GetCount(FileVersion),
                ScheduleCode.GetSize(FileVersion), ref offset)
                .Select(i => new ScheduleCode(i, 0, FileVersion)));

            HolidayCodes.AddRange(GetArray(bytes,
                HolidayCode.GetCount(FileVersion),
                HolidayCode.GetSize(FileVersion), ref offset)
                .Select(i => new HolidayCode(i, 0, FileVersion)));

            ProgramCodes.AddRange(GetArray(bytes,
                ProgramCode.GetCount(FileVersion),
                ProgramCode.GetSize(FileVersion), ref offset)
                .Select(i => new ProgramCode(i, 0, FileVersion)));

            AnalogCustomUnits.AddRange(GetArray(bytes,
                AnalogCustomUnitsPoint.GetCount(FileVersion),
                AnalogCustomUnitsPoint.GetSize(FileVersion), ref offset)
                .Select(i => new AnalogCustomUnitsPoint(i, 0, FileVersion)));

            if (offset != Length)
            {
                throw new ArgumentException($@"Offset != Length after reading.
Offset: {offset}, Length: {Length}");
            }

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

            bytes.AddRange(Signature.ToBytes(2));
            bytes.Add((byte)Version);

            //'for' instead 'foreach' for upgrade support

            for (var i = 0; i < InputPoint.GetCount(FileVersion); ++i)
            {
                var obj = Inputs.ElementAtOrDefault(i) ?? new InputPoint();
                obj.FileVersion = FileVersion;
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < OutputPoint.GetCount(FileVersion); ++i)
            {
                var obj = Outputs.ElementAtOrDefault(i) ?? new OutputPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < VariablePoint.GetCount(FileVersion); ++i)
            {
                var obj = Variables.ElementAtOrDefault(i) ?? new VariablePoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < ProgramPoint.GetCount(FileVersion); ++i)
            {
                var obj = Programs.ElementAtOrDefault(i) ?? new ProgramPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < ControllerPoint.GetCount(FileVersion); ++i)
            {
                var obj = Controllers.ElementAtOrDefault(i) ?? new ControllerPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < ScreenPoint.GetCount(FileVersion); ++i)
            {
                var obj = Screens.ElementAtOrDefault(i) ?? new ScreenPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < GraphicPoint.GetCount(FileVersion); ++i)
            {
                var obj = Graphics.ElementAtOrDefault(i) ?? new GraphicPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < UserPoint.GetCount(FileVersion); ++i)
            {
                var obj = Users.ElementAtOrDefault(i) ?? new UserPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < DigitalCustomUnitsPoint.GetCount(FileVersion); ++i)
            {
                var obj = CustomUnits.ElementAtOrDefault(i) ?? new DigitalCustomUnitsPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < TablePoint.GetCount(FileVersion); ++i)
            {
                var obj = Tables.ElementAtOrDefault(i) ?? new TablePoint();
                bytes.AddRange(obj.ToBytes());
            }

            {
                var settings = Settings ?? new Settings(FileVersion);
                bytes.AddRange(settings.ToBytes());
            }

            for (var i = 0; i < SchedulePoint.GetCount(FileVersion); ++i)
            {
                var obj = Schedules.ElementAtOrDefault(i) ?? new SchedulePoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < HolidayPoint.GetCount(FileVersion); ++i)
            {
                var obj = Holidays.ElementAtOrDefault(i) ?? new HolidayPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < MonitorPoint.GetCount(FileVersion); ++i)
            {
                var obj = Monitors.ElementAtOrDefault(i) ?? new MonitorPoint();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < ScheduleCode.GetCount(FileVersion); ++i)
            {
                var obj = ScheduleCodes.ElementAtOrDefault(i) ?? new ScheduleCode();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < HolidayCode.GetCount(FileVersion); ++i)
            {
                var obj = HolidayCodes.ElementAtOrDefault(i) ?? new HolidayCode();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < ProgramCode.GetCount(FileVersion); ++i)
            {
                var obj = ProgramCodes.ElementAtOrDefault(i) ?? new ProgramCode();
                bytes.AddRange(obj.ToBytes());
            }

            for (var i = 0; i < AnalogCustomUnitsPoint.GetCount(FileVersion); ++i)
            {
                var obj = AnalogCustomUnits.ElementAtOrDefault(i) ?? new AnalogCustomUnitsPoint();
                bytes.AddRange(obj.ToBytes());
            }

            if (!IsUpgraded && bytes.Count != Length)
            {
                throw new ArgumentException($@"Output lenght != Length after writing.
Output lenght: {bytes.Count}, Length: {Length}");
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
            if (FileVersion == version)
            {
                return;
            }

            FileVersion = version;
            IsUpgraded = true;
            switch (version)
            {
                case FileVersion.Current:
                    Signature = FileVersionUtilities.Rev6Signature;
                    Version = 6;
                    break;

                case FileVersion.Dos:
                    Signature = FileVersionUtilities.DosSignature;
                    break;

            }

            foreach (var variable in Variables)
            {
                variable.FileVersion = version;
            }
        }

        public static Prg Load(string path) => PrgReader.Read(path);
        public void Save(string path) => PrgWriter.Write(this, path);
    }
}