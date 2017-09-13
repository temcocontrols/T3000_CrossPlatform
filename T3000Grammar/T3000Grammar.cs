namespace T3000
{
    using System;
    using System.Collections.ObjectModel;
    using Irony.Parsing;
    using Irony.Interpreter.Ast;

    [Language("Control Basic", "1.0", "T3000 Programming Language")]
    public class T3000Grammar : Grammar
    {
        //public static readonly ReadOnlyCollection<string> Functions = 
        //    new ReadOnlyCollection<string>(
        //    new [] 
        //    {
        //        "INTERVAL", "COM1", "ABS", "MAX", "MIN"
        //    }
        //);

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

            //Non Control Points Identifiers TESTED
            //Validated to be Non Keywords.
            //Only UpperCase
            var Identifier = new IdentifierTerminal("Identifier", ".-_");
            Identifier.CaseRestriction = CaseRestriction.AllUpper;
            Identifier.AllFirstChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
            Identifier.Options = IdOptions.IsNotKeyword;

            var LoopVariable = new IdentifierTerminal("LoopVariable");
            LoopVariable.AllFirstChars = "ABCDEFGHIJK";
            LoopVariable.Options = IdOptions.IsNotKeyword;

            var LocalVariable = new IdentifierTerminal("LocalVariable");
            LoopVariable.AllFirstChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            LoopVariable.Options = IdOptions.IsNotKeyword;

            var VARS = new IdentifierTerminal("VARS");
            VARS.AddPrefix("VAR", IdOptions.NameIncludesPrefix);


            //Puctuation
            var PARIZQ = ToTerm("(");
            var PARDER = ToTerm(")");
            var CommandSeparator = ToTerm(";");
            var Comma = ToTerm(",");

            //Operators
            //Comparisson Operators
            var AssignOp = ToTerm("=");
            var LT = ToTerm("<");
            var GT = ToTerm(">");
            var LTE = ToTerm("<=");
            var GTE = ToTerm(">=");
            var NEQ = ToTerm("<>");
            var EQ = ToTerm("=");

            var NOT = ToTerm("NOT");

            //Logical Operators
            var AND = ToTerm("AND");
            var XOR = ToTerm("XOR");
            var OR = ToTerm("OR");

            //Arithmetic Operators
            var SUM = ToTerm("+");
            var SUB = ToTerm("-");
            var MUL = ToTerm("*");
            var DIV = ToTerm("/");
            var EXP = ToTerm("^");
            var MOD = ToTerm("MOD");



            // 2. Non-terminals

            var CONTROL_BASIC = new NonTerminal("CONTROL_BASIC", typeof(StatementListNode));
            var SentencesSequence = new NonTerminal("SentencesSequence");
            var Sentence = new NonTerminal("Sentence");
            var DECLAREStatement = new NonTerminal("DECLAREStatement");
            var ENDStatement = new NonTerminal("ENDStatement");
            var ProgramLine = new NonTerminal("ProgramLine");
            var Subroutine = new NonTerminal("Subroutine");
            var SubroutineSentences = new NonTerminal("SubRoutineSentences");

            var LineNumber = new NonTerminal("LineNumber");
            var EmptyLine = new NonTerminal("EmptyLine");

            var Statement = new NonTerminal("Statement");
            var Comment = new NonTerminal("Comment");
            var Commands = new NonTerminal("Commands");

            //TODO : Add all commands as terms
            var Command = new NonTerminal("Command");
            var NextCommand = new NonTerminal("NextCommand");

        }   //TODO: Create Assignment statement
            var Assignment = new NonTerminal("Assignment");

            //TODO: Add all branch statements
            var Branch = new NonTerminal("Branch");

            //var Loop = new NonTerminal("Loop");
            var FOR = new NonTerminal("FOR");
            var ENDFOR = new NonTerminal("ENDFOR");
            var STEPFOR = new NonTerminal("STEPFOR");

            //Operators
            var LogicOps = new NonTerminal("LogicOps");
            var ArithmeticOps = new NonTerminal("ArithmeticOps");
            var ComparisonOps = new NonTerminal("ComparisonOps");

            var UnaryOps = new NonTerminal("UnaryOps");
            var BinaryOps = new NonTerminal("BinaryOps");

            var Designator = new NonTerminal("Designator");
            var RemoteDesignator = new NonTerminal("RemoteDesignator");

          

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

            // LISTAS 
            var IdentifierList = new NonTerminal("IdentifierList");
            var LoopVariableList = new NonTerminal("LoopVariableList");
            // 3. BNF rules
            //CONTROL_BASIC ::= SentencesSequence | SubRoutine
            CONTROL_BASIC.Rule = SentencesSequence | Subroutine;
            //SubRoutine ::= (LineNumber DECLARE EndLine SentencesSequence LineNumber END)
            Subroutine.Rule = DECLAREStatement + SubroutineSentences;

            //DECLARE::= 'DECLARE' Identifier(',' Identifier) *
            DECLAREStatement.Rule = LineNumber + ToTerm("DECLARE") + IdentifierList + NewLine;
            SubroutineSentences.Rule = SentencesSequence;
            ENDStatement.Rule = LineNumber + ToTerm("END");
            IdentifierList.Rule = MakePlusRule(IdentifierList, Comma, Identifier);
            //SentencesSequence ::= ProgramLine+
            SentencesSequence.Rule = MakeStarRule(SentencesSequence, ProgramLine);
            //ProgramLine ::= EmptyLine | (LineNumber Sentence EndLine)
            ProgramLine.Rule = EmptyLine | (LineNumber + Sentence + NewLine);
            ProgramLine.NodeCaptionTemplate = "#{0} #{1}";
            //EmptyLine ::= LineNumber? EndLine
            EmptyLine.Rule = LineNumber.Q() + NewLine;

            //Sentence ::= (Comment | (Commands| Assignment | Branch | Loop) Comment?)
            Sentence.Rule = Comment | ((ToTerm("END") | Commands | Assignment | Branch | FOR | ENDFOR) + Comment.Q());
            //Statement.NodeCaptionTemplate = "#{0} #{1}";
            //Comment ::= 'REM' StringLiteral+
            Comment.Rule = ToTerm("REM") + Text;
            Comment.NodeCaptionTemplate = "REM #{1}";
            //Commands::= Command (';' Command) *
            Commands.Rule = MakeStarRule(Command, CommandSeparator, Command);

            Command.Rule = "Command";
            Assignment.Rule = "Assignment";
            Branch.Rule = "Branch";

            //Loop::= FOR SentencesSequence ENDFOR
            //FOR::= 'FOR' LoopVariable AssignOp Integer 'TO' Integer('STEP' Integer) ? EndLine
            //ENDFOR::= 'NEXT'(LoopVariable(',' LoopVariable) *) ?
            //Loop.Rule  = FOR + SentencesSequence | ENDFOR ;
            FOR.Rule = ToTerm("FOR") + LoopVariable + AssignOp + IntegerNumber + ToTerm("TO") + IntegerNumber + STEPFOR;
            STEPFOR.Rule = Empty | (ToTerm("STEP") + IntegerNumber);
            ENDFOR.Rule = ToTerm("NEXT") + LoopVariableList;
            LoopVariableList.Rule = MakePlusRule(LoopVariableList, Comma, LoopVariable);


            LogicOps.Rule = AND | OR | XOR;
            ArithmeticOps.Rule = SUM | SUB | MUL | DIV | MOD | EXP;
            ComparisonOps.Rule = EQ | NEQ | GT | LT | LTE | GTE;

            UnaryOps.Rule  = NOT;
            BinaryOps.Rule = ArithmeticOps | ComparisonOps | LogicOps;
            

            LineNumber.Rule = IntegerNumber;





          

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

 
         

            //Set grammar root 
            Root = CONTROL_BASIC;


            //EXample
            ////jarray.Rule = MakeStarRule(jarray, comma, jvalue);

            RegisterBracePair(PARIZQ.ToString(), PARDER.ToString());
            
            // 4. Operators precedence
            RegisterOperators(100, Associativity.Right, EXP);
            RegisterOperators(90, MUL);
            RegisterOperators(90, DIV);
            RegisterOperators(80, MOD);
            RegisterOperators(70, SUM);
            RegisterOperators(70, SUB);

            RegisterOperators(60, NEQ);
            RegisterOperators(60, LT);
            RegisterOperators(60, GT);
            RegisterOperators(60, LTE);
            RegisterOperators(60, GTE);            
            RegisterOperators(60, EQ);

            RegisterOperators(55, Associativity.Right, NOT);
            RegisterOperators(50, AND);
            RegisterOperators(50, OR);
            RegisterOperators(50, XOR);

            RegisterOperators(10, AssignOp);



            //// 5. Punctuation and transient terms
            MarkPunctuation( PARIZQ.ToString()  , PARDER.ToString()  ,CommandSeparator.ToString() );
            

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