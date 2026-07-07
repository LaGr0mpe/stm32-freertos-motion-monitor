/*
 * gyro.c
 *
 *  Created on: 6 July 2026
 *      Author: ilya.voloshin
 */

#include "gyro.h"

#define GYRO_CS_GPIO_Port GPIOC
#define GYRO_CS_Pin 	  GPIO_PIN_1

#define GYRO_REG_WHO_AM_I 	   0x0F

#define GYRO_REG_CTRL1         0x20
#define GYRO_REG_CTRL2         0x21
#define GYRO_REG_CTRL3         0x22
#define GYRO_REG_CTRL4         0x23
#define GYRO_REG_CTRL5         0x24

#define GYRO_REG_STATUS        0x27
#define GYRO_REG_OUT_X_L       0x28
#define GYRO_REG_OUT_X_H       0x29

extern SPI_HandleTypeDef hspi5;

//HAL_StatusTypeDef Gyro_ReadReg(uint8_t reg, uint8_t *value)
//{
//	if (value == NULL)
//	{
//		return HAL_ERROR;
//	}
//
//	uint8_t tx[2] = {(uint8_t)(reg | 0x80U), 0x00U};
//	uint8_t rx[2] = {0};
//
//	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
//	HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(&hspi5, tx, rx, 2, 100);
//	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_SET);
//
//	if (st == HAL_OK)
//	{
//		*value = rx[1];
//	}
//	return st;
//}

GyroStatus_t Gyro_ReadReg(uint8_t reg, uint8_t *value)
{
	if (value == NULL)
	{
		return GYRO_ERROR;
	}

	uint8_t tx[2] = {(uint8_t)(reg | GYRO_SPI_READ),0x00U};
	uint8_t rx[2] = {0};

	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef hal_status  = HAL_SPI_TransmitReceive(&hspi5, tx, rx, 2, 100);
	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_SET);

	if (hal_status == HAL_TIMEOUT)
	{
		return GYRO_TIMEOUT;
	}

	if (hal_status != HAL_OK)
	{
		return GYRO_ERROR;
	}

	*value = rx[1];
	return GYRO_OK;
}


GyroStatus_t Gyro_WriteReg(uint8_t reg, uint8_t value)
{
	uint8_t tx[2] = {(uint8_t)(reg & GYRO_SPI_WRITE), value};

	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef hal_status = HAL_SPI_Transmit(&hspi5, tx, 2, 100);
	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_SET);

	if (hal_status == HAL_TIMEOUT)
	{
		return GYRO_TIMEOUT;
	}

	if (hal_status != HAL_OK)
	{
		return GYRO_ERROR;
	}

	return GYRO_OK;

}

GyroStatus_t Gyro_ReadWhoAmI(uint8_t *id)
{
	return Gyro_ReadReg(GYRO_REG_WHO_AM_I, id);
}

GyroStatus_t Gyro_Init(void)
{
	uint8_t whoami_id = 0;

	GyroStatus_t gyro_status = Gyro_ReadWhoAmI(&whoami_id);

	if (gyro_status != GYRO_OK)
	{
		return gyro_status;
	}
	if (whoami_id != GYRO_DEVICE_ID)
	{
		return GYRO_BAD_ID;
	}
	return GYRO_OK;

}


