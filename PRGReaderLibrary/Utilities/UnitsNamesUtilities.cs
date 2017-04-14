namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsNamesUtilities
    {
        private static Dictionary<Unit, UnitsNames> BaseDictionary { get; } =
            GetFilledDictionary();
        private static Dictionary<Unit, UnitsNames> BaseVariableAnalogDictionary { get; } =
            GetFilledVariableAnalogDictionary();
        private static Dictionary<Unit, UnitsNames> BaseDigitalDictionary { get; } =
            GetFilledDigitalDictionary();
        private static Dictionary<Unit, UnitsNames> BaseInputAnalogDictionary { get; } =
            GetFilledInputAnalogDictionary();

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

                //Custom analog part
                case Unit.Custom1:
                case Unit.Custom2:
                case Unit.Custom3:
                case Unit.Custom4:
                case Unit.Custom5:
                    return GetCustomAnalogName(unit - Unit.Custom1, customUnits?.Analog, unit.ToString());

                //Custom input analog part
                case Unit.InputAnalogCustom1:
                case Unit.InputAnalogCustom2:
                case Unit.InputAnalogCustom3:
                case Unit.InputAnalogCustom4:
                case Unit.InputAnalogCustom5:
                    return GetCustomAnalogName(unit - Unit.InputAnalogCustom1, customUnits?.Analog, unit.ToString());

                //Custom output analog part
                case Unit.OutputAnalogCustom1:
                case Unit.OutputAnalogCustom2:
                case Unit.OutputAnalogCustom3:
                case Unit.OutputAnalogCustom4:
                case Unit.OutputAnalogCustom5:
                    return GetCustomAnalogName(unit - Unit.OutputAnalogCustom1, customUnits?.Analog, unit.ToString());

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

        private static Dictionary<Unit, UnitsNames> GetFilledVariableAnalogDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsVariableAnalog());

        private static Dictionary<Unit, UnitsNames> GetFilledDigitalDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsDigital());

        private static Dictionary<Unit, UnitsNames> GetFilledInputAnalogDictionary(
            CustomUnits customUnits = null) =>
            GetFilledDictionary(customUnits, units => units.IsInputAnalog());

        public static Dictionary<Unit, UnitsNames> GetNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDictionary : GetFilledDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetVariableAnalogNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseVariableAnalogDictionary : GetFilledVariableAnalogDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetDigitalNames(
            CustomUnits customUnits = null) =>
            customUnits == null ? BaseDigitalDictionary : GetFilledDigitalDictionary(customUnits);

        public static Dictionary<Unit, UnitsNames> GetInputAnalogNames(
            CustomUnits customUnits = null) =>
            customUnits == null
            ? BaseInputAnalogDictionary
            : GetFilledInputAnalogDictionary(customUnits);
    }
}
