namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;
    using System.Linq;

    public static class UnitsExtensions
    {
        public static bool IsAnalog(this Unit unit) =>
            unit < Unit.DigitalUnused;

        public static bool IsAnalogRange(this Unit unit) =>
            unit >= Unit.AnalogRangeUnused;

        public static bool IsDigital(this Unit unit) =>
            !unit.IsAnalog() && !unit.IsAnalogRange();

        public static UnitsNames GetUnitsNames(this Unit unit, CustomUnits customUnits = null)
        {
            var names = UnitsNamesUtilities.GetNames(customUnits);
            if (!names.ContainsKey(unit))
            {
                throw new ArgumentException($@"Unit name not exists.
Unit: {unit}", nameof(unit));
            }

            return names[unit];
        }

        public static string GetOffName(this Unit unit, CustomUnits customUnits = null) =>
            GetUnitsNames(unit, customUnits).OffName;

        public static string GetOnName(this Unit unit, CustomUnits customUnits = null) =>
            GetUnitsNames(unit, customUnits).OnName;

        public static string GetOffOnName(this Unit unit, CustomUnits customUnits = null) =>
            GetUnitsNames(unit, customUnits).OffOnName;


        private static Dictionary<Unit, UnitsNamesAttribute> GetFilledUnitsNamesAttributes()
        {
            var attributes = new Dictionary<Unit, UnitsNamesAttribute>();

            foreach (Unit units in Enum.GetValues(typeof(Unit)))
            {
                attributes.Add(units, units.GetAttribute<UnitsNamesAttribute>());
            }

            return attributes;
        }

        private static Dictionary<Unit, UnitsNamesAttribute> UnitsNamesAttributes { get; set; }
            = GetFilledUnitsNamesAttributes();

        public static UnitsNamesAttribute GetUnitsNames(this Unit value) =>
            UnitsNamesAttributes[value];
    }
}
