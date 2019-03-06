using System;
using System.Runtime.InteropServices;

namespace SpiApplication {

	class SpiLink {

		[DllImport("libspi.so", EntryPoint="spi_init")]
			public static extern int spi_init(int port);

		[DllImport("libspi.so", EntryPoint="spi_read")]

			unsafe public static extern char* spi_read(int cmd, int nbytes, int file);

		[DllImport("libspi.so", EntryPoint="spi_write")]

			unsafe public static extern void spi_write(int cmd, string data, int data_length, int file);

		unsafe static void Main() {

			char[] letters = {'ÿ','ÿ'};
			string alphabet = new string(letters);
			int fd = spi_init(1);
			spi_write(0x13, alphabet, 5, fd);
			//char* ptr = spi_read(0x14, 67, fd);
			//Console.WriteLine("fp {0}",fd);

		}
	}
}

