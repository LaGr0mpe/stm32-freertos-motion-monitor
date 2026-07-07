/*
 * gyro.h
 *
 *  Created on: 6 July 2026
 *      Author: ilya.voloshin
 */

#include "main.h"
#include <stdint.h>


#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#define GYRO_DEVICE_ID   0xD3U
#define GYRO_SPI_READ 	 0x80U
#define GYRO_SPI_WRITE   0x7FU

typedef enum{
	GYRO_OK = 0,
	GYRO_ERROR,
	GYRO_TIMEOUT,
	GYRO_BAD_ID,
	GYRO_INVALID_ARG
} GyroStatus_t;

	GyroStatus_t Gyro_Init(void);
	GyroStatus_t Gyro_ReadWhoAmI(uint8_t *id);
	GyroStatus_t Gyro_ReadReg(uint8_t reg, uint8_t *value);
	GyroStatus_t Gyro_WriteReg(uint8_t reg, uint8_t value);

	//HAL_StatusTypeDef Gyro_ReadReg(uint8_t reg, uint8_t *value);

#endif /* INC_GYRO_H_ */
