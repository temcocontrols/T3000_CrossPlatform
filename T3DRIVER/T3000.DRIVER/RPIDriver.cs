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


        public const int MAX_GPIO_NUMBER = 46;

        public const int PIN_START_INTERVAL = 100;
        public const int PIN_INTERVAL_CHANGE_STEP = 10;
        public const int PINS_LIST_OFFSET = 4;

        public const int MAX_HSP_COUNTERS = 6;
        public const int MAX_INPUTS = 32;
        public const int MAX_OUTPUTS = 24;
        public const int MAX_LEDS = 67;
        public const int MAX_AO_CONF = 7;





        protected PinWatcher watcher;

        private GpioPin[] PINS = new GpioPin[MAX_GPIO_NUMBER];
        private GpioPin[] AOControl = new GpioPin[MAX_AO_CONF];

        private OutputInfo[] OUTLED = new OutputInfo[MAX_OUTPUTS];
        private LedInfo[] LED = new LedInfo[MAX_LEDS];
        private InputInfo[] IN = new InputInfo[MAX_INPUTS];
        private HSPInfo[] HSP = new HSPInfo[MAX_HSP_COUNTERS];


        private PinMode BackupPinMode = PinMode.Input;
        private PinValue BackupPinValue = PinValue.Low;


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
        public bool SPIConnected { get; set; } = false;
        /// <summary>
        /// Is I2C connected?
        /// </summary>
        public bool I2CConnected { get; set; } = false;

        /// <summary>
        /// Clock pin
        /// </summary>
        public int GPIOClockPin { get; set; } = 5;//5; //GPIO 21??
        /// <summary>
        /// Clock Speed
        /// </summary>
        public int GPIOClockSpeed { get; set; } = 500000; // 500 khz ?? 0.5 Mhz not so fast for testing purposes??

                     
        /// <summary>
        /// GPIO instance, changes directly to this object will not be reflected on internal copy of PINS
        /// </summary>
        public Gpio GPIO { get; set; }

        /// <summary>
        /// Log File
        /// </summary>
        public FileLogger Log { get; set; }

        

        #region ******* CONSTRUCTOR AND INITIALIZER *******


        /// <summary>
        /// Initial setup for RPIDriver
        /// Creates a copy of GPIO Pins
        /// </summary>
        public RPIDriver()
        {
	    	Console.WriteLine("In the RPIDriver ctor 109");
            Log = new FileLogger();
	    	Console.WriteLine("In the RPIDriver ctor 111");
            try
            {
                //Same as WiringPiSetup
	    		Console.WriteLine("In the RPIDriver ctor 115");
                GPIO = new Gpio(Gpio.NumberingMode.Broadcom);
                Log.Add($"Sucess! WiringPi setup in {GPIO.PinNumberingMode} mode");
                Log.Add("PiBoard rev. = " + WiringPi.PiBoardRev().ToString());
                //Export all pins
	    		Console.WriteLine("In the RPIDriver ctor 120");
                UpdatePinStates();
	    		Console.WriteLine("In the RPIDriver ctor 122");
                //Initialize OUTInfos
/*                for (int i = 0; i < MAX_OUTPUTS; i++)
                {
	    	   		Console.WriteLine("In the RPIDriver ctor 126");
                    OUTLED[i].Name = $"OUT{i}";
	    	    	Console.WriteLine("In the RPIDriver ctor 128");
                    OUTLED[i].SwitchStatus = 0;
	    	    	Console.WriteLine("In the RPIDriver ctor 130");
                }
                //Initialize LEDInfos
                for (int i = 0; i < MAX_LEDS; i++)
                {
	    	    	Console.WriteLine("In the RPIDriver ctor 135");
                    LED[i].Name = $"LED{i}";
	    	    	Console.WriteLine("In the RPIDriver ctor 137");
                    LED[i].LedStatus = 0;
	    	    	Console.WriteLine("In the RPIDriver ctor 139");
                }
                //Initialize InputsInfos
                for (int i = 0; i < MAX_INPUTS; i++)
                {
	    	    	Console.WriteLine("In the RPIDriver ctor 144");
                    IN[i].Name = $"IN{i}";
	    	    	Console.WriteLine("In the RPIDriver ctor 147");
                    IN[i].ADValue = new byte[] { 0, 0 };
	    	    	Console.WriteLine("In the RPIDriver ctor");
                    IN[i].Range = (int)RANGES.V3_0; //Default is Thermistor as seen in c++
	    	    	Console.WriteLine("In the RPIDriver ctor");
                }

                //Initialize HSPInfos
                for (int i = 0; i < MAX_HSP_COUNTERS; i++)
                {
	    	    	Console.WriteLine("In the RPIDriver ctor");
                    HSP[i].Name = $"HSP{i}";
	    	    	Console.WriteLine("In the RPIDriver ctor");
                    HSP[i].HSPValue = new byte[] { 0, 0, 0, 0 };
	    	    	Console.WriteLine("In the RPIDriver ctor");
                }*/
            }
            catch (Exception ex)
            {
                Log.Add("Error: Failed to initialize WiringPi");
                Log.Add(ex.Message, false);
                throw ex;
            }

        }

        #endregion




        #region GPIO & Info Methods


        /// <summary>
        /// Keeps updated local copy of pins
        /// </summary>
        protected void UpdatePinStates()
        {
        	Console.WriteLine("In the RPIDriver ctor 185");
            try
            {
            	Console.WriteLine("In the RPIDriver ctor 188");
                for (int i = 0; i < MAX_GPIO_NUMBER; i++)
                {
                    PINS[i] = GPIO.GetPin(i);
                }
                Console.WriteLine("In the RPIDriver ctor 193");
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
        /// Printable list of switches states
        /// </summary>
        /// <returns></returns>
        public string PrintSwitchesStatus()
        {
            string retval = "SW STATES:";
            for (int i = 0; i < MAX_OUTPUTS; i++)
            {
                retval += Environment.NewLine +  $"{OUTLED[i].Name}->{OUTLED[i].State}" ;
            }

            return retval;
        }

        /// <summary>
        /// Printable list of inputs values
        /// </summary>
        /// <returns></returns>
        public string PrintInputsValues()
        {
            string retval = "IN VALUES:";
            for (int i = 0; i < MAX_INPUTS; i++)
            {
                retval += Environment.NewLine + $"{IN[i].Name}->{IN[i].ADValue[0]} {IN[i].ADValue[1]}";
            }

            return retval;
        }


        /// <summary>
        /// Get Switch State
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public SWSTATES SwitchState(int index) => index < MAX_OUTPUTS ?  OUTLED[index].State:0;

        //TODO: Add method to get Input AD Values
        //TODO: Add method to get HSP values

        #endregion



        /*=============================================================*/
        //TODO: Encapsulate this attributes for SPI
        public int state = 0; //current state of SPI communications
        public byte SPICommand = 0; //current command in progress
        public byte[] SPIRXBuffer = new byte[120];






        #region SPI Methods


        //REMOVE: private ISPFlag flag_ISP = ISPFlag.Initial; //// 0 - initial, 1 - isp,  2 - normal
        //REMOVE: private byte[] LED_Status = new byte[MAX_LEDS]; //All led status
        //REMOVE : public byte[] Switch_Status = new byte[24]; //24 switches status
        //REMOVE: public byte[,] high_speed_counter = new byte[MAX_HSP_COUNTERS, 4];
        //REMOVE: public byte[,] inputs = new byte[MAX_INPUTS, 2]; //Output values (Analog-Digital)


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
                        //TODO: In order to handle this CMD, we need to implement I2S over SPI using WiringPi
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
            int input_index;
            int advalue_index;
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
                                OUTLED[i].SwitchStatus = (byte) SPIRXBuffer[i + 3]; //skip first 3 0xAA
                                //Switch_Status[array_index] = SPIRXBuffer[i + 3]; //skip first 3 0xAA
                                array_index++;
                            }
                            //Get inputs values
                            for (i = 24; i < 88; i++)
                            {
                               
                                input_index = (array_index - 24) / 2;   //adix counts from 0 to 31 as there are 32 Inputs    

                                advalue_index = (array_index - 24) % 2;  //0 or 1

                                IN[input_index].ADValue[advalue_index] = SPIRXBuffer[i + 3]; //skip first 3 0xAA

                                //inputs[adix, adsubidx] = SPIRXBuffer[i + 3];
                                array_index++;
                            }

                            //Get HSP counters status
                            for (i = 88; i < 112; i++)
                            {
                                int hsp_index = (array_index - 88) / 4; //count 1 every 4, starting from 0
                                int hspbyte_index = (array_index - 88) % 4; //0, 1 ,2 or 3

                                HSP[hsp_index].HSPValue[hspbyte_index] = SPIRXBuffer[i + 3]; //skip first 3 0xAA

                                //high_speed_counter[hsp_index, hspbyte_index] = SPIRXBuffer[i + 3]; //skip first 3 0xAA
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
                    SPIConnected = true;
                    UpdatePinStates();
                    Log.Add($"Channel {SPIx} succesfully open, filedescriptor is {fd}");
                }
                else
                {
                    SPIConnected = false;
                    throw new UnauthorizedAccessException($"Failure to open channel {SPIx}");
                }

            }
            catch (Exception ex)
            {
                Log.Add($"Error while initiating SPI on channel {SPIx}");
                throw ex;
            }

        }


        /// <summary>
        /// Read / Write byte via SPI
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

        #endregion

        #region GPIO Clock and Interrupts Methods

        /// <summary>
        /// Start GPIO Clock
        /// </summary>
        public void StartGPIOClock()
        {
            BackupPinMode = GPIO.GetMode(GPIOClockPin);
            BackupPinValue = GPIO.Read(GPIOClockPin);

            GPIO.SetMode(GPIOClockPin, PinMode.GpioClock);
            GPIO.SetClock(GPIOClockPin, GPIOClockSpeed);
            UpdatePinStates();
            Log.Add($"Pin {GPIOClockPin} in clock mode at {GPIOClockSpeed}");

        }

        /// <summary>
        /// Stop GPIO Clock 
        /// </summary>
        public void StopGPIOClock()
        {

            GPIO.SetMode(GPIOClockPin, PinMode.Output);
            GPIO.Write(GPIOClockPin, PinValue.Low);
            UpdatePinStates();
            Log.Add($"Pin {GPIOClockPin} {BackupPinMode} mode set");
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


        #endregion

        #region Watcher Methods

        /// <summary>
        /// Start pin watcher on all pins
        /// </summary>
        public void StartWatcher()
        {
            watcher = new PinWatcher(PIN_START_INTERVAL, PINS);
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

        #region I²C Methods

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
                    I2CConnected = true;
                    UpdatePinStates();
                    Log.Add($"Device {devID.ToString("X2")} succesfully open, filedescriptor is {I2CFD}");
                }
                else
                {
                    I2CConnected = false;
                    throw new UnauthorizedAccessException($"Failure to open device {devID}");
                }

            }
            catch (Exception ex)
            {

                throw ex;
            }

        }

        #endregion

        #region PWM AO Control Methods


        public void SetDefaultAOControl()
        {
            //As stated by notes
            //ReconfigureAOControlPins(7, 0, 13, 14, 6, 18, 19);

            // This configuration turn on LED SCREEN
            ReconfigureAOControlPins(7, 0, 13, 14, 6, 40, 45);

            // Also read> GPIO18 ALT5 = PWM0 GPIO19 ALT5 = PWM1 GPIO12 ALT0 = PWM0 GPIO13 ALT0 = PWM1
        }

        /// <summary>
        /// Reconfigure AO Pins
        /// </summary>
        /// <param name="AO_GP1_EN">pin number, to enable mux chip number 1, AO1 thru 6</param>
        /// <param name="AO_GP2_EN">pin number, to enable mux chip number 2, AO7 thru 12</param>
        /// <param name="AO_CHSEL0"></param>
        /// <param name="AO_CHSEL1"></param>
        /// <param name="AO_CHSEL2"></param>
        /// <param name="PWM0"></param>
        /// <param name="PWM1"></param>
        public void ReconfigureAOControlPins(int AO_GP1_EN, int AO_GP2_EN, int AO_CHSEL0, int AO_CHSEL1, int AO_CHSEL2,
            int PWM0, int PWM1)
        {
            AOControl = new GpioPin[7];

            AOControl[0] = new GpioPin(GPIO, AO_GP1_EN);
            AOControl[1] = new GpioPin(GPIO, AO_GP2_EN);

            AOControl[2] = new GpioPin(GPIO, AO_CHSEL0);
            AOControl[3] = new GpioPin(GPIO, AO_CHSEL1);
            AOControl[4] = new GpioPin(GPIO, AO_CHSEL2);
            //PWM Pins
            AOControl[5] = new GpioPin(GPIO, PWM0);
            AOControl[6] = new GpioPin(GPIO, PWM1);

            //Use Wiring PWM FUNCTIONS TO START PULSE

            //Reset
            SetAOControlValues(AOPinConfig.RSET_ALL);

        }


        /// <summary>
        /// SEts AO pin values
        /// </summary>
        /// <param name="PinConfiguration">AO Configuration Const</param>
        /// <param name="usePWM0">Using PWM0</param>
        public void SetAOControlValues(AOPinConfig PinConfiguration, bool usePWM0 = true)
        {
            for (int i = 0; i < 5; i++)
            {
                AOControl[i].SetMode(PinMode.Output);
            }


            switch (PinConfiguration)
            {
                case AOPinConfig.OUT13_19: //1 1 0 0 0

                    AOControl[0].Write(PinValue.High);
                    AOControl[1].Write(PinValue.High);
                    AOControl[2].Write(PinValue.Low);
                    AOControl[3].Write(PinValue.Low);
                    AOControl[4].Write(PinValue.Low);


                    break;
                case AOPinConfig.OUT14_20: // 1 1 1 0 0
                    AOControl[0].Write(PinValue.High);
                    AOControl[1].Write(PinValue.High);
                    AOControl[2].Write(PinValue.High);
                    AOControl[3].Write(PinValue.Low);
                    AOControl[4].Write(PinValue.Low);
                    break;
                case AOPinConfig.OUT15_21: // 1 1 0 1 0 
                    AOControl[0].Write(PinValue.High);
                    AOControl[1].Write(PinValue.High);
                    AOControl[2].Write(PinValue.Low);
                    AOControl[3].Write(PinValue.High);
                    AOControl[4].Write(PinValue.Low);
                    break;
                case AOPinConfig.OUT16_22: // 1 1 1 1 0
                    AOControl[0].Write(PinValue.High);
                    AOControl[1].Write(PinValue.High);
                    AOControl[2].Write(PinValue.High);
                    AOControl[3].Write(PinValue.High);
                    AOControl[4].Write(PinValue.Low);
                    break;
                case AOPinConfig.OUT17_23: // 1 1 0 0 1
                    AOControl[0].Write(PinValue.High);
                    AOControl[1].Write(PinValue.High);
                    AOControl[2].Write(PinValue.Low);
                    AOControl[3].Write(PinValue.Low);
                    AOControl[4].Write(PinValue.High);
                    break;

                case AOPinConfig.RSET_ALL: // 0 0 0 0 0 
                default:
                    AOControl[0].Write(PinValue.Low);
                    AOControl[1].Write(PinValue.Low);
                    AOControl[2].Write(PinValue.Low);
                    AOControl[3].Write(PinValue.Low);
                    AOControl[4].Write(PinValue.Low);
                    break;

            }

            //Log PinConfiguration
            Log.Add("Setting Pin Configuration");
            for (int i = 0; i < 5; i++)
            {
                Log.Add($"GPIO{AOControl[i].Number} is {AOControl[i].CurrentMode} = {AOControl[i].Read()}", false);
            }



            if (PinConfiguration != AOPinConfig.RSET_ALL)
            {
                PinMode backupmode0 = AOControl[5].GetMode();
                PinMode backupmode1 = AOControl[6].GetMode();
                int PWMFreq = 50000; //50Mhz

                //Start PWM for adequate pin
                //Log PinConfiguration 
                Log.Add("Reading Pin Configuration before PWM");
                for (int i = 0; i < 2; i++)
                {
                    Log.Add($"GPIO{AOControl[i + 5].Number} is {AOControl[i + 5].CurrentMode} = {AOControl[i + 5].Read()}", false);

                    AOControl[5 + i].SetMode(PinMode.PwmOutput);
                    AOControl[5 + i].SetClock(PWMFreq);
                    AOControl[5 + i].SetPullMode(PullMode.Up);
                    AOControl[5 + i].WritePwm(0);
                }

                if (usePWM0)
                {
                    AOControl[5].WritePwm(100); //PWM0
                }
                else
                {
                    AOControl[5].WritePwm(100); //PWM0
                }

                //Log PinConfiguration
                Log.Add("Setting PWM Pin Configuration");
                for (int i = 0; i < 2; i++)
                {
                    Log.Add($"GPIO{AOControl[i + 5].Number} is {AOControl[i + 5].CurrentMode} = {AOControl[i + 5].Read()}", false);
                }

                //add delay here
                WiringPi.Delay(100);


                //Stop PWM for adequate pin

                AOControl[5].SetMode(backupmode0);
                AOControl[6].SetMode(backupmode1);
            }

        }

        #endregion
    }



}
