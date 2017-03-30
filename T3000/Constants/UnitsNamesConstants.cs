namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    /// <summary>
    /// To Resource for localization
    /// </summary>
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
                    
                case Units.OffOn:
                    return "Off/On";

                case Units.CloseOpen:
                    return "Close/Open";

                case Units.StopStart:
                    return "Stop/Start";

                case Units.DisableEnable:
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

                case Units.UnOccupied:
                    return "Unoccupied/Occupied";

                case Units.LowHigh:
                    return "Low/High";

                case Units.InactiveActive:
                    return "Inactive/Active";

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
