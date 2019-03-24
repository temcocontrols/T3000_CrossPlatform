namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;
    using System.Diagnostics;
    using ExceptionHandling;

    public class Prg : Version
    {
        public string DateTime { get; set; }
        public string Signature { get; set; }
        public ushort PanelNumber { get; set; }
        public ushort NetworkNumber { get; set; }
        public ushort Version { get; set; }
        public ushort MiniVersion { get; set; }
        public byte[] Reserved { get; set; }
        public int Length { get; set; }
        public long Coef { get; set; }
        public bool IsUpgraded { get; set; } = false;
        //


        private ILoadMessages parentClass;  

        public void SetParentClass(object c)  
        {
            parentClass = c as ILoadMessages;
        }


      

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

        public CustomUnits CustomUnits { get; set; } = new CustomUnits();

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
                                CustomUnits.Digital.Add(new CustomDigitalUnitsPoint(data, 0, FileVersion));
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
                //var schedulesSize = SchedulePoint.GetSize(FileVersion);
                for (var j = 0; j < size; j += schedulesCount * schedulesCount)
                {
                    //var list = new List<WrOneDay>();
                    for (var k = 0; k < schedulesCount; ++k)
                    {
                        //var data = bytes.ToBytes(offset, schedulesCount);
                        offset += schedulesCount;
                        //list.Add(WrOneDay.FromBytes(data));
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
                    //var data = bytes.ToBytes(offset, holidaySize);
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
                //var data = bytes.ToBytes(offset, size);
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
            int parts = 1;
            this.parentClass?.PassMessage(parts, $"PRG Header 1 - Offset {offset}");
            

            //Get all inputs
            Inputs.AddRange(GetArray(bytes,
                InputPoint.GetCount(FileVersion),
                InputPoint.GetSize(FileVersion), ref offset)
                .Select(i => new InputPoint(i, 0, FileVersion)));

            parts += Inputs.Count;
            this.parentClass?.PassMessage(parts,$"InputPoints {Inputs.Count} - Offset {offset}");
           

            //Get all outputs
            Outputs.AddRange(GetArray(bytes,
                OutputPoint.GetCount(FileVersion),
                OutputPoint.GetSize(FileVersion), ref offset)
                .Select(i => new OutputPoint(i, 0, FileVersion)));

            parts += Outputs.Count;
            this.parentClass?.PassMessage(parts, $"OutputPoints {Outputs.Count} - Offset {offset}");
           

            //Get all variables
            Variables.AddRange(GetArray(bytes,
                VariablePoint.GetCount(FileVersion),
                VariablePoint.GetSize(FileVersion), ref offset)
                .Select(i => new VariablePoint(i, 0, FileVersion)));
            parts += Variables.Count;
            this.parentClass?.PassMessage(parts, $"VariablePoints {Variables.Count} - Offset {offset}");

            //Get all programs
            Programs.AddRange(GetArray(bytes,
                ProgramPoint.GetCount(FileVersion),
                ProgramPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ProgramPoint(i, 0, FileVersion)));

            parts += Programs.Count;
            this.parentClass?.PassMessage(parts, $"ProgramPoints {Programs.Count} - Offset {offset}");

            //Get all controllers
            Controllers.AddRange(GetArray(bytes,
                ControllerPoint.GetCount(FileVersion),
                ControllerPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ControllerPoint(i, 0, FileVersion)));

            parts += Controllers.Count;
            this.parentClass?.PassMessage(parts, $"ControllerPoints {Controllers.Count} - Offset {offset}");

            //Get all screens
            Screens.AddRange(GetArray(bytes,
                ScreenPoint.GetCount(FileVersion),
                ScreenPoint.GetSize(FileVersion), ref offset)
                .Select(i => new ScreenPoint(i, 0, FileVersion)));

            parts += Screens.Count;
            this.parentClass?.PassMessage(parts, $"ScreenPoints {Screens.Count} - Offset {offset}");

            //Get all graphics

            //TODO: NOT MINE: Constants to object static Size(FileVersion) Count(FileVersion)

            Graphics.AddRange(GetArray(bytes,
                GraphicPoint.GetCount(FileVersion),
                GraphicPoint.GetSize(FileVersion), ref offset)
                .Select(i => new GraphicPoint(i, 0, FileVersion)));

            parts += Graphics.Count;
            this.parentClass?.PassMessage(parts, $"GraphicPoints {Graphics.Count} - Offset {offset}");

            Users.AddRange(GetArray(bytes,
                UserPoint.GetCount(FileVersion),
                UserPoint.GetSize(FileVersion), ref offset)
                .Select(i => new UserPoint(i, 0, FileVersion)));

            parts += Users.Count;
            this.parentClass?.PassMessage(parts, $"UserPoints {Users.Count} - Offset {offset}");

            CustomUnits.Digital.AddRange(GetArray(bytes,
                CustomDigitalUnitsPoint.GetCount(FileVersion),
                CustomDigitalUnitsPoint.GetSize(FileVersion), ref offset)
                .Select(i => new CustomDigitalUnitsPoint(i, 0, FileVersion)));

            parts += CustomUnits.Digital.Count;
            this.parentClass?.PassMessage(parts, $"CustomUnits.DigitalPoints {CustomUnits.Digital.Count} - Offset {offset}");

            Tables.AddRange(GetArray(bytes,
                TablePoint.GetCount(FileVersion),
                TablePoint.GetSize(FileVersion), ref offset)
                .Select(i => new TablePoint(i, 0, FileVersion)));

            parts += Tables.Count;
            this.parentClass?.PassMessage(parts, $"TablePoints {Tables.Count} - Offset {offset}");

            Settings = new Settings(
                GetObject(bytes, Settings.GetSize(FileVersion), ref offset), 0, FileVersion);

            parts += 1;
            this.parentClass?.PassMessage(parts, $"Settings 1 - Offset {offset}");

            Schedules.AddRange(GetArray(bytes,
                SchedulePoint.GetCount(FileVersion),
                SchedulePoint.GetSize(FileVersion), ref offset)
                .Select(i => new SchedulePoint(i, 0, FileVersion)));

            parts += Schedules.Count;
            this.parentClass?.PassMessage(parts, $"SchedulePoints {Schedules.Count} - Offset {offset}");

            Holidays.AddRange(GetArray(bytes,
                HolidayPoint.GetCount(FileVersion),
                HolidayPoint.GetSize(FileVersion), ref offset)
                .Select(i => new HolidayPoint(i, 0, FileVersion)));

            parts += Holidays.Count;
            this.parentClass?.PassMessage(parts, $"HolidayPoints {Holidays.Count} - Offset {offset}");

            Monitors.AddRange(GetArray(bytes,
                MonitorPoint.GetCount(FileVersion),
                MonitorPoint.GetSize(FileVersion), ref offset)
                .Select(i => new MonitorPoint(i, 0, FileVersion)));

            parts += Monitors.Count;
            this.parentClass?.PassMessage(parts, $"MonitorPoints {Monitors.Count} - Offset {offset}");

            ScheduleCodes.AddRange(GetArray(bytes,
                ScheduleCode.GetCount(FileVersion),
                ScheduleCode.GetSize(FileVersion), ref offset)
                .Select(i => new ScheduleCode(i, 0, FileVersion)));

            parts += ScheduleCodes.Count;
            this.parentClass?.PassMessage(parts, $"ScheduleCodes {ScheduleCodes.Count} - Offset {offset}");

            HolidayCodes.AddRange(GetArray(bytes,
                HolidayCode.GetCount(FileVersion),
                HolidayCode.GetSize(FileVersion), ref offset)
                .Select(i => new HolidayCode(i, 0, FileVersion)));

            parts += HolidayCodes.Count;
            this.parentClass?.PassMessage(parts, $"HolidayCodes {HolidayCodes.Count} - Offset {offset}");


            int pcode_offset = offset ;
            var ProgramCodeBytes = bytes.ToBytes(offset, ProgramCode.GetSize(FileVersion));
            ProgramCodes.AddRange(GetArray(bytes,
                ProgramCode.GetCount(FileVersion),
                ProgramCode.GetSize(FileVersion), ref offset)
                //.Select(i => new ProgramCode(i, this, 0, FileVersion)));
                .Select(i => new ProgramCode()));

            ProgramCodes[0] = new ProgramCode(ProgramCodeBytes, this, 0, FileVersion);

            parts += 1;
            this.parentClass?.PassMessage(parts, $"ProgramCodes 1 - Offset {pcode_offset+2000}");


            for (int i = 1; i < ProgramCode.GetCount(FileVersion) ; i++)
            {
                pcode_offset += ProgramCode.GetSize(FileVersion);
                ProgramCodeBytes = bytes.ToBytes(pcode_offset, ProgramCode.GetSize(FileVersion));
                ProgramCodes[i] = new ProgramCode(ProgramCodeBytes, this, 0, FileVersion);

                parts += 1;
                this.parentClass?.PassMessage(parts, $"ProgramCodes {i+1} - Offset {pcode_offset+2000}");

                //Debug.WriteLine($"Leído ProgramCode[{i}]");
            }



            CustomUnits.Analog.AddRange(GetArray(bytes,
                CustomAnalogUnitsPoint.GetCount(FileVersion),
                CustomAnalogUnitsPoint.GetSize(FileVersion), ref offset)
                .Select(i => new CustomAnalogUnitsPoint(i, 0, FileVersion)));

            parts += CustomUnits.Analog.Count;
            this.parentClass?.PassMessage(parts, $"CustomUnits.AnalogPoints {CustomUnits.Analog.Count} - Offset {offset}");

            CheckOffset(offset, Length);

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

        public Prg() : base() {; }


        /// <summary>
        /// Creates a Prg Object from a sequence of bytes
        /// Also sets the parent object for messaging purposes. (Load Progress in a Progress Bar?!)
        /// </summary>
        /// <param name="bytes">Sequencec of bytes</param>
        /// <param name="parent">Parent Object</param>
        public Prg(byte[] bytes, Object parent)
            : base(FileVersionUtilities.GetFileVersion(bytes))
        {
            //Set the parent object
            this.SetParentClass(parent);
            try
            {

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
            catch(Exception ex){
   
                ExceptionHandler.Show(ex, "public Prg(byte[] bytes, Object parent)", true);
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
                                bytes.AddRange(CustomUnits.Digital[j].ToBytes());
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
            //Update if Unit changed
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

            for (var i = 0; i < CustomDigitalUnitsPoint.GetCount(FileVersion); ++i)
            {
                var obj = CustomUnits.Digital.ElementAtOrDefault(i) ?? new CustomDigitalUnitsPoint();
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

            for (var i = 0; i < CustomAnalogUnitsPoint.GetCount(FileVersion); ++i)
            {
                var obj = CustomUnits.Analog.ElementAtOrDefault(i) ?? new CustomAnalogUnitsPoint();
                bytes.AddRange(obj.ToBytes());
            }

            if (!IsUpgraded)
            {
                CheckSize(bytes.Count, Length);
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
           
            

        }

        /// <summary>
        /// Read all bytes from a .PRG File to build an object.
        /// Now it supports Class messaging with its parent.
        /// Allows to show LOAD progress in a control of a parent FORM
        /// </summary>
        /// <param name="path">Path to .PRG File</param>
        /// <param name="parent">Parent object</param>
        /// <!--Modified by LRUIZ : 2018-06-05-->
        /// <returns>Prg Object</returns>
        public static Prg Load(string path, object parent)
        {
            Prg _prg = new Prg();
            
            _prg = PrgReader.Read(path,parent);
            _prg.SetParentClass(parent);
            return _prg;
        }


        public void Save(string path) => PrgWriter.Write(this, path);

     
    }


    public interface ILoadMessages
    {
        void PassMessage(int counter,  string theMessage);


    }
}