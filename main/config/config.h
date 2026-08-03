#pragma once

#define ESPNOW_PEER_ADDR_CONF {0x8c, 0xbf, 0xea, 0x8e, 0x51, 0x78}

/* Logging strategy */
#define LOG_MODE_NONE   0
#define LOG_MODE_SERIAL 1
#define LOG_MODE_TELEM  2

/* I2C Config */
#define I2C_PORT_CONF 0
#define SDA_GPIO_CONF 5
#define SCL_GPIO_CONF 6

/* ------------------------------ */
// Tasks Config
/* ------------------------------ */
#define READ_SENSORS_TASK_STACK_SIZE 4096
#define TELEMETRY_LOG_TASK_STACK_SIZE 4096

/* ------------------------------ */
// Read Sensors Task Config
/* ------------------------------ */
#define READ_SENSORS_TASK_FREQ_HZ 1000
#define READ_GYRO_FREQ_DIV 1
#define READ_ACCEL_FREQ_DIV 2
#define READ_MAG_FREQ_DIV 4
#define READ_BAROM_FREQ_DIV 8


#define RATE_CTRL_FREQ_HZ
#define ANGLE_CTRL_FREQ_HZ

/* config.c functions */
void nvs_init(void);
void wifi_init(void);
void init_espnow(void);
void i2c_init(void);
