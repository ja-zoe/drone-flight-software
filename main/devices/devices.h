#pragma once
#include "mpu6050.h"
#include "qmc5883p.h"
#include "bmp280.h"

extern mpu6050_dev_t mpu6050;
extern qmc5883p_dev_t qmc5883p;
extern bmp280_t bmp280;

void init_mpu6050(void);
void init_bmp280(void);
void init_qmc5883p(void);