using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WiringPiNet.Wrapper
{
    public class Serial
    {
        [DllImport("libwiringPi.so", EntryPoint = "serialOpen")]
        public static extern int SerialOpen(string device, int baud);

        [DllImport("libwiringPi.so", EntryPoint = "serialClose")]
        public static extern void SerialClose(int fd);

        [DllImport("libwiringPi.so", EntryPoint = "serialFlush")]
        public static extern void SerialFlush(int fd);

        [DllImport("libwiringPi.so", EntryPoint = "serialPutchar")]
		public static extern void SerialPutChar(int fd, char c);

		[DllImport("libwiringPi.so", EntryPoint = "serialPutchar")]
		public static extern void SerialPutByte(int fd, byte c);

        [DllImport("libwiringPi.so", EntryPoint = "serialPuts")]
        public static extern void SerialPuts(int fd, string c);

        [DllImport("libwiringPi.so", EntryPoint = "serialDataAvail")]
        public static extern int SerialDataAvail(int fd);

        [DllImport("libwiringPi.so", EntryPoint = "serialGetchar")]
		public static extern char SerialGetChar(int fd);

		[DllImport("libwiringPi.so", EntryPoint = "serialGetchar")]
		public static extern byte SerialGetByte(int fd);
    }
}
