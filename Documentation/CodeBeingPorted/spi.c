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

int spi_init(char filename[40]) {
	static int file;
	__u8 mode = 0, lsb, bits = 8;
	__u32 speed = 500000;

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


int main()
{
	int fd;
	char *check, *send_buf;
	int i;

	send_buf = (char *) calloc(S_COMM_LED_LEN, sizeof(char));

	fd = spi_init("/dev/spidev0.1");

	send_buf[0] = 0xFF;
	send_buf[1] = 0xFF;
//	for (i = 2; i < 64; i++)
//		send_buf[i] = 255;
//
//
//	spi_write(S_ALL, send_buf , S_ALL_LEN, fd);
//
	spi_write(S_COMM_LED, send_buf, S_COMM_LED_LEN, fd);
	free(send_buf);

	check = spi_read(G_ALL, G_ALL_LEN, fd);

	free(check);

	spi_write(S_COMM_LED, send_buf, S_COMM_LED_LEN, fd);
	free(send_buf);

	close(fd);
	return 0;
}
