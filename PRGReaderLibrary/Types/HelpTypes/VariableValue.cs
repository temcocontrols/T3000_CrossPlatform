namespace PRGReaderLibrary
{
    using System;
    using System.Globalization;

    public class VariableValue
    {
        public int Value { get; set; }
        public Unit Unit { get; set; }
        public CustomUnits CustomUnits { get; set; }
        public int MaxRange { get; set; }

        #region Static methods

        public static string BooleanToDigitalValue(bool value, Unit unit,
            CustomUnits customUnits = null) =>
            value ? unit.GetOnName(customUnits) : unit.GetOffName(customUnits);

        public static bool DigitalValueToBoolean(string value, Unit unit,
            CustomUnits customUnits = null)
        {
            var onName = unit.GetOnName(customUnits);
            var offName = unit.GetOffName(customUnits);
            if (!value.Equals(onName, StringComparison.OrdinalIgnoreCase) &&
                !value.Equals(offName, StringComparison.OrdinalIgnoreCase))
            {
                throw new ArgumentException($@"Value not valid.
Value: {value}, Unit: {unit}.
Supporting values: {onName}, {offName}
CustomUnits: {customUnits}");
            }

            return value.Equals(onName, StringComparison.OrdinalIgnoreCase);
        }

        public static string ConvertValue(string value, Unit fromUnit, Unit toUnit,
            CustomUnits fromCustomUnits = null,
            CustomUnits toCustomUnits = null)
        {
            if (fromUnit.IsDigital())
            {
                var boolean = DigitalValueToBoolean(value, fromUnit, fromCustomUnits);

                return toUnit.IsDigital()
                    ? BooleanToDigitalValue(boolean, toUnit, toCustomUnits)
                    : boolean.ToByte().ToString();
            }

            if (toUnit.IsDigital())
            {
                double doubleValue;
                if (!double.TryParse(value, out doubleValue))
                {
                    BooleanToDigitalValue(true, toUnit, toCustomUnits);
                }

                return BooleanToDigitalValue(doubleValue != 0.0, toUnit, toCustomUnits);
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

        public static object ToObject(int value, Unit unit)
        {
            switch (unit)
            {
                case Unit.Time:
                    return ToTimeSpan(value);

                default:
                    if (unit.IsDigital())
                    {
                        return Convert.ToBoolean(value);
                    }

                    return Convert.ToDouble(value) / 1000.0;
            }
        }

        public static object ToObject(string value, Unit unit, CustomUnits customUnits)
        {
            switch (unit)
            {
                case Unit.Time:
                    return TimeSpan.Parse(value);

                default:
                    Console.WriteLine(value);
                    return unit.IsDigital()
                        ? DigitalValueToBoolean(value, unit, customUnits)
                        : (object)double.Parse(value, CultureInfo.InvariantCulture);
            }
        }

        public static string ToString(object value, Unit unit, CustomUnits customUnits)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                var boolean = Convert.ToBoolean(value);
                if (!unit.IsDigital())
                {
                    throw new ArgumentException($@"Bool value acceptably only for digital unit.
Value: {boolean}, Unit: {unit}");
                }

                return BooleanToDigitalValue(boolean, unit, customUnits);
            }
            else if (type == typeof(TimeSpan))
            {
                var span = (TimeSpan)value;
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
Type: {type}, Value: {value}, Unit: {unit}
Supported types: bool, float, TimeSpan");
            }
        }

        public static int ToInt(object value, Unit unit, int maxRange = 1)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                if (!unit.IsDigital())
                {
                    throw new ArgumentException($"Please select digital unit for boolean value or cast it." +
                                                $"Value: {value}, Unit: {unit}, Type: {type}");
                }

                return Convert.ToInt32(value) * Math.Max(1, maxRange);
            }
            else if (type == typeof(TimeSpan))
            {
                if (unit.IsDigital())
                {
                    throw new ArgumentException($"Please select time unit for TimeSpan value or cast it." +
                                                $"Value: {value}, Unit: {unit}, Type: {type}");
                }

                return FromTimeSpan((TimeSpan)value);
            }
            else if (type == typeof(double))
            {
                if (unit.IsDigital())
                {
                    throw new ArgumentException($"Please select analog unit for double value or cast it." +
                                                $"Value: {value}, Unit: {unit}, Type: {type}");
                }
                return Convert.ToInt32((Convert.ToDouble(value)) * 1000.0);
            }

            throw new NotImplementedException($@"Type not supported.
Type: {type}, Value: {value}, Unit: {unit}
Supported types: bool, float, TimeSpan");
        }

        #endregion

        public VariableValue(int value, Unit unit, CustomUnits customUnits = null,
            int maxRange = -1)
        {
            Value = value;
            Unit = unit;
            CustomUnits = customUnits;
            MaxRange = !unit.IsDigital()
                ? -1
                : maxRange == -1
                    ? value
                    : maxRange;
        }

        public VariableValue(object value, Unit unit, CustomUnits customUnits = null,
            int maxRange = -1)
            : this(ToInt(value, unit, maxRange), unit, customUnits, maxRange)
        { }

        public VariableValue(string value, Unit unit, CustomUnits customUnits = null,
            int maxRange = -1)
            : this(ToObject(value, unit, customUnits), unit, customUnits, maxRange)
        { }

        public string ConvertValue(Unit unit, CustomUnits customUnits = null) =>
            ConvertValue(ToString(), Unit, unit, CustomUnits, customUnits);

        public VariableValue GetInverted()
        {
            var obj = ToObject();
            if (obj.GetType() == typeof(bool))
            {
                return new VariableValue(!(bool)obj, Unit, CustomUnits, MaxRange);
            }

            return new VariableValue(obj, Unit, CustomUnits, MaxRange);
        }

        #region Overrided

        public override int GetHashCode() => Value.GetHashCode() ^ Unit.GetHashCode() ^ MaxRange.GetHashCode();
        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();
        public object ToObject() => ToObject(Value, Unit);
        public override string ToString() => ToString(ToObject(), Unit, CustomUnits);

        #endregion


    }
}
