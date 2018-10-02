using System;
using WiringPiNet.Wrapper;

namespace WiringPiNet
{
	public class Pwm : IDisposable
	{
		public void SetRange(uint range)
		{
			Wrapper.WiringPi.PwmSetRange(range);
		}

		public void SetClock(int divisor)
		{
			Wrapper.WiringPi.PwmSetClock(divisor);
		}

		public void SetMode(PwmMode mode)
		{
			Wrapper.WiringPi.PwmSetMode((int)mode);
		}

		public void Write(int pin, int value)
		{
			Wrapper.WiringPi.PwmWrite(pin, value);
		}

		public void Dispose()
		{
			
		}
	}
}