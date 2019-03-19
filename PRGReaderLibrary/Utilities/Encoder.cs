using PRGReaderLibrary.Extensions;
using PRGReaderLibrary.Types.Enums.Codecs;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;


namespace PRGReaderLibrary.Utilities
{

    /// <summary>
    /// Code Control Basic into Bytes
    /// </summary>
    public class Encoder
    {

        /// <summary>
        /// Required copy of Control Points Labels just for semantic validations
        /// </summary>
        public ControlPoints Identifiers { get; set; } = new ControlPoints();

        /// <summary>
        /// Set a local copy of all identifiers in prg
        /// </summary>
        /// <param name="prg">Program prg</param>
         public void SetControlPoints(Prg prg)
        {
            Identifiers = new ControlPoints(prg);
            TimeBuff = new TimeBuffer(Identifiers);
        }

        /// <summary>
        /// Required copy con TimeBuffer entries
        /// </summary>
        public TimeBuffer TimeBuff { get; set; }

        /// <summary>
        /// Encode a ProgramCode Into Byte Array
        /// </summary>
        /// <param name="Tokens">Preprocessed list of tokens</param>
        /// <returns>byte array</returns>
        public byte[] EncodeBytes(List<EditorTokenInfo> Tokens)
        {
            var result = new List<byte>();
            byte[] prgsize = { (byte)0x00, (byte)0x00 };
            result.AddRange(prgsize);

            Stack<int> offsets = new Stack<int>();
            Stack<EditorJumpInfo> Jumps = new Stack<EditorJumpInfo>();
            List<EditorLineInfo> Lines = new List<EditorLineInfo>();

            int offset = 1; //offset is a count of total encoded bytes

            int tokenIndex = 0;
            bool isFirstToken = true;
            bool isTimeBuffered = false;

            for (tokenIndex = 0; tokenIndex < Tokens.Count; tokenIndex++)
            {
                var token = Tokens[tokenIndex];

                switch (token.TerminalName)
                {
                    #region IF IF+ IF- THEN ELSE
                    case "IF":
                    case "IF+":
                    case "IF-":
                    case "THEN":
                    case "ELSE":
                    case "EOE":
                        //TODO: Ver si es posible eliminar el último EOE antes de LF para evitar que se guarden como comas
                        result.Add((byte)token.Token);
                        offset++;

                        if (token.Token == (short)LINE_TOKEN.EOE)
                        {
                            if (offsets.Count > 0)
                            {
                                int newoffset = offset + 1;
                                int idxoffset = offsets.Pop();
                                //encode and replace
                                short NewOffSetNumber = Convert.ToInt16(newoffset);
                                byte[] byteoffset = NewOffSetNumber.ToBytes();
                                result[idxoffset] = byteoffset[0];
                                result[idxoffset + 1] = byteoffset[1];

                            }
                        }

                        break;


                    #endregion

                    #region REM COMMENTS
                    case "REM":
                    case "ASSIGN":

                        result.Add((byte)token.Token);
                        offset++;
                        break;
                    case "Comment":
                    case "PhoneNumber":
                        result.Add((byte)token.Type); //Lenght of String
                        offset++;
                        result.AddRange(token.Text.ToBytes());
                        offset += token.Type;
                        break;
                    #endregion

                    #region Special Numbers
                    #region Line Numbers
                    case "LineNumber":
                        if (isFirstToken)
                        {
                            result.Add((byte)TYPE_TOKEN.NUMBER); //TYPE OF NEXT TOKEN: NUMBER 1 Byte
                            short LineNumber = Convert.ToInt16(token.Text);
                            result.AddRange(LineNumber.ToBytes()); //LINE NUMBER, 2 Bytes
                            Lines.Add(new EditorLineInfo(Convert.ToInt32(LineNumber), Convert.ToInt32(offset + 1)));
                            offset += 3;
                            isFirstToken = false;
                        }
                        else
                        {
                            //else: linenumber for a jump

                            short LineNumber = Convert.ToInt16(token.Text);
                            byte[] RawLineNumber = LineNumber.ToBytes();
                            RawLineNumber[1] = (byte)LINE_TOKEN.RAWLINE;
                            RawLineNumber[0] = (byte)LINE_TOKEN.RAWLINE;
                            result.AddRange(RawLineNumber);
                            Jumps.Push(new EditorJumpInfo(0, LineNumber, offset + 1));
                            offset += 2;

                        }
                        break; 
                    #endregion

                    case "OFFSET": //2 Bytes
                        //push index of next byte for new offset.
                        offsets.Push(offset + 1);
                        short OffSetNumber = Convert.ToInt16(token.Token);
                        result.AddRange(OffSetNumber.ToBytes()); //OFFSET NUMBER, 2 Bytes
                        offset += 2;

                        break;

                    //Index and Counters: 1 Byte
                    case "ARGCOUNT":
                    case "SYSPRG":
                    case "PRG":
                    case "PANEL":

                        short IdentCount = Convert.ToInt16(token.Index);
                        byte[] bytesIdentCount = IdentCount.ToBytes();
                        result.Add(bytesIdentCount[0]); //OFFSET NUMBER, 1 Bytes
                        offset += 1;

                        break;

                    case "PRT_A":
                    case "PRT_B":
                    case "PRT_0":
                    case "ALL":
                        short prt = Convert.ToInt16(token.Token);
                        byte[] bytesPrt = prt.ToBytes();
                        result.Add(bytesPrt[0]); //OFFSET NUMBER, 1 Bytes
                        offset += 1;
                        break;

                    case "WAITCOUNTER":
                        result.Add((byte)token.Token);
                        offset++;
                        int WaitCounter = Convert.ToInt32(token.Index);
                        result.AddRange(WaitCounter.ToBytes()); //OFFSET NUMBER, 4 Bytes
                        offset += 4;

                        break;
                    #endregion

                    #region Operators, Functions and Commands
                    //OPERATORS
                    case "PLUS":
                    case "MINUS":
                    case "MUL":
                    case "DIV":
                    case "POW":
                    case "MOD":
                    case "LT":
                    case "GT":
                    case "LE":
                    case "GE":
                    case "EQ":
                    case "NE":
                    case "AND":
                    case "XOR":
                    case "OR":
                    case "NOT":

                    //FUNCTIONS
                    case "ABS":
                    case "INTERVAL":
                    case "_INT":
                    case "LN":
                    case "LN_1":
                    case "SQR":
                    case "_Status":
                    case "CONPROP":
                    case "CONRATE":
                    case "CONRESET":
                    case "TBL":
                    case "TIME":
                    
                    case "WR_ON":
                    case "WR_OFF":
                    case "DOY":
                    case "DOM":
                    case "DOW":
                    case "POWER_LOSS":
                    case "UNACK":
                    case "SCANS":
                    case "USER_A":
                    case "USER_B":

                    //COMMANDS
                    case "START":
                    case "STOP":
                    case "CLEAR":
                    case "RETURN":
                    case "WAIT":
                    case "HANGUP":
                    case "GOTO":
                    case "GOSUB":
                    case "ON_ERROR":
                    case "ON_ALARM":
                    case "ENABLEX":
                    case "DISABLEX":
                    case "ENDPRG":
                    case "RUN_MACRO":
                    case "CALL":
                    case "SET_PRINTER":
                    case "DECLARE":
                    case "PRINT_AT":
                    case "ALARM_AT":
                    case "PHONE":
                    case "PRINT":
                    case "OPEN":
                    case "CLOSE":


                        result.Add((byte)token.Token);
                        offset++;
                        break;

                    #region Buffer time functions
                    case "TIME_ON":
                    case "TIME_OFF":
                        result.Add((byte)token.Token);
                        offset++;
                        //next token will be an identifier
                        isTimeBuffered = true;
                        break; 
                    #endregion

                    #region Functions with variable list of expressions, must add count of expressions as last token.
                    case "AVG":
                    case "MAX":
                    case "MIN":

                        result.Add((byte)token.Token);
                        result.Add((byte)token.Index);
                        offset += 2;
                        break; 
                    #endregion

                    #endregion

                    #region Identifiers, Registers, VARS, INS, OUTS, etc 3 bytes
                    case "Identifier":
                    case "Register":
                    case "VARS":
                    case "INS":
                    case "OUTS":
                    case "PIDS":
                        //Encode directly: Token + Index + Type
                        if (!isTimeBuffered)
                        {
                            result.Add((byte)token.Token);
                            result.Add((byte)token.Index);
                            result.Add((byte)token.Type);
                            offset += 3;
                            //Register??
                            if(token.Token == (short) PCODE_CONST.REMOTE_POINT_PRG)
                            {
                                //We need to add 3 bytes: PanelID, Subnet and 1
                                result.Add((byte)Convert.ToInt16(token.PanelID));
                                result.Add((byte)Convert.ToInt16(token.Subnet));
                                result.Add((byte)1);
                                offset += 3;

                            }
                        }
                        else //It's a time buffered function
                        {
                            //add to time buffer!!
                            short TimeBufferPos= (short)TimeBuff.Add((IdentifierTypes)token.Type, token.Index);
                            result.AddRange(TimeBufferPos.ToBytes());
                            offset += 2;
                        }
                        isTimeBuffered = false;
                        break;

                    #endregion

                    #region NUMBERS (4-5 BYTES ONLY)
                    case "Number":
                    case "CONNUMBER":
                    case "TABLENUMBER":
                    case "TIMER":
                    case "WRNUMBER":

                        result.Add((byte)token.Token);
                        offset++;
                        //And... voilá...  trick revealed.
                        //All numbers are converted to integer 32b, multiplying by 1000.
                        //on Decoding bytes: reverse operation dividing by 1000, so if not exact
                        //floating point numbers only have 3 decimals
                        int numVal = (int)(Convert.ToSingle(token.Text) * 1000);
                        byte[] byteArray = BitConverter.GetBytes(numVal);
                        result.AddRange(byteArray);
                        offset += 4;
                        break;

                    case "TimeLiteral":

                        //NEW: Added special treatment for TIME FORMAT numbers, see related TODO for DECODER
                        result.Add((byte)token.Token);
                        offset++;
                        string hh, mm, ss;
                        hh = token.Text.Substring(0, 2);
                        mm = token.Text.Substring(3, 2);
                        ss = token.Text.Substring(6, 2);
                        int numericvalue = Convert.ToInt32(hh) * 3600 + Convert.ToInt32(mm) * 60 + Convert.ToInt32(ss);
                        numericvalue *= 1000;
                        byte[] timeByteArray = BitConverter.GetBytes(numericvalue);
                        result.AddRange(timeByteArray);
                        //extra byte to mark a TIME FORMAT VALUE
                        result.Add((byte)token.Type);
                        offset += 5;
                        break;

                    #endregion


                    #region EOF CRLF

                    case "LF":
                        isFirstToken = true;

                        break;

                    case "EOF":
                        if ((tokenIndex + 1) == Tokens.Count)
                        {
                            //EOF: Last LF, should be replaced with xFE
                            result.Add((byte)LINE_TOKEN.EOF);
                            //No increment to offset, as EOF doesn't count on 
                        }

                        //EOL: LF, Just Ignored. Next Token should be another LineNumber
                        break;

                    #endregion

                    case "CMDSEPARATOR":
                    default:
                        Trace.WriteLine($"Token ignored and not encoded: {token.ToString()}");
                        break;

                }
                isFirstToken = token.TerminalName == "LF" ? true : false;

            }

            //Set Jumps offsets
            if (Jumps.Count > 0 && Lines.Count > 0)
            {
                while (Jumps.Count > 0)
                {
                    EditorJumpInfo NewJump = Jumps.Pop();
                    var LineIdx = Lines.FindIndex(k => k.Before == NewJump.LineIndex);
                    if (LineIdx >= 0)
                    {
                        short LineOffset = Convert.ToInt16(Lines[LineIdx].After);
                        byte[] LObytes = LineOffset.ToBytes();
                        result[NewJump.Offset] = LObytes[0];
                        result[NewJump.Offset + 1] = LObytes[1];

                    }
                    else //LineIdx is -1, not found!
                    {
                        MessageBox.Show($"Error: Line not found: {NewJump.LineIndex}");
                    }

                }

            }

            //calculate SIZE of Program
            offset--;
            byte[] size = offset.ToBytes();
            result[0] = size[0];
            result[1] = size[1];

            //Add Time Buffer here

            short bufferCount = (short)TimeBuff.BufferCount;

            if (bufferCount>0)
            {

                //Test if it fits
                byte[] btime = TimeBuff.ToBytes();
                if (result.Count > (2000 - btime.Length))
                    throw new OverflowException($"Time Buffer not allocated, exceeding 2000 bytes. Current PRG size is {result.Count} and TimeBuffer requires {btime.Length}");
                else
                    result.AddRange(btime);
               

            }

            //////fill with nulls til the end of block

            while (result.Count < 2000)
            {
                result.Add((byte)0x00);
            }
            return result.ToArray();
        }


    }

}
