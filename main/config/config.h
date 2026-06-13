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

#define TELEMETRY_LOG_TASK_STACK_SIZE 4096

/* config.c functions */
void nvs_init(void);
void wifi_init(void);
void init_espnow(void);
void i2c_init(void);
