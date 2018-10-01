<<<<<<< HEAD
using System;
=======
﻿using System;
>>>>>>> AIM_BRANCH
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PRGReaderLibrary.Utilities
{
    /// <summary>
    /// Stores values Before and After Renumbering.
    /// </summary>
    public class EditorLineInfo
    {
        /// <summary>
        /// Line number before renumbering
        /// </summary>
        public int Before { get; set; }
        /// <summary>
        /// Line number after renumbering
        /// </summary>
        public int After { get; set; }
        /// <summary>
        /// Default constructor of class LineInfo
        /// </summary>
        /// <param name="b">Before value</param>
        /// <param name="a">After value</param>
        public EditorLineInfo(int b, int a) { Before = b; After = a; }
        /// <summary>
        /// LineInfo ToString() override
        /// </summary>
        /// <returns>Line number After renumbering as a string
        /// Ready to use in line number replacements</returns>
        public override string ToString()
        {
            return After.ToString();
        }
    };
<<<<<<< HEAD
}
=======
}
>>>>>>> AIM_BRANCH
