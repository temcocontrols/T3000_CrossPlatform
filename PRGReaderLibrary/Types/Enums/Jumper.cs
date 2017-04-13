namespace PRGReaderLibrary
{
    using System;
    using System.Linq;
    using System.Collections.Generic;

    public enum Jumper
    {
        [Name("Thermistor Dry Contact")]
        Thermistor,
        [Name("4-20 ma")]
        To20Ma,
        [Name("0-5 V")]
        To5V,
        [Name("0-10 V")]
        To10V
    }

    public static class JumperExtensions
    {
        private static Dictionary<Jumper, string> Names { get; set; } =
            Enum.GetValues(typeof(Jumper))
                .Cast<Jumper>()
                .ToDictionary(i => i, i => i.GetAttribute<NameAttribute>().Name);

        public static string GetName(this Jumper value) => Names[value];
    }
}