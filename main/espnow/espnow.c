#include "espnow.h"
#include "esp_now.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "drone_common.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "Espnow";

extern control_packet_t control_packet;
extern SemaphoreHandle_t controlPacketMutexHandle;

static void espnow_send_cb(const esp_now_send_info_t *tx_info, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_FAIL) {
    printf("ESP now delivery failed\n");
  } else {
    printf("ESP now delivery sucecess\n");
  }
};

static void espnow_recv_cb(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len) {
  if (data == NULL || len <= 0) {
    ESP_LOGE(TAG, "Receive cb arg error");
    return;
  }

  if(xSemaphoreTake(controlPacketMutexHandle, pdMS_TO_TICKS(3)) == pdFALSE) {
    ESP_LOGE(TAG, "Failed to take mutex");
    return;
  }
    memcpy(&control_packet, data, len);
  xSemaphoreGive(controlPacketMutexHandle);
};

void init_espnow(void) {
  esp_err_t ret;

  ESP_ERROR_CHECK( esp_now_init() );
  ESP_ERROR_CHECK( esp_now_register_send_cb(espnow_send_cb) );
  ESP_ERROR_CHECK( esp_now_register_recv_cb(espnow_recv_cb) );

  /*---- Add esp-now peer ----*/ 
  esp_now_peer_info_t peer_info = {
    .peer_addr = ESPNOW_PEER_ADDR_CONF,
    .channel = 1,
    .ifidx = WIFI_IF_STA,
  };
  ret = esp_now_add_peer(&peer_info);
  ESP_ERROR_CHECK(ret);
}