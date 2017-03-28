namespace PRGReaderLibrary
{
    using System;
    using System.Collections.Generic;

    /// <summary>
    /// To Resource for localization
    /// </summary>
    public static class UnitsNamesConstants
    {
        public static string GetName(UnitsEnum units)
        {
            switch (units)
            {
                case UnitsEnum.DegreesC:
                    return "°C";

                case UnitsEnum.DegreesF:
                    return "°F";
                    
                case UnitsEnum.OffOn:
                    return "Off/On";

                case UnitsEnum.CloseOpen:
                    return "Close/Open";

                case UnitsEnum.StopStart:
                    return "Stop/Start";

                case UnitsEnum.DisableEnable:
                    return "Disable/Enable";

                case UnitsEnum.NormalAlarm:
                    return "Normal/Alarm";

                case UnitsEnum.NormalHigh:
                    return "Normal/High";

                case UnitsEnum.NormalLow:
                    return "Normal/Low";

                case UnitsEnum.NoYes:
                    return "No/Yes";

                case UnitsEnum.CoolHeat:
                    return "Cool/Heat";

                case UnitsEnum.UnOccupied:
                    return "Unoccupied/Occupied";

                case UnitsEnum.LowHigh:
                    return "Low/High";

                case UnitsEnum.InactiveActive:
                    return "Inactive/Active";

                default:
                    return units.ToString();
            }
        }

        public static UnitsNameItem GetNameItem(UnitsEnum units) =>
            new UnitsNameItem(units, GetName(units));

        public static IList<UnitsNameItem> GetNames()
        {
            var names = new List<UnitsNameItem>();
            foreach (UnitsEnum units in Enum.GetValues(typeof(UnitsEnum)))
            {
                names.Add(GetNameItem(units));
            }

            return names;
        }
    }
}
