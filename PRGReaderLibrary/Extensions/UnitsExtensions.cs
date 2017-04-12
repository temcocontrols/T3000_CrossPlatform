namespace PRGReaderLibrary
{
    using System;

    public static class UnitsExtensions
    {
        public static bool IsAnalog(this Units units) =>
            units < Units.DigitalUnused;

        public static bool IsAnalogRange(this Units units) =>
            units >= Units.AnalogRangeUnused;

        public static bool IsDigital(this Units units) =>
            !units.IsAnalog() && !units.IsAnalogRange();

        public static UnitsNames GetUnitsNames(this Units units, CustomUnits customUnits = null)
        {
            var names = UnitsNamesConstants.GetNames(customUnits);
            if (!names.ContainsKey(units))
            {
                throw new ArgumentException($@"Units name not exists.
Units: {units}", nameof(units));
            }

            return names[units];
        }

        public static string GetOffName(this Units units, CustomUnits customUnits = null) =>
            GetUnitsNames(units, customUnits).OffName;

        public static string GetOnName(this Units units, CustomUnits customUnits = null) =>
            GetUnitsNames(units, customUnits).OnName;

        public static string GetOffOnName(this Units units, CustomUnits customUnits = null) =>
            GetUnitsNames(units, customUnits).OffOnName;

        public static string GetName(this Units units, CustomUnits customUnits = null) =>
            units.GetOffOnName(customUnits);
    }
}
