namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;
    using System.Linq;

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
            var names = UnitsNamesUtilities.GetNames(customUnits);
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


        private static Dictionary<Units, UnitsNamesAttribute> GetFilledUnitsNamesAttributes()
        {
            var attributes = new Dictionary<Units, UnitsNamesAttribute>();

            foreach (Units units in Enum.GetValues(typeof(Units)))
            {
                attributes.Add(units, units.GetAttribute<UnitsNamesAttribute>());
            }

            return attributes;
        }

        private static Dictionary<Units, UnitsNamesAttribute> UnitsNamesAttributes { get; set; }
            = GetFilledUnitsNamesAttributes();

        public static UnitsNamesAttribute GetUnitsNames(this Units value) =>
            UnitsNamesAttributes[value];
    }
}
