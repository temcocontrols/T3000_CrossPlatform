using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WiringPiNet
{
    /// <summary>
    /// GPIO Pin modes
    /// </summary>
    public enum PinMode : int
    {
        Input = 0,
        Output = 1,
        PwmOutput = 2,
        GpioClock = 3,
        SoftPwmOutput = 4,
        SoftToneOutput = 5,
        PwmToneOutput = 6
    }

    /// <summary>
    /// Pin Values
    /// </summary>
    public enum PinValue : int
    {
        Low = 0,
        High = 1,
    }

    /// <summary>
    /// Pin interna pull resistor mode
    /// </summary>
    public enum PullMode : int
    {
        Off = 0,
        Down = 1,
        Up = 2,
    }

    /// <summary>
    /// Pulse width modulation mode
    /// </summary>
    public enum PwmMode : int
    {
        Ms = 0,
        Bal = 1,
    }

    /// <summary>
    /// Interrupt level mode
    /// </summary>
    public enum InterruptLevel : int
    {
        EdgeSetup = 0,
        EdgeFalling = 1,
        EdgeRising = 2,
        EdgeBoth = 3,
    }

    /// <summary>
    /// Board Models
    /// </summary>
    public enum BoardModel : int
    {
        Unknown = 0,
        PiA = 1,
        PiB = 2,
        PiBP = 3,
        PiCM = 4,
        PiAP = 5,
        OdroidC = 6,
        OdroidXU34 = 7,
    }

    /// <summary>
    /// Board revisions
    /// </summary>
    public enum BoardVersion : int
    {
        Unknown = 0,
        Version1 = 1,
        Version11 = 2,
        Version12 = 3,
        Version2 = 4,
    }

    /// <summary>
    /// Makers
    /// </summary>
    public enum BoardMaker : int
    {
        Unknown = 0,
        EgoMan = 1,
        Sony = 2,
        Quisda = 3,
        HardKernel = 4,
    }

    /// <summary>
    /// 2 SPI Channels
    /// </summary>
    public enum SPIChannels: int
    {
        SPI0 = 0,
        SPI1 = 1
    }

   

    /// <summary>
    /// All types of T3
    /// </summary>
    public enum T3Type: int
    {
        BB = 0, //MiniType can be BIG or SMALL
        LB = 1,
        TB = 2
    }

    /// <summary>
    /// Mini panel types
    /// </summary>
    public enum MiniPanelType: int
    {
        None = 0, //Do not get mini type
        BIG,
        SMALL,
        TINY
    }


//#define BIG 1
//#define SMALL 2
//#define TINY 3


    /// <summary>
    /// Original T3 SPI Commands for TOP PCB Communication
    /// </summary>
    public enum T3Commands: byte
    {
        Ç_INITIAL = 0x00,

        /// <summary>
        /// 0x10 + 24 bytes
        /// </summary>
        S_OUTPUT_LED = 0x10,
        /// <summary>
        /// 0x11 + 32 bytes
        /// </summary>
        S_INPUT_LED = 0x11,
        /// <summary>
        /// 0x12 + 6 bytes
        /// </summary>
        S_HI_SP_FLAG = 0x12,
        /// <summary>
        /// 0x13 + 6 bytes
        /// </summary>
        S_COMM_LED =  0x13,
        /// <summary>
        /// 0x14 + 64 bytes
        /// </summary>
        S_ALL = 0x14,

        G_SWTICH_STATUS = 0x20, /* 0x20 + 24 bytes */
        G_INPUT_VALUE = 0x21,   /* 0x21 + 64 bytes */
        G_TOP_CHIP_INFO = 0x23, /* 0x21 + 12 bytes */
        G_SPEED_COUNTER = 0x30,  // 112

        /// <summary>
        /// Get All Status
        /// 0x24 
        /// </summary>
        G_ALL = 0x24,

        S_55 = 0x55, //Unknown

        C_MINITYPE = 0x80,
        C_ASIX_ISP = 0X81,
        C_END = 255


    }


    public enum ISPFlag: int
    {
        Initial = 0,
        ISP = 1,
        Normal = 2
    }

}
