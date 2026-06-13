#include "freertos/FreeRTOS.h"
#include "drone_common.h"
#include "config.h"
#include "esp_log.h"
#include "tasks_common.h"

const char *TAG = "Main";

// Shared controls packet
control_packet_t control_packet;
SemaphoreHandle_t controlPacketMutexHandle;

// Shared telemetry packet
telemetry_packet_t telemetry_packet;
SemaphoreHandle_t telemetryPacketMutexHandle;

void app_main(void)
{
/*---- Initialize nvs memory for persistent wifi credentials ----*/ 
  ESP_LOGI(TAG, "Initializing NVS memory...");
  nvs_init();
  ESP_LOGI(TAG, "Done initializing NVS memory");
/*---- Initialize WiFi ----*/ 
  ESP_LOGI(TAG, "Initializing WIFI...");  
  wifi_init();
  ESP_LOGI(TAG, "Done initializing WIFI");  
/*---- Initialize ESPNOW ----*/ 
  ESP_LOGI(TAG, "Initializing ESPNOW...");  
  init_espnow();
  ESP_LOGI(TAG, "Done initializing ESPNOW");  
/*---- Initialize I2C ----*/
  ESP_LOGI(TAG, "Initializing I2C...");  
  i2c_init();
  ESP_LOGI(TAG, "Done initializing I2C");

/*---- Create Shared Resources ----*/
  static StaticSemaphore_t controlPacketMutexBuffer;
  controlPacketMutexHandle = xSemaphoreCreateMutexStatic( &controlPacketMutexBuffer );
  configASSERT(controlPacketMutexHandle);
  
  static StaticSemaphore_t telemetryPacketMutexBuffer;
  telemetryPacketMutexHandle = xSemaphoreCreateMutexStatic( &telemetryPacketMutexBuffer );
  configASSERT(telemetryPacketMutexHandle);

/*---- Start Tasks ----*/
  // ====================================
  // Telemetry Log Task: log telemetry
  // ====================================
  TaskHandle_t telemetryLogTaskHandle = NULL;
  static StaticTask_t telemetryLogTaskBuffer;
  static StackType_t telemetryLogTaskStack[ TELEMETRY_LOG_TASK_STACK_SIZE ];
  telemetryLogTaskHandle = xTaskCreateStatic(
                logTelemetryTask,        // Function that implements the task.
                "Telemetry-Log-Task",    // Text name for the task.
                TELEMETRY_LOG_TASK_STACK_SIZE,// Number of indexes in the xStack array.
                NULL,                 // Parameter passed into the task.
                tskIDLE_PRIORITY,     // Priority at which the task is created.
                telemetryLogTaskStack,       // Array to use as the task's stack.
                &telemetryLogTaskBuffer );   // Variable to hold the task's data structure.
  configASSERT(telemetryLogTaskHandle);
  
  ay(pdMS_TO_TICKS(20)); 
}
