namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;

    public enum DirectReverse
    {
        [Name("+")]
        Direct,
        [Name("-")]
        Reverse
    }
    public static class DirectReverseExtensions
    {
        private static Dictionary<DirectReverse, string> Names { get; set; } =
            Enum.GetValues(typeof(DirectReverse))
                .Cast<DirectReverse>()
                .ToDictionary(i => i, i => i.GetAttribute<NameAttribute>().Name);

        public static string GetName(this DirectReverse value) => Names[value];
    }
}
