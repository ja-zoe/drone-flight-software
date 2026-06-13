#include "esp_log.h"
#include "esp_now.h"
#include "freertos/FreeRTOS.h"
#include "drone_common.h"
#include "config.h"

static const char *TAG = "Receive_Task";

extern control_packet_t control_packet;
extern SemaphoreHandle_t controlPacketMutexHandle;

void controlsReceiveTask( void *pvParameters ) {
  static esp_err_t ret;
  static uint32_t lock_fail_count;
  static control_packet_t control_packet_in;
  static const uint8_t peer_addr[6] = ESPNOW_PEER_ADDR_CONF;

  configASSERT(controlPacketMutexHandle);

  while(1){
    if (xSemaphoreTake(controlPacketMutexHandle, pdMS_TO_TICKS(3)) == pdFALSE) {
      lock_fail_count++;
      ESP_LOGI(TAG, "Failed to take mutex on attempt %u", lock_fail_count);
      continue;
    }

    control_packet_in = control_packet;
    xSemaphoreGive(controlPacketMutexHandle);
    vTaskDelay(pdMS_TO_TICKS(5));
  };
};