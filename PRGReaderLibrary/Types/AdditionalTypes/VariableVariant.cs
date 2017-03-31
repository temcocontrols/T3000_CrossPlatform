namespace PRGReaderLibrary
{
    using System;

    public class VariableVariant
    {
        public uint Value { get; set; }
        public Units Units { get; set; }

        public object Object {
            get { return ToObject(Value, Units); }
        }

        public Type Type {
            get { return Object.GetType(); }
        }

        public string Text {
            get { return ToString(Object, Units); }
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

        public static object ToObject(uint value, Units units)
        {
            switch (units)
            {
                case Units.Time:
                    return ToTimeSpan((int)value);

                default:
                    return units.IsAnalog()
                        ? Convert.ToDouble(value) / 1000.0
                        : (object)Convert.ToBoolean(value);
            }
        }

        public static object ToObject(string value, Units units)
        {
            switch (units)
            {
                case Units.Time:
                    return TimeSpan.Parse(value);

                case Units.OffOn:
                    if (!value.Equals("On", StringComparison.OrdinalIgnoreCase) &&
                        !value.Equals("Off", StringComparison.OrdinalIgnoreCase))
                    {
                        throw new ArgumentException($@"Value not valid.
Value: {value}, Units: {units}.
Supporting values: On, Off");
                    }

                    return value.Equals("On", StringComparison.OrdinalIgnoreCase);

                default:
                    return units.IsAnalog()
                        ? (object)Convert.ToDouble(value)
                        : Convert.ToBoolean(value);
            }
        }

        public static string ToString(object value, Units units)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                var boolean = Convert.ToBoolean(value);
                switch (units)
                {
                    case Units.OffOn:
                        return boolean ? "On" : "Off";

                    default:
                        return $"{boolean}";
                }
            }
            else if (type == typeof(TimeSpan))
            {
                return ((TimeSpan)value).ToString(@"hh\:mm\:ss\.fff");
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

        public static uint ToUInt(object value, Units units)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                if (units.IsAnalog())
                {
                    throw new ArgumentException($"Please select digital units for boolean value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }

                switch (units)
                {
                    case Units.NoYes:
                        return Convert.ToUInt32(value) * 1000;

                    default:
                        return Convert.ToUInt32(value);
                }
            }
            else if (type == typeof(TimeSpan))
            {
                if (!units.IsAnalog())
                {
                    throw new ArgumentException($"Please select time units for TimeSpan value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }

                return Convert.ToUInt32(FromTimeSpan((TimeSpan)value));
            }
            else if (type == typeof(double))
            {
                if (!units.IsAnalog())
                {
                    throw new ArgumentException($"Please select analog units for float value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }
                return Convert.ToUInt32((Convert.ToDouble(value)) * 1000.0);
            }
            else
            {
                throw new NotImplementedException($@"Type not supported.
Type: {type}, Value: {value}, Units: {units}
Supported types: bool, float, TimeSpan");
            }
        }

        public VariableVariant(uint value, Units units)
        {
            Value = value;
            Units = units;
        }

        public VariableVariant(object value, Units units)
            : this(ToUInt(value, units), units)
        { }

        public VariableVariant(string value, Units units)
            : this(ToObject(value, units), units)
        { }

        public override int GetHashCode() =>
            Value.GetHashCode() ^ Units.GetHashCode();

        public override bool Equals(object obj)
        {
            if (obj == null || obj.GetType() != typeof(VariableVariant))
                return false;

            var objVariant = (VariableVariant)obj;
            return
                Value == objVariant.Value &&
                Units == objVariant.Units;
        }

        public object ToObject() => ToObject(Value, Units);

        public override string ToString() => ToString(ToObject(), Units);
    }
}
