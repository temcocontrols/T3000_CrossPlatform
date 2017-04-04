﻿namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public class VariableVariant
    {
        public uint Value { get; set; }
        public Units Units { get; set; }
        public List<CustomUnitPoint> CustomUnits { get; set; }

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

        public static object ToObject(string value, Units units, List<CustomUnitPoint> customUnits)
        {
            switch (units)
            {
                case Units.Time:
                    return TimeSpan.Parse(value);

                default:
                    return units.IsAnalog()
                        ? (object)Convert.ToDouble(value)
                        : UnitsUtilities.DigitalValueToBoolean(value, units, customUnits);
            }
        }

        public static string ToString(object value, Units units, List<CustomUnitPoint> customUnits)
        {
            var type = value.GetType();
            if (type == typeof(bool))
            {
                var boolean = Convert.ToBoolean(value);
                if (!units.IsDigital())
                {
                    throw new ArgumentException($@"Bool value acceptably onle for digital units.
Value: {boolean}, Units: {units}");
                }

                return UnitsUtilities.BooleanToDigitalValue(boolean, units, customUnits);
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

                    case Units.OnOff:
                        return Convert.ToUInt32(value) * 1000;

                    case Units.OffOn:
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

        public VariableVariant(uint value, Units units, List<CustomUnitPoint> customUnits = null)
        {
            Value = value;
            Units = units;
            CustomUnits = customUnits;
        }

        public VariableVariant(object value, Units units, List<CustomUnitPoint> customUnits = null)
            : this(ToUInt(value, units), units, customUnits)
        { }

        public VariableVariant(string value, Units units, List<CustomUnitPoint> customUnits = null)
            : this(ToObject(value, units, customUnits), units, customUnits)
        { }

        public object ToObject() => ToObject(Value, Units);

        public override int GetHashCode() => Value.GetHashCode() ^ Units.GetHashCode();
        public override bool Equals(object obj) => GetHashCode() == obj.GetHashCode();
        public override string ToString() => ToString(ToObject(), Units, CustomUnits);

    }
}