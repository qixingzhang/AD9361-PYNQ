///*
// * xadc.c
// *
// *  Created on: 2020Äê1ÔÂ22ÈÕ
// *      Author: lichen
// */
//#include "xadc.h"
//
//#include <stdio.h>
//static XAdcPs XAdcInstPtr;
//int xadc_initial(u16 XAdcDeviceId) {
//	int Status;
//	XAdcPs_Config *ConfigPtr;
//	ConfigPtr = XAdcPs_LookupConfig(XAdcDeviceId);
//	if (ConfigPtr == NULL) {
//		return XST_FAILURE;
//	}
//	XAdcPs_CfgInitialize(&XAdcInstPtr, ConfigPtr, ConfigPtr->BaseAddress);
//	Status = XAdcPs_SelfTest(&XAdcInstPtr);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}
//	XAdcPs_SetSequencerMode(&XAdcInstPtr, XADCPS_SEQ_MODE_SAFE);
//	return XST_SUCCESS;
//}
//int xadc_read_temp(float *Temp) {
//	u32 TempRawData;
//	float TempData;
//	TempRawData = XAdcPs_GetAdcData(&XAdcInstPtr, XADCPS_CH_TEMP);
//	TempData = XAdcPs_RawToTemperature(TempRawData);
//	*Temp = TempData;
//	return XST_SUCCESS;
//}
