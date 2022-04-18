#ifndef _ADXL345_H
#define _ADXL345_H

#include "main.h"

uint8_t adxlBegin(I2C_HandleTypeDef *i2cdev);
void readADXLAccel(float *gx, float *gy, float *gz);

#endif /* _ADXL345_H */
