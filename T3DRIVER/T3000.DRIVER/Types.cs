using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace T3000.DRIVER
{
    /// <summary>
    /// Lists basic configurations for AO
    /// </summary>
    public enum AOPinConfig : int
    {
        RSET_ALL = 0,
        OUT13_19 = 1,
        OUT14_20 = 2,
        OUT15_21 = 3,
        OUT16_22 = 4,
        OUT17_23 = 5
    }

    /// <summary>
    /// Switches states
    /// </summary>
    public enum SWSTATES: int
    {
        OFF = 0,
        AUTO = 1,
        HAND = 2 
    }

    /// <summary>
    /// Ranges for Inputs
    /// </summary>
    public enum RANGES: int
    {
        V0_5 = 0,
        V0_10 = 1,
        I0_20ma = 2,
        V3_0 = 3,
        Thermistor = 3 //Resistencia de calor según creo
    }

    /// <summary>
    /// Outputs info
    /// </summary>
    public class OutputInfo
    {
        /// <summary>
        /// Switch status
        /// </summary>
        public byte SwitchStatus { get; set; } = 0;

        public string Name { get; set; }

        public SWSTATES State => (SWSTATES)SwitchStatus;
    }

    /// <summary>
    /// Leds Info
    /// </summary>
    public class LedInfo
    {
        public byte LedStatus { get; set; } = 0;
        public string Name { get; set; }
    }

    /// <summary>
    /// Inputs Info
    /// </summary>
    public class InputInfo
    {
        public byte[] ADValue { get; set; } = { 0, 0 };
        public byte Range { get; set; } = 3;
        public string Name { get; set; }

        public RANGES RangeValue => (RANGES)Range;
    }

    /// <summary>
    /// HSP Counters Info
    /// </summary>
    public class HSPInfo
    {
        public byte[] HSPValue { get; set; } = { 0, 0 , 0 ,0 };
        public string Name { get; set; }

    }

}
