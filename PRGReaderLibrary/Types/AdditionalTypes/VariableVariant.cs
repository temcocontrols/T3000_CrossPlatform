namespace PRGReaderLibrary
{
    using System;

    public class VariableVariant
    {
        public uint Value { get; set; }
        public UnitsEnum Units { get; set; }

        public object Object {
            get { return ToObject(Value, Units); }
        }

        public Type Type {
            get { return Object.GetType(); }
        }

        public string Text {
            get { return ToString(Object, Units); }
        }

        public static bool IsAnalogUnits(UnitsEnum units) =>
            units < UnitsEnum.OffOn;

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

        public static object ToObject(uint value, UnitsEnum units)
        {
            switch (units)
            {
                case UnitsEnum.Time:
                    return ToTimeSpan((int)value);

                default:
                    return IsAnalogUnits(units)
                        ? Convert.ToDouble(value) / 1000.0
                        : (object)Convert.ToBoolean(value);
            }
        }

        public static object ToObject(string value, UnitsEnum units)
        {
            switch (units)
            {
                case UnitsEnum.Time:
                    return TimeSpan.Parse(value);

                case UnitsEnum.OffOn:
                    if (!value.Equals("On", StringComparison.OrdinalIgnoreCase) &&
                        !value.Equals("Off", StringComparison.OrdinalIgnoreCase))
                    {
                        throw new ArgumentException($@"Value not valid.
Value: {value}, Units: {units}.
Supporting values: On, Off");
                    }

                    return value.Equals("On", StringComparison.OrdinalIgnoreCase);

                default:
                    return IsAnalogUnits(units)
                        ? (object)Convert.ToDouble(value)
                        : Convert.ToBoolean(value);
            }
        }

        public static string ToString(object value, UnitsEnum units)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                var boolean = Convert.ToBoolean(value);
                switch (units)
                {
                    case UnitsEnum.OffOn:
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

        public static uint ToUInt(object value, UnitsEnum units)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                if (IsAnalogUnits(units))
                {
                    throw new ArgumentException($"Please select digital units for boolean value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }

                switch (units)
                {
                    case UnitsEnum.NoYes:
                        return Convert.ToUInt32(value) * 1000;

                    default:
                        return Convert.ToUInt32(value);
                }
            }
            else if (type == typeof(TimeSpan))
            {
                if (!IsAnalogUnits(units))
                {
                    throw new ArgumentException($"Please select time units for TimeSpan value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }

                return Convert.ToUInt32(FromTimeSpan((TimeSpan)value));
            }
            else if (type == typeof(double))
            {
                if (!IsAnalogUnits(units))
                {
                    throw new ArgumentException($"Please select analog units for float value or cast it." +
                                                $"Value: {value}, Units: {units}, Type: {type}");
                }
                return IsAnalogUnits(units)
                    ? Convert.ToUInt32((Convert.ToDouble(value)) * 1000.0)
                    : Convert.ToUInt32(value);
            }
            else
            {
                throw new NotImplementedException($@"Type not supported.
Type: {type}, Value: {value}, Units: {units}
Supported types: bool, float, TimeSpan");
            }
        }

        public VariableVariant(uint value, UnitsEnum units)
        {
            Value = value;
            Units = units;
        }

        public VariableVariant(object value, UnitsEnum units)
            : this(ToUInt(value, units), units)
        { }

        public VariableVariant(string value, UnitsEnum units)
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
