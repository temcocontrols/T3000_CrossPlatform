namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsNamesConstants
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
                //Analog part
                case Units.DegreesC:
                    return new UnitsNames("°C");

                case Units.DegreesF:
                    return new UnitsNames("°F");

                case Units.Percents:
                    return new UnitsNames("%");

                case Units.Cfh:
                    return new UnitsNames("Kg");

                //Digital part
                case Units.DigitalUnused:
                    return new UnitsNames("DigitalUnused", bool.FalseString, bool.TrueString);

                case Units.OffOn:
                    return new UnitsNames("Off/On", "/");

                case Units.ClosedOpen:
                    return new UnitsNames("Closed/Open", "/");

                case Units.StopStart:
                    return new UnitsNames("Stop/Start", "/");

                case Units.DisabledEnabled:
                    return new UnitsNames("Disabled/Enabled", "/");

                case Units.NormalAlarm:
                    return new UnitsNames("Normal/Alarm", "/");

                case Units.NormalHigh:
                    return new UnitsNames("Normal/High", "/");

                case Units.NormalLow:
                    return new UnitsNames("Normal/Low", "/");

                case Units.NoYes:
                    return new UnitsNames("No/Yes", "/");

                case Units.CoolHeat:
                    return new UnitsNames("Cool/Heat", "/");

                case Units.UnoccupiedOccupied:
                    return new UnitsNames("Unoccupied/Occupied", "/");

                case Units.OnOff:
                    return new UnitsNames("On/Off", "/");

                case Units.OpenClosed:
                    return new UnitsNames("Open/Closed", "/");

                case Units.StartStop:
                    return new UnitsNames("Start/Stop", "/");

                case Units.EnabledDisabled:
                    return new UnitsNames("Enabled/Disabled", "/");

                case Units.AlarmNormal:
                    return new UnitsNames("Alarm/Normal", "/");

                case Units.HighNormal:
                    return new UnitsNames("High/Normal", "/");

                case Units.LowHigh:
                    return new UnitsNames("Low/High", "/");

                case Units.LowNormal:
                    return new UnitsNames("Low/Normal", "/");

                case Units.YesNo:
                    return new UnitsNames("Yes/No", "/");

                case Units.HeatCool:
                    return new UnitsNames("Heat/Cool", "/");

                case Units.OccupiedUnoccupied:
                    return new UnitsNames("Occupied/Unoccupied", "/");

                case Units.HighLow:
                    return new UnitsNames("High/Low", "/");

                case Units.CustomDigital1:
                case Units.CustomDigital2:
                case Units.CustomDigital3:
                case Units.CustomDigital4:
                case Units.CustomDigital5:
                case Units.CustomDigital6:
                case Units.CustomDigital7:
                case Units.CustomDigital8:
                    return GetCustomDigitalName(units - Units.CustomDigital1, customUnits?.Digital, units.ToString());

                //Analog range part
                case Units.DegCY3K150:
                    return new UnitsNames("Y3K -40 to 150 °C");

                case Units.DegFY3K300:
                    return new UnitsNames("Y3K -40 to 300 °F");

                case Units.DegC10K120:
                    return new UnitsNames("10K -40 to 120 °C");

                case Units.DegF10K250:
                    return new UnitsNames("10K -40 to 250 °F");

                case Units.DegCG3K120:
                    return new UnitsNames("G3K -40 to 120 °C");

                case Units.DegFG3K250:
                    return new UnitsNames("G3K -40 to 250 °F");

                case Units.DegCKM10K120:
                    return new UnitsNames("KM10K -40 to 120 °C");

                case Units.DegFKM10K250:
                    return new UnitsNames("KM10K -40 to 250 °F");

                case Units.DegCA10K110:
                    return new UnitsNames("A10K -50 to 110 °C");

                case Units.DegFA10K200:
                    return new UnitsNames("A10K -60 to 200 °F");

                case Units.Volts5:
                    return new UnitsNames("0.0 to 5.0 Volts");

                case Units.Amps100:
                    return new UnitsNames("0.0 to 10.0 Amps");

                case Units.Ma20:
                    return new UnitsNames("0.0 to 20.0 Ma");

                case Units.Psi20:
                    return new UnitsNames("0.0 to 20.0 Psi");

                case Units.Counts2pow22:
                    return new UnitsNames("0.0 to 2^22 Counts");

                case Units.FPM3000:
                    return new UnitsNames("0.0 to 3000 FPM");

                case Units.PercentsVolts5:
                    return new UnitsNames("0.0 to 100% (0-5V)");

                case Units.PercentsMa20:
                    return new UnitsNames("0.0 to 100% (4-20Ma)");

                case Units.PulsesPerMin:
                    return new UnitsNames("Pulses/Min");

                //Custom range analog part
                case Units.AnalogRangeCustom1:
                case Units.AnalogRangeCustom2:
                case Units.AnalogRangeCustom3:
                case Units.AnalogRangeCustom4:
                case Units.AnalogRangeCustom5:
                    return GetCustomAnalogName(units - Units.AnalogRangeCustom1, customUnits?.Analog, units.ToString());

                default:
                    return new UnitsNames(units.ToString());
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
            ? BaseDigitalDictionary
            : GetFilledDigitalDictionary(customUnits);

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
