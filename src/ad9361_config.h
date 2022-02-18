/*
 * ad9361_config.h
 *
 *  Created on: 2018Äê3ÔÂ25ÈÕ
 *      Author: liche
 */

#ifndef SRC_AD9361_CONFIG_H_
#define SRC_AD9361_CONFIG_H_

#include "ad9361.h"
int32_t ad9361_config(struct ad9361_rf_phy *ad9361_phy) ;
int32_t ad9361_set_sample(struct ad9361_rf_phy *ad9361_phy,uint32_t *sample_freq);
#endif /* SRC_AD9361_CONFIG_H_ */
