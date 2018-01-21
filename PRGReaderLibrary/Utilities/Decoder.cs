using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PRGReaderLibrary.Types.Enums.Codecs;
using PRGReaderLibrary.Extensions;

namespace PRGReaderLibrary.Utilities
{
    /// <summary>
    /// Decodes array of bytes into plain text Control Basic
    /// </summary>
    public class Decoder
    {

        /// <summary>
        /// Required copy of Control Points Labels just for semantic validations
        /// </summary>
        static public ControlPoints Identifiers { get; set; } = new ControlPoints();

        /// <summary>
        /// Set a local copy of all identifiers in prg
        /// </summary>
        /// <param name="prg">Program prg</param>
        static public void  SetControlPoints(Prg prg)
        {
            Identifiers = new ControlPoints(prg);
        }


        /// <summary>
        /// Decode a ProgramCode Into Plain Text
        /// </summary>
        /// <param name="PCode">Byte array (encoded program)</param>
        static public string DecodeBytes(byte[] PCode)
        {
            byte[] prgsize = new byte[2];
            string result = "";
            Array.Copy(PCode, 0, prgsize, 0, 2);
            int ProgLenght = BytesExtensions.ToInt16(prgsize);

            int offset; //offset after count of total encoded bytes
            bool isFirstToken = true;

            for (offset=2; offset <= ProgLenght;offset++)
            {
                var tokenvalue = (byte)PCode[offset];
                switch (tokenvalue)
                {
                    case (byte)TYPE_TOKEN.NUMBER:
                        if (isFirstToken)
                        {
                        offset++;
                        short LineNumber = BytesExtensions.ToInt16(PCode, ref offset);
                        result += LineNumber.ToString(); //LINE NUMBER, 2 Bytes
                        }

                        isFirstToken = false;
                        break;

                    case (byte)LINE_TOKEN.REM:
                        result += " " + GetComment(PCode,ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.ASSIGN:
                        result += " " + GetAssigment(PCode,ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;
                    
                    default:
                        break;
                }
            }

            return result;
        }

        private static string GetComment(byte[] source, ref int offset)
        {
            string result = "REM ";
            offset++;
            short count = source[offset++];
            
            List<byte> comment = new List<byte>();
            comment = source.ToList().GetRange(offset, count);
            //Array.Copy(source, offset, comment, 0, count);
            result += System.Text.Encoding.Default.GetString(comment.ToArray()) + System.Environment.NewLine;
            offset += count;


            return result;

        }

        private static string GetAssigment(byte[] source,ref int offset)
        {
            string result = "↑";

            //TODO: Will need fx to get identifier labels and Postfix to Infix decoder.
            offset++; //skip LINETOKEN ASSIGNMENT
            //get left side of assigment
            result = GetIdentifierLabel(source, ref offset);
            result += " = ";

            //Get right side of assigment (expression)
            result += GetExpression(source, ref offset);
            
            return result;
        }

        /// <summary>
        /// Parse tokens from postfix (RPN) into infix notation
        /// </summary>
        /// <param name="source">Byte encoded source</param>
        /// <param name="offset">start of expression</param>
        /// <returns></returns>
        private static string GetExpression(byte[] source, ref int offset)
        {
            //Create a list of ordered tokeneditorsinfo
            List<EditorTokenInfo> ExprTokens = new List<EditorTokenInfo>();

            bool isEOL = false;

            while (!isEOL)
            {
                switch(source[offset])
                {
                    case (byte)PCODE_CONST.LOCAL_POINT_PRG:
                        EditorTokenInfo localpoint = new EditorTokenInfo("Identifier", "Identifier");
                        localpoint.Token = (byte)PCODE_CONST.LOCAL_POINT_PRG;
                        localpoint.Index = source[offset + 1];
                        localpoint.Type = source[offset + 2];
                        localpoint.Text = GetIdentifierLabel(source, ref offset);
                        ExprTokens.Add(localpoint);
                        break;
                    case (byte)PCODE_CONST.CONST_VALUE_PRG:
                        //TODO: Set a EditorTokenInfo for a numeric constant value
                        //.Text should be ready with decoded value
                        break;

                    case (byte)LINE_TOKEN.EOF:
                    case (byte)LINE_TOKEN.THEN:
                    case (byte)LINE_TOKEN.REM:
                    case (byte)LINE_TOKEN.ELSE:
                    case (byte)LINE_TOKEN.EOE:
                    case (byte)TYPE_TOKEN.NUMBER:
                    default:
                        isEOL = true;
                        //expression ends here, this byte-token should be processed outside this function
                        break;
                }
               
            }
            return null;
        }

        private static string GetIdentifierLabel(byte[] source, ref int offset)
        {
            string IdentLabel = "UNKNOWN_IDENT";
            //get the target identifier
            short Token = source[offset];
            int TokenIdx = source[offset + 1];
            short TokenType = source[offset + 2];

            offset += 3;

            switch (TokenType)
            {
                case (short)PCODE_CONST.VARPOINTTYPE:
                    IdentLabel = Identifiers.Variables[TokenIdx].Label;
                    break;
                case (short)PCODE_CONST.INPOINTTYPE:
                    IdentLabel = Identifiers.Inputs[TokenIdx].Label;
                    break;
                case (short)PCODE_CONST.OUTPOINTTYPE:
                    IdentLabel = Identifiers.Outputs[TokenIdx].Label;
                    break;

                default:
                    break;
            }
            return IdentLabel;
        }
    }
}