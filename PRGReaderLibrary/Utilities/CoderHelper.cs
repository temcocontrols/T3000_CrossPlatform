using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
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
