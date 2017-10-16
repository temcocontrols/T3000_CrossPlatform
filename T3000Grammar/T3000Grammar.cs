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
            new[]
            {
               // "INTERVAL", "COM1", "ABS", "MAX", "MIN"
                "INTERVAL", "COM1", "MAX", "MIN","CONRATE"
            }
        );

        public T3000Grammar() :
            base(caseSensitive: true) //Changed, Control Basic is Case Sensitive: SET-PRINTER vs Set-Printer
        {
            // 1. Terminals

            //Comentarios
            CommentTerminal Comment = new CommentTerminal("Comment", "REM ", "\n", "\r\n");


            var Number = new NumberLiteral("Number", NumberOptions.AllowStartEndDot | NumberOptions.AllowSign);
            Number.DefaultIntTypes = new TypeCode[] { TypeCode.Int32, TypeCode.Int64 };
            Number.DefaultFloatType = TypeCode.Single;
            Number.AddExponentSymbols("E", TypeCode.Double);
            Number.AddExponentSymbols("E-", TypeCode.Double);
            Number.Priority = 20;
           

            //string MyNumberLiteral = "(\\-?\\d+)\\.?\\d+(E\\-|E\\+|E|\\d+)\\d+";
            //var Number = new RegexBasedTerminal("MyNumber", MyNumberLiteral);
            //Number.Priority = 20;
                        

            var IntegerNumber = new NumberLiteral("IntegerNumber", NumberOptions.IntOnly);
            IntegerNumber.Priority = 10;

            var LineNumber = new NumberLiteral("LineNumber", NumberOptions.IntOnly);
            LineNumber.Priority = 11;

            //var Space = new RegexBasedTerminal("Space", "\\s+");

            //var AlarmMessage = new RegexBasedTerminal("AlarmMessage", "(\\w| |\\.|-|,|;|:|!|\\?|¡|¿|\\|\\/){1,69}");

            var StringMessage = new FreeTextLiteral("Text",
                FreeTextOptions.AllowEmpty |
                FreeTextOptions.AllowEof, Environment.NewLine);
            StringMessage.Priority = 5;

            var EnclosedString = new StringLiteral ("EnclosedString","\"", StringOptions.NoEscapes  );       
            EnclosedString.Priority = 5;

            string IDTYPE1 = "[A-Z0-9]+?[\\.\\-_A-Z0-9]*(([A-Z]+[\\.]?[0-9]*)+?)";
            var Identifier = new RegexBasedTerminal("Identifier", IDTYPE1);
            Identifier.Priority = 30;
            

            //123.25BAC_NET 1245.4A
            //12.3.FLOOR
            //FLOOR
            //FLOOR_A2
            //12.A 15.0A
            // VAR1 VAR2 OUT12 IN1 THRU IN128 AY1 TRHU AY64
            //12.5E23    <-- POSSIBLE CONFLICT BUT CORRECT NUMBER SciNotation SHOULD BE 12.5E+23
            //19.253.REG136
            //SCALTOT2
            //A12 A23.3  <-- NOT SUPPORTED BY IDTYPE1


            var LoopVariable = new RegexBasedTerminal("LoopVariable", "[A-K]");

            var LocalVariable = new RegexBasedTerminal("LocalVariable", "[A-Z]{1}");


            string PrintAscii = "(3[2-9])|([4-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5])|('[A-Za-z]')";
            var PrintableAscii = new RegexBasedTerminal("PrintableAscii", PrintAscii);
            PrintableAscii.Priority = 25;

            //RegEx Tested Strings, for ending valid Control Points
            string UPTO128 = "12[0-8]|1[0-1][0-9]|[1-9][0-9]?";
            string UPTO96 = "9[0-6]|[1-8][0-9]?";
            string UPTO64 = "6[0-4]|[1-5][0-9]?";
            string UPTO48 = "4[0-8]|[1-3][0-9]?";
            string UPTO32 = "3[0-2]|[1-2][0-9]?";
            string UPTO16 = "1[0-6]|[1-9]";
            //string UPTO8 = "[1-8]";
            string UPTO4 = "[1-4]";
            string UPTO31 = "3[0-1]|[1-2][0-9]?";
            string UPTO5 = "[1-5]";


            //Control Points
            var VARS = new RegexBasedTerminal("VARS", "VAR(" + UPTO128 + ")");
            VARS.Priority = 40;
            var OUTS = new RegexBasedTerminal("OUTS", "OUT("+ UPTO128 +")");
            OUTS.Priority = 40;
            //TODO: Set appropiate priority and suffix based on Regular Expression all ControlPoints
            var INS = new RegexBasedTerminal("INS", "IN("+UPTO128+")");
            INS.Priority = 40;
            var PRG = new RegexBasedTerminal("PRG", "PRG(" + UPTO128 + ")");
            PRG.Priority = 40;
            var DMON = new RegexBasedTerminal("DMON", "DMON("+ UPTO128 + ")");
            DMON.Priority = 40;
            var AMON = new RegexBasedTerminal("AMON", "AMON(" +UPTO96 + ")");
            AMON.Priority = 40;
            //ARRAYS ELEMENTS
            var ARR = new RegexBasedTerminal("ARR", "AY("+ UPTO48 + ")\\[\\d+\\]" );
            ARR.Priority = 40;

            //Controllers, now known as PIDS
            var PIDS = new RegexBasedTerminal("PIDS", "PID(" + UPTO64 + ")");
            PIDS.Priority = 40;
            //Controllers, for backwards compatibility
            var CON = new RegexBasedTerminal("CON", "CON(" + UPTO64 +")");
            CON.Priority = 40;
            
            //Weekly Routines, now known as Schedules
            var WRS = new RegexBasedTerminal("WRS", "SCH(" + UPTO64 +")");
            WRS.Priority = 40;
            //Anual routines, now known as Holidays
            var ARS = new RegexBasedTerminal("ARS", "HOL(" + UPTO64 + ")");
            ARS.Priority = 40;

            var GRP = new RegexBasedTerminal("GRP", "GRP(" + UPTO32 +")");
            GRP.Priority = 40;

            
            //Other sub-literals


            var DayNumber = new RegexBasedTerminal("DayNumber", UPTO31);
            DayNumber.Priority  = 9;

            var TimeLiteral = new RegexBasedTerminal("TimeLiteral", "(2[0-3]|[0-1][0-9]):[0-5][0-9]:[0-5][0-9]");
            TimeLiteral.Priority = 100;
            var Ordinal = new RegexBasedTerminal("Ordinal", UPTO64);

            String Phone = "(\\+\\d{1,2}[\\s\\.\\-])?(\\(?\\d{3}\\)?[\\s\\.\\-]?)?\\d{3,4}[\\s.-]?\\d{3,4}";
            var PhoneNumber = new RegexBasedTerminal("PhoneNumber", Phone);
            PhoneNumber.Priority = 1;
            //v3 Manual states that only exists 5 customs tables.
            var TABLENUMBER = new RegexBasedTerminal("TABLENUMBER", UPTO5);
            //Same, up to 16 program codes (control Basic)
            var SYSPRG = new RegexBasedTerminal("SYSPRG", UPTO16);
            var TIMER = new RegexBasedTerminal("TIMER", UPTO4);

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
            var DATE = ToTerm("DATE");
            var TIME = ToTerm("TIME");
            var UNACK = ToTerm("UNACK");
            var USERA = ToTerm("USER-A");
            var USERB = ToTerm("USER-B");
            var BEEP = ToTerm("BEEP");
            var SCANS = ToTerm("SCANS");

            

            // 2. Non-terminals

            var CONTROL_BASIC = new NonTerminal("CONTROL_BASIC", typeof(StatementListNode));
            var SentencesSequence = new NonTerminal("SentencesSequence");
            var Sentence = new NonTerminal("Sentence");
            var DECLAREStatement = new NonTerminal("DECLAREStatement");
            var ENDStatement = new NonTerminal("ENDStatement");
            var ProgramLine = new NonTerminal("ProgramLine");
            var BasicLine = new NonTerminal("BasicLine");

            var Subroutine = new NonTerminal("Subroutine");
            var SubroutineSentences = new NonTerminal("SubRoutineSentences");

            //var LineNumber = new NonTerminal("LineNumber");
            var EmptyLine = new NonTerminal("EmptyLine");

            var Statement = new NonTerminal("Statement");
            var EndProgLine = new NonTerminal("CommentOpt");

            var Commands = new NonTerminal("Commands");
            var Command = new NonTerminal("Command");
            var NextCommand = new NonTerminal("NextCommand");

            //Commands
            var START = new NonTerminal("START");
            var STOP = new NonTerminal("STOP");
            var LET = new NonTerminal("LET");
            var ALARM = new NonTerminal("ALARM");
            var ALARMAT = new NonTerminal("ALARMAT");
            var CALL = new NonTerminal("CALL");
            var CALLARGS = new NonTerminal("CALLARGS");
            var CALLARGSLIST = new NonTerminal ("CALLARGLIST");
            var ARG = new NonTerminal("ARG");
            var CLEAR = new NonTerminal("CLEAR");
            var DALARM = new NonTerminal("DALARM");
            var DISABLE = new NonTerminal("DISABLE");
            var ENABLE = new NonTerminal("ENABLE");
            var HANGUP = new NonTerminal("HANGUP");
            var PHONE = new NonTerminal("PHONE");
            var PRINT = new NonTerminal("PRINT");
            var PRINTAT = new NonTerminal("PRINTAT");
            var PANELS = new NonTerminal("PANELS");
            var PrintableKeywords = new NonTerminal("PrintableKeywords");
            var REMOTEGET = new NonTerminal("REMOTEGET");
            var REMOTESET = new NonTerminal("REMOTESET");
            var RETURN = new NonTerminal("RETURN");
            var RUNMACRO = new NonTerminal("RUNMACRO");
            var SETPRINTER = new NonTerminal("SETPRINTER");
            var PrintEverything = new NonTerminal("FULLPRINTING");
            var PrintOnlyCommands = new NonTerminal("ONLYCOMMANDSPRINTING");
            var WAIT = new NonTerminal("WAIT");


            var Function = new NonTerminal("Function");
            var ABS = new NonTerminal("ABS");
            var AVG = new NonTerminal("AVG");
            var CONPROP = new NonTerminal("CONPROP");
            var CONRATE = new NonTerminal("CONRATE");
            var CONRESET = new NonTerminal("CONRESET");
            var INT = new NonTerminal("INT");
            var INTERVAL = new NonTerminal("INVERVAL");
            var LN = new NonTerminal("LN");
            var LN1 = new NonTerminal("LN1");
            var MAX = new NonTerminal("MAX");
            var MIN = new NonTerminal("MIN");
            //SQR | STATUS | TBL
           
            var SQR = new NonTerminal("SQR");
            var STATUS = new NonTerminal("STATUS");
            var TBL = new NonTerminal("TBL");
            //TIMEOFF | TIMEON | WRON | WROFF 

            var TIMEOFF = new NonTerminal("TIMEOFF");
            var TIMEON = new NonTerminal("TIMEON");
            var WRON = new NonTerminal("WRON");
            var WROFF = new NonTerminal("WROFF");
            var COM1 = new NonTerminal("COM1");
            var BAUDRATE = new NonTerminal("BAUDRATE");
            var PORT = new NonTerminal("PORT");
            var CHARS = new NonTerminal("CHARS");
            var ComParameters = new NonTerminal("ComParameters");
            
            //Create Assignment statement
            var Assignment = new NonTerminal("Assignment");

            //TODO: Add all branch statements
            var Branch = new NonTerminal("Branch");
            //BRANCH
            //Branch ::= IF | IFTRUE | IFFALSE | GOSUB | GOTO | ON
            var IF = new NonTerminal("IF");
            var IFTRUE = new NonTerminal("IFTRUE");
            var IFFALSE = new NonTerminal("IFFALSE");
            var GOSUB = new NonTerminal("GOSUB");
            var GOTO = new NonTerminal("GOTO");
            var ON = new NonTerminal("ON");
            var IFCLAUSE = new NonTerminal("IFCLAUSE");
            var ELSEOPT = new NonTerminal("ELSEOPT");
            var GOSELECTOR = new NonTerminal("GOSELECTOR");
            var ONALARM = new NonTerminal("ONALARM");
            var ONERROR = new NonTerminal("ONERROR");

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
            //var TimeLiteral = new NonTerminal("TimeLiteral");
           
            //Terms to Expressions 
          
            var UnaryExpression = new NonTerminal("UnaryExpression");
            var BinaryExpression = new NonTerminal("BinaryExpression");
            var EnclosableExpression = new NonTerminal("EnclosableExpression");
            var Expression = new NonTerminal("Expression");
            
            

            // LISTAS 
            var IdentifierList = new NonTerminal("IdentifierList");
            var LoopVariableList = new NonTerminal("LoopVariableList");
            var ExpressionListOpt = new NonTerminal("ExpressionListOpt");
            var LineNumberListOpt = new NonTerminal("LineNumberListOpt");
            var PrintableListOpt = new NonTerminal("PrintableListOpt");

            // 3. BNF rules

            /////////////////////
            //Set grammar root 
            /////////////////////
            Root = CONTROL_BASIC;

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
            //ProgramLine.Rule = EmptyLine | (LineNumber + Sentence + ReduceHere() + EndProgLine);
            ProgramLine.Rule = LineNumber + Sentence + EndProgLine;

            EndProgLine.Rule = Comment.Q() + NewLine;

            //EmptyLine ::= LineNumber? EndLine
            //EmptyLine.Rule = LineNumber.Q() + NewLine;
            EmptyLine.Rule = Empty;

            //Sentence ::= (Comment | (Commands| Assignment | Branch | Loop) Comment?)
            //Sentence.Rule = Comment | ((ToTerm("END") + ReduceHere() | Commands | Assignment | Branch | FOR | ENDFOR) + Comment.Q()  );
            Sentence.Rule = ToTerm("END") | Commands  | Assignment | Branch | FOR | ENDFOR | Comment;


            //Commands::= Command (';' Command) *
            Commands.Rule = Command + NextCommand;

            //Command ::= ALARM | ALARMAT | CALL | CLEAR | DALARM | DISABLE | ENABLE | 
            //END | HANGUP | ONALARM | ONERROR  | PHONE | PRINT | PRINTAT | REMOTEGET 
            //| REMOTESET | RETURN | RUNMACRO | SETPRINTER | START | STOP | WAIT
            Command.Rule = ALARM | ALARMAT | CALL | CLEAR | DALARM | DISABLE| ENABLE | HANGUP 
            | PHONE | PRINT| PRINTAT| REMOTEGET| REMOTESET| RETURN | RUNMACRO | SETPRINTER 
            | START | STOP | WAIT;

            NextCommand.Rule = MakeStarRule(NextCommand, CommandSeparator + Command);

            //ALARM ::= 'ALARM' Expression ComparisonOps Expression ',' Expression ',' StringLiteral*
            ALARM.Rule = "ALARM" + Expression + ComparisonOps + Expression + Comma + Expression + Comma + StringMessage ;
            
            //ALARMAT ::= 'ALARM-AT' PANEL | 'ALL'
            ALARMAT.Rule = "ALARM-AT" + (IntegerNumber | "ALL");
            //CALL ::= 'CALL' PRG (AssignOp ARG (Space ',' Space ARG)* )?
            CALL.Rule = "CALL" + PRG + CALLARGS.Q();
            CALLARGS.Rule = AssignOp + ARG + CALLARGSLIST;
            CALLARGSLIST.Rule = MakeStarRule(CALLARGSLIST, Comma + ARG);
            ARG.Rule = Designator | Expression;

            CLEAR.Rule = ToTerm("CLEAR");
            //DALARM ::= 'DALARM' Expression ',' NumberLiteral ',' StringLiteral+
            DALARM.Rule = "DALARM" + Expression + Comma + Number + Comma + StringMessage;
            //DISABLE ::= 'DISABLE' Identifier
            DISABLE.Rule = "DISABLE" + Designator;
            ENABLE.Rule = "ENABLE" + Designator;
            HANGUP.Rule = ToTerm("HANGUP");
            PHONE.Rule = "PHONE" + PhoneNumber;
            PRINT.Rule = "PRINT" + PrintableKeywords + PrintableListOpt;
            PrintableKeywords.Rule = DATE | TIME | USERA | USERB | BEEP | PointIdentifier | EnclosedString ;
            PrintableListOpt.Rule  = MakeStarRule(PrintableListOpt, CommandSeparator + PrintableKeywords);
            PRINTAT.Rule = "PRINT-AT" + (PANELS | "ALL");
            PANELS.Rule = MakePlusRule(PANELS, Comma.Q() + IntegerNumber);
            //REMOTEGET ::= 'REMOTE-GET' Designator AssignOp RemoteDesignator
            //REMOTESET::= 'REMOTE-SET' RemoteDesignator AssignOp Designator
            REMOTEGET.Rule = "REMOTE-GET" + Designator  + AssignOp + RemoteDesignator;
            REMOTESET.Rule = "REMOTE-SET" + RemoteDesignator + AssignOp + Designator;
            RETURN.Rule = ToTerm("RETURN");
            //RUNMACRO::= 'RUN-SYSTEM' SYSPRG
            RUNMACRO.Rule = "RUN-SYSTEM" + SYSPRG;
            SETPRINTER.Rule = PrintEverything | PrintOnlyCommands;
            PrintEverything.Rule = "SET-PRINTER" + (ToTerm("A") | ToTerm("B") | ToTerm("0"));
            PrintOnlyCommands.Rule = "Set-Printer" + (ToTerm("a") | ToTerm("b") | ToTerm("0"));
            START.Rule = "START" + Designator;
            STOP.Rule = "STOP" + Designator;
            WAIT.Rule = "WAIT" + Expression ;


            //Assignment ::= Designator AssignOp Expression 
            LET.Rule = "LET";
            Assignment.Rule = LET.Q() + Designator + AssignOp + Expression;


            //Branch ::= IF | IFTRUE | IFFALSE | GOSUB | GOTO | ON
            //   IF::= 'IF' Expression 'THEN' IFCLAUSE('ELSE' IFCLAUSE) ?
            //  IFTRUE::= 'IF+' Expression 'THEN' IFCLAUSE('ELSE' IFCLAUSE) ?
            // IFFALSE::= 'IF-' Expression 'THEN' IFCLAUSE('ELSE' IFCLAUSE) ?
            //IFCLAUSE::= (Sentence | LineNumber)

            Branch.Rule = IF | IFTRUE | IFFALSE | GOSUB | GOTO | ON | ONALARM | ONERROR ;
            IF.Rule = "IF" + Expression + "THEN" + IFCLAUSE + ELSEOPT.Q() ;

            IFTRUE.Rule = "IF+" + Expression + "THEN" + IFCLAUSE + ELSEOPT.Q();
            IFFALSE.Rule = "IF-" + Expression + "THEN" + IFCLAUSE + ELSEOPT.Q();
            //Added Function for testing purposes: Error found on a sample code PRG1 of BTUMETERrev22.prg
            IFCLAUSE.Rule = Commands | Function | Assignment | GOSELECTOR | LineNumber;
            ELSEOPT.Rule = "ELSE" + IFCLAUSE;
            
            //ON ::= 'ON' IntegerTerm (GOTO | GOSUB) (',' LineNumber)*
            ON.Rule = ToTerm("ON") +  Expression + GOSELECTOR + LineNumberListOpt ;
            GOSELECTOR.Rule = GOTO | GOSUB;
            LineNumberListOpt.Rule = MakeStarRule(LineNumberListOpt, Comma + LineNumber);
            //GOSUB::= 'GOSUB' LineNumber
            GOSUB.Rule = "GOSUB" + LineNumber;
            //GOTO ::= 'GOTO' LineNumber
            GOTO.Rule = "GOTO" + LineNumber;

            ONALARM.Rule = ToTerm("ON-ALARM") + LineNumber;
            ONERROR.Rule = ToTerm("ON-ERROR") + LineNumber;

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

            UnaryOps.Rule = NOT;
            BinaryOps.Rule = ArithmeticOps | ComparisonOps | LogicOps;


            //LineNumber.Rule = IntegerNumber;
            //PointIdentifier ::= VARS | CONS | WRS | ARS | OUTS | INS | PRG | GRP | DMON | AMON | ARR
            PointIdentifier.Rule = VARS | PIDS | WRS | ARS | OUTS | INS | PRG | GRP | DMON | AMON | ARR |CON;
            
            //Designator ::= Identifier | PointIdentifier | LocalVariable
            Designator.Rule = PointIdentifier | Identifier | LocalVariable;
            RemoteDesignator.Rule = Designator;

            DayLiteral.Rule = SUN | MON | TUE | WED | THU | FRI | SAT;
            MonthLiteral.Rule = JAN | FEB | MAR | APR | MAY | JUN | JUL | AUG | SEP | OCT | NOV | DEC;

            //DatesLiteral ::= MonthLiteral Space ([1-2] [1-9] | [3] [0-1])
            DatesLiteral.Rule = MonthLiteral + DayNumber;
            //TimeLiteral ::= HH ':' MM ':' SS
            //TimeLiteral.Rule = HH + DDOT + MM + DDOT + SS;
            //Literal ::= NumbersLiteral | DatesLiteral | DaysLiteral | TimeLiteral
            Literal.Rule = IntegerNumber | Number | DatesLiteral | DayLiteral | TimeLiteral;


            //27 Functions
            //Function::= ABS | AVG | CONPROP | CONRATE | CONRESET | DOM | DOW | DOY |
            //INT | INTERVAL | LN | LN1 | MAX | MIN | POWERLOSS | SCANS | SQR | STATUS | TBL |
            //TIME | TIMEOFF | TIMEON | WRON | WROFF | UNACK | USERA | USERB
            Function.Rule = ABS | AVG | CONPROP | CONRATE | CONRESET | COM1 | DOY | DOM | 
                DOW | INT | INTERVAL | LN | LN1 | MAX | MIN | POWERLOSS | SCANS | SQR | STATUS 
                | TBL | TIME | TIMEON | TIMEOFF | WRON | WROFF | UNACK | USERA | USERB;

            ABS.Rule = "ABS" + PARIZQ + Expression + PARDER;
            //AVG      ::= 'AVG' PARIZQ EXPRESSION ( Space ',' Space EXPRESSION )* PARDER
            AVG.Rule = "AVG" + PARIZQ + Expression + ExpressionListOpt + PARDER;
            //CONPROP  ::= 'CONPROP' PARIZQ Ordinal ',' Expression PARDER 
            //TODO: Verify MAX value for integer values of CONPROP
            CONPROP.Rule = "CONPROP" + PARIZQ + CON + Comma + Expression + PARDER;
            
            //CONRATE  ::= 'CONRATE' PARIZQ Ordinal ',' Expression PARDER RANGE
            CONRATE.Rule = "CONRATE" + PARIZQ + CON + Comma + Expression + PARDER;

            //CONRESET ::= 'CONRESET' PARIZQ Ordinal ',' Expression PARDER RANGE
            CONRESET.Rule = "CONRESET" + PARIZQ + CON + Comma + Expression + PARDER;
            //INT      ::= 'INT' PARIZQ Expression PARDER
            INT.Rule = "INT" + PARIZQ + Expression + PARDER;
            //INTERVAL::= 'INTERVAL' PARIZQ Expression PARDER
            INTERVAL.Rule = "INTERVAL" + PARIZQ + Expression + PARDER;
            //LN::= 'LN' PARIZQ Expression PARDER
            LN.Rule = "LN" + PARIZQ +  Expression  + PARDER;
            //LN1 ::= 'LN-1' PARIZQ Expression PARDER
            LN1.Rule = "LN-1" + PARIZQ + Expression + PARDER;
            //MAX ::= 'MAX' PARIZQ Expression (Space ',' Space Expression)*PARDER
            MAX.Rule = "MAX" + PARIZQ   + Expression + ExpressionListOpt + PARDER;
            //MIN::= 'MIN' PARIZQ Expression (Space ',' Space Expression)*PARDER
            MIN.Rule = "MIN" + PARIZQ + Expression + ExpressionListOpt + PARDER;
            //SQR ::= 'SQR' PARIZQ Expression PARDER
            SQR.Rule = "SQR" + PARIZQ + Expression + PARDER;
            //STATUS ::= 'STATUS' PARIZQ Expression PARDER
            STATUS.Rule = "STATUS" + PARIZQ + Expression + PARDER;
            //TBL ::= 'TBL' PARIZQ Expression ',' TABLENUMBER PARDER
            TBL.Rule = "TBL" + PARIZQ + Expression + Comma + TABLENUMBER + PARDER;
            //TIMEON ::= 'TIME-ON' PARIZQ Designator PARDER
            TIMEON.Rule = "TIME-ON" + PARIZQ + Designator + PARDER;
            //TIMEOFF::= 'TIME-OFF' PARIZQ Designator PARDER
            TIMEOFF.Rule = "TIME-OFF" + PARIZQ + Designator + PARDER;
            //WRON ::= 'WR-ON' PARIZQ SYSPRG ',' TIMER PARDER
            WRON.Rule = "WR-ON" + PARIZQ + SYSPRG  + Comma + TIMER + PARDER;
            //WROFF::= 'WR-OFF' PARIZQ SYSPRG ',' TIMER PARDER
            WROFF.Rule = "WR-OFF" + PARIZQ + SYSPRG + Comma + TIMER + PARDER;


            //COM1 ::= 'COM1' PARIZQ BAUDRATE ',' PORT (CHARS+ | ',' EnclosedString) PARDER
            //BAUDRATE::= '9600' | '115200'
            //PORT::= '1' | 'Z' | 'Y' | 'X'
            //CHARS::= ','(PrintableAscii | ['] [A-Za-z] ['])
            //PrintableAscii::= '3'[2 - 9] | [4 - 9][0 - 9] | '1'[0 - 9][0 - 9] | '2'[0 - 4][0 - 9] | '25'[0 - 5]

            COM1.Rule = "COM1" + PARIZQ + BAUDRATE + Comma + PORT + ComParameters + PARDER;
            BAUDRATE.Rule = ToTerm("9600") | ToTerm("115200");
            PORT.Rule = ToTerm("1") | ToTerm("Z") | ToTerm("Y") | ToTerm("X");
            ComParameters.Rule = CHARS | EnclosedString;
            CHARS.Rule = MakePlusRule(CHARS, Comma + PrintableAscii);

             

            //EXPR.Rule = number | variable | FUN_CALL | stringLiteral | BINARY_EXPR 
            //          | "(" + EXPR + ")" | UNARY_EXPR;
            Expression.Rule = 
                Function 
                | Literal 
                | Designator 
                | UnaryExpression 
                | BinaryExpression 
                | EnclosableExpression ;
                        
            //UnaryExpression ::=  UnaryOps Term
            UnaryExpression.Rule = UnaryOps  + Expression;
            //BinaryExpression::= Expression BinaryOps Expression
            BinaryExpression.Rule = Expression + BinaryOps + Expression;
            
            //EnclosableExpression ::= ParIzq SimpleExpression ParDer
            EnclosableExpression.Rule = PARIZQ + Expression + PARDER;

            ExpressionListOpt.Rule = MakeStarRule(ExpressionListOpt, Comma + Expression);

                                   
            RegisterBracePair(PARIZQ.ToString(), PARDER.ToString());
            
            // 4. Operators precedence
            RegisterOperators(100, Associativity.Right, EXP);
            RegisterOperators(90, MUL,DIV);
            RegisterOperators(80, MOD);
            RegisterOperators(70, SUM, SUB);
            
            RegisterOperators(60, LT,GT,LTE,GTE,EQ,NEQ);
            
            RegisterOperators(50, Associativity.Right ,NOT);
            RegisterOperators(50, AND,OR,XOR);
            
            
            //// 5. Punctuation and transient terms
            MarkPunctuation( PARIZQ.ToString()  , PARDER.ToString()  ,CommandSeparator.ToString() );
            PARIZQ.IsPairFor = PARDER;


            //MarkTransient(LineNumber);
            
           

            //MarkTransient(CodeLine, ProgramLine, 
            //    Term, Expression,
            //    BinaryOperator, UnaryOperator, 
            //    AssignmentOperator,//FunctionOperator, 
            //    ParentExpression);

            LanguageFlags = 
                //LanguageFlags.CreateAst | 
                LanguageFlags.NewLineBeforeEOF;

            #region Define Keywords

            //GENERAL KEYWORDS
            MarkReservedWords("DECLARE","END", "FOR","NEXT","TO", "STEP","NOT");
            //27 FUNCTIONS
            //9 Non parenthesis enclosed functions
            MarkReservedWords("DOY", "DOM", "DOW", "POWER-LOSS", "DATE", "TIME", "UNACK", "USER-A", "USER-B", "SCANS");
            //18 Parenthesis enclosed functions
            MarkReservedWords("ABS", "AVG", "CONPROP", "CONRATE", "CONRESET", "INT", "INTERVAL");
            MarkReservedWords("LN", "LN-1", "MAX", "MIN","SQR","STATUS","TBL","TIME-ON","TIME-OFF");
            MarkReservedWords("WR-ON", "WR-OFF","COM1");
            //Branches
            MarkReservedWords("IF", "IF+", "IF-","ON-ALARM", "ON-ERROR", "ON", "GOTO", "GOSUB", "ELSE","THEN");
            //Commands
            MarkReservedWords("START", "STOP","LET", "ALARM", "ALARM-AT", "CALL","ALL");
            MarkReservedWords("CLEAR", "DALARM","DISABLE","ENABLE", "HANGUP","PHONE","PRINT",
                "PRINT-AT","REMOTE-GET","REMOTE-SET","RETURN","RUN-SYSTEM","WAIT",
                "SET-PRINTER","Set-Printer");
               

            MarkReservedWords("AND", "OR", "XOR");
            #endregion
        }
    }
}