/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "spi_ctrl.h"

#include "util.h"
#include "platform.h"
#include "parameters.h"
uint32_t cdcm6208_init_data[] = {//40MHz reference clock
		((uint32_t) 3  << 16) | 0x10B0,
		((uint32_t) 0  << 16) | 0x01B1,
		((uint32_t) 1  << 16) | 0x0000,
		((uint32_t) 2  << 16) | 0x003B,
		((uint32_t) 3  << 16) | 0x10B0,
		((uint32_t) 4  << 16) | 0x306C,
		((uint32_t) 5  << 16) | 0x01B8,
		((uint32_t) 6  << 16) | 0x000E,
		((uint32_t) 7  << 16) | 0x0000,
		((uint32_t) 8  << 16) | 0x0014,
		((uint32_t) 9  << 16) | 0x2000,
		((uint32_t) 10 << 16) | 0x0000,
		((uint32_t) 11 << 16) | 0x0000,
		((uint32_t) 12 << 16) | 0x2052,
		((uint32_t) 13 << 16) | 0x0000,
		((uint32_t) 14 << 16) | 0x0000,
		((uint32_t) 15 << 16) | 0x0000,
		((uint32_t) 16 << 16) | 0x0000,
		((uint32_t) 17 << 16) | 0x0000,
		((uint32_t) 18 << 16) | 0x0000,
		((uint32_t) 19 << 16) | 0x0000,
		((uint32_t) 20 << 16) | 0x0000,
		((uint32_t) 21 << 16) | 0x0000,
		((uint32_t) 3  << 16) | 0x10F0,
	};
uint32_t cdcm6208_y5p_data = { ((uint32_t) 12 << 16) | 0x2052 };
uint32_t cdcm6208_y5s_data = { ((uint32_t) 12 << 16) | 0x4052 };
int32_t spi_write32(struct spi_device *spi, uint32_t val) {
	uint8_t buf[4];
	int32_t ret;
	uint32_t cmd = val;

	buf[0] = cmd >> 24;
	buf[1] = cmd >> 16;
	buf[2] = cmd >> 8;
	buf[3] = cmd & 0xFF;

	ret = spi_write_then_read(spi, buf, 4, NULL, 0);
	if (ret < 0) {
		return ret;
	}
	return 0;
}
int32_t cdcm6208_init(struct spi_device *spi) {
	int ret;
	int i;
	int32_t val = cdcm6208_spi_read(spi, 40);
	printf("cdcm6208_reg[40]=%lx\n", val);
	for (i = 0; i < ARRAY_SIZE(cdcm6208_init_data); i++) {
		ret = spi_write32(spi, cdcm6208_init_data[i]);
	}
	return ret;
}
int32_t cdcm6208_y5_internal(struct spi_device *spi) {
	int ret;
	ret = spi_write32(spi, cdcm6208_y5p_data);
	return ret;
}
int32_t cdcm6208_y5_external(struct spi_device *spi) {
	int ret;
	ret = spi_write32(spi, cdcm6208_y5s_data);
	return ret;
}
int32_t cdcm6208_spi_readm(struct spi_device *spi, uint32_t reg,
		uint8_t *rbuf, uint32_t num)
{
	uint8_t buf[2];
	int32_t ret;
	uint16_t cmd;

	cmd = 0x8000 | (reg & 0x7FF);
	buf[0] = cmd >> 8;
	buf[1] = cmd & 0xFF;
	ret = spi_write_then_read(spi, &buf[0], 2, rbuf, num);
	return ret;
}
int32_t cdcm6208_spi_read(struct spi_device *spi, uint32_t reg)
{
	uint8_t buf[2];
	int32_t ret;

	ret = cdcm6208_spi_readm(spi, reg, &buf[0], 2);
	if (ret < 0)
		return ret;
	uint16_t bufrx=(uint16_t)buf[0]<<8 | buf[1];
	return bufrx;
}
int32_t ad9361_spi_write_m1(struct spi_device *spi, uint32_t reg, uint32_t mask,
		uint32_t offset, uint32_t val) {
	uint8_t buf;
	int32_t ret;

	if (!mask)
		return -EINVAL;

	ret = ad9361_spi_readm(spi, reg, &buf, 1);
	if (ret < 0)
		return ret;

	buf &= ~mask;
	buf |= ((val << offset) & mask);

	return ad9361_spi_write(spi, reg, buf);
}
#define ad9361_spi_write_m(spi, reg, mask, val) \
		ad9361_spi_write_m1(spi, reg, mask, find_first_bit(mask), val)
int32_t ad9361_set_auxdac1(struct ad9361_rf_phy *phy, uint32_t val_mV) {
	uint32_t val, tmp;
	struct spi_device *spi = phy->spi;
	/* Disable DAC if val == 0, Ignored in ENSM Auto Mode */
	ad9361_spi_write_m(spi, REG_AUXDAC_ENABLE_CTRL, AUXDAC_MANUAL_BAR(1),
			val_mV ? 0 : 1);

	if (val_mV < 306)
		val_mV = 306;

	if (val_mV < 1888) {
		val = ((val_mV - 306) * 1000) / 1404; /* Vref = 1V, Step = 2 */
		tmp = AUXDAC_1_VREF(0);
	} else {
		val = ((val_mV - 1761) * 1000) / 1836; /* Vref = 2.5V, Step = 2 */
		tmp = AUXDAC_1_VREF(3);
	}

	val = clamp_t(uint32_t, val, 0, 1023);

	ad9361_spi_write(spi, REG_AUXDAC_1_WORD, val >> 2);
	ad9361_spi_write(spi, REG_AUXDAC_1_CONFIG, AUXDAC_1_WORD_LSB(val) | tmp);
	phy->auxdac1_value = val_mV;
	return 0;
}
