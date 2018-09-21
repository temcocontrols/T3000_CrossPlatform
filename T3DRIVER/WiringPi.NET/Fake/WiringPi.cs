using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WiringPiNet.Fake
{
    public class WiringPi
    {
		public delegate void WiringPiISRDelegate();

		public static bool WarningEnabled { get; set; }

		protected static void PrintWarning(String methodName)
		{
			if (WarningEnabled)
			{
				Console.WriteLine("Warning! Using fake WiringPi wrapper for method call WiringPi.{0}.", methodName);
			}
		}

        public static int WiringPiSetup()
		{
			PrintWarning("WiringPiSetup");
			return 0;
		}
			
        public static int WiringPiSetupSys()
		{
			PrintWarning("WiringPiSetupSys");
			return 0;
		}
			
        public static int WiringPiSetupGpio()
		{
			PrintWarning("WiringPiSetupGpio");
			return 0;
		}

        public static int WiringPiSetupPhys()
		{
			PrintWarning("WiringPiSetupPhys");
			return 0;
		}


        public static void PinModeAlt(int pin, int mode)
		{
			PrintWarning("PinModeAlt");
		}

        public static void PinMode(int pin, int mode)
		{
			PrintWarning("PinMode");
		}

        public static void PullUpDnControl(int pin, int pud)
		{
			PrintWarning("PullUpDnControl");
		}

        public static int DigitalRead(int pin)
		{
			PrintWarning("DigitalRead");
			return 0;
		}

        public static void DigitalWrite(int pin, int value)
		{
			PrintWarning("DigitalWrite");
		}

        public static void PwmWrite(int pin, int value)
		{
			PrintWarning("PwmWrite");
		}

        public static int AnalogRead(int pin)
		{
			PrintWarning("AnalogRead");
			return 0;
		}

        public static void AnalogWrite(int pin, int value)
		{
			PrintWarning("AnalogWrite");
		}


        public static int  PiBoardRev()
		{
			PrintWarning("PiBoardRev");
			return (int)BoardVersion.Unknown;
		}

        public static int  WpiPinToGpio(int wpiPin)
		{
			PrintWarning("WpiPinToGpio");
			return 0;
		}

        public static int  PhysPinToGpio(int physPin)
		{
			PrintWarning("PhysPinToGpio");
			return 0;
		}

        public static void SetPadDrive(int group, int value)
		{
			PrintWarning("SetPadDrive");
		}

        public static int  GetAlt(int pin)
		{
			PrintWarning("GetAlt");
			return 0;
		}

        public static void PwmToneWrite(int pin, int freq)
		{
			PrintWarning("PwmToneWrite");
		}

        public static void DigitalWriteByte(int value)
		{
			PrintWarning("DigitalWriteByte");
		}

        public static void PwmSetMode(int mode)
		{
			PrintWarning("PwmSetMode");
		}

        public static void PwmSetRange(uint range)
		{
			PrintWarning("PwmSetRange");
		}

        public static void PwmSetClock(int divisor)
		{
			PrintWarning("PwmSetClock");
		}

        public static void GpioClockSet(int pin, int freq)
		{
			PrintWarning("GpioClockSet");
		}


        public static int WaitForInterrupt(int pin, int mS)
		{
			PrintWarning("WaitForInterrupt");
			return 0;
		}

        public static int WiringPiISR(int pin, int mode, WiringPiISRDelegate callback)
		{
			PrintWarning("WiringPiISR");
			return 0;
		}


        public static int PiHiPri(int pri)
		{
			PrintWarning("PiHiPri");
			return 0;
		}


        public static void Delay(uint howLong)
		{
			PrintWarning("Delay");
		}

        public static void DelayMicroseconds(uint howLong)
		{
			PrintWarning("DelayMicroseconds");
		}

        public static uint Millis()
		{
			PrintWarning("Millis");
			return 0;
		}

        public static uint Micros()
		{
			PrintWarning("Micros");
			return 0;
		}
    }
}
