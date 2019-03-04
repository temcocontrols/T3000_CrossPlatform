/*
 * spi_devtest.c
 *
 *  Created on: Jan 19, 2019
 *      Author: Tejas
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include "comm.h"

char buf[10];
char buf2[10];

struct spi_ioc_transfer xfer[2];

int spi_init(int port) {
	static int file;
	char filename[40];
#if 0
	printf("Hello ===== \n");
#endif
	__u8 mode = 0, lsb, bits = 8;
	__u32 speed = 500000;

	if(port)
		strcpy(filename,"/dev/spidev0.1");
	else
		strcpy(filename,"/dev/spidev0.0");


	if ((file = open(filename, O_RDWR)) < 0) {
		perror("Failed to open the bus.");
		exit(1);
	}

	if (ioctl(file, SPI_IOC_WR_MODE, &mode) < 0) {
		perror("can't set spi mode");
		return 1;
	}

	if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		return 1;
	}

	if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed)<0) {
		perror("can't set max speed hz");
		return 1;
	}

	printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n", filename,
			mode, bits, lsb ? "(lsb first) " : "", speed);
	return file;
}

char * spi_read(int cmd, int nbytes, int file) {

	int status;
	int i;

	char *buf2 = malloc(nbytes * sizeof(char));

	memset(buf, 0, sizeof buf);
	memset(buf2, 0, sizeof buf2);

	buf[0] = cmd;
	buf[1] = 0xff;
	xfer[0].tx_buf = (unsigned long) buf;
	xfer[0].len = 2; /* Length of  command to write*/
	xfer[1].rx_buf = (unsigned long) buf2;
	xfer[1].len = nbytes; /* Length of Data to read */
	status = ioctl(file, SPI_IOC_MESSAGE(2), xfer);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return NULL;
	}

	for (i = 0; i < nbytes; i++)
		printf("check[%d] = %d\n", i, buf2[i]);

	return buf2;
}

void spi_write(int cmd, char *data, int data_length, int file) {

	int status;

	printf("At line number %d\n",__LINE__);

	char * buf = malloc(data_length * sizeof(char));

	printf("At line number %d\n",__LINE__);

	memset(buf, 0, data_length + 3);

	buf[0] = cmd;
	memcpy(&buf[1], data, data_length - 2);
//	strncpy(buf + 1, data, data_length);
	buf[data_length - 1] = 0x55;
	buf[data_length - 2] = 0xAA;
	xfer[0].tx_buf = (unsigned long) buf;
	xfer[0].len = data_length; /* Length of  command to write*/
	status = ioctl(file, SPI_IOC_MESSAGE(1), xfer);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return;
	}

}



