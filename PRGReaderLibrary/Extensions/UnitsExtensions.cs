namespace PRGReaderLibrary
{
    using System.Collections.Generic;

    public static class UnitsExtensions
    {
        public static bool IsAnalog(this Units units) =>
            units < Units.OffOn;

        public static bool IsDigital(this Units units) =>
            !units.IsAnalog();

        public static UnitsNames GetUnitsNames(this Units units, List<UnitsElement> customUnits = null) =>
            UnitsNamesConstants.GetNames(customUnits)[units];

        public static string GetOffName(this Units units, List<UnitsElement> customUnits = null) =>
            GetUnitsNames(units, customUnits).OffName;

        public static string GetOnName(this Units units, List<UnitsElement> customUnits = null) =>
            GetUnitsNames(units, customUnits).OnName;

        public static string GetOffOnName(this Units units, List<UnitsElement> customUnits = null) =>
            GetUnitsNames(units, customUnits).OffOnName;
    }
}
