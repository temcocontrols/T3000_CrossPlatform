using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony;
using Irony.Parsing;


namespace T3000.Forms
{
    /// <summary>
    /// TokeInfo stores information about a single token
    /// </summary>
    public class TokenInfo
    {
        /// <summary>
        /// Original text token from parsing
        /// </summary>
        string Text { get; set; }
        /// <summary>
        /// Associated Terminal Name from Grammar
        /// </summary>
        string TerminalName { get; set; }
        /// <summary>
        /// Token Type (1 Byte)
        /// </summary>
        int Type { get; set; }
        /// <summary>
        /// Token value (1 Byte)
        /// </summary>
        int Token { get; set; }

        /// <summary>
        /// Default constructor: Create Basic TokenInfo from Text and Terminal Name
        /// Expected to be fulfilled with more token info
        /// </summary>
        /// <param name="Text">Plain Text tokenizable</param>
        /// <param name="TName">Terminal Name</param>
        public TokenInfo(string Text, string TName)
        {
            this.Text = Text;
            this.TerminalName  = TName;
        }

        /// <summary>
        /// TokenInfo ToString Override
        /// </summary>
        /// <returns>string formatted as {Text|TerminalName}</returns>
        public override string ToString()
        {
            string result = "{";
            result += this.Text ?? "NULL";
            result += "|";
            result += this.TerminalName ?? "NULL";
            result += "} ";
            return result;
        }

    }

    /// <summary>
    /// Send Event Arguments
    /// Code and tokens list
    /// </summary>
    public class SendEventArgs : EventArgs
    {
        
        string codetext;
        List<TokenInfo> tokenlist = new List<TokenInfo>();

        /// <summary>
        /// Default and basic constructor
        /// </summary>
        /// <param name="code">Full program in plan text</param>
        /// <param name="tree">Irony Parse Tree Object</param>
        public SendEventArgs(string code, ParseTree tree)
        {
            codetext = code;
            string[] excludeTokens = { "CONTROL_BASIC","LF" };
            bool isFirstToken = true;

            foreach (var tok in tree.Tokens)
            {
                var tokentext = tok.Text;
                var terminalname = tok.Terminal.Name;
                

                switch(tok.Terminal.Name)
                {
                    case "Comment":
                        //split into two tokens
                        Tokens.Add(new TokenInfo("REM", "REM"));
                        Tokens.Add(new TokenInfo(tok.Text.Substring(4), "Comment"));
                        break;
                    case "IntegerNumber":
                        //rename to LineNumber only if first token on line.
                        
                        Tokens.Add(new TokenInfo(tokentext, isFirstToken?"LineNumber":terminalname));
                        break;
                    
                        
                    default:
                        Tokens.Add(new TokenInfo(tokentext, terminalname ));
                        break;
                }
                isFirstToken = terminalname == "LF" ? true:false;
            }
            
        }

        /// <summary>
        /// Plain text code with numbered lines
        /// </summary>
        public string Code
        {
            get { return codetext; }
            private set { codetext = value; }
        }

        /// <summary>
        /// List of Tokens
        /// </summary>
        public List<TokenInfo> Tokens
        {
           get{ return tokenlist; }
           set { tokenlist = value; }
        }

        /// <summary>
        /// Send EventArgs ToString() override
        /// </summary>
        /// <returns>string</returns>
        public override string ToString()
        {
            string result = "";
            foreach (var tok in this.tokenlist)
            {
                result += tok.ToString();
            }
            return result;
        }

    }
}
