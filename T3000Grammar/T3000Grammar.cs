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

            //RegEx Tested Strings, for ending valid Control Points
            string UPTO128 = "12[0-8]|1[0-1][0-9]|[1-9][0-9]?";
            string UPTO96 = "9[0-6]|[1-8][0-9]?";
            string UPTO64 = "6[0-4]|[1-5][0-9]?";
            string UPTO48 = "4[0-8]|[1-3][0-9]?";
            string UPTO32 = "3[0-2]|[1-2][0-9]?";
            string UPTO16 = "1[0-6]|[1-9]";
            string UPTO8 = "[1-8]";
            string UPTO4 = "[1-4]";
            string UPTO31 = "3[0-1]|[1-2][0-9]?";
            string UPTO23 = "2[0-3]|[0-1][0-9]";
            string UPTO59 = "[0-5][0-9]";


            //Control Points
            var VARS = new RegexBasedTerminal("VARS", UPTO128, "VAR");
            var OUTS = new RegexBasedTerminal("OUTS", UPTO128, "OUT");
            var INS = new RegexBasedTerminal("INS", UPTO128, "IN");
            var PRG = new RegexBasedTerminal("PRG", UPTO128, "PRG");
            var DMON = new RegexBasedTerminal("DMON", UPTO128, "DMON");

            var AMON = new RegexBasedTerminal("AMON", UPTO96, "AMON");

            var PIDS = new RegexBasedTerminal("PIDS", UPTO64, "PID");

            var ARR = new RegexBasedTerminal("ARR", UPTO48, "AY");

            //WRS ::= 'WR' UPTO32

            var WRS = new RegexBasedTerminal("WRS", UPTO32, "WR");
            var GRP = new RegexBasedTerminal("GRP", UPTO32, "GRP");

            //ARS ::= 'AR' UPTO8

            var ARS = new RegexBasedTerminal("ARS", UPTO8, "AR");

            //Other sub-literals

            
            var DayNumber = new RegexBasedTerminal("DayNumber", UPTO31);

            var HH = new RegexBasedTerminal("HH", UPTO23);
            var MM = new RegexBasedTerminal("MM", UPTO59);
            var SS = new RegexBasedTerminal("SS", UPTO59);


            //KEYWORDS


            //Puctuation
            var PARIZQ = ToTerm("(");
            var PARDER = ToTerm(")");
            var CommandSeparator = ToTerm(";");
            var Comma = ToTerm(",");
            var DDOT = ToTerm(":");

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

            //Months
            var JAN = ToTerm("JAN");
            var FEB = ToTerm("FEB");
            var MAR = ToTerm("MAR");
            var APR = ToTerm("APR");
            var MAY = ToTerm("MAY");
            var JUN = ToTerm("JUN");
            var JUL = ToTerm("JUL");
            var AUG = ToTerm("AUG");
            var SEP = ToTerm("SEP");
            var OCT = ToTerm("OCT");
            var NOV = ToTerm("NOV");
            var DEC = ToTerm("DEC");

            //Days

            var SUN = ToTerm("SUN");
            var MON = ToTerm("MON");
            var TUE = ToTerm("TUE");
            var WED = ToTerm("WED");
            var THU = ToTerm("THU");
            var FRI = ToTerm("FRI");
            var SAT = ToTerm("SAT");

            //Functions 

            var DOY = ToTerm("DOY");
            var DOM = ToTerm("DOM");
            var DOW = ToTerm("DOW");
            var POWERLOSS = ToTerm("POWER-LOSS");
            var TIME = ToTerm("TIME");
            var UNACK = ToTerm("UNACK");
            var USERA = ToTerm("USER-A");
            var USERB = ToTerm("USER-B");

           




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

            //TODO : Add all commands names as terms
            var Command = new NonTerminal("Command");
            var NextCommand = new NonTerminal("NextCommand");

            //TDDO: Add all function names as terms
            var Function = new NonTerminal("Function");


           //TODO: Create Assignment statement
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
            var PointIdentifier = new NonTerminal("PointIdentifier");
            var Literal = new NonTerminal("Literal");
            var DatesLiteral = new NonTerminal("DatesLiteral");
            var MonthLiteral = new NonTerminal("MonthLiteral");
            var DayLiteral = new NonTerminal("DayLiteral");
            var TimeLiteral = new NonTerminal("TimeLiteral");
            

            //Terms to Expressions 
            var Term = new NonTerminal("Term");


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
            //PointIdentifier ::= VARS | CONS | WRS | ARS | OUTS | INS | PRG | GRP | DMON | AMON | ARR
            PointIdentifier.Rule = VARS | PIDS | WRS | ARS | OUTS | INS | PRG | GRP | DMON | AMON | ARR;
            //Designator ::= Identifier | PointIdentifier | LocalVariable
            Designator.Rule = PointIdentifier | Identifier | LocalVariable;
            RemoteDesignator.Rule = Designator;

            DayLiteral.Rule = SUN | MON | TUE | WED | THU | FRI | SAT;
            MonthLiteral.Rule = JAN | FEB | MAR | APR | MAY | JUN | JUL | AUG | SEP | OCT | NOV | DEC;

            //DatesLiteral ::= MonthLiteral Space ([1-2] [1-9] | [3] [0-1])
            DatesLiteral.Rule = MonthLiteral + DayNumber;
            //TimeLiteral ::= HH ':' MM ':' SS
            TimeLiteral.Rule = HH + DDOT + MM + DDOT + SS;
            //Literal ::= NumbersLiteral | DatesLiteral | DaysLiteral | TimeLiteral
            Literal.Rule = Number | DatesLiteral | DayLiteral | TimeLiteral ;
            //Term ::= Function | Designator | Literal
            Term.Rule = Designator | Literal | Function;

            //Functions
            //Function::= ABS | AVG | CONPROP | CONRATE | CONRESET | DOM | DOW | DOY | INT | INTERVAL | LN | LN1 | MAX | MIN | POWERLOSS | SCANS | SQR | STATUS | TBL | TIME | TIMEOFF | TIMEON | WRON | WROFF | UNACK | USERA | USERB
            Function.Rule = DOY | DOM | DOW | POWERLOSS | TIME | UNACK | USERA | USERB;


            /////////////////////
            //Set grammar root 
            /////////////////////
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