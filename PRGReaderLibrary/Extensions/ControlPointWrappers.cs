using ExceptionHandling;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PRGReaderLibrary.Extensions
{
    /// <summary>
    /// Enumerable Identifiers Types
    /// </summary>
    public enum IdentifierTypes
    {
        VARS, INS, OUTS, PRGS, SCHS, HOLS
    }

    /// <summary>
    /// Basic info for controlpoint identifiers
    /// </summary>
    public class ControlPointInfo
    {
        //Identifier Info
        public string Label { get; set; } = "";
        public string FullLabel { get; set; } = "";
        public string ControlPointName { get; set; } = "";
        public string Value { get; set; } = "";
        public string Units { get; set; } = "";
        public string AutoManual { get; set; } = "";

        //ControlPoint Type
        public IdentifierTypes Type { get; set; } = IdentifierTypes.VARS;

        /// <summary>
        /// Default constructor
        /// </summary>
        public ControlPointInfo() { }

               
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
                    AutoManual = variable.AutoManual == 0 ? "Auto" : "Manual"
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
                    AutoManual = input.AutoManual == 0 ? "Auto" : "Manual"
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
                    AutoManual = output.AutoManual == 0 ? "Auto" : "Manual"
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
                    AutoManual = program.AutoManual == 0 ? "Auto" : "Manual"
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
                    AutoManual = schedule.AutoManual == 0 ? "Auto" : "Manual"
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
                    AutoManual = holiday.AutoManual == 0 ? "Auto" : "Manual"
                };

                Outputs.Add(newCPInfo);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Addition of new Holiday to ControlPointsInfo");
            }

        }

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
                    Add(prg.Variables[i], i+1);
                //Copy inputs info
                for (i = 0; i < prg.Inputs.Count(); i++)
                    Add(prg.Inputs[i], i+1);
                //Copy outputs info
                for (i = 0; i < prg.Outputs.Count(); i++)
                    Add(prg.Outputs[i], i+1);
                //Copy programs info
                for (i = 0; i < prg.Programs.Count(); i++)
                    Add(prg.Programs[i], i+1);
                //Copy schedules info
                for (i = 0; i < prg.Schedules.Count(); i++)
                    Add(prg.Schedules[i], i+1);
                //Copy holidays info
                for (i = 0; i < prg.Holidays.Count(); i++)
                    Add(prg.Holidays[i], i+1);
            }
            catch (Exception ex)
            {
                ExceptionHandler.Show(ex, "Copying Control Points");
            }


        }
    }
}