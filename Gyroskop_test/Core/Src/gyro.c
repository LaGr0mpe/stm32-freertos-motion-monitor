/*
 * gyro.c
 *
 *  Created on: 6 July 2026
 *      Author: ilya.voloshin
 */

#include "gyro.h"
#include "stdlib.h"

#define GYRO_CS_GPIO_Port GPIOC
#define GYRO_CS_Pin 	  GPIO_PIN_1

#define GYRO_REG_WHO_AM_I 	   0x0FU

#define GYRO_SPI_AUTO_INC      0x40U

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

#define GYRO_CTRL4_FS_245DPS   0x00U
#define GYRO_CTRL4_FS_500DPS   0x10U
#define GYRO_CTRL4_FS_2000DPS  0x20U

#define GYRO_SENS_FOR_245DPS   0.00875f
#define GYRO_SENS_FOR_500DPS   0.01750f
#define GYRO_SENS_FOR_2000DPS  0.07000f

#define GYRO_CTRL4_SET 		   GYRO_CTRL4_FS_245DPS
static const float GYRO_SENS_DPS_PER_LSB = GYRO_SENS_FOR_245DPS;


extern SPI_HandleTypeDef hspi5;

static GyroBias_t gyro_bias = {0};

void Start_Gyro_SPI(void)
{
	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
}

void Stop_Gyro_SPI(void)
{
	HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_SET);
}

GyroStatus_t Gyro_ReadReg(uint8_t reg, uint8_t *value)
{
	if (value == NULL)
	{
		return GYRO_ERROR;
	}

	uint8_t tx[2] = {(uint8_t)(reg | GYRO_SPI_READ),0x00U};
	uint8_t rx[2] = {0};

	Start_Gyro_SPI();
	HAL_StatusTypeDef hal_status  = HAL_SPI_TransmitReceive(&hspi5, tx, rx, 2, 100);
	Stop_Gyro_SPI();

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

GyroStatus_t Gyro_ReadMultiReg(uint8_t start_reg, uint8_t *buf, uint16_t len)
{
    if ((buf == NULL) || (len == 0U) || (len > GYRO_MAX_BURST_LEN))
    {
        return GYRO_INVALID_ARG;
    }

    uint8_t tx[GYRO_MAX_BURST_LEN + 1U] = {0};   // 1 command byte + 6 dummy bytes
    uint8_t rx[GYRO_MAX_BURST_LEN + 1U] = {0};

    // Команда: READ + auto-increment + starting register
    // Для I3G4250D это чтение с OUT_X_L.
    tx[0] = (uint8_t)(start_reg | GYRO_SPI_READ | GYRO_SPI_AUTO_INC);

    Start_Gyro_SPI();
    HAL_StatusTypeDef hal_status = HAL_SPI_TransmitReceive(&hspi5, tx, rx, (uint16_t)(len + 1U), 100);
    Stop_Gyro_SPI();

    if (hal_status == HAL_TIMEOUT)
    {
        return GYRO_TIMEOUT;
    }
    if (hal_status != HAL_OK)
    {
        return GYRO_ERROR;
    }

    // rx[0] — мусор/служебный байт во время передачи команды
    // rx[1..6] — данные регистра подряд
    for (uint16_t i = 0U; i < len; i++)
    {
        buf[i] = rx[i + 1U];
    }

    return GYRO_OK;
}


GyroStatus_t Gyro_WriteReg(uint8_t reg, uint8_t value)
{
	uint8_t tx[2] = {(uint8_t)(reg & GYRO_SPI_WRITE), value};

	Start_Gyro_SPI();
	HAL_StatusTypeDef hal_status = HAL_SPI_Transmit(&hspi5, tx, 2, 100);
	Stop_Gyro_SPI();

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

GyroStatus_t Gyro_WriteMultiReg(uint8_t start_reg, const uint8_t *buf, uint16_t len)
{
    if ((buf == NULL) || (len == 0U) || (len > GYRO_MAX_BURST_LEN))
    {
        return GYRO_INVALID_ARG;
    }

    uint8_t tx[GYRO_MAX_BURST_LEN + 1U] = {0};
    uint8_t rx[GYRO_MAX_BURST_LEN + 1U] = {0};

    // Команда: WRITE + auto-increment + starting register

    tx[0] = (uint8_t)((start_reg & GYRO_SPI_WRITE) | GYRO_SPI_AUTO_INC);

    for (uint16_t i = 0U; i < len; i++)
    {
    	tx[i + 1U] = buf[i];
    }

    Start_Gyro_SPI();
    HAL_StatusTypeDef hal_status = HAL_SPI_TransmitReceive(&hspi5, tx, rx, (uint16_t)(len + 1U), 100);
    Stop_Gyro_SPI();

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
	uint8_t ctrl4_set = GYRO_CTRL4_SET;
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


	//Calibrate Zero
	for (int8_t i = 0; i < GYRO_CALIBRATION_TRIES; i++)
	{
		GyroStatus_t gyro_status_calibration = Gyro_CalibrateZero((uint16_t) GYRO_CALIBRATION_SAMPLES);
		if (gyro_status_calibration == GYRO_OK)
		{
			return GYRO_OK;
		}
	}

	return GYRO_ERROR;
}

GyroStatus_t Gyro_ReadRaw(GyroRawData_t *data)
{
    if (data == NULL)
    {
        return GYRO_ERROR;
    }

    uint8_t buf[6] = {0};
    GyroStatus_t status = Gyro_ReadMultiReg(GYRO_REG_OUT_X_L, buf, sizeof(buf));
    if (status != GYRO_OK)
    {
        return status;
    }

    data->x = (int16_t)((uint16_t)buf[1] << 8 | buf[0]);
    data->y = (int16_t)((uint16_t)buf[3] << 8 | buf[2]);
    data->z = (int16_t)((uint16_t)buf[5] << 8 | buf[4]);

    return GYRO_OK;
}

GyroStatus_t Gyro_CalibrateZero(uint16_t samples)
{
	if (samples == 0) return GYRO_INVALID_ARG;

	int64_t sum_x = 0;
	int64_t sum_y = 0;
	int64_t sum_z = 0;

	GyroRawData_t Raw_data;

	for (uint16_t i = 0; i < samples; i++)
	{
		GyroStatus_t status = Gyro_ReadRaw(&Raw_data);
		if (status != GYRO_OK) return status;

		if (!Gyro_RawSampleValid(&Raw_data))
		{
			sum_x = 0;
			sum_y = 0;
			sum_z = 0;
			return GYRO_ERROR;
		}
		else
		{
			sum_x += Raw_data.x;
			sum_y += Raw_data.y;
			sum_z += Raw_data.z;

			HAL_Delay(10);
		}
	}

	gyro_bias.bias_x = (float)sum_x / (float)samples;
	gyro_bias.bias_y = (float)sum_y / (float)samples;
	gyro_bias.bias_z = (float)sum_z / (float)samples;
	gyro_bias.calibrated = true;

    return GYRO_OK;
}

bool Gyro_RawSampleValid(GyroRawData_t *data)
{
    if (data == NULL)
    {
        return false;
    }

    if (abs(data->x) > 100 || abs(data->y) > 100 || abs(data->z) > 100) return false;
    return true;
}

void Gyro_ConvertToDps(const GyroRawData_t *raw_data, GyroConvertedData_t *converted_data)
{
	converted_data->x = (raw_data->x - gyro_bias.bias_x) * GYRO_SENS_DPS_PER_LSB;
	converted_data->y = (raw_data->y - gyro_bias.bias_y) * GYRO_SENS_DPS_PER_LSB;
	converted_data->z = (raw_data->z - gyro_bias.bias_z) * GYRO_SENS_DPS_PER_LSB;
}

GyroStatus_t Gyro_ReadConverted(GyroConvertedData_t *data)
{
    GyroRawData_t raw;

    GyroStatus_t st = Gyro_ReadRaw(&raw);
    if (st != GYRO_OK)
    {
        return st;
    }

    Gyro_ConvertToDps(&raw, data);

    return GYRO_OK;
}



