﻿namespace T3000Grammar
{
    using Irony.Parsing;

    class TimeTerminal : IdentifierTerminal
    {
        public TimeTerminal(string name) : 
            base(name, IdOptions.None)
        {
            AllFirstChars = "1234567890";
            AllChars = AllFirstChars + ":";
        }
    }
}
