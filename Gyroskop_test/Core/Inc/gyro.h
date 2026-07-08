/*
 * gyro.h
 *
 *  Created on: 6 July 2026
 *      Author: ilya.voloshin
 */

#include "main.h"
#include <stdint.h>
#include <stdbool.h>


#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#define GYRO_DEVICE_ID   0xD3U
#define GYRO_SPI_READ 	 0x80U
#define GYRO_SPI_WRITE   0x7FU

#define GYRO_MAX_BURST_LEN    		32U
#define GYRO_CALIBRATION_SAMPLES 	500U
#define GYRO_CALIBRATION_TRIES 		10U



typedef enum{
	GYRO_OK = 0,
	GYRO_ERROR,
	GYRO_TIMEOUT,
	GYRO_BAD_ID,
	GYRO_INVALID_ARG,
	GYRO_VERIFY_FAIL
} GyroStatus_t;

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
} GyroRawData_t;

typedef struct
{
	float x;
	float y;
	float z;
} GyroConvertedData_t;

typedef struct
{
	float bias_x;
	float bias_y;
	float bias_z;
	bool calibrated;
}GyroBias_t;


	GyroStatus_t Gyro_ReadWhoAmI(uint8_t *id);
	GyroStatus_t Gyro_ReadReg(uint8_t reg, uint8_t *value);
	GyroStatus_t Gyro_ReadMultiReg(uint8_t start_reg, uint8_t *buf, uint16_t len);
	GyroStatus_t Gyro_WriteReg(uint8_t reg, uint8_t value);
	GyroStatus_t Gyro_WriteMultiReg(uint8_t start_reg, const uint8_t *buf, uint16_t len);

	GyroStatus_t Gyro_Init(void);
	GyroStatus_t Gyro_ReadRaw(GyroRawData_t *data);
	GyroStatus_t Gyro_ReadConverted(GyroConvertedData_t *data);
	bool Gyro_RawSampleValid(GyroRawData_t *data);
	GyroStatus_t Gyro_CalibrateZero(uint16_t samples);
	void Gyro_ConvertToDps(const GyroRawData_t *raw_data, GyroConvertedData_t *converted_data);

	void Start_Gyro_SPI(void);
	void Stop_Gyro_SPI(void);

	//HAL_StatusTypeDef Gyro_ReadReg(uint8_t reg, uint8_t *value);

#endif /* INC_GYRO_H_ */
