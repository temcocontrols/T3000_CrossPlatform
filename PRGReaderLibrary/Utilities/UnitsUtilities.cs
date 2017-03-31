﻿namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsUtilities
    {
        public static string BooleanToDigitalValue(bool value, Units units, List<UnitsElement> customUnits = null) =>
            value ? units.GetOnName(customUnits) : units.GetOffName(customUnits);

        public static bool DigitalValueToBoolean(string value, Units units, List<UnitsElement> customUnits = null)
        {
            var onName = units.GetOnName(customUnits);
            var offName = units.GetOffName(customUnits);
            if (!value.Equals(onName, StringComparison.OrdinalIgnoreCase) &&
                !value.Equals(offName, StringComparison.OrdinalIgnoreCase))
            {
                throw new ArgumentException($@"Value not valid.
Value: {value}, Units: {units}.
Supporting values: {onName}, {offName}
CustomUnits: {customUnits}");
            }

            return value.Equals(onName, StringComparison.OrdinalIgnoreCase);
        }

        public static string ConvertValue(string value, Units fromUnits, Units toUnits, List<UnitsElement> customUnits = null)
        {
            if (fromUnits.IsDigital())
            {
                var boolean = DigitalValueToBoolean(value, fromUnits, customUnits);

                return toUnits.IsDigital()
                    ? BooleanToDigitalValue(boolean, toUnits, customUnits)
                    : boolean.ToByte().ToString();
            }

            if (toUnits.IsDigital())
            {
                var boolean = double.Parse(value) != 0.0;

                return BooleanToDigitalValue(boolean, toUnits, customUnits);
            }

            return value;
        }
    }
}