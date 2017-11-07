namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;
    using PRGReaderLibrary.Types.Enums.Codecs;

    
    public static class Enum<T>
    {
        public static bool IsDefined(T value)
        {
            return Enum.IsDefined(typeof(T), value);
        }
    }

    public static class ProgramCodeUtilities
    {
        public static bool IsLine(byte value) =>
            value == (byte)LINE_TOKEN.ASSIGN;

        public static bool IsVariable(byte value) =>
            value == (byte)FUNCTION_TOKEN.CONST_VALUE_PRG ||
            value == (byte)FUNCTION_TOKEN.REMOTE_POINT_PRG ||
            value == (byte)FUNCTION_TOKEN.LOCAL_POINT_PRG ||
            value == (byte)FUNCTION_TOKEN.TIME_ON;

        public static bool IsFunction(byte value)
        {
            if (IsVariable(value))
            {
                return false;
            }

            if (value == (byte)LINE_TOKEN.STOP)
            {
                return true;
            }

            return Enum<FUNCTION_TOKEN>.IsDefined((FUNCTION_TOKEN)value);
        }

        public static bool IsExpression(byte value)
        {
            if (IsVariable(value) || IsFunction(value) || value == 0)
            {
                return false;
            }

            return Enum<TYPE_TOKEN>.IsDefined((TYPE_TOKEN)value);
        }

        public static bool IsBinaryExpression(TYPE_TOKEN value)
        {
            return value != TYPE_TOKEN.NOT &&
                   value != TYPE_TOKEN.MINUSUNAR;
        }

        public enum ByteType
        {
            None,
            Variable,
            Line,
            Function,
            Expression
        }

        public static ByteType GetByteType(byte[] bytes, int offset)
        {
            var value = bytes[offset];

            if (IsVariable(value))
                return ByteType.Variable;
            else if (IsLine(value))
                return ByteType.Line;
            else if (IsFunction(value))
                return ByteType.Function;
            else if (IsExpression(value))
                return ByteType.Expression;

            return ByteType.None;
        }
    }

    public class Expression : Version
    {
        public TYPE_TOKEN Type { get; set; }

        public Expression(FileVersion version = FileVersion.Current)
            : base(version)
        { }

        public static Expression operator +(Expression expression1, Expression expression2) =>
            new BinaryExpression(expression1, expression2,
                TYPE_TOKEN.PLUS, expression1.FileVersion);

        public static Expression operator -(Expression expression1, Expression expression2) =>
            new BinaryExpression(expression1, expression2,
                TYPE_TOKEN.MINUS, expression1.FileVersion);
    }

    public class VariableExpression : Expression
    {
        public Prg Prg { get; set; }

        public FUNCTION_TOKEN Token { get; set; }
        public int Number { get; set; }

        public int Number2 { get; set; }
        public int Number3 { get; set; }
        public int Number4 { get; set; }
        public int Number5 { get; set; }

        public VariableValue Value { get; set; }

        public override string ToString()
        {
            switch (Token)
            {
                case FUNCTION_TOKEN.TIME_ON:
                    return $"{Token.GetName()} ( INIT )";

                case FUNCTION_TOKEN.CONST_VALUE_PRG:
                    var text = Value.Unit == Unit.Time
                        ? $"{Value}"
                        : $"{((double)Value.ToObject()).ToString("####")}";
                    return string.IsNullOrWhiteSpace(text)
                        ? "0"
                        : text;

                case FUNCTION_TOKEN.LOCAL_POINT_PRG:
                    return Prg.Variables[Number].Label ?? $"VAR{Number}";

                case FUNCTION_TOKEN.REMOTE_POINT_PRG:
                    return $"{Number3}.{Number4}.REG{Number + 1}";

                default:
                    return $"{Token.GetName()}";
            }
        }


        #region Binary data

        public VariableExpression(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Prg = prg;
            Token = (FUNCTION_TOKEN)bytes.ToByte(ref offset);

            switch (Token)
            {
                case FUNCTION_TOKEN.TIME_ON:
                    Number = bytes.ToByte(ref offset);
                    Type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    break;

                case FUNCTION_TOKEN.LOCAL_POINT_PRG:
                    Number = bytes.ToByte(ref offset);
                    Type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    break;

                case FUNCTION_TOKEN.REMOTE_POINT_PRG:
                    Number = bytes.ToByte(ref offset);
                    Number2 = bytes.ToByte(ref offset);
                    Number3 = bytes.ToByte(ref offset);
                    Number4 = bytes.ToByte(ref offset);
                    Number5 = bytes.ToByte(ref offset);
                    break;

                case FUNCTION_TOKEN.CONST_VALUE_PRG:
                    var value = bytes.ToInt32(ref offset);
                    var unit = Unit.Unused;
                    if (offset < bytes.Length)
                    {
                        var valueType = (FUNCTION_TOKEN)bytes.ToByte(ref offset);
                        if (valueType == FUNCTION_TOKEN.TIME_FORMAT)
                        {
                            unit = Unit.Time;
                        }
                        else
                        {
                            offset -= 1;
                        }
                    }
                    Value = new VariableValue(value, unit);
                    break;

                default:
                    //Number = bytes.ToByte(ref offset);
                    //Type = (ExpressionType)bytes.ToByte(ref offset);
                    break;
                    //throw new NotImplementedException(
                    //    $"Function token: {Token} not implemented.");
            }
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            return bytes.ToArray();
        }

        #endregion

    }

    public class FunctionExpression : Expression
    {
        public FUNCTION_TOKEN Token { get; set; }
        public List<Expression> Arguments { get; set; } = new List<Expression>();

        public FunctionExpression(
            FUNCTION_TOKEN token,
            FileVersion version = FileVersion.Current, params Expression[] arguments)
            : base(version)
        {
            Token = token;

            Arguments.AddRange(arguments);
        }

        public override string ToString()
        {
            switch (Type)
            {
                case (TYPE_TOKEN)29:
                    return $"STOP {string.Join(" , ", Arguments.Select(i => i.ToString()))}";

                default:
                    return $"{Token.GetName()} ( {string.Join(" , ", Arguments.Select(i => i.ToString()))} )";
            }
        }

        #region Binary data


        public FunctionExpression(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Arguments.Add(new VariableExpression(bytes, prg, ref offset, FileVersion));
            var token = bytes.ToByte(ref offset);
            while (!ProgramCodeUtilities.IsFunction(token))
            {
                --offset;
                Arguments.Add(new VariableExpression(bytes, prg, ref offset, FileVersion));
                token = bytes.ToByte(ref offset);
            }
            Token = (FUNCTION_TOKEN)token;
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            return bytes.ToArray();
        }

        #endregion

    }

    public class UnaryExpression : Expression
    {
        public Expression Expression { get; set; }

        public UnaryExpression(Expression expression,
            TYPE_TOKEN type,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Expression = expression;
            Type = type;
        }

        public override string ToString()
        {
            switch (Type)
            {
                case TYPE_TOKEN.MINUSUNAR:
                    return $"{Type.GetName()}{Expression.ToString()}";

                case TYPE_TOKEN.NOT:
                    return $"{Type.GetName()} {Expression.ToString()}";

                case (TYPE_TOKEN)LINE_TOKEN.STOP:
                    return $"STOP {Expression.ToString()}";

                default:
                    return $"{Type.GetName()} ( {Expression.ToString()} )";
            }
        }

        #region Binary data

        public UnaryExpression(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Expression = new VariableExpression(bytes, prg, ref offset, FileVersion);
            Type = (TYPE_TOKEN)bytes.ToByte(ref offset);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            return bytes.ToArray();
        }

        #endregion

    }

    public class BinaryExpression : Expression
    {
        public Expression First { get; set; }
        public Expression Second { get; set; }

        public BinaryExpression(Expression first, Expression second,
            TYPE_TOKEN type,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            First = first;
            Second = second;
            Type = type;
        }

        public override string ToString()
        {
            switch (Type)
            {
                case (TYPE_TOKEN)9:
                    return $"{First.ToString()} = {Second.ToString()}";

                case TYPE_TOKEN.DELIMITER:
                    return $"{First.ToString()} {Second.ToString()}";

                default:
                    return $"{First.ToString()} {Type.GetName()} {Second.ToString()}";
            }
        }

        #region Binary data

        public BinaryExpression(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            First = new VariableExpression(bytes, prg, ref offset, FileVersion);
            Second = new VariableExpression(bytes, prg, ref offset, FileVersion);
            Type = (TYPE_TOKEN)bytes.ToByte(ref offset);
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            return bytes.ToArray();
        }

        #endregion

    }

    public class Line : Version
    {
        public TYPE_TOKEN Type { get; set; }
        public int Number { get; set; }
        public LINE_TOKEN Token { get; set; }
        public byte[] Data { get; set; }
        public List<Expression> Expressions { get; set; } = new List<Expression>();

        public override string ToString()
        {
            switch (Token)
            {
                case LINE_TOKEN.REM:
                    return $"{Number} {Token} {Data.GetString()}";

                case LINE_TOKEN.IF:
                case LINE_TOKEN.IFM:
                case LINE_TOKEN.IFP:
                    var text = $"{Number} {Token.GetName()} {Expressions[0]?.ToString()}";

                    if (Expressions.Count >= 2)
                    {
                        text += $" THEN {Expressions[1]?.ToString()}";
                    }

                    if (Expressions.Count >= 3)
                    {
                        text += $" ELSE {Expressions[2]?.ToString()}";
                    }

                    return text;


                case LINE_TOKEN.ASSIGN:
                    return $"{Number} {Expressions[0].ToString()} = {Expressions[1].ToString()}";
                //LRUIZ:
                //Additions of raw lines, preproccessed by a real PARSER
                case LINE_TOKEN.RAWLINE:
                    return $"{Data.GetString()}";

                default:
                    Console.WriteLine(Token);
                    return string.Empty;
            }
        }


        #region Binary data

        public static byte[] GetLinePart(byte[] bytes, ref int offset,
            FileVersion version = FileVersion.Current,
            int nextPart = 0)
        {
            var i = offset;
            for (; bytes[i] != 255; ++i) ;
            if (nextPart != 0)
            {
                i = bytes[nextPart - 1] != 255 ? nextPart : nextPart - 1;
            }
            else
            {
                //--i;
            }

            var part = bytes.ToBytes(offset, i - offset);
            offset = i;

            return part;
        }






        const char Srt = '`';

        /* return true if c is a space or a tab*/
        private bool iswhite(char c)
        {
            
            return (c == ' ' || c == '\t' || c == Srt) ? true : false;

        }


        /* return true if c is a delimiter */
        private bool isdelim(char c)
       
        {
            string delimiters = " :!;,<>'*^=()[]";
            if (c == 9 || c == '\r' || c == 0) return true;
            return delimiters.Contains(c) ? true:false;

        }


        private List<Expression> GetExpressions(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current, LINE_TOKEN lineToken = 0,
            bool isTrace = false)
        {
            if (isTrace)
            {
                Console.WriteLine("----------------------------");
                Console.WriteLine(DebugUtilities.CompareBytes(bytes, bytes,
                    onlyDif: false, toText: false, offset: offset));
            }

            var expressions = new List<Expression>();

            while (offset < bytes.Length)
            {
                var byteType = ProgramCodeUtilities.GetByteType(bytes, offset);

                if (byteType == ProgramCodeUtilities.ByteType.Variable)
                {
                    if (isTrace)
                    {
                        Console.WriteLine($"IsVariable {offset}");
                    }
                    var expression = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    expressions.Add(expression);
                }
                else if (byteType == ProgramCodeUtilities.ByteType.Line)
                {
                    if (isTrace)
                    {
                        Console.WriteLine($"IsLine {offset}");
                    }
                    var token = (LINE_TOKEN)bytes.ToByte(ref offset);
                    var lineExpressions = GetExpressions(bytes, prg, ref offset, version, token, isTrace);
                    var expression = lineExpressions.Count > 1 ? new BinaryExpression(
                        lineExpressions[0],
                        lineExpressions[1],
                        (TYPE_TOKEN)token, FileVersion) :
                        lineExpressions[0];
                    expressions.Add(expression);
                }
                else if (byteType == ProgramCodeUtilities.ByteType.Function)
                {
                    if (isTrace)
                    {
                        Console.WriteLine($"IsFunction {offset}");
                    }
                    var token = (FUNCTION_TOKEN)bytes.ToByte(ref offset);
                    if ((byte)token == (byte)LINE_TOKEN.STOP)
                    {
                        var variable = new VariableExpression(bytes, prg, ref offset, FileVersion);
                        var expression = new UnaryExpression(variable, (TYPE_TOKEN)LINE_TOKEN.STOP, version);

                        expressions.Add(expression);
                    }
                    else if (expressions.Count == 0)
                    {
                        Console.WriteLine("expressions.Count = 0");
                        var temp = 0;
                        offset -= 1;
                        expressions.Add(new VariableExpression(bytes, prg, ref offset, FileVersion));
                        expressions.AddRange(
                            GetExpressions(bytes.ToBytes(ref offset, 3), prg, ref temp, FileVersion, lineToken));

                        var prevLastExpression = expressions[expressions.Count - 2];
                        var lastExpression = expressions[expressions.Count - 1];
                        expressions.RemoveAt(expressions.Count - 1);
                        expressions.RemoveAt(expressions.Count - 1);
                        var expression = new BinaryExpression(prevLastExpression, lastExpression, TYPE_TOKEN.DELIMITER, FileVersion);
                        expressions.Add(expression);
                    }
                    else
                    {
                        var expression = new FunctionExpression(token, FileVersion, expressions.ToArray());
                        expressions.Clear();
                        expressions.Add(expression);
                    }
                }
                else if (byteType == ProgramCodeUtilities.ByteType.Expression)
                {
                    if (isTrace)
                    {
                        Console.WriteLine($"IsExpression {offset}");
                    }
                    var type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    if (ProgramCodeUtilities.IsBinaryExpression(type))
                    {
                        var prevLastExpression = expressions[expressions.Count - 2];
                        var lastExpression = expressions[expressions.Count - 1];
                        expressions.RemoveAt(expressions.Count - 1);
                        expressions.RemoveAt(expressions.Count - 1);
                        var expression = new BinaryExpression(prevLastExpression, lastExpression, type, FileVersion);
                        expressions.Add(expression);
                    }
                    else
                    {
                        var lastExpression = expressions[expressions.Count - 1];
                        expressions.RemoveAt(expressions.Count - 1);
                        var expression = new UnaryExpression(lastExpression, type, FileVersion);
                        expressions.Add(expression);
                    }
                }
                else
                {
                    break;
                }
            }

            if (isTrace)
            {
                Console.WriteLine($"Result: {expressions.Count} expressions. Line token: {lineToken}");
                for (var i = 0; i < expressions.Count; ++i)
                {
                    Console.WriteLine($"Expression {i + 1}: {expressions[i].ToString()}");
                }
                Console.WriteLine("----------------------------");
                Console.WriteLine("");
            }

            return expressions;
        }

        private Expression ToExpression(byte[] bytes, Prg prg, int offset = 0,
            FileVersion version = FileVersion.Current, bool isTrace = false)
        {
            var expressions = GetExpressions(bytes, prg, ref offset, FileVersion, isTrace: isTrace);

            if (offset != bytes.Length || expressions.Count != 1)
            {
                Console.WriteLine($@"Bad part:
bytes: {DebugUtilities.CompareBytes(bytes, bytes, onlyDif: false, toText: false)}
offset: {offset}
bytes.Length: {bytes.Length}
expressions: {expressions.Count}
");
            }

            //One expression
            if (expressions.Count == 1)
            {
                return expressions[0];
            }

            return null;
        }

        private void FromASSIGN(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
        {
            Expressions.Add(new VariableExpression(bytes, prg, ref offset, FileVersion));

            var first = new VariableExpression(bytes, prg, ref offset, FileVersion);
            var second = new VariableExpression(bytes, prg, ref offset, FileVersion);
            var type = (TYPE_TOKEN)bytes.ToByte(ref offset);
            Expression expression = new BinaryExpression(first, second, type, FileVersion);

            //var temp = offset;
            var check = bytes.ToByte(ref offset);
            --offset;
            //Console.WriteLine($"{Number} {check} before");
            if (check != (byte)TYPE_TOKEN.NUMBER)
            {
                if (ProgramCodeUtilities.IsVariable(check))
                {
                    var third = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var type2 = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    expression = new BinaryExpression(expression, third, type2, FileVersion);
                }
                else if (ProgramCodeUtilities.IsFunction(check))
                {
                    var token = (FUNCTION_TOKEN)bytes.ToByte(ref offset);
                    expression = new FunctionExpression(token, FileVersion, expression);
                }

                //++offset;
                //check = (ExpressionType)bytes.ToByte(ref offset);
                //--offset;
                //Console.WriteLine($"{Number} {check} after");
            }

            Expressions.Add(expression);
        }

        private void FromIFM(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
        {
            var ifPart = GetLinePart(bytes, ref offset, FileVersion);
            Expressions.Add(ToExpression(ifPart, prg, 0, FileVersion));
            offset += 4;
            var thenPart = GetLinePart(bytes, ref offset, FileVersion);
            Expressions.Add(ToExpression(thenPart, prg, 0, FileVersion));
            offset += 1;
        }

        private void FromIF(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
        {
            var ifPart = GetLinePart(bytes, ref offset, FileVersion);
            Expressions.Add(ToExpression(ifPart, prg, 0, FileVersion));
            var check = bytes.ToByte(ref offset);
            if (check != 0xFF)
            {
                throw new OffsetException(offset, ifPart.Length);
            }
            var nextOffset = bytes.ToUInt16(ref offset);

            var thenPart = GetLinePart(bytes, ref offset, FileVersion, nextOffset);
            Expressions.Add(ToExpression(thenPart, prg, 0, FileVersion));
            if (bytes[offset] == 0xFF)
                offset += 1; //0xFF byte
            if (offset != nextOffset)
            {
                throw new OffsetException(offset, nextOffset);
            }

            return;
        }

        /// <summary>
        /// Raw Lines Constructor
        /// </summary>
        /// <remarks>Author: LRUIZ</remarks>

        static public byte[] RawLine(string line)
        {

            List<byte> returnvalue = new List<byte>();
            List<byte> Data = new List<byte>();
            byte Type, Token;
            short Number;

            Type = (byte)TYPE_TOKEN.NUMBER; //1 Byte
            returnvalue.Add((byte)Type);


            string[] separators = { " " };
            string[] LineParts = line.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            if (!LineParts.Any())
            {
                throw new Exception($"Not enough tokens in line: {line}");
            }

            if (String.IsNullOrEmpty(LineParts[0]))
            {
                Number = 0;
            }
            else
            {
                Number = Convert.ToInt16(LineParts[0]);
            }



            byte[] intBytes = BitConverter.GetBytes(Number);
            //if (BitConverter.IsLittleEndian)
            //    Array.Reverse(intBytes);
            if (intBytes.Count() < 2)
            {
                throw new Exception("Line Number less than 2 bytes");
            }
            byte[] result = intBytes;


            Console.WriteLine($"Converting {Number} to bytes[] : {result}");
            returnvalue.AddRange(result);


            switch (LineParts[1] ?? "RAW")
            {
                case "REM":
                    Token = (byte)LINE_TOKEN.REM;
                    break;
                //case "IF+":
                //    Token = (byte)LineToken.IFP;
                //    break;

                //case "IF-":
                //    Token = (byte)LineToken.IFM;
                //    break;
                //case "IF":
                //    Token = (byte)LineToken.IF;
                //    break;
                default:
                    Token = (byte)LINE_TOKEN.RAWLINE;
                    break;


            }
            returnvalue.Add(Token);


            //Number = bytes.ToInt16(ref offset); //2 Bytes
            int OffSet = (Token == (byte)LINE_TOKEN.RAWLINE ? 1 : 2);

            line = string.Join(" ", LineParts, OffSet, LineParts.Count() - OffSet);

            Data.AddRange(line.ToBytes());

            //Data = PRGReaderLibrary.BytesExtensions.ToBytes(line.ToBytes());
            byte size = (byte)Data.Count();

            returnvalue.Add(size);
            returnvalue.AddRange(Data);

            return returnvalue.ToArray();
        }




        public Line(byte[] bytes, Prg prg, ref int offset,
            FileVersion version = FileVersion.Current)
            : base(version)
        {
            Type = (TYPE_TOKEN)bytes.ToByte(ref offset); //1 Byte
            Number = bytes.ToInt16(ref offset); //2 Bytes
            Token = (LINE_TOKEN)bytes.ToByte(ref offset); //1 Byte


            //Offset is 4

            try
            {
                if (Number == 140) //8C 00
                {

                    var ifPart = GetLinePart(bytes, ref offset, FileVersion);
                    Expressions.Add(ToExpression(ifPart, prg, 0, FileVersion));
                    var check = bytes.ToByte(ref offset);
                    if (check != 0xFF)
                    {
                        throw new OffsetException(offset, ifPart.Length);
                    }
                    var nextOffset = bytes.ToUInt16(ref offset);

                    //Expressions.Add(new FunctionExpression(bytes, prg, ref offset, FileVersion));
                    //offset += 4;
                    //offset += 3;
                    //var type = (ExpressionType)bytes.ToByte(ref offset);
                    //var first = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    //var second = new FunctionExpression(bytes, prg, ref offset, FileVersion);
                    //Expressions.Add(new BinaryExpression(first, second, type, FileVersion));
                    //offset += 2;

                    var thenPart = GetLinePart(bytes, ref offset, FileVersion, nextOffset);
                    Expressions.Add(ToExpression(thenPart, prg, 0, FileVersion, isTrace: true));
                    if (bytes[offset] == 0xFF)
                        offset += 1; //0xFF byte
                    if (offset != nextOffset)
                    {
                        throw new OffsetException(offset, nextOffset);
                    }

                    return;
                }

                if (Number == 300) //2C 01
                {
                    Expressions.Add(new UnaryExpression(bytes, prg, ref offset, FileVersion));
                    offset += 3;
                    var type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    var first = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var expression = new VariableExpression(bytes, prg, ref offset, FileVersion) +
                         new VariableExpression(bytes, prg, ref offset, FileVersion);
                    expression.Type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    expression = new FunctionExpression(
                        (FUNCTION_TOKEN)bytes.ToByte(ref offset), FileVersion,
                        expression);
                    expression = first + expression;
                    expression.Type = type;
                    Expressions.Add(expression);
                    offset += 1;
                    return;
                }

                if (Number == 350) //5E 01
                {
                    var ifPart = GetLinePart(bytes, ref offset, FileVersion);
                    Expressions.Add(ToExpression(ifPart, prg, 0, FileVersion));
                    offset += 3;
                    var type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    var first = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var second = new UnaryExpression(bytes, prg, ref offset, FileVersion);
                    var third = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var four = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var type2 = (FUNCTION_TOKEN)bytes.ToByte(ref offset);
                    offset += 1;
                    var type3 = (FUNCTION_TOKEN)bytes.ToByte(ref offset);
                    offset += 1;
                    Expression expression = new FunctionExpression(type2, FileVersion, third, four);
                    expression = new FunctionExpression(type3, FileVersion, second, expression);
                    expression = new BinaryExpression(first, expression, type, FileVersion);
                    Expressions.Add(expression);
                    offset += 1;
                    return;
                }

                if (Number == 360) //68 01
                {
                    var ifPart = GetLinePart(bytes, ref offset, FileVersion);
                    Expressions.Add(ToExpression(ifPart, prg, 0, FileVersion));
                    offset += 3;
                    var type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    var first = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var second = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var third = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var type2 = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    var four = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    var type3 = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    Expression expression = new BinaryExpression(second, third, type2, FileVersion);
                    expression = new BinaryExpression(expression, four, type3, FileVersion);
                    expression = new BinaryExpression(first, expression, type, FileVersion);
                    Expressions.Add(expression);
                    offset += 5;
                    type = (TYPE_TOKEN)bytes.ToByte(ref offset);
                    first = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    second = new VariableExpression(bytes, prg, ref offset, FileVersion);
                    expression = new BinaryExpression(first, second, type, FileVersion);
                    Expressions.Add(expression);
                    offset += 1;
                    return;
                }

                switch (Token)
                {
                    case LINE_TOKEN.IF:
                        FromIF(bytes, prg, ref offset, FileVersion);
                        break;

                    case LINE_TOKEN.IFM:
                        FromIFM(bytes, prg, ref offset, FileVersion);
                        break;

                    case LINE_TOKEN.ASSIGN:
                        FromASSIGN(bytes, prg, ref offset, FileVersion);
                        break;

                    case LINE_TOKEN.REM:
                    case LINE_TOKEN.RAWLINE:
                    default:
                        var size = bytes.ToByte(ref offset);
                        Data = bytes.ToBytes(ref offset, size);
                        break;
                }

                if (Number == 380) //7C 01
                {
                    offset += 115;
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine($@"Exception on line: 
Type: {Type}
Number: {Number}
Token: {Token}
{exception.Message}");
                throw;
            }
        }

        public byte[] ToBytes()
        {
            var bytes = new List<byte>();

            return bytes.ToArray();
        }

        #endregion

    }

    public class ProgramCode : BaseCode, IBinaryObject
    {
        public int Version { get; set; }
        public List<Line> Lines { get; set; } = new List<Line>();

        public override string ToString() => string.Join(Environment.NewLine,
            Lines.Select(line => line.ToString()));

        public ProgramCode(byte[] code = null, FileVersion version = FileVersion.Current)
            : base(2000, version)
        {
            Code = code;
        }


        #region Binary data

        public static int GetCount(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 16;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        public static int GetSize(FileVersion version = FileVersion.Current)
        {
            switch (version)
            {
                case FileVersion.Current:
                    return 2000;

                default:
                    throw new FileVersionNotImplementedException(version);
            }
        }

        /// <summary>
        /// FileVersion.Current - need 2000 bytes
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="offset"></param>
        /// <param name="version"></param>
        public ProgramCode(byte[] bytes, Prg prg, int offset = 0,
            FileVersion version = FileVersion.Current)
            : base(bytes, 2000, offset, version)
        {
            var maxSize = GetSize(FileVersion);

            Version = bytes.ToInt16(ref offset);
            while (offset < maxSize)
            {
                //Console.WriteLine($"{offset}: Line {Lines.Count}");
                var line = new Line(bytes, prg, ref offset, FileVersion);

                Lines.Add(line);
            }

            offset = 2000;
            CheckOffset(offset, GetSize(FileVersion));
        }

        /// <summary>
        /// FileVersion.Current - 2000 bytes
        /// </summary>
        /// <returns></returns>
        public new byte[] ToBytes()
        {
            var bytes = base.ToBytes();

            CheckSize(bytes.Length, GetSize(FileVersion));

            return bytes;
        }

        #endregion

    }


   


    struct variable_table
    {
        char[] name; //= new char [20];
        char[] label; // = new char[9];
        char type;
        char var_type;
        int l;
        int c;
        byte network;
        byte sub_panel;
        char panel;
        char point_type;
        //char num_point;
        short num_point;
    };

    struct buf_str
    {
        int v;
        char[] var;//[20];
        float fvar;
        char[] op;//[10];
    };






    
    class SymbolTable
    {
        
        Dictionary<string, byte> FTABLE = new Dictionary<string, byte>();
        Dictionary<string, byte> CTABLE = new Dictionary<string, byte>();

        /// <summary>
        /// Returns token byte from function name
        /// </summary>
        /// <param name="name">function name</param>
        /// <returns>byte (token)</returns>
        public byte GetFunctionToken(string name)
        {
            byte value = 0;
            if(!FTABLE.TryGetValue(name, out value))
            {
                throw new NotImplementedException(@"Token ""{name}"" not implemented.");
            }
            return value;
        }

        /// <summary>
        /// Return token byte from command name
        /// </summary>
        /// <param name="name">command name</param>
        /// <returns>byte (token)</returns>
        public byte GetCommandToken(string name)
        {
            byte value = 0;
            if (!CTABLE.TryGetValue(name, out value))
            {
                throw new NotImplementedException(@"Token ""{name}"" not implemented.");
            }
            return value;
        }

        /// <summary>
        /// Returns name of function from token byte
        /// </summary>
        /// <param name="token">token number (byte)</param>
        /// <returns>function name (string)</returns>
        public string GetFunctionName(byte token)
        {
            string TokenName = "";

            TokenName = FTABLE.Keys.Where(k => FTABLE[k] == token).ToString();
            return TokenName;
        }

        /// <summary>
        /// Returns name of command from token byte
        /// </summary>
        /// <param name="token">token number (byte)</param>
        /// <returns>command name (string)</returns>
        public string GetCommandName(byte token)
        {
            string TokenName = "";

            TokenName = CTABLE.Keys.Where(k => CTABLE[k] == token).ToString();
            return TokenName;
        }


        SymbolTable ()
        {

            //Functions
            FTABLE.Add("ABS", (byte)FUNCTION_TOKEN.ABS);
            FTABLE.Add("AVG", (byte)FUNCTION_TOKEN.AVG);
            FTABLE.Add("COM1", (byte)FUNCTION_TOKEN.COM_1);
            FTABLE.Add("CONPROP", (byte)FUNCTION_TOKEN.CONPROP);
            FTABLE.Add("CONRATE", (byte)FUNCTION_TOKEN.CONRATE);
            FTABLE.Add("CONRESET", (byte)FUNCTION_TOKEN.CONRESET);
            FTABLE.Add("CLEARPORT", (byte)FUNCTION_TOKEN.CLEARPORT);
            FTABLE.Add("DOW", (byte)FUNCTION_TOKEN.DOW);
            FTABLE.Add("DOM", (byte)FUNCTION_TOKEN.DOM);
            FTABLE.Add("DOY", (byte)FUNCTION_TOKEN.DOY);
            FTABLE.Add("MOY", (byte)FUNCTION_TOKEN.MOY);
            FTABLE.Add("INPUT", (byte)FUNCTION_TOKEN.INKEYD);
            FTABLE.Add("INT", (byte)FUNCTION_TOKEN._INT);
            FTABLE.Add("INTERVAL", (byte)FUNCTION_TOKEN.INTERVAL);
            FTABLE.Add("LN", (byte)FUNCTION_TOKEN.LN);
            FTABLE.Add("LN-1", (byte)FUNCTION_TOKEN.LN_1);
            FTABLE.Add("LN_1", (byte)FUNCTION_TOKEN.LN_1);
            FTABLE.Add("MAX", (byte)FUNCTION_TOKEN.MAX);
            FTABLE.Add("MIN", (byte)FUNCTION_TOKEN.MIN);
            FTABLE.Add("OUTPUT", (byte)FUNCTION_TOKEN.OUTPUTD);
            FTABLE.Add("POWER-LOSS", (byte)FUNCTION_TOKEN.POWER_LOSS);
            FTABLE.Add("POWER_LOSS", (byte)FUNCTION_TOKEN.POWER_LOSS);
            FTABLE.Add("SCANS", (byte)FUNCTION_TOKEN.SCANS);
            FTABLE.Add("SQR", (byte)FUNCTION_TOKEN.SQR);
            FTABLE.Add("STATUS", (byte)FUNCTION_TOKEN._Status);
            FTABLE.Add("RUNTIME", (byte)FUNCTION_TOKEN.RUNTIME);
            FTABLE.Add("TBL", (byte)FUNCTION_TOKEN.TBL);
            FTABLE.Add("TIME", (byte)FUNCTION_TOKEN.TIME);
            FTABLE.Add("TIME_FORMAT", (byte)FUNCTION_TOKEN.TIME_FORMAT);
            FTABLE.Add("TIME-ON", (byte)FUNCTION_TOKEN.TIME_ON);
            FTABLE.Add("TIME_ON", (byte)FUNCTION_TOKEN.TIME_ON);
            FTABLE.Add("TIME-OFF", (byte)FUNCTION_TOKEN.TIME_OFF);
            FTABLE.Add("TIME_OFF", (byte)FUNCTION_TOKEN.TIME_OFF);
            FTABLE.Add("WR-ON", (byte)FUNCTION_TOKEN.WR_ON);
            FTABLE.Add("WR_ON", (byte)FUNCTION_TOKEN.WR_ON);
            FTABLE.Add("WR-OFF", (byte)FUNCTION_TOKEN.WR_OFF);
            FTABLE.Add("WR_OFF", (byte)FUNCTION_TOKEN.WR_OFF);
            FTABLE.Add("SENSOR-ON", (byte)LINE_TOKEN.SENSOR_ON);
            FTABLE.Add("SENSOR_ON", (byte)LINE_TOKEN.SENSOR_ON);
            FTABLE.Add("SENSOR-OFF", (byte)LINE_TOKEN.SENSOR_OFF);
            FTABLE.Add("SENSOR_OFF", (byte)LINE_TOKEN.SENSOR_OFF);
            FTABLE.Add("UNACK", (byte)FUNCTION_TOKEN.UNACK);
            FTABLE.Add("USER-A", (byte)LINE_TOKEN.USER_A);
            FTABLE.Add("USER_A", (byte)LINE_TOKEN.USER_A);
            FTABLE.Add("USER-B", (byte)LINE_TOKEN.USER_B);
            FTABLE.Add("USER_B", (byte)LINE_TOKEN.USER_B);
            FTABLE.Add("NOT", (byte)TYPE_TOKEN.NOT);
            FTABLE.Add("SUNDAY", (byte)FUNCTION_TOKEN.SUN);
            FTABLE.Add("MONDAY", (byte)FUNCTION_TOKEN.MON);
            FTABLE.Add("TUESDAY", (byte)FUNCTION_TOKEN.TUE);
            FTABLE.Add("WEDNESDAY", (byte)FUNCTION_TOKEN.WED);
            FTABLE.Add("THURSDAY", (byte)FUNCTION_TOKEN.THU);
            FTABLE.Add("FRIDAY", (byte)FUNCTION_TOKEN.FRI);
            FTABLE.Add("SATURDAY", (byte)FUNCTION_TOKEN.SAT);
            FTABLE.Add("JANUARY", (byte)FUNCTION_TOKEN.JAN);
            FTABLE.Add("FEBRUARY", (byte)FUNCTION_TOKEN.FEB);
            FTABLE.Add("MARCH", (byte)FUNCTION_TOKEN.MAR);
            FTABLE.Add("APRIL", (byte)FUNCTION_TOKEN.APR);
            FTABLE.Add("MAY", (byte)FUNCTION_TOKEN.MAY);
            FTABLE.Add("JUNE", (byte)FUNCTION_TOKEN.JUN);
            FTABLE.Add("JULY", (byte)FUNCTION_TOKEN.JUL);
            FTABLE.Add("AUGUST", (byte)FUNCTION_TOKEN.AUG);
            FTABLE.Add("SEPTEMBER", (byte)FUNCTION_TOKEN.SEP);
            FTABLE.Add("OCTOBER", (byte)FUNCTION_TOKEN.OCT);
            FTABLE.Add("NOVEMBER", (byte)FUNCTION_TOKEN.NOV);
            FTABLE.Add("DECEMBER", (byte)FUNCTION_TOKEN.DEC);
            FTABLE.Add("", (byte)LINE_TOKEN.ENDPRG);
            

            //LOCAL_POINT_PRG = 156,
            //CONST_VALUE_PRG,
            //REMOTE_POINT_PRG

            // Commands

            CTABLE.Add("ALARM", (byte)LINE_TOKEN.Alarm);
            CTABLE.Add("ALARM-AT", (byte)LINE_TOKEN.ALARM_AT);
            CTABLE.Add("ALARM_AT", (byte)LINE_TOKEN.ALARM_AT);
            CTABLE.Add("CALL", (byte)LINE_TOKEN.CALLB);
            CTABLE.Add("CLEAR", (byte)LINE_TOKEN.CLEARX);
            CTABLE.Add("CLOSE", (byte)LINE_TOKEN.CLOSE);
            CTABLE.Add("DALARM", (byte)LINE_TOKEN.DALARM);
            CTABLE.Add("DECLARE", (byte)LINE_TOKEN.DECLARE);
            CTABLE.Add("DISABLE", (byte)LINE_TOKEN.DISABLEX);
            CTABLE.Add("ENABLE", (byte)LINE_TOKEN.ENABLEX);
            CTABLE.Add("END", (byte)LINE_TOKEN.ENDPRG);
            CTABLE.Add("FOR", (byte)LINE_TOKEN.FOR);
            CTABLE.Add("TO", (byte)LINE_TOKEN.TO);
            CTABLE.Add("STEP", (byte)LINE_TOKEN.STEP);
            CTABLE.Add("GOSUB", (byte)LINE_TOKEN.GOSUB);
            CTABLE.Add("GOTO", (byte)LINE_TOKEN.GOTO);
            CTABLE.Add("HANGUP", (byte)LINE_TOKEN.HANGUP);
            CTABLE.Add("IF", (byte)LINE_TOKEN.IF);
            CTABLE.Add("IF+", (byte)LINE_TOKEN.IFP);
            CTABLE.Add("IF-", (byte)LINE_TOKEN.IFM);
            CTABLE.Add("THEN", (byte)LINE_TOKEN.THEN);
            CTABLE.Add("ELSE", (byte)LINE_TOKEN.ELSE);
            CTABLE.Add("LET", (byte)LINE_TOKEN.LET);
            CTABLE.Add("MOD", (byte)TYPE_TOKEN.MOD);
            CTABLE.Add("NEXT", (byte)LINE_TOKEN.NEXT);
            CTABLE.Add("ON", (byte)LINE_TOKEN.ON);
            CTABLE.Add("ON-ALARM", (byte)LINE_TOKEN.ON_ALARM);
            CTABLE.Add("ON_ALARM", (byte)LINE_TOKEN.ON_ALARM);
            CTABLE.Add("ON-ERROR", (byte)LINE_TOKEN.ON_ERROR);
            CTABLE.Add("ON_ERROR", (byte)LINE_TOKEN.ON_ERROR);
            CTABLE.Add("OPEN", (byte)LINE_TOKEN.OPEN);
            CTABLE.Add("PHONE", (byte)LINE_TOKEN.PHONE);
            CTABLE.Add("PRINT", (byte)LINE_TOKEN.PRINT);
            CTABLE.Add("PRINT-AT", (byte)LINE_TOKEN.PRINT_AT);
            CTABLE.Add("PRINT_AT", (byte)LINE_TOKEN.PRINT_AT);
            CTABLE.Add("REM", (byte)LINE_TOKEN.REM);
            CTABLE.Add("REMOTE-GET", (byte)LINE_TOKEN.REMOTE_GET);
            CTABLE.Add("REMOTE_GET", (byte)LINE_TOKEN.REMOTE_GET);
            CTABLE.Add("REMOTE-SET", (byte)LINE_TOKEN.REMOTE_SET);
            CTABLE.Add("REMOTE_SET", (byte)LINE_TOKEN.REMOTE_SET);
            CTABLE.Add("RETURN", (byte)LINE_TOKEN.RETURN);
            CTABLE.Add("RUN-MACRO", (byte)LINE_TOKEN.RUN_MACRO);
            CTABLE.Add("RUN_MACRO", (byte)LINE_TOKEN.RUN_MACRO);
            CTABLE.Add("SET-PRINTER", (byte)LINE_TOKEN.SET_PRINTER);
            CTABLE.Add("SET_PRINTER", (byte)LINE_TOKEN.SET_PRINTER);
            CTABLE.Add("START", (byte)LINE_TOKEN.STARTPRG);
            CTABLE.Add("STOP", (byte)LINE_TOKEN.STOP);
            CTABLE.Add("WAIT", (byte)LINE_TOKEN.WAIT);
            CTABLE.Add("AND", (byte)(byte)TYPE_TOKEN.AND);
            CTABLE.Add("OR", (byte)TYPE_TOKEN.OR);
            CTABLE.Add("XOR", (byte)TYPE_TOKEN.XOR);
            CTABLE.Add("DIM", (byte)LINE_TOKEN.DIM);
            CTABLE.Add("INTEGER", (byte)PCODE_CONST.INTEGER_TYPE);
            CTABLE.Add("STRING", (byte)PCODE_CONST.STRING_TYPE);
            CTABLE.Add("BYTE", (byte)PCODE_CONST.BYTE_TYPE);
            CTABLE.Add("FLOAT", (byte)PCODE_CONST.FLOAT_TYPE);
            CTABLE.Add("LONG", (byte)PCODE_CONST.LONG_TYPE);
            CTABLE.Add("", (byte)LINE_TOKEN.ENDPRG);/* marks the end of the table */


        }
    }
 
}