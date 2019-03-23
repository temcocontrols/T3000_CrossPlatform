using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PRGReaderLibrary.Utilities
{

    /// <summary>
    /// TokeInfo stores information about a single token
    /// </summary>
    public class EditorTokenInfo
    {
        /// <summary>
        /// Original text token from parsing
        /// </summary>
        public string Text { get; set; }
        /// <summary>
        /// Associated Terminal Name from Grammar
        /// </summary>
        public string TerminalName { get; set; }
        /// <summary>
        /// Token Type (1 Byte)
        /// Token size for Comment string
        /// </summary>
        public short Type { get; set; }
        /// <summary>
        /// Token value (1 Byte)
        /// </summary>
        public short Token { get; set; }
        /// <summary>
        /// Control Point index
        /// </summary>
        public short Index { get; set; }
        /// <summary>
        /// Operators Precedence
        /// </summary>
        public short Precedence { get; set; }

        /// <summary>
        /// Default constructor: Create Basic TokenInfo from Text and Terminal Name
        /// Expected to be fulfilled with more token info
        /// </summary>
        /// <param name="Text">Plain Text tokenizable</param>
        /// <param name="TName">Terminal Name</param>
        public EditorTokenInfo(string Text, string TName)
        {
            this.Text = Text;
            this.TerminalName = TName;
            this.Precedence = 0;
            this.Index = 0;
            this.Type = 0;
        }

        /// <summary>
        /// TokenInfo ToString Override
        /// </summary>
        /// <returns>string formatted as ·×Text×· or ·TerminalName·
        /// ·×Text· means there is no TerminalName defined
        /// </returns>
        public override string ToString()
        {
            string result = " ";
            //result     += this.Text ?? "NULL";
            //result     += "->";
            result += this.TerminalName ?? $"×{this.Text}";
            result += "·";
            return result;
        }

    }
}
