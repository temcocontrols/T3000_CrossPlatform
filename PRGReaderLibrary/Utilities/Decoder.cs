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

            string Result = "";

            // 4. Operators precedence, same as in grammar
            ////RegisterOperators(100, Associativity.Right, EXP);
            ////RegisterOperators(90, MUL, DIV, IDIV);
            ////RegisterOperators(80, MOD);
            ////RegisterOperators(70, SUM, SUB);

            ////RegisterOperators(60, LT, GT, LTE, GTE, EQ, NEQ);

            ////RegisterOperators(50, Associativity.Right, NOT);
            ////RegisterOperators(50, AND, OR, XOR);



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
                    //case (byte)TYPE_TOKEN.NOT:
                    //    EditorTokenInfo nottoken = new EditorTokenInfo("NOT", "NOT");
                    //    nottoken.Token = source[offset];
                    //    ExprTokens.Add(nottoken);
                    //    offset++;
                    //    break;


                    #endregion

                    //TODO: Functions

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

            }// after this, we should have a list of all tokens in the expression.
            //lets parse RPN into Infix, 
            Stack<BinaryTree<EditorTokenInfo>> BTStack =
                 new Stack<BinaryTree<EditorTokenInfo>>();

         

            //parse using BTreeStack every token in RPN list of preprocessed tokens
            foreach (EditorTokenInfo token in ExprTokens)
            {
                if(token.Precedence < 50) 
                    //It's an operand, just push to stack
                    BTStack.Push(new BinaryTree<EditorTokenInfo>(token));
            
                else
                {
                    //it's and operator, push two operands, create a new tree and push to stack again.
                    BinaryTree<EditorTokenInfo> operatornode = new BinaryTree<EditorTokenInfo>(token);
                    operatornode.Right = BTStack.Pop();
                    operatornode.Left = BTStack.Pop();
                    BTStack.Push(operatornode);

                    //TODO: some exceptions may be found here for unary operators.

                }


            }

            BinaryTree<EditorTokenInfo> root = BTStack.Peek();
            //now we end the the top most node on stack as a complete tree of RPN
             Result = TraverseInOrder(root);

            return Result;
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
            if(token.Precedence < 50)
            {
                //its an operand, return the text
                return token.Text;
            }
            else
            {
                //its a operator, visit left, concat with root and right.
                Result = TraverseInOrder(rootnode.Left,token.Precedence ) + " " + token.Text + " " + TraverseInOrder(rootnode.Right,token.Precedence);
                //take account of prior precedence vs current node precedence, and add parenthesis
                if(token.Precedence < priorPrecedence)
                {
                    Result += "(" + Result + ")";
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