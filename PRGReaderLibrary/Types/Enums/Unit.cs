namespace PRGReaderLibrary
{
    public enum Unit
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
        /// Input analog part
        /// </summary>
        InputAnalogUnused = 256,

        [UnitsNames("Y3K/-40 to 150 °C", "/")]
        DegCY3K150 = 257,

        [UnitsNames("Y3K/-40 to 300 °F", "/")]
        DegFY3K300,

        [UnitsNames("10K/-40 to 120 °C", "/")]
        DegC10K120,

        [UnitsNames("10K/-40 to 250 °F", "/")]
        DegF10K250,

        [UnitsNames("G3K/-40 to 120 °C", "/")]
        DegCG3K120,

        [UnitsNames("G3K/-40 to 250 °F", "/")]
        DegFG3K250,

        [UnitsNames("KM10K/-40 to 120 °C", "/")]
        DegCKM10K120,

        [UnitsNames("KM10K/-40 to 250 °F", "/")]
        DegFKM10K250,

        [UnitsNames("A10K/-50 to 110 °C", "/")]
        DegCA10K110,

        [UnitsNames("A10K/-60 to 200 °F", "/")]
        DegFA10K200,

        [UnitsNames("Volts/0.0 to 5.0", "/")]
        Volts5,

        [UnitsNames("Amps/0.0 to 10.0", "/")]
        Amps10,

        [UnitsNames("Ma/0.0 to 20.0", "/")]
        Ma20,

        [UnitsNames("Psi/0.0 to 20.0", "/")]
        Psi20,

        [UnitsNames("Counts/0.0 to 2^22", "/")]
        Counts2pow22,

        [UnitsNames("FPM/0.0 to 3000", "/")]
        FPM3000,

        [UnitsNames("%(0-5V)/0.0 to 100", "/")]
        PercentsVolts5,

        [UnitsNames("%(4-20Ma)/0.0 to 100", "/")]
        PercentsMa20,

        [UnitsNames("Pulses/Min")]
        PulsesPerMin,
        /// <summary>
        /// Custom analog part
        /// </summary>
        InputAnalogCustom1,
        InputAnalogCustom2,
        InputAnalogCustom3,
        InputAnalogCustom4,
        InputAnalogCustom5,

        /// <summary>
        /// Output analog part
        /// </summary>
        OutputAnalogUnused = 512,

        [UnitsNames("Volts/0.0 -> 10", "/")]
        OutputVolts = 513,

        [UnitsNames("%Open/0.0 -> 100", "/")]
        OutputPercentsOpen,

        [UnitsNames("psi/0.0 -> 20", "/")]
        OutputPsi,

        [UnitsNames("%/0.0 -> 100", "/")]
        OutputPercents,

        [UnitsNames("%Cls/0.0 -> 100", "/")]
        OutputPercentsCls,

        [UnitsNames("ma/0.0 -> 20", "/")]
        OutputMa,

        [UnitsNames("%PWM/0.0 -> 100", "/")]
        OutputPercentsPWM,
        /// <summary>
        /// Custom analog part
        /// </summary>
        OutputAnalogCustom1,
        OutputAnalogCustom2,
        OutputAnalogCustom3,
        OutputAnalogCustom4,
        OutputAnalogCustom5
    }
}