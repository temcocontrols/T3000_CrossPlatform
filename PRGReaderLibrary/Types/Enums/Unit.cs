namespace PRGReaderLibrary
{
    public enum Unit
    {
        /// <summary>
        /// Analog part
        /// </summary>
        Unused,

        [UnitsNames("Deg.C")]
        DegreesC,

        [UnitsNames("Deg.F")]
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

        [UnitsNames("Unused", "False", "True")]
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
        [UnitsNames("Low/High", "/")]
        LowHigh,
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
        CustomDigital9,

        /// <summary>
        /// Input analog part
        /// </summary>
        [UnitsNames("Unused", "Unused", "Unused")]
        InputAnalogUnused = 256,

        [UnitsNames("Y3K/-40 to 150 Deg.C", "/")]
        DegCY3K150 = 257,

        [UnitsNames("Y3K/-40 to 300 Deg.F", "/")]
        DegFY3K300,

        [UnitsNames("10K/-40 to 120 Deg.C", "/")]
        DegC10K120,

        [UnitsNames("10K/-40 to 250 Deg.F", "/")]
        DegF10K250,

        [UnitsNames("G3K/-40 to 120 Deg.C", "/")]
        DegCG3K120,

        [UnitsNames("G3K/-40 to 250 Deg.F", "/")]
        DegFG3K250,

        [UnitsNames("KM10K/-40 to 120 Deg.C", "/")]
        DegCKM10K120,

        [UnitsNames("KM10K/-40 to 250 Deg.F", "/")]
        DegFKM10K250,

        [UnitsNames("A10K/-50 to 110 Deg.C", "/")]
        DegCA10K110,

        [UnitsNames("A10K/-60 to 200 Deg.F", "/")]
        DegFA10K200,

        [UnitsNames("Volts/0.0 to 5.0", "/")]
        Volts5,

        [UnitsNames("Amps/0.0 to 100.0", "/")]
        Amps10,

        [UnitsNames("Ma/0.0 to 20.0", "/")]
        Ma20,

        [UnitsNames("Psi/0.0 to 20.0", "/")]
        Psi20,

        [UnitsNames("Counts/0.0 to 2^22", "/")]
        Counts2pow22,

        [UnitsNames("%(0-10V)/0.0 to 100", "/")]
        PercentsVolts10,

        [UnitsNames("%(0-5V)/0.0 to 100", "/")]
        PercentsVolts5,

        [UnitsNames("%(4-20Ma)/0.0 to 100", "/")]
        PercentsMa20,
        [UnitsNames("Volts/0.0 to 10.0", "/")]
        Volts10,
        /// <summary>
        /// Custom analog part
        /// </summary>
        [UnitsNames("Custom1", "Custom1", "")]
        InputAnalogCustom1,
        [UnitsNames("Custom2", "Custom2", "")]
        InputAnalogCustom2,
        [UnitsNames("Custom3", "Custom3", "")]
        InputAnalogCustom3,
        [UnitsNames("Custom4", "Custom4", "")]
        InputAnalogCustom4,
        [UnitsNames("Custom5", "Custom5", "")]
        InputAnalogCustom5,

        [UnitsNames("Pulses Count(Fast 100HZ)", "/")]
        PulsesPerMin,
        [UnitsNames("Frequency(HZ)", "/")]
        HZ,
        [UnitsNames("Humidity(%)", "/")]
        HUM,
        [UnitsNames("Pressure inWc", "/")]
        PreinWc,
        [UnitsNames("Pressure Kpa", "/")]
        PreKpa,
        [UnitsNames("Pressure Psi", "/")]
        PrePsi,
        [UnitsNames("Pressure mmHg", "/")]
        PremmHg,
        [UnitsNames("Pressure inHg", "/")]
        PreinHg,
        [UnitsNames("Pressure Kgcm", "/")]
        PreKgcm,
        [UnitsNames("Pressure atmos", "/")]
        Preatmos,
        [UnitsNames("Pressure bar", "/")]
        Prebar,
        [UnitsNames("Reserved1", "", "")]
        Reserved1,
        [UnitsNames("Reserved2", "", "")]
        Reserved2,
        [UnitsNames("Reserved3", "", "")]
        Reserved3,
        [UnitsNames("20Amps", "", "")]
        Amps20,
        [UnitsNames("50Amps", "", "")]
        Amps50,
        [UnitsNames("75Amps", "", "")]
        Amps75,
        
        /// <summary>
        /// Output analog part
        /// </summary>
        [UnitsNames("Unused", "Unused", "Unused")]
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
        [UnitsNames("0.0->100%(2-10V", "/")]
        Output2_10V,
        /// <summary>
        /// Custom analog part
        /// </summary>
        [UnitsNames("Custom1", "Custom1", "")]
        OutputAnalogCustom1,
        [UnitsNames("Custom2", "Custom2", "")]
        OutputAnalogCustom2,
        [UnitsNames("Custom3", "Custom3", "")]
        OutputAnalogCustom3,
        [UnitsNames("Custom4", "Custom4", "")]
        OutputAnalogCustom4,
        [UnitsNames("Custom5", "Custom5", "")]
        OutputAnalogCustom5
    }
}