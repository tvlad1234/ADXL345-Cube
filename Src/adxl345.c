#include "adxl345.h"

#define ADXL345_REG_POWER_CTL 0x2D // power management register address
#define ADXL345_REG_DEVID 0x00	   // read-only register containing address (for testing communication)
#define ADXL345_REG_DATAX0 0x32	   // where accel data starts (Xh, Xl, Yh, Yl, Zh, Zl)

#define ADXL345_DEVICE_ID 0xE5

#define SENSORS_GRAVITY_EARTH (9.80665F)

float adxl_accel_multiplier = 0.004;

static const uint8_t ADXL345_ADDR = 0x53 << 1; // Use 8-bit address
I2C_HandleTypeDef *adxlPort;

uint8_t adxlBegin(I2C_HandleTypeDef *i2cdev)
{
	adxlPort = i2cdev;
	uint8_t a;

	HAL_I2C_Mem_Read(adxlPort, ADXL345_ADDR, ADXL345_REG_DEVID, 1, &a, 1,
					 HAL_MAX_DELAY);
	if (a != ADXL345_DEVICE_ID)
		return 0;

	a = 0;
	HAL_I2C_Mem_Write(adxlPort, ADXL345_ADDR, ADXL345_REG_POWER_CTL, 1, &a, 1,
					  HAL_MAX_DELAY);
	HAL_Delay(10);

	a = 16;
	HAL_I2C_Mem_Write(adxlPort, ADXL345_ADDR, ADXL345_REG_POWER_CTL, 1, &a, 1,
					  HAL_MAX_DELAY);
	HAL_Delay(10);

	a = 8;
	HAL_I2C_Mem_Write(adxlPort, ADXL345_ADDR, ADXL345_REG_POWER_CTL, 1, &a, 1,
					  HAL_MAX_DELAY);
	HAL_Delay(100);

	return 1;
}

void readADXLRawAccel(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t buf[6];
	HAL_I2C_Mem_Read(adxlPort, ADXL345_ADDR, ADXL345_REG_DATAX0, 1, buf, 6,
					 HAL_MAX_DELAY);
	*x = (buf[1] << 8 | buf[0]);
	*y = (buf[3] << 8 | buf[2]);
	*z = (buf[5] << 8 | buf[4]);
}

void readADXLAccel(float *gx, float *gy, float *gz)
{
	int16_t x, y, z;
	readADXLRawAccel(&x, &y, &z);
	*gx = ((float)x * adxl_accel_multiplier) * SENSORS_GRAVITY_EARTH;
	*gy = ((float)y * adxl_accel_multiplier) * SENSORS_GRAVITY_EARTH;
	*gz = ((float)z * adxl_accel_multiplier) * SENSORS_GRAVITY_EARTH;
}
