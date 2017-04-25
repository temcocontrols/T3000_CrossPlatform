namespace T3000Grammar
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
                FreeTextOptions.AllowEof, 
                Environment.NewLine, "THEN");
            var String = new StringLiteral("String", "'", StringOptions.AllowsAllEscapes);
            var Number = new NumberLiteral("Number");
            var Space = ToTerm(" ", "Space");
            var AssignmentOperator = ToTerm("=", "AssignmentOperator");
            var Identifier = new IdentifierTerminal("Identifier");

            // Keywords
            var RemKeyword = ToTerm("REM");
            var IfKeyword = ToTerm("IF");
            var ThenKeyword = ToTerm("THEN");
            var AndKeyword = ToTerm("AND");

            // Functions
            var TimeOnFunction = ToTerm("TIME-ON");

            // 2. Non-terminals
            var Program = new NonTerminal("Program", typeof(StatementListNode));
            var ProgramLine = new NonTerminal("ProgramLine");
            var Statement = new NonTerminal("Statement");
            var CodeLine = new NonTerminal("CodeLine");

            var RemLine = new NonTerminal("RemLine");
            var IfLine = new NonTerminal("IfLine");
            var AssignLine = new NonTerminal("AssignLine", typeof(AssignmentNode));

            var Expression = new NonTerminal("Expression");
            var AssignExpression = new NonTerminal("AssignExpression");
            var ConstExpression = new NonTerminal("ConstExpression");
            var VariableExpression = new NonTerminal("VariableExpression");
            var Function = new NonTerminal("Function");

            // 3. BNF rules
            Program.Rule = MakeStarRule(Program, ProgramLine);
            ProgramLine.Rule = Statement + NewLine;
            Statement.Rule = CodeLine | Empty;
            CodeLine.Rule =
                RemLine |
                IfLine |
                AssignLine;

            RemLine.Rule = Number + Space + RemKeyword + Space + Text;
            IfLine.Rule = Number + Space + IfKeyword + Expression + ThenKeyword + Expression;
            AssignLine.Rule = Number + Space + Identifier + Space + AssignmentOperator + Space + Expression;

            VariableExpression.Rule = Identifier;
            ConstExpression.Rule = Number;
            Expression.Rule = Text;
            AssignExpression.Rule = VariableExpression + Space + "/" + Space + ConstExpression;
            //Function.Rule = TimeOnFunction + "(" + Text + ")";

            //Set grammar root 
            Root = Program;

            // 4. Operators precedence

            // 5. Punctuation and transient terms
            MarkPunctuation(
                Number, RemKeyword, IfKeyword, 
                ThenKeyword, String, Identifier, 
                Text, AssignmentOperator);
            MarkTransient(CodeLine, Statement, ProgramLine);

            //automatically add NewLine before EOF
            //so that our BNF rules work correctly 
            //when there's no final line break in source
            LanguageFlags = 
                //LanguageFlags.CreateAst | 
                LanguageFlags.NewLineBeforeEOF;

        }

        public override void SkipWhitespace(ISourceStream source)
        {
            //base.SkipWhitespace(source);
        }
    }
}