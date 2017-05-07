namespace T3000
{
    using System;
    using Irony.Parsing;
    using Irony.Interpreter.Ast;

    [Language("T3000ProgrammingLanguage", "0.1", "T3000 Programming Language")]
    public class T3000Grammar : Grammar
    {
        public T3000Grammar()
        {
            // 1. Terminals
            var Text = new FreeTextLiteral("Text", 
                FreeTextOptions.AllowEmpty |
                FreeTextOptions.AllowEof |
                FreeTextOptions.IncludeTerminator, Environment.NewLine);
            //var String = new StringLiteral("String", "'", StringOptions.AllowsAllEscapes);
            var Number = new NumberLiteral("Number");
            //var Space = new RegexBasedTerminal("Space", "\\s+");
            var Time = new TimeTerminal("Time");
            var Identifier = new IdentifierTerminal("Identifier", "._", "1234567890");

            // 2. Non-terminals
            var Program = new NonTerminal("Program", typeof(StatementListNode));
            var ProgramLine = new NonTerminal("ProgramLine");
            var Statement = new NonTerminal("Statement");
            var CodeLine = new NonTerminal("CodeLine");
            var Term = new NonTerminal("Term");

            //Lines
            var RemLine = new NonTerminal("RemLine");
            var IfLine = new NonTerminal("IfLine", typeof(IfNode));
            var AssignLine = new NonTerminal("AssignLine", typeof(AssignmentNode));

            //Expressions
            var Expression = new NonTerminal("Expression");
            var ParentExpression = new NonTerminal("ParentExpression");
            var UnaryExpression = new NonTerminal("UnaryExpression", typeof(UnaryOperationNode));
            var FunctionExpression = new NonTerminal("FunctionExpression", typeof(FunctionCallNode));
            var BinaryExpression = new NonTerminal("BinaryExpression", typeof(BinaryOperationNode));

            //Operators
            var UnaryOperator = new NonTerminal("UnaryOperator");
            var FunctionOperator = new NonTerminal("FunctionOperator", typeof(FunctionDefNode));
            var BinaryOperator = new NonTerminal("BinaryOperator", "operator");
            var AssignmentOperator = new NonTerminal("AssignmentOperator", "assignment operator");

            // 3. BNF rules
            Program.Rule = MakeStarRule(Program, ProgramLine);
            ProgramLine.Rule = Statement + NewLine;
            Statement.Rule = ( Number + CodeLine ) | Empty;
            Statement.NodeCaptionTemplate = "#{0} #{1}";
            CodeLine.Rule =
                RemLine |
                IfLine |
                AssignLine;
            Term.Rule = Number | ParentExpression | Identifier | Time;
            Term.NodeCaptionTemplate = "#{0}";

            //Lines
            RemLine.Rule = "REM" + Text;
            RemLine.NodeCaptionTemplate = "REM #{1}";
            IfLine.Rule = "IF" + 
                //CustomActionHere((i, j) => i.AddTrace("")) + 
                Expression + "THEN" + Expression |
                //"IF" + PreferShiftHere() + "-" + Expression + "THEN" + Expression |
                "IF" + Expression + "THEN" + Expression + PreferShiftHere() + "ELSE" + Expression;
            IfLine.NodeCaptionTemplate = "IF #{1} THEN #{3}";
            AssignLine.Rule = Identifier + AssignmentOperator + Expression;
            AssignLine.NodeCaptionTemplate = "#{0} = #{2}";

            //Expressions
            Expression.Rule = Term | UnaryExpression | 
                FunctionExpression | BinaryExpression | 
                AssignLine;
            Expression.NodeCaptionTemplate = "#{0}";
            ParentExpression.Rule = "(" + Expression + ")";
            ParentExpression.NodeCaptionTemplate = "(#{1})";
            UnaryExpression.Rule = UnaryOperator + Term;
            UnaryExpression.NodeCaptionTemplate = "#{0} #{1}";
            BinaryExpression.Rule = Expression + BinaryOperator + Expression;
            BinaryExpression.NodeCaptionTemplate = "#{0} #{1} #{2}";
            FunctionExpression.Rule = FunctionOperator + "(" + Expression + ")";
            FunctionExpression.NodeCaptionTemplate = "#{0}( #{2} )";

            //Operators
            UnaryOperator.Rule = ToTerm("+") | "-" |
                "NOT" |
                "STOP";
            UnaryOperator.NodeCaptionTemplate = "#{0}";
            FunctionOperator.Rule = ToTerm("TIME") + "-" + "ON" |
                "INTERVAL" |
                "COM1" | "ABS" |
                "MAX" | "MIN";
            FunctionOperator.NodeCaptionTemplate = "#{0}";
            BinaryOperator.Rule = ToTerm(",") |
                "AND" | "OR" |
                "<" | ">" |
                "+" | "-" |
                "*" | "/" |
                "**";
            BinaryOperator.NodeCaptionTemplate = "#{0}";
            AssignmentOperator.Rule = ToTerm("=") | 
                "+=" | "-=" | 
                "*=" | "/=";
            AssignmentOperator.NodeCaptionTemplate = "#{0}";

            //Set grammar root 
            Root = Program;

            // 4. Operators precedence
            RegisterOperators(1, ",");
            RegisterOperators(2, "AND", "OR");
            RegisterOperators(3, "<", ">");
            RegisterOperators(4, "+", "-");
            RegisterOperators(5, "*", "/");
            RegisterOperators(6, Associativity.Right, "**");

            // 5. Punctuation and transient terms
            MarkPunctuation("(", ")");
            RegisterBracePair("(", ")");
            MarkTransient(CodeLine, ProgramLine, 
                Term, Expression,
                BinaryOperator, UnaryOperator, 
                AssignmentOperator,//FunctionOperator, 
                ParentExpression);

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