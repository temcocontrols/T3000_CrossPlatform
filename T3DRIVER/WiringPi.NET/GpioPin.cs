using System;
using WiringPiNet.Exceptions;
using WiringPiNet;
using System.Collections.Generic;
using WiringPiNet.Wrapper;

namespace WiringPiNet
{
	public class GpioPin
	{
		public class PinValueChangedEventArgs : EventArgs
		{
			public GpioPin Pin { get; set; }
		}

		public class PinModeChangedEventArgs : EventArgs
		{
			public GpioPin Pin { get; set; }
		}

		public delegate void PinValueChangedEventHandler(object sender, PinValueChangedEventArgs e);
		public delegate void PinModeChangedEventHandler(object sender, PinModeChangedEventArgs e);

		public event PinValueChangedEventHandler PinValueChanged;
		public event PinModeChangedEventHandler PinModeChanged;

		public Gpio Parent { get; protected set; }
		public int Number { get; protected set; }
		public PinValue? CurrentValue { get; protected set; }
		public PinValue? LastValue { get; protected set; }
		public PinMode? CurrentMode { get; protected set; }
		public PinMode? LastMode { get; protected set; }
		public PullMode PullMode { get; protected set; }
		public String Tag { get; set; }

		public GpioPin(Gpio parent, int number)
		{
			this.Parent = parent;
			this.Number = number;
		}

		public PinMode GetMode()
		{
			PinMode mode = Parent.GetMode(this.Number);
			this.LastMode = this.CurrentMode;
			this.CurrentMode = mode;

			if (HasModeChangedFromLastRead())
			{
				OnPinModeChanged();
			}

			return mode;
		}

		public void SetMode(PinMode mode)
		{
			Parent.SetMode(this.Number, mode);
		}

		public PinValue Read()
		{
			PinValue value = Parent.Read(this.Number);
			this.LastValue = this.CurrentValue;
			this.CurrentValue = value;

			if (HasValueChangedFromLastRead())
			{
				OnPinValueChanged();
			}

			return value;
		}

		public void Write(PinValue value)
		{
			Parent.Write(this.Number, value);
		}

		public int ReadAnalog()
		{
			return Parent.ReadAnalog(this.Number);
		}

		public void WriteAnalog(int value)
		{
			Parent.WriteAnalog(this.Number, value);
		}

		public void SetPullMode(PullMode mode)
		{
			this.PullMode = mode;
			Parent.SetPullMode(this.Number, mode);
		}

		public void SetClock(int frequency)
		{
			Parent.SetClock(this.Number, frequency);
		}

		public void WritePwm(int value)
		{
			Parent.WritePwm(this.Number, value);
		}

		public bool HasModeChangedFromLastRead()
		{
			return this.LastMode == null || this.LastMode.Equals(this.CurrentMode) == false;
		}

		public bool HasValueChangedFromLastRead()
		{
			return this.LastValue == null || this.LastValue.Equals(this.CurrentValue) == false;
		}

		protected void OnPinValueChanged()
		{
			if (PinValueChanged != null)
			{
				PinValueChanged.Invoke(this, new PinValueChangedEventArgs(){ Pin = this });
			}
		}

		protected void OnPinModeChanged()
		{
			if (PinModeChanged != null)
			{
				PinModeChanged.Invoke(this, new PinModeChangedEventArgs(){ Pin = this });
			}
		}
	}
}

