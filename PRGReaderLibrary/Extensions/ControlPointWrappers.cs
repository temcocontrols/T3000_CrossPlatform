using ExceptionHandling;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PRGReaderLibrary.Types.Enums.Codecs;

namespace PRGReaderLibrary.Extensions
{
    /// <summary>
    /// Enumerable Identifiers Types
    /// </summary>
    public enum IdentifierTypes
    {
        //TODO: Reorder to match CODEC enums values PCONST, after PIDS
        OUTS=1, INS, VARS, PIDS, PRGS, SCHS, HOLS
    }

    /// <summary>
    /// Basic info for controlpoint identifiers
    /// </summary>
    public class ControlPointInfo
    {
        #region Properties
        //Identifier Info
        public string Label { get; set; } = "";
        public string FullLabel { get; set; } = "";
        public string ControlPointName { get; set; } = "";
        public string Value { get; set; } = "";
        public string Units { get; set; } = "";
        public string AutoManual { get; set; } = "";
        public short Index { get; set; } = 0;

        //ControlPoint Type
        public IdentifierTypes Type { get; set; } = IdentifierTypes.VARS; 
        #endregion


        /// <summary>
        /// Enumerator to byte array
        /// </summary>
        /// <returns>byte array form of the control point</returns>
        internal IEnumerable<byte> GetBytes()
        {
            byte[] result = { 0x00, 0x00, 0x00 };

            result[0] = 156;
            result[1] = (byte)Index;
            result[2] = (byte)Type;


            return result;
        }
    }

    /// <summary>
    /// List of all enumerables identifiers/controlpoints
    /// </summary>
    public class ControlPoints
    {

        #region Lists of ControlPoints
        /// <summary>
        /// Variables identifiers
        /// </summary>
        public List<ControlPointInfo> Variables { get; set; } = new List<ControlPointInfo>();

        /// <summary>
        /// Inputs identifiers
        /// </summary>
        public List<ControlPointInfo> Inputs { get; set; } = new List<ControlPointInfo>();

        /// <summary>
        /// Outputs identifiers
        /// </summary>
        public List<ControlPointInfo> Outputs { get; set; } = new List<ControlPointInfo>();

        /// <summary>
        /// Programs Identifiers
        /// </summary>
        public List<ControlPointInfo> Programs { get; set; } = new List<ControlPointInfo>();


        /// <summary>
        /// Schedules identifiers
        /// </summary>
        public List<ControlPointInfo> Schedules { get; set; } = new List<ControlPointInfo>();

        /// <summary>
        /// Holidays identifiers
        /// </summary>
        public List<ControlPointInfo> Holidays { get; set; } = new List<ControlPointInfo>();

        #endregion

        #region Add Methods

        /// <summary>
        /// Add a variable control point info
        /// </summary>
        /// <param name="variable">VariablePoint</param>
        /// <param name="index">Index</param>
        public void Add(VariablePoint variable, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "VAR" + index,
                    Label = variable.Label,
                    FullLabel = variable.Description,
                    Type = IdentifierTypes.VARS,
                    Value = variable.Value.ToString(),
                    Units = variable.Value.Unit.GetUnitsNames(null).OffOnName,
                    AutoManual = variable.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };


                Variables.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Variable to ControlPointsInfo");
            }

        }

        /// <summary>
        /// Add a Input control point info
        /// </summary>
        /// <param name="input">Input Point</param>
        /// <param name="index">Index</param>
        public void Add(InputPoint input, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "IN" + index,
                    Label = input.Label,
                    FullLabel = input.Description,
                    Type = IdentifierTypes.INS,
                    Value = input.Value.ToString(),
                    Units = input.Value.Unit.GetUnitsNames(null).OffOnName,
                    AutoManual = input.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };


                Inputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Input to ControlPointsInfo");
            }

        }

        /// <summary>
        /// Add Output control point info
        /// </summary>
        /// <param name="output">Output Point</param>
        /// <param name="index">Index</param>
        public void Add(OutputPoint output, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "OUT" + index,
                    Label = output.Label,
                    FullLabel = output.Description,
                    Type = IdentifierTypes.OUTS,
                    Value = output.Value.ToString(),
                    Units = output.Value.Unit.GetUnitsNames(null).OffOnName,
                    AutoManual = output.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };


                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Output to ControlPointsInfo");
            }

        }

        /// <summary>
        /// Add Program control point info
        /// </summary>
        /// <param name="program">Program Point</param>
        /// <param name="index">Index</param>
        public void Add(ProgramPoint program, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "PRG" + index,
                    Label = program.Label,
                    FullLabel = program.Description,
                    Type = IdentifierTypes.PRGS,
                    Value = "",
                    Units = "",
                    AutoManual = program.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };


                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Program to ControlPointsInfo");
            }

        }

        /// <summary>
        /// Add Schedule control point info
        /// </summary>
        /// <param name="schedule">Schedule Point</param>
        /// <param name="index">Index</param>
        public void Add(SchedulePoint schedule, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "SCH" + index,
                    Label = schedule.Label,
                    FullLabel = schedule.Description,
                    Type = IdentifierTypes.SCHS,
                    Value = "",
                    Units = "",
                    AutoManual = schedule.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };

                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Schedule to ControlPointsInfo");
            }

        }

        /// <summary>
        /// Add Holiday control point info
        /// </summary>
        /// <param name="holiday">Holiday Point</param>
        /// <param name="index">Index</param>
        public void Add(HolidayPoint holiday, int index)
        {

            try
            {
                ControlPointInfo newCPInfo = new ControlPointInfo
                {
                    ControlPointName = "HOL" + index,
                    Label = holiday.Label,
                    FullLabel = holiday.Description,
                    Type = IdentifierTypes.HOLS,
                    Value = "",
                    Units = "",
                    AutoManual = holiday.AutoManual == 0 ? "Auto" : "Manual",
                    Index = (short)index
                };

                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Holiday to ControlPointsInfo");
            }

        }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor;
        /// </summary>
        public ControlPoints() { }

        /// <summary>
        /// Builds a copy from PRG Control Points
        /// </summary>
        /// <param name="prg">PRG object</param>
        public ControlPoints(Prg prg)
        {

            try
            {
                int i;
                //Copy variables info
                for (i = 0; i < prg.Variables.Count(); i++)
                    Add(prg.Variables[i], i + 1);
                //Copy inputs info
                for (i = 0; i < prg.Inputs.Count(); i++)
                    Add(prg.Inputs[i], i + 1);
                //Copy outputs info
                for (i = 0; i < prg.Outputs.Count(); i++)
                    Add(prg.Outputs[i], i + 1);
                //Copy programs info
                for (i = 0; i < prg.Programs.Count(); i++)
                    Add(prg.Programs[i], i + 1);
                //Copy schedules info
                for (i = 0; i < prg.Schedules.Count(); i++)
                    Add(prg.Schedules[i], i + 1);
                //Copy holidays info
                for (i = 0; i < prg.Holidays.Count(); i++)
                    Add(prg.Holidays[i], i + 1);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Copying Control Points");
            }


        }

        #endregion
        
        /// <summary>
        /// Get ControlPointInfo by Type and Index
        /// </summary>
        /// <param name="Type">Identifier Type</param>
        /// <param name="Index">Zero based index</param>
        /// <returns>Full Control Point Info</returns>
        public ControlPointInfo GetControlPointInfo(IdentifierTypes Type, int Index)
        {
            ControlPointInfo cp = new ControlPointInfo();
            switch (Type)
            {
                case IdentifierTypes.OUTS:
                    cp = Outputs[Index];
                    break;
                case IdentifierTypes.INS:
                    cp = Inputs[Index];
                    break;
                case IdentifierTypes.VARS:
                    cp = Variables[Index];
                    break;
                case IdentifierTypes.PIDS:
                    
                    break;
                //TODO: Return apropiate ControlPointInfo

                //case IdentifierTypes.PRGS:
                //    break;
                //case IdentifierTypes.SCHS:
                //    break;
                //case IdentifierTypes.HOLS:
                //    break;
                default:
                    break;
            }

            return cp;
        }
    }



    /// <summary>
    /// Time buffer element: ControlPointInfo  +  Byte Position
    /// </summary>
    public class TBufferElement
    {
        public ControlPointInfo Info { get; set; }
        public int Position { get; set; } = 5;

    }

    /// <summary>
    /// Time Buffer Manager
    /// </summary>
    public class TimeBuffer
    {
        /// <summary>
        /// Bytes Array Buffer
        /// </summary>
        private List<byte> Buffer { get; set; } = new List<byte>();
        /// <summary>
        /// List of Elements in Buffer
        /// </summary>
        public List<TBufferElement> Elements { get; set; } = new List<TBufferElement>();

        /// <summary>
        /// Local copy of identifiers for conversions.
        /// </summary>
        private ControlPoints Identifiers;

        /// <summary>
        /// Buffer Size
        /// </summary>
        public  int BufferSize => Elements == null ? 0 : Elements.Count() * 9;
        /// <summary>
        ///Elements count
        /// </summary>
        public int BufferCount => Elements == null ? 0 : Elements.Count();


        /// <summary>
        /// TimeBuffer from source code (byte array)
        /// </summary>
        /// <param name="source"></param>
        public TimeBuffer( ControlPoints identifiers, byte[] source = null)
        {
            int i = 0;
            int POS = 0;
            byte[] len = { 0x00, 0x00 };
            Identifiers = identifiers;
            if (source == null) return;

            try
            {
                if (source.Length > 2000)
                {
                    throw new ArgumentOutOfRangeException($"Program Lenght exceeds 2000 bytes: {source.Length}");
                }
                else
                {
                    //find EOF byte, do not trust PROG SIZE in control point
                    do
                        i++;
                    while (source[i] != (byte)LINE_TOKEN.EOF);

                    if (i >= 2000)
                    {
                        throw new IndexOutOfRangeException($"Out of bounds or no EOF found at index: {i}");
                    }
                    POS = i + 1; //Position of TimeBuffer -> first byte after 0xFE (EOF)
                             
                    i = POS + 4; //Jump first 4 bytes, those are always 0x00
                    //next two bytes are the buffer lenght
                    len[0] = source[i];
                    len[1] = source[i+1];
                    int _BufferSize = BytesExtensions.ToInt16(len);
                    int _BufferCount = (BufferSize) / 9;
                    //Copy the time buffer
                    //If BufferSize = 0 then Buffer will stay empty
                    for (i = 0; i <= _BufferSize + 5; i++)
                        Buffer.Add(source[POS + i]);

                    //Convert every byte sequence into Elements
                    for (i = 6; i < _BufferSize + 5; i += 9)
                    {
                        //skip first byte 0x00;
                        byte TOKEN = Buffer[i];
                        byte INDEX = Buffer[i + 1];
                        IdentifierTypes  TYPE = (IdentifierTypes) Buffer[i + 2];
                        byte Marker = Buffer[i + 3];
                        if(Marker != (byte) LINE_TOKEN.EOE)
                        {
                            throw new Exception($"EOF not found. Instead of marker, I found  this: {Marker}");
                        }

                        if (Identifiers != null)
                        {

                            switch ((IdentifierTypes)TYPE)
                            {
                                case IdentifierTypes.OUTS:
                                case IdentifierTypes.INS:
                                case IdentifierTypes.VARS:
                                    Add(Identifiers.GetControlPointInfo(TYPE, INDEX));
                                    break;

                                default:
                                    throw new NotSupportedException("Identifier type not supported by TimeBuffer()");
                            } 
                        }

                    }
                  

                }
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "TimeBuffer");
            }
        }

        /// <summary>
        /// Read Only Indexer for time entry, used by DECODER
        /// </summary>
        /// <param name="position">position of element</param>
        /// <returns>Label of referenced control point</returns>
        public string this[int position]
        {
            get
            {
                string Label = "<UNKNOWN IDENT>";
                int realIndex = Elements.FindIndex(e => e.Position == position);
                if(realIndex > -1)
                {
                    Label = Elements[realIndex].Info.Label;
                }
                else
                {
                   throw new KeyNotFoundException($"Identifier at position {position} does not exist in TimeBuffer Elements");
                }

                return Label;
            }

        }


        /// <summary>
        /// Add a new ControlPointInfo reference in TimeBuffer
        /// </summary>
        /// <param name="info">ControlPoint info to add</param>
        /// <returns>New Position</returns>
        public int  Add(ControlPointInfo info)
        {
            int NewPosition = 5;
            if (Elements.Count > 0)
            {
                NewPosition = Elements.Last().Position + 9; //9 bytes 
            }
            TBufferElement newElement = new TBufferElement();
            newElement.Position = NewPosition;
            newElement.Info = info;

            Elements.Add(newElement);
            return NewPosition;
        }

        /// <summary>
        /// Add a new ControlPointInfo reference in TimeBuffer from Type and Index
        /// </summary>
        /// <param name="Type">Identifier Type</param>
        /// <param name="Index">Real Index</param>
        /// <returns>New Position</returns>
        public int Add(IdentifierTypes Type, int Index)
        {
            int NewPosition = 5;
            if (Elements.Count > 0)
            {
                NewPosition = Elements.Last().Position + 9; //9 bytes 
            }
            TBufferElement newElement = new TBufferElement();
            newElement.Position = NewPosition;
            newElement.Info = Identifiers.GetControlPointInfo(Type,Index);

            Elements.Add(newElement);
            return NewPosition;

        }


        /// <summary>
        /// Get the control point info.
        /// </summary>
        /// <param name="Position">Position</param>
        /// <returns>ControlPointInfo</returns>
        public ControlPointInfo GetControlPointInfo(int Position)
        {
            ControlPointInfo cpi = new ControlPointInfo();
            int realIndex = Elements.FindIndex(e => e.Position == Position);
            if (realIndex > -1)
            {
                cpi = Elements[realIndex].Info;
            }
            else
            {
                throw new KeyNotFoundException($"Element position {Position} was not found in TimeBuffer Elements");
            }
            return cpi;
        }


        /// <summary>
        /// Gets byte array (triplet) at position
        /// </summary>
        /// <param name="Position">Warning: Use only values of the series i*9+5 Where i=0,1,2,4... => 5, 14, 23,....</param>
        /// <returns>3 bytes representing Token, Index and Type, or null if no elements in buffer</returns>
        public byte[] GetBytesAtPosition(int Position)
        {
            if (BufferCount == 0) return null;

            
            if (BufferCount > 0 && Buffer.Count() == 0)
                ToBytes();//Rebuild Time Buffer

            byte[] result = { 0x00, 0x00, 0x00 };
            for(int i = 0; i < 3; i++)
            {
                result[i] = Buffer[Position + i + 1];
            }
            return result;

        }

        /// <summary>
        /// Rebuild the buffer and return array of bytes
        /// </summary>
        /// <returns>Full array of TimeBuffer or null if no elements in time buffer</returns>
        public byte[] ToBytes()
        {
            if (BufferCount == 0) return null;

            Buffer = new List<byte>();
            for (int i = 0; i < 4; i++) Buffer.Add(0x00);
            short bs = (short) BufferSize;
            Buffer.AddRange(bs.ToBytes());
            for (int i = 0; i < BufferCount; i++)
            {
                Buffer.AddRange(Elements[i].Info.GetBytes());
                Buffer.Add((byte)LINE_TOKEN.EOE);
                for (int j = 0; j < 5; j++) Buffer.Add(0x00);
            }
                

            return Buffer.ToArray();
        }

    }
}
