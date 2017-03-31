namespace PRGReaderLibrary
{
    using System;

    public class UnitsNames : ICloneable
    {
        public string OffOnName { get; set; }
        public string OffName { get; set; }
        public string OnName { get; set; }

        public UnitsNames(string offOnName, string offName = "", string onName = "")
        {
            OffOnName = offOnName;
            OffName = offName;
            OnName = onName;
        }

        public object Clone() => new UnitsNames(OffOnName, OffName, OnName);

        public static UnitsNames TrueFalseUnitsNames { get; } = new UnitsNames(
            $"{bool.FalseString}/{bool.TrueString}", bool.FalseString, bool.TrueString);
    }
}