/*
 * gyro.c
 *
 *  Created on: 6 July 2026
 *      Author: ilya.voloshin
 */

#include "gyro.h"

#define GYRO_CS_GPIO_Port GPIOC
#define GYRO_CS_Pin 	  GPIO_PIN_1

#define GYRO_REG_WHO_AM_I 	   0x0FU

#define GYRO_REG_CTRL1         0x20U
#define GYRO_REG_CTRL2         0x21U
#define GYRO_REG_CTRL3         0x22U
#define GYRO_REG_CTRL4         0x23U
#define GYRO_REG_CTRL5         0x24U

#define GYRO_REG_STATUS        0x27U

#define GYRO_REG_OUT_X_L       0x28U
#define GYRO_REG_OUT_X_H       0x29U

#define GYRO_REG_OUT_Y_L       0x2AU
#define GYRO_REG_OUT_Y_H       0x2BU

#define GYRO_REG_OUT_Z_L       0x2CU
#define GYRO_REG_OUT_Z_H       0x2DU

#define GYRO_SET_CTRL_REG1     0x0FU

#define GYRO_CTRL4_FS_245DPS   (0x00U)
#define GYRO_CTRL4_FS_500DPS   (0x10U)
#define GYRO_CTRL4_FS_2000DPS  (0x20U)

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
	//Check WhoAmI register
	uint8_t whoami_id = 0;

	GyroStatus_t gyro_status_whoami = Gyro_ReadWhoAmI(&whoami_id);

	if (gyro_status_whoami != GYRO_OK)
	{
		return gyro_status_whoami;
	}
	if (whoami_id != GYRO_DEVICE_ID)
	{
		return GYRO_BAD_ID;
	}

	//Set CTRL_REG1 register
	uint8_t ctrl1_set = GYRO_SET_CTRL_REG1;
	GyroStatus_t gyro_status_write_ctrl1 = Gyro_WriteReg(GYRO_REG_CTRL1, ctrl1_set);
	if (gyro_status_write_ctrl1 != GYRO_OK)
	{
		return gyro_status_write_ctrl1;
	}

	uint8_t ctrl1_check = 0;
	GyroStatus_t gyro_status_read_ctrl1 = Gyro_ReadReg(GYRO_REG_CTRL1, &ctrl1_check);
	if (gyro_status_read_ctrl1 != GYRO_OK)
	{
		return gyro_status_read_ctrl1;
	}

	if (ctrl1_check != ctrl1_set)
	{
		return GYRO_VERIFY_FAIL;
	}

	//Set CTRL_REG4 register
	uint8_t ctrl4_set = GYRO_CTRL4_FS_245DPS;
	GyroStatus_t gyro_status_write_ctrl4 = Gyro_WriteReg(GYRO_REG_CTRL4, ctrl4_set);
	if (gyro_status_write_ctrl4 != GYRO_OK)
	{
		return gyro_status_write_ctrl4;
	}

	uint8_t ctrl4_check = 0;
	GyroStatus_t gyro_status_read_ctrl4 = Gyro_ReadReg(GYRO_REG_CTRL4, &ctrl4_check);
	if (gyro_status_read_ctrl4 != GYRO_OK)
	{
		return gyro_status_read_ctrl4;
	}

	if (ctrl4_check != ctrl4_set)
	{
		return GYRO_VERIFY_FAIL;
	}

	return GYRO_OK;
}

GyroStatus_t Gyro_ReadRaw(GyroRawData_t *data)
{
	if (data == NULL)
	{
		return GYRO_ERROR;
	}

	//Read raw X axis
	uint8_t raw_X_H = 0;
	uint8_t raw_X_L = 0;
	GyroStatus_t status = Gyro_ReadReg(GYRO_REG_OUT_X_L, &raw_X_L);
	if (status != GYRO_OK)
	{
		return status;
	}
	status = Gyro_ReadReg(GYRO_REG_OUT_X_H, &raw_X_H);
	if (status != GYRO_OK)
	{
		return status;
	}


	//Read raw Y axis
	uint8_t raw_Y_H = 0;
	uint8_t raw_Y_L = 0;
	status = Gyro_ReadReg(GYRO_REG_OUT_Y_L, &raw_Y_L);
	if (status != GYRO_OK)
	{
		return status;
	}
	status = Gyro_ReadReg(GYRO_REG_OUT_Y_H, &raw_Y_H);
	if (status != GYRO_OK)
	{
		return status;
	}

	//Read raw Z axis
	uint8_t raw_Z_H = 0;
	uint8_t raw_Z_L = 0;
	status = Gyro_ReadReg(GYRO_REG_OUT_Z_L, &raw_Z_L);
	if (status != GYRO_OK)
	{
		return status;
	}
	status = Gyro_ReadReg(GYRO_REG_OUT_Z_H, &raw_Z_H);
	if (status != GYRO_OK)
	{
		return status;
	}

	data->x = (int16_t)((raw_X_H << 8) | raw_X_L);
	data->y = (int16_t)((raw_Y_H << 8) | raw_Y_L);
	data->z = (int16_t)((raw_Z_H << 8) | raw_Z_L);

	return GYRO_OK;
}





