namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsNamesUtilities
    {
        private static Dictionary<Units, UnitsNames> BaseDictionary { get; } =
            GetFilledDictionary();
        private static Dictionary<Units, UnitsNames> BaseAnalogDictionary { get; } =
            GetFilledAnalogDictionary();
        private static Dictionary<Units, UnitsNames> BaseDigitalDictionary { get; } =
            GetFilledDigitalDictionary();
        private static Dictionary<Units, UnitsNames> BaseAnalogRangeDictionary { get; } =
            GetFilledAnalogRangeDictionary();

        private static UnitsNames GetCustomDigitalName(int index,
            List<CustomDigitalUnitsPoint> customUnits = null,
            string defaultOnOff = "")
        {
            if (customUnits == null ||
                index < 0 ||
                index >= customUnits.Count)
            {
                return new UnitsNames(defaultOnOff);
            }

            var unit = customUnits[index];
            return unit.IsEmpty
                ? new UnitsNames(defaultOnOff, bool.FalseString, bool.TrueString)
                : new UnitsNames($"{unit.DigitalUnitsOff}/{unit.DigitalUnitsOn}",
                unit.DigitalUnitsOff, unit.DigitalUnitsOn);
        }

        private static UnitsNames GetCustomAnalogName(int index,
            List<CustomAnalogUnitsPoint> customUnits = null,
            string defaultName = "")
        {
            if (customUnits == null ||
                index < 0 ||
                index >= customUnits.Count)
            {
                return new UnitsNames(defaultName);
            }

            var unit = customUnits[index];
            return new UnitsNames(unit.IsEmpty ? defaultName : unit.Name);
        }

        private static UnitsNames GetNameCollection(Units units,
            CustomUnits customUnits = null)
        {
            switch (units)
            {
                //Custom digital part
                case Units.CustomDigital1:
                case Units.CustomDigital2:
                case Units.CustomDigital3:
                case Units.CustomDigital4:
                case Units.CustomDigital5:
                case Units.CustomDigital6:
                case Units.CustomDigital7:
                case Units.CustomDigital8:
                    return GetCustomDigitalName(units - Units.CustomDigital1, customUnits?.Digital, units.ToString());

                //Custom range analog part
                case Units.AnalogRangeCustom1:
                case Units.AnalogRangeCustom2:
                case Units.AnalogRangeCustom3:
                case Units.AnalogRangeCustom4:
                case Units.AnalogRangeCustom5:
                    return GetCustomAnalogName(units - Units.AnalogRangeCustom1, customUnits?.Analog, units.ToString());

                default:
                    return units.GetUnitsNames()?.UnitsNames ?? new UnitsNames(units.ToString());
            }
        }

        private static Dictionary<Units, UnitsNames> GetFilledDictionary(
            CustomUnits customUnits = null,
            Func<Units, bool> predicate = null)
        {
            var names = new Dictionary<Units, UnitsNames>();
            foreach (Units units in Enum.GetValues(typeof(Units)))
            {
                if (predicate != null && !predicate(units))
                {
                    continue;
                }

                names.Add(units, GetNameCollection(units, customUnits));
            }

            return names;
        }

        private static Dictionary<Units, UnitsNames> GetFilledAnalogDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsAnalog());

        private static Dictionary<Units, UnitsNames> GetFilledDigitalDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsDigital());

        private static Dictionary<Units, UnitsNames> GetFilledAnalogRangeDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsAnalogRange());

        public static Dictionary<Units, UnitsNames> GetNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDictionary : GetFilledDictionary(customUnits);

        public static Dictionary<Units, UnitsNames> GetAnalogNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseAnalogDictionary : GetFilledAnalogDictionary(customUnits);

        public static Dictionary<Units, UnitsNames> GetDigitalNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDigitalDictionary : GetFilledDigitalDictionary(customUnits);

        public static Dictionary<Units, UnitsNames> GetAnalogRangeNames(
            CustomUnits customUnits = null) =>
            customUnits == null
            ? BaseAnalogRangeDictionary
            : GetFilledAnalogRangeDictionary(customUnits);

        public static Units UnitsFromName(string name,
            CustomUnits customUnits = null)
        {
            var names = GetNames(customUnits);
            foreach (var pair in names)
            {
                if (name.Equals(pair.Value.OffOnName, StringComparison.OrdinalIgnoreCase))
                {
                    return pair.Key;
                }
            }

            throw new NotImplementedException($@"This name not implemented.
Name: {name}
CustomUnits: {customUnits?.PropertiesText(shortMode: true)}");
        }
    }
}
