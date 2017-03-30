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
        Rh,
        PPerMin,
        Counts,
        Open,
        Cfh,
        Gpm,
        Gph,
        Gal,
        Cf,
        Btu,
        Cmh,
        /// <summary>
        /// Custom analog part
        /// </summary>
        Custom1 = 34,
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
        DigitalUnused = 100,
        OffOn,
        ClosedOpen,
        StopStart,
        DisabledEnabled,
        NormalAlarm,
        NormalHigh,
        NormalLow,
        NoYes,
        CoolHeat,
        UnoccupiedOccupied,
        OnOff,
        OpenClosed,
        StartStop,
        EnabledDisabled,
        AlarmNormal,
        HighNormal,
        LowHigh,
        LowNormal,
        YesNo,
        HeatCool,
        OccupiedUnoccupied,
        HighLow,
        /// <summary>
        /// Custom digital part
        /// </summary>
        CustomDigital1 = 123,
        CustomDigital2,
        CustomDigital3,
        CustomDigital4,
        CustomDigital5,
        CustomDigital6,
        CustomDigital7,
        CustomDigital8
    }
}