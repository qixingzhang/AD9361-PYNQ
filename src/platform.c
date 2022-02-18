/***************************************************************************//**
 *   @file   Platform.c
 *   @brief  Implementation of Platform Driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2013(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdint.h>
#include "util.h"
#include "platform.h"
#include "spidev_lib.h"
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/mman.h>

static inline void usleep(unsigned long usleep)
{
	unsigned long delay = 0;

	for(delay = 0; delay < usleep * 10; delay++);
}


/***************************************************************************//**
 * @brief spi_write_then_read
*******************************************************************************/
int spi_write_then_read(struct spi_device *spi,
		const unsigned char *txbuf, unsigned n_tx,
		unsigned char *rxbuf, unsigned n_rx)
{
	int spifd = spi->spifd;
	int ret = spi_xfer(spifd, txbuf, n_tx, rxbuf, n_rx);
	if (ret > 0) {
		return SUCCESS;
	} else {
		return -1;
	}
}

/***************************************************************************//**
 * @brief gpio_direction
*******************************************************************************/
void gpio_direction(uint8_t pin, uint8_t direction)
{
}

/***************************************************************************//**
 * @brief gpio_is_valid
*******************************************************************************/
bool gpio_is_valid(int number)
{
	if(number >= 0)
		return 1;
	else
		return 0;
}

/***************************************************************************//**
 * @brief gpio_set_value
*******************************************************************************/
void gpio_set_value(unsigned gpio, int value)
{
//	printf("set gpio %d to %d\n", gpio, value);
	unsigned num = 338 + 78 + gpio;
	FILE *p = NULL;
	char path_str[50];
	p = fopen("/sys/class/gpio/export", "w");
	fprintf(p, "%d", num);
	fclose(p);

	sprintf(path_str, "/sys/class/gpio/gpio%d/direction", num);
	p = fopen(path_str, "w");
	fprintf(p, "out");
	fclose(p);

	sprintf(path_str, "/sys/class/gpio/gpio%d/value", num);
	p = fopen(path_str, "w");
	fprintf(p, "%d", value);
	fclose(p);

	p = fopen("/sys/class/gpio/unexport", "w");
	fprintf(p, "%d", num);
	fclose(p);
}

/***************************************************************************//**
 * @brief udelay
*******************************************************************************/
void udelay(unsigned long usecs)
{
	usleep(usecs);
}

/***************************************************************************//**
 * @brief mdelay
*******************************************************************************/
void mdelay(unsigned long msecs)
{
	usleep(msecs * 1000);
}

/***************************************************************************//**
 * @brief msleep_interruptible
*******************************************************************************/
unsigned long msleep_interruptible(unsigned int msecs)
{
	mdelay(msecs);

	return 0;
}

unsigned mem_read32(unsigned addr, unsigned offset) {
	unsigned char *map_base;
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1) {
		printf("open /dev/mem fail\n");
		return -1;
	}
	map_base = mmap(0, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr);
	if (map_base == 0) {
		printf("NULL pointer\n");
		return -1;
	}
	unsigned byte0, byte1, byte2, byte3, value;
	byte0 = map_base[offset];
	byte1 = map_base[offset + 1];
	byte2 = map_base[offset + 2];
	byte3 = map_base[offset + 3];
	value = byte3 << 24 | byte2 << 16 | byte1 << 8 | byte0;
	close(fd);
	munmap(map_base, 0x1000);
	return value;
}

int mem_write32(unsigned addr, unsigned offset, unsigned value) {
	unsigned char *map_base;
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1) {
		printf("open /dev/mem fail\n");
		return -1;
	}
	map_base = mmap(0, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr);
	if (map_base == 0) {
		printf("NULL pointer\n");
		return -1;
	}
	map_base[offset] = value & 0xff;
	map_base[offset + 1] = (value >> 8) & 0xff;
	map_base[offset + 2] = (value >> 16) & 0xff;
	map_base[offset + 3] = (value >> 24) & 0xff;
	close(fd);
	munmap(map_base, 0x1000);
	return 0;
}

