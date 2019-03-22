using System;
using System.Text;
using WiringPiNet;
using System.Collections.Generic;

namespace WiringPiNet.Tools
{
	public class SerializationTool
	{
		const char SEPARATOR = ';';

		public string SerializeState()
		{
			return SerializeState(0, 40);
		}

		public string SerializeState(int firstPin, int lastPin, Dictionary<int, string> tags = null)
		{
			List<GpioPin> pins = new List<GpioPin>();
			using (Gpio gpio = new Gpio())
			{
				for (int i = firstPin; i <= lastPin; i++)
				{
					GpioPin pin = gpio.GetPin(i);
					if (tags != null && tags.ContainsKey(pin.Number))
					{
						pin.Tag = tags[pin.Number];
					}
					pins.Add(pin);
				}
			}

			return SerializeState(pins);
		}

		public string SerializeState(IEnumerable<GpioPin> pins)
		{
			StringBuilder sb = new StringBuilder();

			foreach (GpioPin pin in pins)
			{
				try
				{
					pin.GetMode();
					pin.Read();
					sb.Append(pin.Number)
						.Append(SEPARATOR)
						.Append(pin.CurrentMode != null ? pin.CurrentMode.Value.ToString() : "")
						.Append(SEPARATOR)
						.Append(pin.CurrentValue != null ? pin.CurrentValue.Value.ToString() : "")
						.Append(SEPARATOR)
						.Append(pin.PullMode)
						.Append(SEPARATOR)
						.Append(pin.Tag)
						.Append("\n");
				}
				catch
				{
				}
			}

			return sb.ToString();
		}

		public string DeserializeState(string state)
		{
			Dictionary<int, string> tagsState;
			return DeserializeState(state, out tagsState);
		}

		public string DeserializeState(string state, out Dictionary<int, string> tagsState)
		{
			tagsState = new Dictionary<int, string>();

			StringBuilder log = new StringBuilder();

			if (state != null)
			{
				using (Gpio gpio = new Gpio())
				{
					string[] lines = state.Split(new string[]{ "\n" }, StringSplitOptions.RemoveEmptyEntries);
					foreach (string line in lines)
					{
						string[] fields = line.Split(SEPARATOR);
						if (fields.Length == 5)
						{
							try
							{
								int pinNumber = Int32.Parse(fields[0]);
								PinMode pinMode = (PinMode)Enum.Parse(typeof(PinMode), fields[1]);
								PinValue pinValue = (PinValue)Enum.Parse(typeof(PinValue), fields[2]);
								PullMode pullMode = (PullMode)Enum.Parse(typeof(PullMode), fields[3]);
								string tag = fields[4];

								GpioPin pin = gpio.GetPin(pinNumber);
								pin.Tag = tag;
								pin.SetMode(pinMode);
								pin.SetPullMode(pullMode);
								pin.Write(pinValue);

								if (tagsState != null)
								{
									tagsState.Add(pin.Number, pin.Tag);
								}

								log.AppendFormat("Pin {0} set to mode {1}, pull {2}, value {3}, tag {4}", pinNumber, pinMode, pullMode, pinValue, tag);
							}
							catch (Exception e)
							{
								log.AppendFormat("Error: {0}", e.Message);
							}

							log.AppendLine();
						}
					}
				}
			}

			return log.ToString();
		}

		public string DeserializeState(string state, IList<GpioPin> targetPins)
		{
			StringBuilder log = new StringBuilder();

			if (state != null)
			{
				string[] lines = state.Split(new string[]{ "\n" }, StringSplitOptions.RemoveEmptyEntries);
				foreach (string line in lines)
				{
					string[] fields = line.Split(SEPARATOR);
					if (fields.Length == 5)
					{
						try
						{
							int pinNumber = Int32.Parse(fields[0]);
							PinMode pinMode = (PinMode)Enum.Parse(typeof(PinMode), fields[1]);
							PinValue pinValue = (PinValue)Enum.Parse(typeof(PinValue), fields[2]);
							PullMode pullMode = (PullMode)Enum.Parse(typeof(PullMode), fields[3]);
							string tag = fields[4];

							GpioPin pin = targetPins[pinNumber];
							pin.Tag = tag;
							pin.SetMode(pinMode);
							pin.SetPullMode(pullMode);
							pin.Write(pinValue);

							log.AppendFormat("Pin {0} set to mode {1}, pull {2}, value {3}", pinNumber, pinMode, pullMode, pinValue);
						}
						catch (Exception e)
						{
							log.AppendFormat("Error: {0}", e.Message);
						}

						log.AppendLine();
					}
				}
			}

			return log.ToString();
		}
	}
}

