#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include <stdint.h>
#include "mpu6050.h"
#include "config.h"
#include "devices.h"
#include "MadgwickAHRS.h"

void readSensorsTask( void *pvParameters ) {
  uint8_t counts = 0;
  
  /*------------------------------*/
  // Sensor Measurements
  /*------------------------------*/
  mpu6050_rotation_t gyro_meas;
  mpu6050_acceleration_t accel_meas;
  qmc5883p_data_t magnet_meas;
  float temperature, pressure, humidity;

  while(1) {
    /*------------------------------*/
    // Read gyroscope
    /*------------------------------*/
    if (counts % READ_GYRO_FREQ_DIV == 0) {
      mpu6050_get_rotation(&mpu6050, &gyro_meas);
    }
    /*------------------------------*/
    // Read accelerometer
    /*------------------------------*/
    if (counts % READ_ACCEL_FREQ_DIV == 0) {
      mpu6050_get_acceleration(&mpu6050, &accel_meas);
    }
    /*------------------------------*/
    // Read magnetometer
    /*------------------------------*/
    if (counts % READ_MAG_FREQ_DIV == 0) {
      qmc5883p_read_data(&qmc5883p, &magnet_meas);
    }
    /*------------------------------*/
    // Read barometer
    /*------------------------------*/
    if (counts % READ_BAROM_FREQ_DIV == 0) {
      bmp280_read_float(&bmp280, &temperature, &pressure, &humidity);
    }
    counts++;

    /*------------------------------*/
    // 
    /*------------------------------*/
    if ()
    float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz  
    MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

    vTaskDelay(pdMS_TO_TICKS(1/READ_SENSORS_TASK_FREQ_HZ));
  }
}