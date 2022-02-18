/*
 *
 * This file is based on  of pyA20.
 * spi_lib.c python SPI extension.
 *
 * Copyright (c) 2014 Stefan Mavrodiev @ OLIMEX LTD, <support@olimex.com>
 *
 * pyA20 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * Adpated by Philippe Van Hecke <lemouchon@gmail.com>
 */


#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>

#include <linux/spi/spidev.h>

#include "spidev_lib.h"

int spi_open(char *device, spi_config_t config) {
    int fd;

    /* Open block device */
    fd = open(device, O_RDWR);
    if (fd < 0) {
        return fd;
    }

    /* Set SPI_POL and SPI_PHA */
    if (ioctl(fd, SPI_IOC_WR_MODE32, &config.mode) < 0) {
    	printf("SPI_IOC_WR_MODE32 set error\n");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MODE32, &config.mode) < 0) {
    	printf("SPI_IOC_RD_MODE32 set error\n");
        return -1;
    }

    /* Set bits per word*/
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &config.bits_per_word) < 0) {
    	printf("SPI_IOC_WR_BITS_PER_WORD set error\n");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &config.bits_per_word) < 0) {
    	printf("SPI_IOC_RD_BITS_PER_WORD set error\n");
        return -1;
    }

    /* Set SPI speed*/
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &config.speed) < 0) {
    	printf("SPI_IOC_WR_MAX_SPEED_HZ set error\n");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &config.speed) < 0) {
    	printf("SPI_IOC_RD_MAX_SPEED_HZ set error\n");
        return -1;
    }

    /* Return file descriptor */
    return fd;
}

int spi_close(int fd) {
    return close(fd);
}

//int32_t spi_xfer(int fd, uint8_t *data, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len)
//{
//	uint8_t bytes_number = rx_len + tx_len;
//	struct spi_ioc_transfer tr = {
//		.tx_buf = (unsigned long)data,
//		.rx_buf = (unsigned long)data,
//		.len = bytes_number,
//	};
//	int ret;
//
//
//	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
//	if (ret == 1) {
//		printf("%s: Can't send spi message\n\r", __func__);
//		return -1;
//	}
//	if (rx_len > 0) {
//	 	printf("ret: %02x\n", data[0]);
//	}
//	return 0;
//}


int spi_xfer(int fd, uint8_t *tx_buffer, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len) {

//	printf("write %d bytes: ", tx_len);
//	for (int i = 0; i < tx_len; i++) {
//		printf("%02x", tx_buffer[i]);
//	}
//	printf("\n");

    struct spi_ioc_transfer spi_message[2];
    int ret;
    memset(spi_message, 0, sizeof(spi_message));

    spi_message[0].tx_buf = (unsigned long)tx_buffer;
    spi_message[0].len = tx_len;
    spi_message[1].rx_buf = (unsigned long)rx_buffer;
    spi_message[1].len = rx_len;
    
    ret = ioctl(fd, SPI_IOC_MESSAGE(2), spi_message);
    if (ret < 0) {
    	printf("spi message send error\n");
    }
    return ret;
}

int spi_read(int fd, uint8_t *rx_buffer, uint8_t rx_len){
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    
    spi_message[0].rx_buf = (unsigned long)rx_buffer;
    spi_message[0].len = rx_len;
    
    
    return ioctl(fd, SPI_IOC_MESSAGE(1), spi_message);
}

int spi_write(int fd, uint8_t *tx_buffer, uint8_t tx_len){
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    
    spi_message[0].tx_buf = (unsigned long)tx_buffer;
    spi_message[0].len = tx_len;
    
    return ioctl(fd, SPI_IOC_MESSAGE(1), spi_message);
}


