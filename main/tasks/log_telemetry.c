#include "freertos/FreeRTOS.h"
#include "drone_common.h"
#include "esp_log.h"

static const char *TAG = "Telemetry Log";

extern control_packet_t control_packet;
extern SemaphoreHandle_t controlPacketMutexHandle;

control_packet_t control_packet_in;

void logTelemetryTask( void *pvParameters ) {
  while (1) {
    if(xSemaphoreTake(controlPacketMutexHandle, pdMS_TO_TICKS(3)) == pdFALSE) {
      ESP_LOGE(TAG, "Failed to take mutex");
      return;
    }
      control_packet_in = control_packet;
    xSemaphoreGive(controlPacketMutexHandle);

    ESP_LOGI(TAG, "\nTHROTTLE: %d\nYAW: %d\nPITCH: %d\nROLL: %d", control_packet_in.joysticks_values.throttle, control_packet_in.joysticks_values.yaw, control_packet_in.joysticks_values.pitch, control_packet_in.joysticks_values.roll);
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}