/**
 * @file sensor_adv_format.c
 * @brief
 *
 * Copyright (c) 2020 Laird Connectivity
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/
#include "laird_bluetooth.h"
#include "sensor_adv_format.h"

/******************************************************************************/
/* Global Data Definitions                                                    */
/******************************************************************************/
const uint8_t BT510_AD_HEADER[SENSOR_AD_HEADER_SIZE] = {
	LSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	MSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	LSB_16(BT510_1M_PHY_AD_PROTOCOL_ID), MSB_16(BT510_1M_PHY_AD_PROTOCOL_ID)
};

const uint8_t BT510_RSP_HEADER[SENSOR_AD_HEADER_SIZE] = {
	LSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID2),
	MSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID2),
	LSB_16(BT510_1M_PHY_RSP_PROTOCOL_ID),
	MSB_16(BT510_1M_PHY_RSP_PROTOCOL_ID)
};

const uint8_t BT510_CODED_HEADER[SENSOR_AD_HEADER_SIZE] = {
	LSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	MSB_16(LAIRD_CONNECTIVITY_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	LSB_16(BT510_CODED_PHY_AD_PROTOCOL_ID),
	MSB_16(BT510_CODED_PHY_AD_PROTOCOL_ID)
};
const uint8_t BK_AD_HEADER[2] = { //BK company ID : 0x061A
	LSB_16(BECKETT_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	MSB_16(BECKETT_MANUFACTURER_SPECIFIC_COMPANY_ID1)
};
const uint8_t ATT_AD_HEADER[2] = { //ATT company ID : 0x6C1F
	LSB_16(ATT_MANUFACTURER_SPECIFIC_COMPANY_ID1),
	MSB_16(ATT_MANUFACTURER_SPECIFIC_COMPANY_ID1)
};