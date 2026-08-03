#include "config.h"
#include "devices.h"

mpu6050_dev_t mpu6050;
qmc5883p_dev_t qmc5883p;
bmp280_t bmp280;

i2c_master_bus_handle_t i2c_bus_handle;

void init_mpu6050(void) {
  mpu6050_init_desc(&mpu6050, MPU6050_I2C_ADDRESS_LOW, I2C_PORT_CONF, SDA_GPIO_CONF, SCL_GPIO_CONF);
};

void init_bmp280(void) {
  qmc5883p_init(&qmc5883p, i2c_bus_handle, QMC5883P_I2C_ADDR_DEF);
};

void init_qmc5883p(void) {
  bmp280_init_desc(&bmp280, BMP280_I2C_ADDRESS_0, I2C_PORT_CONF, SDA_GPIO_CONF, SCL_GPIO_CONF);
};