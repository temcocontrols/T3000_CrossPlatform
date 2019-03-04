using System;
using System.Runtime.InteropServices;

namespace SpiApplication {

	class SpiLink {

		[DllImport("libspi.so", EntryPoint="spi_init")]
			public static extern int spi_init(int port);

		[DllImport("libspi.so", EntryPoint="spi_read")]

			unsafe public static extern char* spi_read(int cmd, int nbytes, int file);

		[DllImport("libspi.so", EntryPoint="spi_write")]

			unsafe public static extern void spi_write(int cmd, char *data, int data_length, int file);

		unsafe static void Main() {

			int fd = spi_init(1);
			char* ptr = spi_read(0x14, 67, fd);
			Console.WriteLine("fp {0}",fd);

		}
	}
}

