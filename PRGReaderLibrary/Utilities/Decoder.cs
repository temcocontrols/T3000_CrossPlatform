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
                switch (source[offset])
                {
                    #region Identifiers
                  
                    case (byte)PCODE_CONST.LOCAL_POINT_PRG:
                        EditorTokenInfo localpoint = new EditorTokenInfo("Identifier", "Identifier");
                        localpoint.Token = source[offset];
                        localpoint.Index = source[offset + 1];
                        localpoint.Type = source[offset + 2];
                        //text will be ready with identifier label
                        localpoint.Text = GetIdentifierLabel(source, ref offset); //increments offset after reading identifier
                        ExprTokens.Add(localpoint);
                        break;

                    #endregion

                    #region Numeric Constants

                    case (byte)PCODE_CONST.CONST_VALUE_PRG:
                        //TODO: Set a EditorTokenInfo for a numeric constant value
                        //.Text should be ready with decoded value
                        EditorTokenInfo constvalue = new EditorTokenInfo("NUMBER", "NUMBER");
                        constvalue.Token = source[offset];
                        constvalue.Text = GetConstValue(source, ref offset); //incrementes offset after reading const 
                        ExprTokens.Add(constvalue);
                        break;

                    #endregion

                    #region Single Tokens

                    case (byte)TYPE_TOKEN.PLUS:
                        EditorTokenInfo plustoken = new EditorTokenInfo("+","PLUS");
                        plustoken.Token = source[offset];
                        ExprTokens.Add(plustoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MINUS:
                        EditorTokenInfo minustoken = new EditorTokenInfo("-", "MINUS");
                        minustoken.Token = source[offset];
                        ExprTokens.Add(minustoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.DIV:
                        EditorTokenInfo divtoken = new EditorTokenInfo("/", "DIV");
                        divtoken.Token = source[offset];
                        ExprTokens.Add(divtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.IDIV:
                        EditorTokenInfo idivtoken = new EditorTokenInfo("\\", "IDIV");
                        idivtoken.Token = source[offset];
                        ExprTokens.Add(idivtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MUL:
                        EditorTokenInfo multoken = new EditorTokenInfo("*", "MUL");
                        multoken.Token = source[offset];
                        ExprTokens.Add(multoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.POW:
                        EditorTokenInfo powtoken = new EditorTokenInfo("^", "POW");
                        powtoken.Token = source[offset];
                        ExprTokens.Add(powtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MOD:
                        EditorTokenInfo modtoken = new EditorTokenInfo("MOD", "MOD");
                        modtoken.Token = source[offset];
                        ExprTokens.Add(modtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.LT:
                        EditorTokenInfo lttoken = new EditorTokenInfo("<", "LT");
                        lttoken.Token = source[offset];
                        ExprTokens.Add(lttoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.LE:
                        EditorTokenInfo letoken = new EditorTokenInfo("<=", "LE");
                        letoken.Token = source[offset];
                        ExprTokens.Add(letoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.GT:
                        EditorTokenInfo gttoken = new EditorTokenInfo(">", "GT");
                        gttoken.Token = source[offset];
                        ExprTokens.Add(gttoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.GE:
                        EditorTokenInfo getoken = new EditorTokenInfo(">=", "GE");
                        getoken.Token = source[offset];
                        ExprTokens.Add(getoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.EQ:
                        EditorTokenInfo eqtoken = new EditorTokenInfo("=", "EQ");
                        eqtoken.Token = source[offset];
                        ExprTokens.Add(eqtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.NE:
                        EditorTokenInfo netoken = new EditorTokenInfo("<>", "NE");
                        netoken.Token = source[offset];
                        ExprTokens.Add(netoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.XOR:
                        EditorTokenInfo xortoken = new EditorTokenInfo("XOR", "XOR");
                        xortoken.Token = source[offset];
                        ExprTokens.Add(xortoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.OR:
                        EditorTokenInfo ortoken = new EditorTokenInfo("OR", "OR");
                        ortoken.Token = source[offset];
                        ExprTokens.Add(ortoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.AND:
                        EditorTokenInfo andtoken = new EditorTokenInfo("AND", "AND");
                        andtoken.Token = source[offset];
                        ExprTokens.Add(andtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.NOT:
                        EditorTokenInfo nottoken = new EditorTokenInfo("NOT", "NOT");
                        nottoken.Token = source[offset];
                        ExprTokens.Add(nottoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.NOT:
                        EditorTokenInfo nottoken = new EditorTokenInfo("NOT", "NOT");
                        nottoken.Token = source[offset];
                        ExprTokens.Add(nottoken);
                        offset++;
                        break;


                    #endregion

                    #region End of expressions (MARKERS)


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

                    #endregion
                }

            }
            return null;
        }

        /// <summary>
        /// Get a numeric constant value from sourcec
        /// </summary>
        /// <param name="source">source bytes</param>
        /// <param name="offset">start</param>
        /// <returns></returns>
        private static string GetConstValue(byte[] source, ref int offset)
        {
            string result = "";
            byte[] value = { 0, 0, 0, 0 };
            Int64 intvalue = 0;

            for (int i = 0; i < 4; i++)
            {
                value[i] = source[offset + i + 1];
            }

            intvalue = BitConverter.ToInt64(value, 0);
            double dvalue = intvalue / 1000;
            intvalue = Convert.ToInt64 (dvalue);

            //check if a whole number
            if(dvalue % 1 == 0)
            {
                result = intvalue.ToString();
            }
            else
            {
                result = dvalue.ToString();
            }
            
         
            offset += 5;
            return result;
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