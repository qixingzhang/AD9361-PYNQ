/*
 * ad9361_config.h
 *
 *  Created on: 2018��3��25��
 *      Author: liche
 */

#include <stdint.h>
#include "ad9361_config.h"
#include "ad9361_api.h"
#include "platform.h"
extern uint32_t sample_rate;
extern uint64_t tx_lo_freq;
extern uint64_t rx_lo_freq;
extern uint32_t bandwidth;
extern int32_t gain;
extern uint32_t txatt;
extern uint32_t regr;
extern AD9361_RXFIRConfig rx_fir_config_4_128;
extern AD9361_TXFIRConfig tx_fir_config_4_128;
extern AD9361_RXFIRConfig rx_fir_config_2_128;
extern AD9361_TXFIRConfig tx_fir_config_2_128;
extern AD9361_RXFIRConfig rx_fir_config_2_96;
extern AD9361_TXFIRConfig tx_fir_config_2_96;
extern AD9361_RXFIRConfig rx_fir_config_2_64;
extern AD9361_TXFIRConfig tx_fir_config_2_64;
AD9361_TXFIRConfig tx_fir_config;
AD9361_RXFIRConfig rx_fir_config;
int32_t ad9361_set_sample(struct ad9361_rf_phy *ad9361_phy,
		uint32_t *sample_freq) {
	ad9361_set_trx_fir_en_dis(ad9361_phy, 0);
	if (*sample_freq > 53333333 && *sample_freq <= 61440000) {
		tx_fir_config = tx_fir_config_2_64;
		rx_fir_config = rx_fir_config_2_64;
	} else if (*sample_freq >= 40000000) {
		tx_fir_config = tx_fir_config_2_96;
		rx_fir_config = rx_fir_config_2_96;
	} else if (*sample_freq >= 20000000) {
		tx_fir_config = tx_fir_config_2_128;
		rx_fir_config = rx_fir_config_2_128;
	} else {
		tx_fir_config = tx_fir_config_4_128;
		rx_fir_config = rx_fir_config_4_128;
	}
	ad9361_set_tx_fir_config(ad9361_phy, tx_fir_config);
	ad9361_set_rx_fir_config(ad9361_phy, rx_fir_config);
	printf("tx_fir_config:coef_size=%d,int=%d\n", tx_fir_config.tx_coef_size,
			tx_fir_config.tx_int);
	printf("rx_fir_config:coef_size=%d,dec=%d\n", rx_fir_config.rx_coef_size,
			rx_fir_config.rx_dec);
	if (*sample_freq >= 25000000 / 12)
		ad9361_set_tx_sampling_freq(ad9361_phy, *sample_freq);
	else
		ad9361_set_tx_sampling_freq(ad9361_phy, 3e6);
	ad9361_set_trx_fir_en_dis(ad9361_phy, 1);
	if (*sample_freq < 25000000 / 12)
		ad9361_set_tx_sampling_freq(ad9361_phy, *sample_freq);
	ad9361_get_tx_sampling_freq(ad9361_phy, sample_freq);
	printf("sample_freq=%dHz\n", *sample_freq);
	return 0;
}
int32_t ad9361_config(struct ad9361_rf_phy *ad9361_phy) {
	ad9361_set_sample(ad9361_phy, &sample_rate);
	ad9361_set_tx_lo_freq(ad9361_phy, tx_lo_freq);
	ad9361_set_rx_lo_freq(ad9361_phy, rx_lo_freq);
	ad9361_set_rx_rf_bandwidth(ad9361_phy, bandwidth);
	ad9361_set_tx_rf_bandwidth(ad9361_phy, bandwidth);
	ad9361_set_rx_gain_control_mode(ad9361_phy, 0, RF_GAIN_MGC);
	ad9361_set_rx_gain_control_mode(ad9361_phy, 1, RF_GAIN_MGC);
	ad9361_set_rx_rf_gain(ad9361_phy, 0, gain);
	ad9361_set_rx_rf_gain(ad9361_phy, 1, gain);
	ad9361_set_tx_attenuation(ad9361_phy, 0, txatt);
	ad9361_set_tx_attenuation(ad9361_phy, 1, txatt);
	int32_t val;
	val = ad9361_spi_read(ad9361_phy->spi, regr);
//	ad9361_spi_write(ad9361_phy->spi, 0x3F4, 0x0B);
//	ad9361_spi_write(ad9361_phy->spi, 0x3F5, 0x41);
	return val;
}
