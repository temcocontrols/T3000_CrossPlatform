using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using PRGReaderLibrary.Extensions;
using PRGReaderLibrary.Types.Enums.Codecs;

namespace PRGReaderLibrary.Utilities
{
    /// <summary>
    /// Statics Helpers
    /// </summary>
    static public class CoderHelper
    {
        /// <summary>
        /// Returns PCODE_CONST value and Index for the especified Identifier
        /// </summary>
        /// <param name="Ident">Label of Point Identifier</param>
        /// <param name="Index">Out Index of Point Identifier</param>
        /// <returns>PCODE_CONST value and Index</returns>
        static public PCODE_CONST GetTypeIdentifier(ControlPoints Identifiers, string Ident, out int Index)
        {
            try
            {
                if (Identifiers == null) //Null object
                {
                    Index = -1;
                    return PCODE_CONST.UNDEFINED_SYMBOL;
                }

                #region Test if generic control point

                //RegEx Tested Strings, for ending valid Control Points
                string UPTO128 = "12[0-8]|1[0-1][0-9]|[1-9][0-9]?";
                //string UPTO96 = "9[0-6]|[1-8][0-9]?";
                string UPTO64 = "6[0-4]|[1-5][0-9]?";
                //string UPTO48 = "4[0-8]|[1-3][0-9]?";
                //string UPTO32 = "3[0-2]|[1-2][0-9]?";
                //string UPTO16 = "1[0-6]|[1-9]";
                //string UPTO8 = "[1-8]";
                //string UPTO4 = "[1-4]";
                //string UPTO31 = "3[0-1]|[1-2][0-9]?";
                //string UPTO5 = "[1-5]";

                //Same as in T3000Grammar, updated for Rev6
                string VARS = "VAR(" + UPTO128 + ")";
                string OUTS = "OUT(" + UPTO64 + ")";
                string INS = "IN(" + UPTO64 + ")";

                string Generic = Regex.Match(Ident,VARS +"|" + OUTS + "|" + INS).Value;

                if (Generic.Trim()!="")
                {
                    string GenericIndex = Regex.Match(Ident, @"\d+").Value;

                    switch (Generic.Substring(0,2))
                    {
                        case "VA":
                            Index = Convert.ToInt16(GenericIndex) - 1; //VAR1 will get index 0, and so on.
                            return PCODE_CONST.VARPOINTTYPE;
                        case "OU":
                            Index = Convert.ToInt16(GenericIndex) - 1; //OUT1 will get index 0, and so on.
                            return PCODE_CONST.OUTPOINTTYPE; ;
                        case "IN":
                            Index = Convert.ToInt16(GenericIndex) - 1; //IN1 will get index 0, and so on.
                            return PCODE_CONST.INPOINTTYPE;

                        default:
                            break;
                    }
                }
                #endregion


                #region Test is label for control point
                //Test Variables
                Index = Identifiers.Variables.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.VARPOINTTYPE;

                //Test Inputs
                Index = Identifiers.Inputs.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.INPOINTTYPE;

                //Test Outputs
                Index = Identifiers.Outputs.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.OUTPOINTTYPE;


                //TODO: SET CORRECT TOKENTYPE FOR PRG, SCH AND HOL.

                //Test Programs
                Index = Identifiers.Programs.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.LOCAL_POINT_PRG;

                //Test Schedules
                Index = Identifiers.Schedules.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.LOCAL_POINT_PRG;


                //Test Holidays
                Index = Identifiers.Holidays.FindIndex(v => v.Label == Ident);
                if (!Index.Equals(-1)) return PCODE_CONST.LOCAL_POINT_PRG; 
                #endregion

            }
            catch
            {
                Index = -1;
                return PCODE_CONST.UNDEFINED_SYMBOL;
            }

            Index = -2;
            return PCODE_CONST.UNDEFINED_SYMBOL;

        }

        /// <summary>
        /// Prints a byte array - Static Helper
        /// </summary>
        /// <param name="ByteEncoded">Byte array to print</param>
        /// <param name="HeaderString">Optional Header string</param>
        public static void ConsolePrintBytes(byte[] ByteEncoded, string HeaderString = "")
        {

            var PSize = BitConverter.ToInt16(ByteEncoded, 0);
            int STEPBYTES = 50;
            Debug.Write(HeaderString);
            //Console.Write(HeaderString); // different in 2015 vs 2017
            int countByLine = 0;
            int countLines = 0;
            Debug.Write(" Bytes = { ");
            //Console.Write(" Bytes = { ");
            for (var i = 0; i < PSize + 3; i++)
            {
                Debug.Write($"{ByteEncoded[i]} ");
                countByLine++;
                if (countByLine == STEPBYTES)
                {
                    countByLine = 0;
                    countLines++;
                    Debug.Write(System.Environment.NewLine + $"[{countLines * STEPBYTES}]-> ");


                }
            }
            Debug.WriteLine("}");
        }





    }




}
