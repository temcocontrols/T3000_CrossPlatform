namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsExtensions
    {
        public static bool IsAnalog(this Units units) =>
            units < Units.DigitalUnused;

        public static bool IsDigital(this Units units) =>
            !units.IsAnalog();

        public static UnitsNames GetUnitsNames(this Units units, List<CustomDigitalUnitsPoint> customUnits = null)
        {
            var names = UnitsNamesConstants.GetNames(customUnits);
            if (!names.ContainsKey(units))
            {
                throw new ArgumentException($@"Units name not exists.
Units: {units}", nameof(units));
            }

            return names[units];
        }

        public static string GetOffName(this Units units, List<CustomDigitalUnitsPoint> customUnits = null) =>
            GetUnitsNames(units, customUnits).OffName;

        public static string GetOnName(this Units units, List<CustomDigitalUnitsPoint> customUnits = null) =>
            GetUnitsNames(units, customUnits).OnName;

        public static string GetOffOnName(this Units units, List<CustomDigitalUnitsPoint> customUnits = null) =>
            GetUnitsNames(units, customUnits).OffOnName;
    }
}
