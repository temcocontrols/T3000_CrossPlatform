namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsNamesUtilities
    {
        private static Dictionary<Unit, UnitsNames> BaseDictionary { get; } =
            GetFilledDictionary();
        private static Dictionary<Unit, UnitsNames> BaseAnalogDictionary { get; } =
            GetFilledAnalogDictionary();
        private static Dictionary<Unit, UnitsNames> BaseDigitalDictionary { get; } =
            GetFilledDigitalDictionary();
        private static Dictionary<Unit, UnitsNames> BaseAnalogRangeDictionary { get; } =
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

        private static UnitsNames GetNameCollection(Unit unit,
            CustomUnits customUnits = null)
        {
            switch (unit)
            {
                //Custom digital part
                case Unit.CustomDigital1:
                case Unit.CustomDigital2:
                case Unit.CustomDigital3:
                case Unit.CustomDigital4:
                case Unit.CustomDigital5:
                case Unit.CustomDigital6:
                case Unit.CustomDigital7:
                case Unit.CustomDigital8:
                    return GetCustomDigitalName(unit - Unit.CustomDigital1, customUnits?.Digital, unit.ToString());

                //Custom range analog part
                case Unit.AnalogRangeCustom1:
                case Unit.AnalogRangeCustom2:
                case Unit.AnalogRangeCustom3:
                case Unit.AnalogRangeCustom4:
                case Unit.AnalogRangeCustom5:
                    return GetCustomAnalogName(unit - Unit.AnalogRangeCustom1, customUnits?.Analog, unit.ToString());

                default:
                    return unit.GetUnitsNames()?.UnitsNames ?? new UnitsNames(unit.ToString());
            }
        }

        private static Dictionary<Unit, UnitsNames> GetFilledDictionary(
            CustomUnits customUnits = null,
            Func<Unit, bool> predicate = null)
        {
            var names = new Dictionary<Unit, UnitsNames>();
            foreach (Unit units in Enum.GetValues(typeof(Unit)))
            {
                if (predicate != null && !predicate(units))
                {
                    continue;
                }

                names.Add(units, GetNameCollection(units, customUnits));
            }

            return names;
        }

        private static Dictionary<Unit, UnitsNames> GetFilledAnalogDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsAnalog());

        private static Dictionary<Unit, UnitsNames> GetFilledDigitalDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsDigital());

        private static Dictionary<Unit, UnitsNames> GetFilledAnalogRangeDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsAnalogRange());

        public static Dictionary<Unit, UnitsNames> GetNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDictionary : GetFilledDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetAnalogNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseAnalogDictionary : GetFilledAnalogDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetDigitalNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDigitalDictionary : GetFilledDigitalDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetAnalogRangeNames(
            CustomUnits customUnits = null) =>
            customUnits == null
            ? BaseAnalogRangeDictionary
            : GetFilledAnalogRangeDictionary(customUnits);

        public static Unit UnitsFromName(string name,
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
