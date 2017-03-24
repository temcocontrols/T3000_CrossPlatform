namespace PRGReaderLibrary
{
    public enum UnitsEnum
    {
        /// <summary>
        /// Analog part
        /// </summary>
        Unused,
        degC,
        degF,
        FPM,
        Pa,
        KPa,
        psi,
        inW,
        Watts,
        KW,
        KWH,
        Volts,
        KV,
        Amps,
        ma,
        CFM,
        Sec,
        Min,
        Hours,
        Days,
        Time,
        ohms,
        Percents,
        PercentsRH,
        pDivMin,
        count,
        PercentsOpen,
        PercentsCls,
        CFH,
        GPM,
        GPH,
        GAL,
        CF,
        BTU,
        CMH,
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