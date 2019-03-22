using System;
using System.Timers;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace WiringPiNet
{
	public class PinWatcher : IDisposable
	{
		public class PinsStateChangedEventArgs : EventArgs
		{
			public GpioPin[] Pins { get; protected set; }

			public PinsStateChangedEventArgs(IEnumerable<GpioPin> changedPins)
			{
				this.Pins = changedPins.ToArray();
			}
		}

		public delegate void PinsStateChangedEventHandler(object sender, PinsStateChangedEventArgs e);
		public event PinsStateChangedEventHandler PinsStateChanged;
			
		public double Interval { get { return timer.Interval; } set { timer.Interval = value; } }

		protected readonly object locker = new object();
		protected Timer timer;
		protected List<GpioPin> pins = new List<GpioPin>();

		public PinWatcher(double interval, params GpioPin[] pins)
		{
			Add(pins);

			timer = new Timer(interval);
			timer.Elapsed += TimerTick;
			timer.Enabled = true;
		}

		public GpioPin Get(int index)
		{
			lock (locker)
			{
				if (index < this.pins.Count)
				{
					return this.pins[index];
				}
			}

			return null;
		}

		public List<GpioPin> GetAll()
		{
			return pins;
		}

		public void Add(params GpioPin[] pins)
		{
			if (pins != null)
			{
				lock (locker)
				{
					this.pins.AddRange(pins);
				}
			}
		}

		public bool Contains(params GpioPin[] pins)
		{
			if (pins != null)
			{
				lock (locker)
				{
					foreach (GpioPin p in pins)
					{
						if (this.pins.Contains(p) == false)
						{
							return false;
						}
					}
				}

				return true;
			}

			return false;
		}

		public void Remove(params GpioPin[] pins)
		{
			if (pins != null)
			{
				lock (locker)
				{
					foreach (GpioPin p in pins)
					{
						this.pins.Remove(p);
					}
				}
			}
		}

		public void RemoveAll()
		{
			lock (locker)
			{
				this.pins.Clear();
			}
		}

		public void Start()
		{
			timer.Start();
		}

		public void Stop()
		{
			timer.Stop();
		}

		public void Dispose()
		{
			if (timer != null)
			{
				timer.Elapsed -= TimerTick;
				timer.Close();
			}
		}

		public void Probe()
		{
			TimerTick(this, null);
		}

		protected void TimerTick(object sender, ElapsedEventArgs e)
		{
			lock (locker)
			{
				List<GpioPin> changed = new List<GpioPin>();

				foreach (GpioPin pin in pins)
				{
					try
					{
						pin.Read();
						pin.GetMode();
						if (pin.HasValueChangedFromLastRead() || pin.HasModeChangedFromLastRead())
						{
							changed.Add(pin);
						}
					}
					catch { }
				}

				OnPinsValueChanged(changed);
			}
		}

		protected void OnPinsValueChanged(List<GpioPin> changedPins)
		{
			if (PinsStateChanged != null && changedPins.Count > 0)
			{
				PinsStateChanged.Invoke(this, new PinsStateChangedEventArgs(changedPins));
			}
		}
	}
}

