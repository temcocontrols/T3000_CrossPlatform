using System;
using System.Text;
using WiringPiNet.Exceptions;
using System.Collections.Generic;

namespace WiringPiNet
{
	public class SerialPort : IDisposable
	{
		public string Device { get; protected set; }
		public int FileDescriptor { get; protected set; }
		public int BaudRate { get; protected set; }

		public SerialPort (string device, int baud)
		{
			this.Device = device;
			this.BaudRate = baud;
			OpenDevice();
		}

		public void Dispose()
		{
			CloseDevice();
		}

		protected void OpenDevice()
		{
			FileDescriptor = WiringPiNet.Wrapper.Serial.SerialOpen(this.Device, this.BaudRate);

			if (FileDescriptor < 0)
			{
				throw new DeviceNotAvailableException(this.Device);
			}
		}

		protected void CloseDevice()
		{
			WiringPiNet.Wrapper.Serial.SerialClose(this.FileDescriptor);
		}

		public void Write(params byte[] b)
		{
			foreach (byte bb in b)
			{
				WiringPiNet.Wrapper.Serial.SerialPutByte(this.FileDescriptor, bb);
			}
		}

		public void Write(params char[] chr)
		{
			foreach (char c in chr)
			{
				WiringPiNet.Wrapper.Serial.SerialPutChar(this.FileDescriptor, c);
			}
		}

		public void Write(string str)
		{
			WiringPiNet.Wrapper.Serial.SerialPuts(this.FileDescriptor, str);
		}

		public void Write(string format, params object[] args)
		{
			Write(String.Format(format, args));
		}

		public byte ReadByte()
		{
			return WiringPiNet.Wrapper.Serial.SerialGetByte(this.FileDescriptor);
		}

		public byte[] ReadByte(int length)
		{
			List<byte> output = new List<byte>();

			for (int i = 0; i < length; i++)
			{
				output.Add(ReadByte());
			}

			return output.ToArray();
		}

		public byte[] ReadByte(params byte[] delimiter)
		{
			return ReadByte(null, delimiter);
		}

		public byte[] ReadByte(int? limit, params byte[] delimiter)
		{
			List<byte> output = new List<byte>();

			int i = 0;
			while (limit == null || i++ < limit.Value)
			{
				byte bt = ReadByte();
				if (Array.Exists(delimiter, x => x.Equals(bt)))
				{
					break;
				}
				else
				{
					output.Add(bt);
				}
			}

			return output.ToArray();
		}

		public char ReadChar()
		{
			return WiringPiNet.Wrapper.Serial.SerialGetChar(this.FileDescriptor);
		}

		public string ReadChar(int length)
		{
			StringBuilder sb = new StringBuilder();

			for (int i = 0; i < length; i++)
			{
				sb.Append(ReadChar());
			}

			return sb.ToString();
		}

		public string ReadChar(params char[] delimiter)
		{
			return ReadChar(null, delimiter);
		}

		public string ReadChar(int? limit, params char[] delimiter)
		{
			StringBuilder sb = new StringBuilder();

			int i = 0;
			while (limit == null || i++ < limit.Value)
			{
				char chr = ReadChar();
				if (Array.Exists(delimiter, x => x.Equals(chr)))
				{
					break;
				}
				else
				{
					sb.Append(chr);
				}
			}

			return sb.ToString();
		}

		public int GetAvailableDataLength()
		{
			return WiringPiNet.Wrapper.Serial.SerialDataAvail(this.FileDescriptor);
		}

		public void Flush()
		{
			WiringPiNet.Wrapper.Serial.SerialFlush(this.FileDescriptor);
		}
	}
}

