namespace T3000
{
    using System;
    using System.Collections.ObjectModel;
    using Irony.Parsing;
    using Irony.Interpreter.Ast;

    [Language("Control Basic", "1.0", "T3000 Programming Language")]
    public class T3000Grammar : Grammar
    {
        public static readonly ReadOnlyCollection<string> Functions = 
            new ReadOnlyCollection<string>(
            new [] 
            {
                "INTERVAL", "COM1", "ABS", "MAX", "MIN"
            }
        );

        public T3000Grammar() :
            base(caseSensitive: true) //Changed, Control Basic is Case Sensitive: SET-PRINTER vs Set-Printer
        {
            // 1. Terminals
            var Text = new FreeTextLiteral("Text",
                FreeTextOptions.AllowEmpty |
                FreeTextOptions.AllowEof |
                FreeTextOptions.IncludeTerminator, Environment.NewLine);
            //var String = new StringLiteral("String", "'", StringOptions.AllowsAllEscapes);
            var Number = new NumberLiteral("Number");
            var IntegerNumber = new NumberLiteral("IntegerNumber", NumberOptions.IntOnly);
            //var Space = new RegexBasedTerminal("Space", "\\s+");
            var Time = new TimeTerminal("Time");//new DataLiteralBase("Time", TypeCode.DateTime);
            var Identifier = new IdentifierTerminal("Identifier"); //, "._", "1234567890");

            //Starting with primitive Terminals
            var NonZeroDigit = new RegexBasedTerminal("[1-9]");
            var SingleDigit = new RegexBasedTerminal("[0-9]");
            
            var Letter = new RegexBasedTerminal("[A-Z]");
            var LoopVariable = new RegexBasedTerminal("[A-K]");
            var StringLiteral = new FreeTextLiteral("Text",
                FreeTextOptions.AllowEmpty |
                FreeTextOptions.AllowEof |
                FreeTextOptions.IncludeTerminator, Environment.NewLine);
            var CommandSeparator = ToTerm(";");
            var Comma = ToTerm(",");

            // 2. Non-terminals

            var CONTROL_BASIC = new NonTerminal("CONTROL_BASIC", typeof(StatementListNode));
            var SentencesSequence = new NonTerminal("SentencesSequence");
            var Sentence = new NonTerminal("Sentence");
            var DECLAREStatement = new NonTerminal("DECLAREStatement");
            var ENDStatement = new NonTerminal("ENDStatement");
            var ProgramLine = new NonTerminal("ProgramLine");
            var Subroutine = new NonTerminal("Subroutine");
            var LineNumber = new NonTerminal("LineNumber");
            var EmptyLine = new NonTerminal("EmptyLine");
            
            var Statement = new NonTerminal("Statement");
            var Comment = new NonTerminal("Comment");
            var Commands = new NonTerminal("Commands");
            var Command = new NonTerminal("Command");
            var NextCommand = new NonTerminal("NextCommand");
            
            var Assignment = new NonTerminal("Assignment");
            var Branch = new NonTerminal("Branch");
            var Loop = new NonTerminal("Loop");

            //var CodeLine = new NonTerminal("CodeLine");
            //var Term = new NonTerminal("Term");

            ////Lines
            //var RemLine = new NonTerminal("RemLine");
            //var IfLine = new NonTerminal("IfLine", typeof(IfNode));
            //var AssignLine = new NonTerminal("AssignLine", typeof(AssignmentNode));

            ////Expressions
            //var Expression = new NonTerminal("Expression");
            //var ParentExpression = new NonTerminal("ParentExpression");
            //var UnaryExpression = new NonTerminal("UnaryExpression", typeof(UnaryOperationNode));
            //var FunctionExpression = new NonTerminal("FunctionExpression", typeof(FunctionCallNode));
            //var BinaryExpression = new NonTerminal("BinaryExpression", typeof(BinaryOperationNode));

            ////Operators
            //var UnaryOperator = new NonTerminal("UnaryOperator");
            //var FunctionOperator = new NonTerminal("FunctionOperator", typeof(FunctionDefNode));
            //var BinaryOperator = new NonTerminal("BinaryOperator", "operator");
            //var AssignmentOperator = new NonTerminal("AssignmentOperator", "assignment operator");


            var IdentifierList = new NonTerminal("IdentifierList");
            
            // 3. BNF rules
            //CONTROL_BASIC ::= SentencesSequence | SubRoutine
            CONTROL_BASIC.Rule = SentencesSequence | Subroutine;
            //SubRoutine ::= (LineNumber DECLARE EndLine SentencesSequence LineNumber END)
            Subroutine.Rule = DECLAREStatement + SentencesSequence + ENDStatement ;
            //DECLARE::= 'DECLARE' Identifier(',' Identifier) *
            DECLAREStatement.Rule = LineNumber + ToTerm("DECLARE") + IdentifierList + NewLine;
            ENDStatement.Rule = LineNumber + ToTerm("END") + NewLine;
            IdentifierList.Rule = MakePlusRule(IdentifierList, Comma, Identifier);
           //SentencesSequence ::= ProgramLine+
           SentencesSequence.Rule = MakeStarRule(SentencesSequence, ProgramLine);
            //ProgramLine ::= EmptyLine | (LineNumber Sentence EndLine)
            ProgramLine.Rule = EmptyLine | (LineNumber + Sentence + NewLine);

            //EmptyLine ::= LineNumber? EndLine
            EmptyLine.Rule = LineNumber.Q() + NewLine;

            //Sentence ::= (Comment | (Commands| Assignment | Branch | Loop) Comment?)
            Sentence.Rule = Comment | ( Commands  | Assignment | Branch | Loop ) +  Comment.Q();
            //Statement.NodeCaptionTemplate = "#{0} #{1}";
            //Comment ::= 'REM' StringLiteral+
            Comment.Rule = ToTerm("REM") + StringLiteral;
            //Commands::= Command (';' Command) *
            Commands.Rule = MakeStarRule(Command, CommandSeparator, Command);

            Command.Rule = "Command";
            Assignment.Rule  = "Assignment";
            Branch.Rule  = "Branch";
            Loop.Rule  = "Loop";
            
            LineNumber.Rule = IntegerNumber;
          
           
            
           
            
            //CodeLine.Rule =
            //    RemLine |
            //    IfLine |
            //    AssignLine;
            //Term.Rule = Number | ParentExpression | Identifier | Time;
            //Term.NodeCaptionTemplate = "#{0}";

            ////Lines
            //RemLine.Rule = "REM" + Text;
            //RemLine.NodeCaptionTemplate = "REM #{1}";
            //IfLine.Rule = "IF" + 
            //    //CustomActionHere((i, j) => i.AddTrace("")) + 
            //    Expression + "THEN" + Expression |
            //    //"IF" + PreferShiftHere() + "-" + Expression + "THEN" + Expression |
            //    "IF" + Expression + "THEN" + Expression + PreferShiftHere() + "ELSE" + Expression;
            //IfLine.NodeCaptionTemplate = "IF #{1} THEN #{3}";
            //AssignLine.Rule = Identifier + AssignmentOperator + Expression;
            //AssignLine.NodeCaptionTemplate = "#{0} = #{2}";

            ////Expressions
            //Expression.Rule = Term | UnaryExpression | 
            //    FunctionExpression | BinaryExpression | 
            //    AssignLine;
            //Expression.NodeCaptionTemplate = "#{0}";
            //ParentExpression.Rule = "(" + Expression + ")";
            //ParentExpression.NodeCaptionTemplate = "(#{1})";
            //UnaryExpression.Rule = UnaryOperator + Term;
            //UnaryExpression.NodeCaptionTemplate = "#{0} #{1}";
            //BinaryExpression.Rule = Expression + BinaryOperator + Expression;
            //BinaryExpression.NodeCaptionTemplate = "#{0} #{1} #{2}";
            //FunctionExpression.Rule = FunctionOperator + "(" + Expression + ")";
            //FunctionExpression.NodeCaptionTemplate = "#{0}( #{2} )";

            ////Operators
            //UnaryOperator.Rule = ToTerm("+") | "-" |
            //    "NOT" |
            //    "STOP";
            //UnaryOperator.NodeCaptionTemplate = "#{0}";
            //FunctionOperator.Rule = ToTerm("TIME") + "-" + "ON";
            //foreach (var function in Functions)
            //{
            //    FunctionOperator.Rule |= function;
            //}

            //FunctionOperator.NodeCaptionTemplate = "#{0}";
            //BinaryOperator.Rule = ToTerm(",") |
            //    "AND" | "OR" |
            //    "<" | ">" |
            //    "+" | "-" |
            //    "*" | "/" |
            //    "**";
            //BinaryOperator.NodeCaptionTemplate = "#{0}";
            //AssignmentOperator.Rule = ToTerm("=") | 
            //    "+=" | "-=" | 
            //    "*=" | "/=";
            //AssignmentOperator.NodeCaptionTemplate = "#{0}";

            //Set grammar root 
            Root = CONTROL_BASIC ;

            //// 4. Operators precedence
            //RegisterOperators(1, ",");
            ////jarray.Rule = MakeStarRule(jarray, comma, jvalue);
            //RegisterOperators(2, "AND", "OR");
            //RegisterOperators(3, "<", ">");
            //RegisterOperators(4, "+", "-");
            //RegisterOperators(5, "*", "/");
            //RegisterOperators(6, Associativity.Right, "**");

            //// 5. Punctuation and transient terms
            MarkPunctuation("(", ")",CommandSeparator.ToString() );
            //RegisterBracePair("(", ")");

            //MarkTransient(CodeLine, ProgramLine, 
            //    Term, Expression,
            //    BinaryOperator, UnaryOperator, 
            //    AssignmentOperator,//FunctionOperator, 
            //    ParentExpression);

            LanguageFlags = 
                //LanguageFlags.CreateAst | 
                LanguageFlags.NewLineBeforeEOF;

            #region Define Keywords

            //??
            //MarkReservedWords("");

            #endregion
        }
    }
}