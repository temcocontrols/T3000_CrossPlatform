namespace PRGReaderLibrary
{
    using System;

    public class UnitsNames : ICloneable
    {
        public string OffOnName { get; set; }
        public string OffName { get; set; }
        public string OnName { get; set; }

        public UnitsNames(string offOnName, string offName, string onName)
        {
            OffOnName = offOnName;
            OffName = offName;
            OnName = onName;
        }

        public UnitsNames(string offOnName)
            : this(offOnName, "", "")
        {}

        public static bool ValidateSeparatoredString(string line, string separator)
        {
            if (line == null)
            {
                throw new ArgumentNullException(nameof(line));
            }
            if (separator == null)
            {
                throw new ArgumentNullException(nameof(separator));
            }

            if (!line.Contains(separator.ToString()))
            {
                return false;
            }

            var values = line.Split(separator.ToCharArray());
            var length = values.Length;
            if (values.Length != 2 ||
                string.IsNullOrWhiteSpace(values[0]) ||
                string.IsNullOrWhiteSpace(values[1]))
            {
                return false;
            }

            return true;
        }

        public UnitsNames(string offOnName, string separator)
        {
            OffOnName = offOnName;

            var values = offOnName.Split(separator.ToCharArray());
            if (!ValidateSeparatoredString(offOnName, separator))
            {
                throw new ArgumentException($@"Not valid data. Need two values.
Valid input: Value1{separator}Value2
OffOnName: {offOnName}
Separator: {separator}");
            }

            OffName = values[0];
            OnName = values[1];
        }

        public object Clone() => new UnitsNames(OffOnName, OffName, OnName);

        public static UnitsNames TrueFalseUnitsNames { get; } = new UnitsNames(
            $"{bool.FalseString}/{bool.TrueString}", bool.FalseString, bool.TrueString);
    }
}