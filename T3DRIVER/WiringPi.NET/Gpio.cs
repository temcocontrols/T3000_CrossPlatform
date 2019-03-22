using System;
using WiringPiNet.Exceptions;
using WiringPiNet;
using System.Collections.Generic;
using WiringPiNet.Wrapper;

namespace WiringPiNet
{
	public class Gpio : IDisposable
	{
		public enum NumberingMode
		{
			Internal,
			Physical,
			System,
            Broadcom
		}

		public NumberingMode PinNumberingMode { get; protected set; }

		public Gpio()
			: this(NumberingMode.Internal)
		{
		}

		public Gpio(NumberingMode mode)
		{
			int output = -1;
			switch (mode)
			{
				default:
				case NumberingMode.Internal:
					output = WiringPi.WiringPiSetup();
					break;
				case NumberingMode.Physical:
					output = WiringPi.WiringPiSetupPhys();
					break;
				case NumberingMode.System:
					output = WiringPi.WiringPiSetupSys();
					break;
                case NumberingMode.Broadcom:
                    output = WiringPi.WiringPiSetupGpio();
                    break;
            }

			PinNumberingMode = mode;

			if (output < 0)
			{
				throw new WiringPiNotAvailableException();
			}
		}

		public GpioPin GetPin(int pinNumber)
		{
			return new GpioPin(this, pinNumber);
		}

		public void SetMode(int pin, PinMode mode)
		{
			WiringPi.PinMode(pin, (int)mode);
		}

		public PinMode GetMode(int pin)
		{
			return (PinMode)(WiringPi.GetAlt(pin));
		}

		public PinValue Read(int pin)
		{
			return (PinValue)WiringPi.DigitalRead(pin);
		}

		public void Write(int pin, PinValue value)
		{
			WiringPi.DigitalWrite(pin, (int)value);
		}

		public int ReadAnalog(int pin)
		{
			return WiringPi.AnalogRead(pin);
		}

		public void WriteAnalog(int pin, int value)
		{
			WiringPi.AnalogWrite(pin, value);
		}

		public void SetPullMode(int pin, PullMode mode)
		{
			WiringPi.PullUpDnControl(pin, (int)mode);
		}

		public void SetClock(int pin, int frequency)
		{
			WiringPi.GpioClockSet(pin, frequency);
		}

		public void WritePwm(int pin, int value)
		{
			WiringPi.PwmWrite(pin, value);
		}

		public void Dispose()
		{
		}
	}
}

