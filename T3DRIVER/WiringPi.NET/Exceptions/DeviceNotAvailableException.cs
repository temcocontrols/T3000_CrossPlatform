using System;

namespace WiringPiNet.Exceptions
{
	public class DeviceNotAvailableException : Exception
	{
		public string DeviceName { get; protected set; }

		public DeviceNotAvailableException (string deviceName) 
			: base("Device " + deviceName + " not available.")
		{
			this.DeviceName = deviceName;
		}
	}
}

