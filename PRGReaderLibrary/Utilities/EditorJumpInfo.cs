using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PRGReaderLibrary.Utilities
{
    /// <summary>
    /// Enumerates type of jumping instructions:
    /// GOTO, GOSUB, ONALARM, ONERROR, THEN
    /// </summary>
    public enum JumpType { GOTO, GOSUB, ONALARM, ONERROR, THEN };

    /// <summary>
    /// Stores Jump intructions information.
    /// Helper in renumbering.
    /// </summary>
    public class EditorJumpInfo
    {   /// <summary>
        /// Type of  Jump Instruction: GOTO, GOSUB, ONALARM, ONERROR, THEN
        /// </summary>
        public JumpType Type { get; set; } //Type of Jump
        /// <summary>
        /// Zero based index of line in list
        /// </summary>
        public int LineIndex { get; set; } //Index of Line in Lines
        /// <summary>
        /// Offset in words count from the start of every line.
        /// </summary>
        public int Offset { get; set; } //Code Offset

        /// <summary>
        /// Default constructor for a Jump Info.
        /// </summary>
        /// <param name="t">Type of Jump</param>
        /// <param name="l">Line index</param>
        /// <param name="o">Offset - Words for start of line</param>
        public EditorJumpInfo(JumpType t, int l, int o)
        {
            Type = t;
            LineIndex = l;
            Offset = o;
        }
    };
}