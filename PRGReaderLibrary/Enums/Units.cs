namespace PRGReaderLibrary
{
    public enum Units
    {
        /// <summary>
        /// Analog part
        /// </summary>
        Unused,

        [UnitsNames("°C")]
        DegreesC,

        [UnitsNames("°F")]
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

        [UnitsNames("%")]
        Percents,
        Rh,
        PPerMin,
        Counts,
        Open,

        [UnitsNames("Kg")]
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

        [UnitsNames("DigitalUnused", "False", "True")]
        DigitalUnused = 100,

        [UnitsNames("Off/On", "/")]
        OffOn,

        [UnitsNames("Closed/Open", "/")]
        ClosedOpen,

        [UnitsNames("Stop/Start", "/")]
        StopStart,

        [UnitsNames("Disabled/Enabled", "/")]
        DisabledEnabled,

        [UnitsNames("Normal/Alarm", "/")]
        NormalAlarm,

        [UnitsNames("Normal/High", "/")]
        NormalHigh,

        [UnitsNames("Normal/Low", "/")]
        NormalLow,

        [UnitsNames("No/Yes", "/")]
        NoYes,

        [UnitsNames("Cool/Heat", "/")]
        CoolHeat,

        [UnitsNames("Unoccupied/Occupied", "/")]
        UnoccupiedOccupied,

        [UnitsNames("On/Off", "/")]
        OnOff,

        [UnitsNames("Open/Closed", "/")]
        OpenClosed,

        [UnitsNames("Start/Stop", "/")]
        StartStop,

        [UnitsNames("Enabled/Disabled", "/")]
        EnabledDisabled,

        [UnitsNames("Alarm/Normal", "/")]
        AlarmNormal,

        [UnitsNames("High/Normal", "/")]
        HighNormal,

        [UnitsNames("Low/High", "/")]
        LowHigh,

        [UnitsNames("Low/Normal", "/")]
        LowNormal,

        [UnitsNames("Yes/No", "/")]
        YesNo,

        [UnitsNames("Heat/Cool", "/")]
        HeatCool,

        [UnitsNames("Occupied/Unoccupied", "/")]
        OccupiedUnoccupied,

        [UnitsNames("High/Low", "/")]
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
        CustomDigital8,

        /// <summary>
        /// Analog range part
        /// </summary>
        AnalogRangeUnused = 200,

        [UnitsNames("Y3K -40 to 150 °C")]
        DegCY3K150,

        [UnitsNames("Y3K -40 to 300 °F")]
        DegFY3K300,

        [UnitsNames("10K -40 to 120 °C")]
        DegC10K120,

        [UnitsNames("10K -40 to 250 °F")]
        DegF10K250,

        [UnitsNames("G3K -40 to 120 °C")]
        DegCG3K120,

        [UnitsNames("G3K -40 to 250 °F")]
        DegFG3K250,

        [UnitsNames("KM10K -40 to 120 °C")]
        DegCKM10K120,

        [UnitsNames("KM10K -40 to 250 °F")]
        DegFKM10K250,

        [UnitsNames("A10K -50 to 110 °C")]
        DegCA10K110,

        [UnitsNames("A10K -60 to 200 °F")]
        DegFA10K200,

        [UnitsNames("0.0 to 5.0 Volts")]
        Volts5,

        [UnitsNames("0.0 to 10.0 Amps")]
        Amps10,

        [UnitsNames("0.0 to 20.0 Ma")]
        Ma20,

        [UnitsNames("0.0 to 20.0 Psi")]
        Psi20,

        [UnitsNames("0.0 to 2^22 Counts")]
        Counts2pow22,

        [UnitsNames("0.0 to 3000 FPM")]
        FPM3000,

        [UnitsNames("0.0 to 100% (0-5V)")]
        PercentsVolts5,

        [UnitsNames("0.0 to 100% (4-20Ma)")]
        PercentsMa20,

        [UnitsNames("Pulses/Min")]
        PulsesPerMin,
        /// <summary>
        /// Custom analog part
        /// </summary>
        AnalogRangeCustom1,
        AnalogRangeCustom2,
        AnalogRangeCustom3,
        AnalogRangeCustom4,
        AnalogRangeCustom5
    }
}