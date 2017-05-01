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
            var RemKeyword = ToTerm("REM", "RemKeyword");
            var IfKeyword = ToTerm("IF", "IfKeyword");
            var IfPKeyword = ToTerm("IF+", "IfPKeyword");
            var IfMKeyword = ToTerm("IF-", "IfMKeyword");
            var ThenKeyword = ToTerm("THEN", "ThenKeyword");
            var AndKeyword = ToTerm("AND", "AndKeyword");

            // Functions
            var TimeOnFunction = ToTerm("TIME-ON");

            // 2. Non-terminals
            var Program = new NonTerminal("Program", typeof(StatementListNode));
            var ProgramLine = new NonTerminal("ProgramLine");
            var Statement = new NonTerminal("Statement");
            var CodeLine = new NonTerminal("CodeLine");

            //Lines
            var RemLine = new NonTerminal("RemLine");
            var IfLine = new NonTerminal("IfLine", typeof(IfNode));
            var IfPLine = new NonTerminal("IfPLine", typeof(IfNode));
            var IfMLine = new NonTerminal("IfMLine", typeof(IfNode));
            var AssignLine = new NonTerminal("AssignLine", typeof(AssignmentNode));

            var IfKeywords = new NonTerminal("IfKeywords");

            //Expressions
            var Expression = new NonTerminal("Expression");
            var AssignExpression = new NonTerminal("AssignExpression");
            var ConstExpression = new NonTerminal("ConstExpression");
            var VariableExpression = new NonTerminal("VariableExpression");
            var FunctionExpression = new NonTerminal("FunctionExpression");

            // 3. BNF rules
            Program.Rule = MakeStarRule(Program, ProgramLine);
            ProgramLine.Rule = Statement + NewLine;
            Statement.Rule = ( Number + CodeLine ) | Empty;
            Statement.NodeCaptionTemplate = "#{0} #{1}";
            CodeLine.Rule =
                RemLine |
                IfLine |
                AssignLine;

            IfKeywords.Rule = 
                IfPKeyword |
                IfMKeyword + PreferShiftHere() | 
                IfKeyword;
            IfKeywords.NodeCaptionTemplate = "#{0}";

            //Lines
            RemLine.Rule = RemKeyword + Text;
            RemLine.NodeCaptionTemplate = "REM #{1}";
            IfLine.Rule = IfKeywords + ReduceHere() + Expression + ThenKeyword + Expression;
            IfLine.NodeCaptionTemplate = "IF #{1} THEN #{3}";
            AssignLine.Rule = Identifier + AssignmentOperator + Expression;
            AssignLine.NodeCaptionTemplate = "#{0} = #{2}";

            //Expressions
            VariableExpression.Rule = Identifier;
            VariableExpression.NodeCaptionTemplate = "#{0}";
            ConstExpression.Rule = Number;
            ConstExpression.NodeCaptionTemplate = "#{0}";
            Expression.Rule = Text;
            Expression.NodeCaptionTemplate = "#{0}";
            AssignExpression.Rule = VariableExpression + "/" + ConstExpression;
            AssignExpression.NodeCaptionTemplate = "#{0} / #{2}";
            //FunctionExpression.Rule = TimeOnFunction + "(" + Text + ")";

            //Set grammar root 
            Root = Program;

            // 4. Operators precedence

            // 5. Punctuation and transient terms
            //MarkPunctuation(
            //    Number, String, Identifier, 
            //    Text, AssignmentOperator);
            MarkTransient(CodeLine, ProgramLine);

            //automatically add NewLine before EOF
            //so that our BNF rules work correctly 
            //when there's no final line break in source
            LanguageFlags = 
                //LanguageFlags.CreateAst | 
                LanguageFlags.NewLineBeforeEOF;


            #region Define Keywords

            //MarkReservedWords("REM", "IF");

            #endregion
        }

        public override void SkipWhitespace(ISourceStream source)
        {
            //source.CreateToken()
            //if (!MatchSymbol("IF"))
                base.SkipWhitespace(source);
        }
    }
}