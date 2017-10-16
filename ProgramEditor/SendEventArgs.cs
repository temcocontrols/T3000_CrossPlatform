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
    /// All info about one single token
    /// </summary>
    public class TokenInfo
    {
        string Text { get; set; }
        string TerminalName { get; set; }
        int Type { get; set; }
        int Token { get; set; }

        /// <summary>
        /// Create Basic TokenInfo
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
        /// <returns>string</returns>
        public override string ToString()
        {
            string result = "[";
            result += this.Text ?? "<<EmptyText>>";
            result += "::";
            result += this.TerminalName ?? "<<EmptyTerminalName>>";
            result += ") ";
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

            foreach (var tok in tree.Tokens)
            {
                
                Tokens.Add(new TokenInfo(tok.Text, tok.Terminal.Name));
                
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