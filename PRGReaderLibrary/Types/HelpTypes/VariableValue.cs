namespace PRGReaderLibrary
{
    using System;

    public class VariableValue
    {
        public int Value { get; set; }
        public Units Units { get; set; }
        public CustomUnits CustomUnits { get; set; }

        public static string BooleanToDigitalValue(bool value, Units units,
            CustomUnits customUnits = null) =>
            value ? units.GetOnName(customUnits) : units.GetOffName(customUnits);

        public static bool DigitalValueToBoolean(string value, Units units,
            CustomUnits customUnits = null)
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

        public static string ConvertValue(string value, Units fromUnits, Units toUnits, 
            CustomUnits fromCustomUnits = null,
            CustomUnits toCustomUnits = null)
        {
            if (fromUnits.IsDigital())
            {
                var boolean = DigitalValueToBoolean(value, fromUnits, fromCustomUnits);

                return toUnits.IsDigital()
                    ? BooleanToDigitalValue(boolean, toUnits, toCustomUnits)
                    : boolean.ToByte().ToString();
            }

            if (toUnits.IsDigital())
            {
                double doubleValue;
                if (!double.TryParse(value, out doubleValue))
                {
                    BooleanToDigitalValue(true, toUnits, toCustomUnits);
                }

                return BooleanToDigitalValue(doubleValue != 0.0, toUnits, toCustomUnits);
            }

            return value;
        }

        public static int FromTimeSpan(TimeSpan time) =>
                ((time.Days * 60 * 60 * 24 +
                    time.Hours * 60 * 60 +
                    time.Minutes * 60 +
                    time.Seconds) * 1000 +
                time.Milliseconds);

        public static TimeSpan ToTimeSpan(int value) =>
            new TimeSpan(
                value / 1000 / 60 / 60 / 24, //days
                value / 1000 / 60 / 60 % 24, //hours
                value / 1000 / 60 % 60,      //minutes
                value / 1000 % 60,           //seconds
                value % 1000                 //milliseconds
            );

        public static object ToObject(int value, Units units)
        {
            switch (units)
            {
                case Units.Time:
                    return ToTimeSpan(value);

                default:
                    if (units.IsDigital())
                    {
                        return Convert.ToBoolean(value);
                    }

                    return Convert.ToDouble(value) / 1000.0;
            }
        }

        public static object ToObject(string value, Units units, CustomUnits customUnits)
        {
            switch (units)
            {
                case Units.Time:
                    return TimeSpan.Parse(value);

                default:
                    return units.IsDigital()
                        ? DigitalValueToBoolean(value, units, customUnits)
                        : (object)Convert.ToDouble(value);
            }
        }

        public static string ToString(object value, Units units, CustomUnits customUnits)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                var boolean = Convert.ToBoolean(value);
                if (!units.IsDigital())
                {
                    throw new ArgumentException($@"Bool value acceptably only for digital units.
Value: {boolean}, Units: {units}");
                }

                return BooleanToDigitalValue(boolean, units, customUnits);
            }
            else if (type == typeof(TimeSpan))
            {
                var span = (TimeSpan) value;
                return span.ToString(
                    $@"{(span.Days == 0 ? string.Empty : @"d\.")}" +
                    @"hh\:mm\:ss" + 
                    $@"{(span.Milliseconds == 0 ? string.Empty : @"\.fff")}");
            }
            else if (type == typeof(double))
            {
                return Convert.ToDouble(value).ToString("F3");
            }
            else
            {
                throw new NotImplementedException($@"Type not supported.
Type: {type}, Value: {value}, Units: {units}
Supported types: bool, float, TimeSpan");
            }
        }

        public static int ToInt(object value, Units units, int maxRange = 1)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                if (!units.IsDigital())
                {
                    throw new ArgumentException($"Please select digital units for boolean value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }
                
                return Convert.ToInt32(value) * maxRange;
            }
            else if (type == typeof(TimeSpan))
            {
                if (units.IsDigital())
                {
                    throw new ArgumentException($"Please select time units for TimeSpan value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }

                return FromTimeSpan((TimeSpan)value);
            }
            else if (type == typeof(double))
            {
                if (units.IsDigital())
                {
                    throw new ArgumentException($"Please select analog units for double value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }
                return Convert.ToInt32((Convert.ToDouble(value)) * 1000.0);
            }

            throw new NotImplementedException($@"Type not supported.
Type: {type}, Value: {value}, Units: {units}
Supported types: bool, float, TimeSpan");
        }

        public VariableValue(int value, Units units, CustomUnits customUnits = null)
        {
            Value = value;
            Units = units;
            CustomUnits = customUnits;
        }

        public VariableValue(object value, Units units, CustomUnits customUnits = null,
            int maxRange = 1)
            : this(ToInt(value, units, maxRange), units, customUnits)
        { }

        public VariableValue(string value, Units units, CustomUnits customUnits = null,
            int maxRange = 1)
            : this(ToObject(value, units, customUnits), units, customUnits, maxRange)
        { }

        public object ToObject() => ToObject(Value, Units);
        public string ConvertValue(Units units, CustomUnits customUnits = null) => 
            ConvertValue(ToString(), Units, units, CustomUnits, customUnits);

        public override int GetHashCode() => Value.GetHashCode() ^ Units.GetHashCode();
        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();
        public override string ToString() => ToString(ToObject(), Units, CustomUnits);

    }
}
