using System;
using System.Collections.Generic;
using System.Text;
using WiringPiNet;
using WiringPiNet.Wrapper;
using WiringPiNet.Tools;
using WiringPiNet.Exceptions;
using FileLog;
using System.Runtime.InteropServices;

namespace T3000.DRIVER
{
    /// <summary>
    /// Setup procedures for T3000
    /// </summary>
    public class RPIDriver
    {
        /// <summary>
        /// T3 Type
        /// </summary>
        public T3Type T3 { get; set; } = T3Type.BB;
        /// <summary>
        /// Mini panel type
        /// </summary>
        public MiniPanelType MiniType { get; set; } = MiniPanelType.BIG;


        public const int MAX_GPIO_NUMBER = 40;
        public const int PIN_START_INTERVAL = 100;
        public const int PIN_INTERVAL_CHANGE_STEP = 10;
        public const int PINS_LIST_OFFSET = 4;

        public const int HI_COMMON_CHANNEL = 6;
        public const int MAX_INPUTS = 32;



        protected PinWatcher watcher;
        public GpioPin[] pins = new GpioPin[MAX_GPIO_NUMBER + 1];



        /// <summary>
        /// Channel SPI
        /// </summary>
        public SPIChannels SPIx { get; set; } = SPIChannels.SPI1; //Default SPI Channel 0

        /// <summary>
        /// I2C File Descriptor
        /// </summary>
        public int I2CFD = -1;

        /// <summary>
        /// Is SPI connected?
        /// </summary>
        public bool isSPIConnected { get; set; } = false;
        /// <summary>
        /// Is I2C connected?
        /// </summary>
        public bool IsI2CConnected { get; set; } = false;

        /// <summary>
        /// CLK pin
        /// </summary>
        public int GPIOClockPin { get; set; } = 5;//5; //GPIO 21??
        /// <summary>
        /// CLK Speed
        /// </summary>
        public int GPIOClockSpeed { get; set; } = 500000; // 0.5 Mhz not so fast for testing purposes??


        private PinMode BackupPinMode = PinMode.Input;
        private PinValue BackupPinValue = PinValue.Low;


        /// <summary>
        /// GPIO and initilizer
        /// </summary>
        public Gpio gpio { get; set; }

        /// <summary>
        /// Log File
        /// </summary>
        public FileLogger Log { get; set; }

        /// <summary>
        /// Initial setup for GpioClock and SPI
        /// </summary>
        public RPIDriver()
        {
            Log = new FileLogger();
            try
            {
                //Same as WiringPiSetup
                gpio = new Gpio(Gpio.NumberingMode.Broadcom);
                Log.Add($"Sucess! WiringPi setup in {gpio.PinNumberingMode} mode");
                //Export all pins
                UpdatePinStates();

            }
            catch (Exception ex)
            {
                Log.Add("Error: Failed to initialize WiringPi");
                Log.Add(ex.Message, false);
                throw ex;
            }

        }


        /// <summary>
        /// Keeps updated local copy of pins
        /// </summary>
        protected void UpdatePinStates()
        {
            try
            {
                for (int i = 0; i <= MAX_GPIO_NUMBER; i++)
                {
                    pins[i] = gpio.GetPin(i);
                }
            }
            catch (Exception ex)
            {

                throw ex;
            }
        }


        /// <summary>
        /// Executes GPIO -g readall
        /// Uses GPIO (BCM native) pin numberings
        /// </summary>
        /// <returns>result of gpio readall</returns>
        public string ReadAllPins()
        {

            UpdatePinStates();

            var pinstatus = "gpio -g readall".Bash();
            Log.Add("Invoke of GPIO -g readall");
            Log.Add(pinstatus, false);
            return pinstatus;

        }


        /// <summary>
        /// Sets and interrupt and IRQHandler on GPIOClockPin
        /// </summary>
        public void SetInterrupt()
        {
            try
            {
                //gpio.SetPullMode(GPIOClockPin, PullMode.Up);
                InterruptLevel LevelMode = InterruptLevel.EdgeFalling;
                WiringPi.WiringPiISR(GPIOClockPin, LevelMode, IRQHandler);
                Log.Add($"IRQHandler is active for {LevelMode} interrupt on pin {GPIOClockPin}");
                UpdatePinStates();
            }
            catch (Exception ex)
            {

                throw ex;
            }
        }



        /// <summary>
        /// Truly Read / Write byte via SPI
        /// </summary>
        /// <param name="newByte">Input-Write byte</param>
        /// <returns>Output-Read byte</returns>
        public byte SPI_RW_byte(byte? newByte)
        {

            byte[] innerbuffer = new byte[1];
            if (newByte.HasValue)
                innerbuffer[0] = newByte.GetValueOrDefault();

            int retval = SPI.WiringPiSPIDataRW(SPIx, innerbuffer, 1);
            if (retval != -1)
            {
                Log.Add($"Receiving {innerbuffer[0]} from {SPIx} channel");
                return innerbuffer[0];

            }

            else
            {
                Log.Add($"Failing to read/write {SPIx} channel");
                return 0x00;
            }

        }


        
        /*=============================================================*/

        public int state = 0; //current state of SPI communications


        public byte SPICommand = 0; //current command in progress
        public byte[] SPIRXBuffer = new byte[120];


        //private ISPFlag flag_ISP = ISPFlag.Initial; //// 0 - initial, 1 - isp,  2 - normal

        //private long[] test = new long[200]; //various counters for different tests


        //Unidimensional status arrays of bytes
        private byte[] LED_Status = new byte[67]; //All led status

        public byte[] Switch_Status = new byte[24]; //24 switches status

        public byte[,] high_speed_counter = new byte[HI_COMMON_CHANNEL,4];
        public byte[,] inputs = new byte[MAX_INPUTS,2]; //Output values (Analog-Digital)


       // private int array_index = 0;
        public string OutputChain = "";


        #region SPI Methods

        /// <summary>
        /// Interrupt Request Handler for pin GPIOx (SPI driver)
        /// </summary>
        public void IRQHandler()
        {

            if (state == 0) //No command in progress., auto G_ALL
            {

                if (SPICommand == 0)
                {
                    WiringPi.DelayMicroseconds(100); //Wait  for a new command or AUTO G_ALL
                    if (SPICommand == 0)
                        SPICommand = (byte)T3Commands.G_ALL;
                }


                SPIRXBuffer = new byte[120];
                SPIRXBuffer[0] = SPICommand;
                SPI.WiringPiSPIDataRW(SPIx, SPIRXBuffer, 120);

                state = 1;

                switch (SPICommand)
                {
                    case (byte)T3Commands.S_ALL:
                        break;
                    case (byte)T3Commands.G_TOP_CHIP_INFO:
                        break;
                    case (byte)T3Commands.G_ALL:
                        G_ALL_Proc();
                        break;
                    case (byte)T3Commands.C_MINITYPE:
                        break;
                        //default:
                        //    if (SPICommand == 0x55) //0x55 IS flag for ISP???
                        //        flag_ISP = ISPFlag.ISP;
                        //    else
                        //        flag_ISP = ISPFlag.Normal;
                        //    break;
                }

            }

        }

        /// <summary>
        /// Process command G_ALL
        /// </summary>
        public void G_ALL_Proc()
        {
            int array_index = 0;
            int i = 0;
            int adix;
            int adsubidx;
            state = 1; //do not allow other commands while processing.

            try
            {
                switch (T3)
                {
                    case T3Type.BB:

                        if (MiniType == MiniPanelType.BIG || MiniType == MiniPanelType.SMALL)
                        {

                            //Get switches status
                            for (i = 0; i < 24; i++)
                            {
                                Switch_Status[array_index] = SPIRXBuffer[i + 3]; //skip first 3 0xAA
                                array_index++;
                            }
                            //Get inputs status
                            for (i = 24; i < 88; i++)
                            {
                                adix = (array_index - 24) / 2;      //count 1 for every 2, starting from 0
                                adsubidx = (array_index - 24) % 2;  //0 or 1

                                inputs[adix, adsubidx] = SPIRXBuffer[i + 3];
                                array_index++;
                            }

                            //Get HSP counters status
                            for (i = 88; i < 112; i++)
                            {
                                int hscidx = (array_index - 88) / 4; //count 1 every 4, starting from 0
                                int hscsubidx = (array_index - 88) % 4; //0, 1 ,2 or 3
                                high_speed_counter[hscidx, hscsubidx] = SPIRXBuffer[i + 3];
                                array_index++;
                            }
                        }
                        break;
                }

                //Always return to listening mode.
                SPICommand = 0;
                state = 0;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        /// <summary>
        /// Start SPI
        /// </summary>
        public void StartSPI()
        {
            try
            {
                int fd = SPI.WiringPiSPISetup(SPIx, GPIOClockSpeed);
                if (fd != -1)
                {
                    isSPIConnected = true;
                    UpdatePinStates();
                    Log.Add($"Channel {SPIx} succesfully open, filedescriptor is {fd}");
                }
                else
                {
                    isSPIConnected = false;
                    throw new UnauthorizedAccessException($"Failure to open channel {SPIx}");
                }

            }
            catch (Exception ex)
            {
                Log.Add($"Error while initiating SPI on channel {SPIx}");
                throw ex;
            }

        }

        #endregion

        #region GPIO Clock Methods

        /// <summary>
        /// Start GPIO Clock
        /// </summary>
        public void StartGPIOClock()
        {
            BackupPinMode = gpio.GetMode(GPIOClockPin);
            BackupPinValue = gpio.Read(GPIOClockPin);

            gpio.SetMode(GPIOClockPin, PinMode.GpioClock);
            gpio.SetClock(GPIOClockPin, GPIOClockSpeed);
            UpdatePinStates();
            Log.Add($"Pin {GPIOClockPin} in clock mode at {GPIOClockSpeed}");

        }

        /// <summary>
        /// Stop GPIO Clock
        /// </summary>
        public void StopGPIOClock()
        {

            gpio.SetMode(GPIOClockPin, PinMode.Output);
            gpio.Write(GPIOClockPin, PinValue.Low);
            UpdatePinStates();
            Log.Add($"Pin {GPIOClockPin} {BackupPinMode} mode set");
        }

        #endregion

        #region Watcher Methods

        /// <summary>
        /// Start pin watcher on all pins
        /// </summary>
        public void StartWatcher()
        {
            watcher = new PinWatcher(PIN_START_INTERVAL, pins);
            watcher.PinsStateChanged += PinsStateUpdate;
            watcher.Start();
            Log.Add("Pin Watcher initiated");
        }

        /// <summary>
        /// Stop pin watcher
        /// </summary>
        public void StopWatcher()
        {
            for (int i = 0; i <= MAX_GPIO_NUMBER; i++)
            {
                watcher.RemoveAll();
            }

            watcher.Stop();
            watcher.PinsStateChanged -= PinsStateUpdate;
            watcher.Dispose();
            Log.Add("Pin Watcher finalized");
        }


        /// <summary>
        /// Update pins states
        /// Callback event handler for PinStateChanged.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void PinsStateUpdate(object sender, PinWatcher.PinsStateChangedEventArgs e)
        {
            if (e.Pins != null)
            {
                foreach (GpioPin pin in e.Pins)
                {
                    switch (pin.Number)
                    {
                        case 7:
                        case 9:
                            break;
                        case 28:
                            IRQHandler();
                            Log.Add($"Pin {pin.Number} has changed value from {pin.LastValue} to {pin.CurrentValue}");
                            break;
                        default:
                            break;
                    }

                }
                UpdatePinStates();
            }
        } 
        #endregion



        /// <summary>
        /// Start I2C for Device
        /// </summary>
        /// <param name="devID">Device ID</param>
        public void SetupI2C(int devID)
        {
            try
            {
                //I2CFD = I2C.WiringPiI2CSetup(devID); //Do not use this, it totally messed all up and tries to connect to I2C-1
                string devicename = "/dev/i2c-0";

                I2CFD = I2C.WiringPiI2CSetupInterface(devicename, devID);
                if (I2CFD != -1)
                {
                    IsI2CConnected = true;
                    UpdatePinStates();
                    Log.Add($"Device {devID.ToString("X2")} succesfully open, filedescriptor is {I2CFD}");
                }
                else
                {
                        IsI2CConnected = false;
                        throw new UnauthorizedAccessException($"Failure to open device {devID}");
                }

                }
            catch (Exception ex)
            {

                throw ex;
            }

        }


    }



}
