# ADXL345-Cube
*ADXL345 Library for STM32Cube*\
Based on [Adafruit ADXL345](https://github.com/adafruit/Adafruit_ADXL345)

### Initializing the sensor
Before reading the sensor, it must be initialized with _adxlBegin_.\
_adxlBegin_ takes a pointer to the I2C Handler and returns 1 if connection was successful.\
_Example:_ `adxlBegin(&hi2c1);`

### Reading the sensor
`readADXLAccel(float *gx, float *gy, float *gz)` provides the acceleration in m/s^2 



