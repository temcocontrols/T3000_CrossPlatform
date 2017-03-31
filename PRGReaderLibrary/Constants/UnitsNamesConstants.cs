namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    public static class UnitsNamesConstants
    {
        public static string GetName(Units units)
        {
            switch (units)
            {
                case Units.DegreesC:
                    return "°C";

                case Units.DegreesF:
                    return "°F";

                case Units.Percents:
                    return "%";

                case Units.OffOn:
                    return "Off/On";

                case Units.ClosedOpen:
                    return "Close/Open";

                case Units.StopStart:
                    return "Stop/Start";

                case Units.DisabledEnabled:
                    return "Disable/Enable";

                case Units.NormalAlarm:
                    return "Normal/Alarm";

                case Units.NormalHigh:
                    return "Normal/High";

                case Units.NormalLow:
                    return "Normal/Low";

                case Units.NoYes:
                    return "No/Yes";

                case Units.CoolHeat:
                    return "Cool/Heat";

                case Units.UnoccupiedOccupied:
                    return "Unoccupied/Occupied";

                case Units.LowHigh:
                    return "Low/High";

                //case Units.Custom1:
                //    return "Inactive/Active";

                default:
                    return units.ToString();
            }
        }

        public static UnitsNameItem GetNameItem(Units units) =>
            new UnitsNameItem(units, GetName(units));

        public static IList<UnitsNameItem> GetNames()
        {
            var names = new List<UnitsNameItem>();
            foreach (Units units in Enum.GetValues(typeof(Units)))
            {
                names.Add(GetNameItem(units));
            }

            return names;
        }
    }
}
