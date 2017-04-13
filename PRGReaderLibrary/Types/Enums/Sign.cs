namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;
    using System.Linq;

    public enum Sign
    {
        [Name("+")]
        Positive,
        [Name("-")]
        Negative
    }

    public static class SignExtensions
    {
        private static Dictionary<Sign, string> Names { get; set; } =
            Enum.GetValues(typeof(Sign))
                .Cast<Sign>()
                .ToDictionary(i => i, i => i.GetAttribute<NameAttribute>().Name);

        public static string GetName(this Sign value) => Names[value];
    }
}
