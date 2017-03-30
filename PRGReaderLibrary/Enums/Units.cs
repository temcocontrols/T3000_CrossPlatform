namespace PRGReaderLibrary
{
    public enum Units
    {
        /// <summary>
        /// Analog part
        /// </summary>
        Unused,
        DegreesC,
        DegreesF,
        Fpm,
        Pa,
        KPa,
        Psi,
        InW,
        Watts,
        Kw,
        KwH,
        Volts,
        KVolts,
        Amps,
        Ma,
        Cfm,
        Sec,
        Min,
        Hours,
        Days,
        Time,
        Ohms,
        Percents,
        PercentsRh,
        PDivMin,
        Count,
        PercentsOpen,
        PercentsCls,
        Cfh,
        Gpm,
        Gph,
        Gal,
        Cf,
        Btu,
        Cmh,
        Custom1,
        Custom2,
        Custom3,
        Custom4,
        Custom5,
        Custom6,
        Custom7,
        Custom8,
        /// <summary>
        /// Digital part
        /// </summary>
        OffOn = 101,
        CloseOpen,
        StopStart,
        DisableEnable,
        NormalAlarm,
        NormalHigh,
        NormalLow,
        NoYes,
        CoolHeat,
        UnOccupied,
        LowHigh,
        /// <summary>
        /// Custom part
        /// </summary>
        InactiveActive = 123
    }
}