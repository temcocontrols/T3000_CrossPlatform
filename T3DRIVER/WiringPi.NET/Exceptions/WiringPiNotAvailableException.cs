using System;

namespace WiringPiNet.Exceptions
{
	public class WiringPiNotAvailableException : Exception
	{
		public WiringPiNotAvailableException()
			:base("Unable to start WiringPi library.")
		{
		}
	}
}

