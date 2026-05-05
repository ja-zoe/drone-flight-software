#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "drone_common.h"

// Shared controls packet
control_packet_t control_packet;
SemaphoreHandle_t controlPacketMutexHandle;

// Shared telemetry packet
telemetry_packet_t telemetry_packet;
SemaphoreHandle_t telemetryPacketMutexHandle;

void app_main(void)
{

}
