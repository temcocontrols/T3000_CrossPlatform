using PRGReaderLibrary.Extensions;
using PRGReaderLibrary.Types.Enums.Codecs;
using System;
using System.Collections.Generic;
using System.Linq;
using NGenerics.DataStructures.Trees;

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
        /// Lists every single linenumber with it byte offset from start of programcode.
        /// </summary>
        static List<EditorJumpInfo> JumpLines { get; set; } = new List<EditorJumpInfo>();

        /// <summary>
        /// Set a local copy of all identifiers in prg
        /// </summary>
        /// <param name="prg">Program prg</param>
        static public void SetControlPoints(Prg prg)
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
            offset = 2;

            while (offset <= (ProgLenght + 2))
            {
                var tokenvalue = (byte)PCode[offset];
                switch (tokenvalue)
                {
                    //linenumbers
                    case (byte)TYPE_TOKEN.NUMBER:
                        if (isFirstToken)
                        {
                            string strLineNum = GetLineNumber(PCode, ref offset);
                            result += strLineNum;
                        }
                        //next token is not the first, 4 sure
                        isFirstToken = false;
                        break;
                    //comments
                    case (byte)LINE_TOKEN.REM:

                        result += " " + GetComment(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    //assigments
                    case (byte)LINE_TOKEN.ASSIGN:
                        result += " " + GetAssigment(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;


                    //TODO: LRUIZ :::: Continue here with COMMANDS

                    #region Single byte commands

                    case (byte)LINE_TOKEN.CLEAR:
                        result += " " + "CLEAR" + System.Environment.NewLine;
                        offset++;
                        isFirstToken = true;
                        break;
                    case (byte)LINE_TOKEN.HANGUP:
                        result += " " + "HANGUP" + System.Environment.NewLine;
                        offset++;
                        isFirstToken = true;
                        break;
                    case (byte)LINE_TOKEN.RETURN:
                        result += " " + "RETURN" + System.Environment.NewLine;
                        offset++;
                        isFirstToken = true;
                        break;
                    case (byte)LINE_TOKEN.ENDPRG:
                        result += " " + "END" + System.Environment.NewLine;
                        offset++;
                        isFirstToken = true;
                        break;
                    #endregion

                    #region 2+ bytes commands
                    case (byte)LINE_TOKEN.START:
                        result += " " + "START ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.STOP:
                        result += " " + "STOP ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.OPEN:
                        result += " " + "OPEN ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.CLOSE:
                        result += " " + "CLOSE ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.ENABLEX:
                        result += " " + "ENABLE ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.DISABLEX:
                        result += " " + "DISABLE ";
                        offset++;
                        result += GetIdentifierLabel(PCode, ref offset) + System.Environment.NewLine;
                        isFirstToken = true;
                        break; 
                    #endregion

                    #region JUMPS
                    case (byte)LINE_TOKEN.GOTO:
                        result += " " + "GOTO ";
                        offset++;
                        int copyoffset = (int)PCode[offset];
                        //TODO: Don't know what happens when offset of JumpLine is higher than 255
                        //What about the second byte???
                        string gotoLine = GetLineNumber(PCode, ref copyoffset);
                        offset += 2; //2 bytes
                        result += gotoLine + System.Environment.NewLine;

                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.GOSUB:
                        result += " " + "GOSUB ";
                        offset++;
                        int copyoffset2 = (int)PCode[offset];
                        //TODO: Don't know what happens when offset of JumpLine is higher than 255
                        //What about the second byte???
                        string gotoLine2 = GetLineNumber(PCode, ref copyoffset2);
                        offset += 2; //2 bytes
                        result += gotoLine2 + System.Environment.NewLine;

                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.ON_ALARM:
                        result += " " + "ON-ALARM ";
                        offset++;
                        int copyoffset3 = (int)PCode[offset];
                        //TODO: Don't know what happens when offset of JumpLine is higher than 255
                        //What about the second byte???
                        string gotoLine3 = GetLineNumber(PCode, ref copyoffset3);
                        offset += 2; //2 bytes
                        result += gotoLine3 + System.Environment.NewLine;

                        isFirstToken = true;
                        break;

                    case (byte)LINE_TOKEN.ON_ERROR:
                        result += " " + "ON-ERROR ";
                        offset++;
                        int copyoffset4 = (int)PCode[offset];
                        //TODO: Don't know what happens when offset of JumpLine is higher than 255
                        //What about the second byte???
                        string gotoLine4 = GetLineNumber(PCode, ref copyoffset4);
                        offset += 2; //2 bytes
                        result += gotoLine4 + System.Environment.NewLine;

                        isFirstToken = true;
                        break;


                    case (byte)LINE_TOKEN.ON:
                        result += " " + "ON ";
                        offset++;
                        result += GetExpression(PCode, ref offset) + " ";
                        isFirstToken = false;
                        break; 
                    #endregion

                    default:
                        offset++; //TODO: This line only for debugging purposes, should be removed, when decoder finished
                        break;
                }
            }

            return result;
        }


        /// <summary>
        /// Get a linenumber
        /// </summary>
        /// <param name="PCode">Source bytes</param>
        /// <param name="offset">position</param>
        /// <returns></returns>
        private static string GetLineNumber(byte[] PCode, ref int offset)
        {
            string result = "";
            offset++; //1 byte = TOKEN {1}
            short LineNumber = BytesExtensions.ToInt16(PCode, ref offset);
            result += LineNumber.ToString(); //LINE NUMBER, 2 Bytes
            //Populate a list of offsets of every linenumbers
            JumpLines.Add(new EditorJumpInfo(JumpType.GOTO, (int)LineNumber, offset - 3));
            return result;
        }

        /// <summary>
        /// Get comments, including REM token, autoincrements offset
        /// </summary>
        /// <param name="source">source bytes</param>
        /// <param name="offset">position</param>
        /// <returns>decoded comments</returns>
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

        /// <summary>
        /// Get assigment
        /// </summary>
        /// <param name="source">source bytes</param>
        /// <param name="offset">position</param>
        /// <returns>decoded string</returns>
        private static string GetAssigment(byte[] source, ref int offset)
        {
            string result = "↑";

            
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
            bool ExpressionAhead = false;
            string NextExpression = "";

            EditorTokenInfo fxtoken;

            string Result = "";

            #region Operators precedence, same as in grammar
            // 4. Operators precedence, same as in grammar
            ////RegisterOperators(100, Associativity.Right, EXP);
            ////RegisterOperators(90, MUL, DIV, IDIV);
            ////RegisterOperators(80, MOD);
            ////RegisterOperators(70, SUM, SUB);

            ////RegisterOperators(60, LT, GT, LTE, GTE, EQ, NEQ);

            ////RegisterOperators(50, Associativity.Right, NOT);
            ////RegisterOperators(50, AND, OR, XOR);

            #endregion
            
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
                        
                        EditorTokenInfo constvalue = new EditorTokenInfo("NUMBER", "NUMBER");
                        constvalue.Token = source[offset];
                        constvalue.Text = GetConstValue(source, ref offset); //incrementes offset after reading const 
                        ExprTokens.Add(constvalue);

                        break;

                    #endregion

                    #region Single Tokens

                    case (byte)TYPE_TOKEN.PLUS:
                        EditorTokenInfo plustoken = new EditorTokenInfo("+", "PLUS");
                        plustoken.Token = source[offset];
                        plustoken.Precedence = 70;
                        ExprTokens.Add(plustoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MINUS:
                        EditorTokenInfo minustoken = new EditorTokenInfo("-", "MINUS");
                        minustoken.Token = source[offset];
                        minustoken.Precedence = 70;
                        ExprTokens.Add(minustoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.DIV:
                        EditorTokenInfo divtoken = new EditorTokenInfo("/", "DIV");
                        divtoken.Token = source[offset];
                        divtoken.Precedence = 90;
                        ExprTokens.Add(divtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.IDIV:
                        EditorTokenInfo idivtoken = new EditorTokenInfo("\\", "IDIV");
                        idivtoken.Token = source[offset];
                        idivtoken.Precedence = 90;
                        ExprTokens.Add(idivtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MUL:
                        EditorTokenInfo multoken = new EditorTokenInfo("*", "MUL");
                        multoken.Token = source[offset];
                        multoken.Precedence = 90;
                        ExprTokens.Add(multoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.POW:
                        EditorTokenInfo powtoken = new EditorTokenInfo("^", "POW");
                        powtoken.Token = source[offset];
                        powtoken.Precedence = 100;
                        ExprTokens.Add(powtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.MOD:
                        EditorTokenInfo modtoken = new EditorTokenInfo("MOD", "MOD");
                        modtoken.Token = source[offset];
                        modtoken.Precedence = 80;
                        ExprTokens.Add(modtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.LT:
                        EditorTokenInfo lttoken = new EditorTokenInfo("<", "LT");
                        lttoken.Token = source[offset];
                        lttoken.Precedence = 60;
                        ExprTokens.Add(lttoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.LE:
                        EditorTokenInfo letoken = new EditorTokenInfo("<=", "LE");
                        letoken.Token = source[offset];
                        letoken.Precedence = 60;
                        ExprTokens.Add(letoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.GT:
                        EditorTokenInfo gttoken = new EditorTokenInfo(">", "GT");
                        gttoken.Token = source[offset];
                        gttoken.Precedence = 60;
                        ExprTokens.Add(gttoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.GE:
                        EditorTokenInfo getoken = new EditorTokenInfo(">=", "GE");
                        getoken.Token = source[offset];
                        getoken.Precedence = 60;
                        ExprTokens.Add(getoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.EQ:
                        EditorTokenInfo eqtoken = new EditorTokenInfo("=", "EQ");
                        eqtoken.Token = source[offset];
                        eqtoken.Precedence = 60;
                        ExprTokens.Add(eqtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.NE:
                        EditorTokenInfo netoken = new EditorTokenInfo("<>", "NE");
                        netoken.Token = source[offset];
                        netoken.Precedence = 60;
                        ExprTokens.Add(netoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.XOR:
                        EditorTokenInfo xortoken = new EditorTokenInfo("XOR", "XOR");
                        xortoken.Token = source[offset];
                        xortoken.Precedence = 50;
                        ExprTokens.Add(xortoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.OR:
                        EditorTokenInfo ortoken = new EditorTokenInfo("OR", "OR");
                        ortoken.Token = source[offset];
                        ortoken.Precedence = 50;
                        ExprTokens.Add(ortoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.AND:
                        EditorTokenInfo andtoken = new EditorTokenInfo("AND", "AND");
                        andtoken.Token = source[offset];
                        andtoken.Precedence = 50;
                        ExprTokens.Add(andtoken);
                        offset++;
                        break;
                    case (byte)TYPE_TOKEN.NOT:
                        EditorTokenInfo nottoken = new EditorTokenInfo("NOT", "NOT");
                        nottoken.Token = source[offset];
                        nottoken.Precedence = 50;
                        ExprTokens.Add(nottoken);
                        offset++;
                        break;
                        //functions that are low precedence as identifiers in expressions
                    case (byte)FUNCTION_TOKEN.DOY:
                        fxtoken = new EditorTokenInfo("DOY", "DOY");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.DOW:
                        fxtoken = new EditorTokenInfo("DOW", "DOW");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.DOM:
                        fxtoken = new EditorTokenInfo("DOM", "DOM");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.POWER_LOSS:
                        fxtoken = new EditorTokenInfo("POWER-LOSS", "POWER_LOSS");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.USER_A:
                        fxtoken = new EditorTokenInfo("USER-B", "USER_A");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.USER_B:
                        fxtoken = new EditorTokenInfo("USER-B", "USER_B");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.SCANS:
                        fxtoken = new EditorTokenInfo("SCANS", "SCANS");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.UNACK:
                        fxtoken = new EditorTokenInfo("UNACK", "UNACK");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 0;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;

                    #endregion

                    #region Functions with single expression

                    case (byte)FUNCTION_TOKEN.ABS:
                        fxtoken = new EditorTokenInfo("ABS", "ABS");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN._INT:
                        fxtoken = new EditorTokenInfo("INT", "_INT");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.INTERVAL:
                        fxtoken = new EditorTokenInfo("INTERVAL", "INTERVAL");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.LN:
                        fxtoken = new EditorTokenInfo("LN", "LN");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.LN_1:
                        fxtoken = new EditorTokenInfo("LN-1", "LN_1");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.SQR:
                        fxtoken = new EditorTokenInfo("SQR", "SQR");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN._Status:
                        fxtoken = new EditorTokenInfo("STATUS", "_Status");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;


                    #region This functions hadnt been tested, PENDING FROM ENCONDING
                    case (byte)FUNCTION_TOKEN.CONPROP:
                        fxtoken = new EditorTokenInfo("CONPROP", "CONPROP");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;

                    case (byte)FUNCTION_TOKEN.CONRATE:
                        fxtoken = new EditorTokenInfo("CONRATE", "CONRATE");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;

                    case (byte)FUNCTION_TOKEN.CONRESET:
                        fxtoken = new EditorTokenInfo("CONRESET", "CONRESET");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;

                    case (byte)FUNCTION_TOKEN.TBL:
                        fxtoken = new EditorTokenInfo("TBL", "TBL");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.TIME:
                        fxtoken = new EditorTokenInfo("TIME", "TIME");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.TIME_ON:
                        fxtoken = new EditorTokenInfo("TIME-ON", "TIME_ON");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.TIME_OFF:
                        fxtoken = new EditorTokenInfo("TIME-OFF", "TIME_OFF");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.WR_ON:
                        fxtoken = new EditorTokenInfo("WR-ON", "WR_ON");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;
                    case (byte)FUNCTION_TOKEN.WR_OFF:
                        fxtoken = new EditorTokenInfo("WR-OFF", "WR_OFF");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        ExprTokens.Add(fxtoken);
                        offset++;
                        break;


                    #endregion


                    #region Functions ended with count of variable arguments
                    case (byte)FUNCTION_TOKEN.AVG:
                        fxtoken = new EditorTokenInfo("AVG", "AVG");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        fxtoken.Index = source[offset + 1];
                        ExprTokens.Add(fxtoken);
                        offset += 2;
                        break;
                    case (byte)FUNCTION_TOKEN.MAX:
                        fxtoken = new EditorTokenInfo("MAX", "MAX");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        fxtoken.Index = source[offset + 1];
                        ExprTokens.Add(fxtoken);
                        offset += 2;
                        break;
                    case (byte)FUNCTION_TOKEN.MIN:
                        fxtoken = new EditorTokenInfo("MIN", "MIN");
                        fxtoken.Token = source[offset];
                        fxtoken.Precedence = 200;
                        fxtoken.Index = source[offset + 1];
                        ExprTokens.Add(fxtoken);
                        offset += 2;
                        break;


                    #endregion

                    #endregion

                    #region End of expressions (MARKERS)

                    case (byte)LINE_TOKEN.EOE:
                        //ExpressionAhead = true;
                        //offset++;
                        //NextExpression = "," + GetExpression(source, ref offset);
                        //isEOL = true;
                        //break;

                    case (byte)LINE_TOKEN.EOF:
                    case (byte)LINE_TOKEN.THEN:
                    case (byte)LINE_TOKEN.REM:
                    case (byte)LINE_TOKEN.ELSE:
                    case (byte)TYPE_TOKEN.NUMBER: //line number
                    default:
                        isEOL = true;
                        //expression ends here, this byte-token should be processed outside this function
                        break;

                    #endregion
                }

            }// after this, we should have a list of all tokens in the expression.
            //lets parse RPN into Infix, 
            if(ExpressionAhead)
                Result = ParseRPN2Infix(ExprTokens) + NextExpression;
            else
                Result = ParseRPN2Infix(ExprTokens);
          
            return Result;
        }


        /// <summary>
        /// Parse a postfix list of tokens into INFIX
        /// </summary>
        /// <param name="ExprTokens"></param>
        /// <returns></returns>
        static string ParseRPN2Infix(List<EditorTokenInfo> ExprTokens)
        {


            string Result = "";
            Stack<BinaryTree<EditorTokenInfo>> BTStack =
               new Stack<BinaryTree<EditorTokenInfo>>();



            //parse using BTreeStack every token in RPN list of preprocessed tokens
            for(int idxtoken=0;idxtoken < ExprTokens.Count;idxtoken++)
            
            {
                EditorTokenInfo token = new EditorTokenInfo("","");
                token = ExprTokens[idxtoken];
               
                if (token.Precedence < 50)
                    //It's an operand, just push to stack
                    BTStack.Push(new BinaryTree<EditorTokenInfo>(token));

                else
                {
                    //it's an operator, push two operands, create a new tree and push to stack again.
                    BinaryTree<EditorTokenInfo> operatornode = new BinaryTree<EditorTokenInfo>(token);
                    
                    switch (operatornode.Data.TerminalName )
                    {
                        //Multiple expressions functions
                        case "AVG":

                            if(BTStack.Count < operatornode.Data.Index)
                                throw new ArgumentException("Not enough arguments in BTStack for AVG Function");

                            for (int i = 1; i< operatornode.Data.Index; i++)
                                NodeAddCommaToken(ref operatornode, BTStack.Pop()); //default, add to the right.

                            NodeAddCommaToken(ref operatornode, BTStack.Pop(),true); //just add to the left
                            BTStack.Push(operatornode);

                            break;

                        default: //Other simple functions and operators

                            if (BTStack.Count > 1) //avoid unary operators and functions exception
                                operatornode.Right = BTStack.Pop();

                            operatornode.Left = BTStack.Pop();
                            BTStack.Push(operatornode);

                            break;
                    }

                }

            }

            if (BTStack.Count > 1)
                throw new ArgumentException("Too many expressions in final BTStack");

            BinaryTree<EditorTokenInfo> root = BTStack.Peek();
            //now we end the the top most node on stack as a complete tree of RPN
            string rootprint = root.ToString();
            Result = TraverseInOrder(root);
            return Result;

        }

        /// <summary>
        /// Add a comma node to the left, and a binary tree to the right.
        /// </summary>
        /// <param name="root">root node</param>
        /// <param name="newTree"></param>
        private static void NodeAddCommaToken(ref BinaryTree<EditorTokenInfo> root, BinaryTree<EditorTokenInfo> newTree,bool onlyLeft = false)
        {
            EditorTokenInfo CommaToken = new EditorTokenInfo(",", "COMMA");
            CommaToken.Precedence = 150;
            
            BinaryTree<EditorTokenInfo> current = root;

            //find the the last left leaf, :) sounds like a tongue-twister
            while (current.Left != null)
                current = current.Left;

            if (!onlyLeft)
            {
                //add a comma to the left
                current.Left = new BinaryTree<EditorTokenInfo>(CommaToken);
                //add a binary tree to the right
                current.Left.Right = newTree;
            }
            else
                current.Left = newTree;
            

            //go back to top parent
            while (current.Parent != null)
                current = current.Parent;

            root = current;

        }



        /// <summary>
        /// Traverse inorder (INFIX NOTATION) all nodes of Btree.
        /// </summary>
        /// <param name="rootnode">Current Node</param>
        /// <param name="priorPrecedence">Prior Precedence</param>
        /// <returns></returns>
        static string TraverseInOrder
            (BinaryTree<EditorTokenInfo> rootnode, int priorPrecedence = 0)
        {
            string Result = "";

            EditorTokenInfo token = rootnode.Data;
            if (token.Precedence < 50)
            {
                //its an operand, return the text
                return token.Text;
            }
            else
            {
                //its a operator, visit left, concatenate with root and right.
                if (rootnode.Right == null)
                {
                    if (token.Precedence == 200) //Its a function, add parenthesis here!!
                        Result = token.Text +  "(" + TraverseInOrder(rootnode.Left, token.Precedence) + ")";

                    else //just a unary operator!?
                        Result = token.Text + " "  + TraverseInOrder(rootnode.Left, token.Precedence);
                }
                else //left and right are not null
                {
                    Result = TraverseInOrder(rootnode.Left, token.Precedence) + " " + token.Text + " " + TraverseInOrder(rootnode.Right, token.Precedence);
                }


                //take account of prior precedence vs current node precedence, and add parenthesis
                if (token.Precedence < priorPrecedence && priorPrecedence != 200 && priorPrecedence != 150)
                {
                    Result = "(" + Result + ")";
                }

            }

            return Result;

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
            Int32 intvalue = 0;

            for (int i = 0; i < 4; i++)
            {
                value[i] = source[offset + i + 1];
            }

            intvalue = BitConverter.ToInt32(value, 0);
            double dvalue = intvalue / 1000;
            intvalue = Convert.ToInt32(dvalue);

            //check if a whole number
            if (dvalue % 1 == 0)
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

        /// <summary>
        /// Get label for current identifier
        /// </summary>
        /// <param name="source">source bytes</param>
        /// <param name="offset">position</param>
        /// <returns></returns>
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