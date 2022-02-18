#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "gpio_initial.h"
#include "ad9361_api.h"
#include "parameters.h"
#include "platform.h"
#include "spi_ctrl.h"
#include "radio_set.h"
#include "ad9361_config.h"
#include "spidev_lib.h"


uint32_t fpga_ver=0xa4;
uint32_t sw_ver=0xa2;
uint32_t config_done=0;
uint32_t sample_rate = 40e6;
uint64_t tx_lo_freq = 1500e6;
uint64_t rx_lo_freq = 1500e6;
uint32_t bandwidth = 5e6;
//int32_t gain = 25;
//uint32_t txatt = 20e3;
int32_t gain = 8;//10
uint32_t txatt = 20e3;
uint32_t regr = REG_PRODUCT_ID;
int32_t tempa;
static struct ad9361_rf_phy *ad9361_phy;

int open_spi() {
	printf("config spi\n");
	spi_config_t spi_config;
	int spifd = 0;
	spi_config.mode = 0x5;
	spi_config.speed=500000;
	spi_config.delay=0;
	spi_config.bits_per_word=8;
	spifd = spi_open("/dev/spidev1.0", spi_config);
	if (spifd < 0) {
		printf("spi open error %d\n", spifd);
		return -1;
	}
	return spifd;
}

int close_spi(int fd) {
	spi_close(fd);
	return 0;
}

int config_gpio() {
	printf("config gpio\n");
	gpio_initial();
	return 0;
}

int init_ad9361(int spifd) {
	printf("init ad9361\n");
	default_init_param.gpio_resetb = RF1_RESETB;
	default_init_param.gpio_sync = -1;
	default_init_param.gpio_cal_sw1 = -1;
	default_init_param.gpio_cal_sw2 = -1;
	default_init_param.spifd = spifd;
	if (ad9361_init(&ad9361_phy, &default_init_param) != 0) {
		printf("init ad9361 failed\n");
		return -1;
	}
	return 0;
}

int config_ad9361() {
	printf("config ad9361\n");
	ad9361_spi_write(ad9361_phy->spi, REG_TX_CLOCK_DATA_DELAY, 0x40);
	int32_t val;
	val = ad9361_config(ad9361_phy);
	printf("REG_PRODUCT_ID=%2X\n\r", val);
	return val;
}

/* Set the Enable State Machine (ENSM) mode. */
int32_t _ad9361_set_en_state_machine_mode(uint32_t mode) {
	return ad9361_set_en_state_machine_mode(ad9361_phy, mode);
}

/* Get the Enable State Machine (ENSM) mode. */
int32_t _ad9361_get_en_state_machine_mode(uint32_t *mode) {
	return ad9361_get_en_state_machine_mode(ad9361_phy, mode);
}

/* Set the receive RF gain for the selected channel. */
int32_t _ad9361_set_rx_rf_gain(uint8_t ch, int32_t gain_db) {
	return ad9361_set_rx_rf_gain(ad9361_phy, ch, gain_db);
}

/* Get current receive RF gain for the selected channel. */
int32_t _ad9361_get_rx_rf_gain(uint8_t ch, int32_t *gain_db) {
	return ad9361_get_rx_rf_gain(ad9361_phy, ch, gain_db);
}

/* Set the RX RF bandwidth. */
int32_t _ad9361_set_rx_rf_bandwidth(uint32_t bandwidth_hz) {
	return ad9361_set_rx_rf_bandwidth(ad9361_phy, bandwidth_hz);
}

/* Get the RX RF bandwidth. */
int32_t _ad9361_get_rx_rf_bandwidth (uint32_t *bandwidth_hz) {
	return ad9361_get_rx_rf_bandwidth (ad9361_phy, bandwidth_hz);
}

/* Set the RX sampling frequency. */
int32_t _ad9361_set_rx_sampling_freq (uint32_t sampling_freq_hz) {
	return ad9361_set_rx_sampling_freq (ad9361_phy, sampling_freq_hz);
}

/* Get current RX sampling frequency. */
int32_t _ad9361_get_rx_sampling_freq (uint32_t *sampling_freq_hz) {
	return ad9361_get_rx_sampling_freq (ad9361_phy, sampling_freq_hz);
}

/* Set the RX LO frequency. */
int32_t _ad9361_set_rx_lo_freq (uint64_t lo_freq_hz) {
	return ad9361_set_rx_lo_freq (ad9361_phy, lo_freq_hz);
}

/* Get current RX LO frequency. */
int32_t _ad9361_get_rx_lo_freq (uint64_t *lo_freq_hz) {
	return ad9361_get_rx_lo_freq (ad9361_phy, lo_freq_hz);
}

/* Switch between internal and external LO. */
int32_t _ad9361_set_rx_lo_int_ext(uint8_t int_ext) {
	return ad9361_set_rx_lo_int_ext(ad9361_phy, int_ext);
}

/* Get the RSSI for the selected channel. */
int32_t _ad9361_get_rx_rssi(uint8_t ch, struct rf_rssi *rssi) {
	return ad9361_get_rx_rssi(ad9361_phy, ch, rssi);
}

/* Set the gain control mode for the selected channel. */
int32_t _ad9361_set_rx_gain_control_mode(uint8_t ch, uint8_t gc_mode) {
	return ad9361_set_rx_gain_control_mode(ad9361_phy, ch, gc_mode);
}

/* Get the gain control mode for the selected channel. */
int32_t _ad9361_get_rx_gain_control_mode(uint8_t ch, uint8_t *gc_mode) {
	return ad9361_get_rx_gain_control_mode(ad9361_phy, ch, gc_mode);
}

/* Set the RX FIR filter configuration. */
int32_t _ad9361_set_rx_fir_config(AD9361_RXFIRConfig fir_cfg) {
	return ad9361_set_rx_fir_config(ad9361_phy, fir_cfg);
}

/* Get the RX FIR filter configuration. */
int32_t _ad9361_get_rx_fir_config(uint8_t rx_ch, AD9361_RXFIRConfig *fir_cfg) {
	return ad9361_get_rx_fir_config(ad9361_phy, rx_ch, fir_cfg);
}

/* Enable/disable the TX FIR filter. */
int32_t _ad9361_set_tx_fir_en_dis (uint8_t en_dis) {
	return ad9361_set_tx_fir_en_dis (ad9361_phy, en_dis);
}

/* Get the status of the TX FIR filter. */
int32_t _ad9361_get_tx_fir_en_dis (uint8_t *en_dis) {
	return ad9361_get_tx_fir_en_dis (ad9361_phy, en_dis);
}

/* Get the TX RSSI for the selected channel. */
int32_t _ad9361_get_tx_rssi (uint8_t ch, uint32_t *rssi_db_x_1000) {
	return ad9361_get_tx_rssi (ad9361_phy, ch, rssi_db_x_1000);
}

/* Set the TX RF output port. */
int32_t _ad9361_set_tx_rf_port_output (uint32_t mode) {
	return ad9361_set_tx_rf_port_output (ad9361_phy, mode);
}

/* Get the selected TX RF output port. */
int32_t _ad9361_get_tx_rf_port_output (uint32_t *mode) {
	return ad9361_get_tx_rf_port_output (ad9361_phy, mode);
}

/* Enable/disable the auto calibration. */
int32_t _ad9361_set_tx_auto_cal_en_dis (uint8_t en_dis) {
	return ad9361_set_tx_auto_cal_en_dis (ad9361_phy, en_dis);
}

/* Get the status of the auto calibration flag. */
int32_t _ad9361_get_tx_auto_cal_en_dis (uint8_t *en_dis) {
	return ad9361_get_tx_auto_cal_en_dis (ad9361_phy, en_dis);
}

/* Store TX fastlock profile. */
int32_t _ad9361_tx_fastlock_store(uint32_t profile) {
	return ad9361_tx_fastlock_store(ad9361_phy, profile);
}

/* Recall TX fastlock profile. */
int32_t _ad9361_tx_fastlock_recall(uint32_t profile) {
	return ad9361_tx_fastlock_recall(ad9361_phy, profile);
}





