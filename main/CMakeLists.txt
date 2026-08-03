idf_component_register(SRCS "main.c" "tasks/controls_receive_task.c" "tasks/log_telemetry.c" "espnow/espnow.c" "config/config.c" "tasks/read_sensors_task.c" "devices/devices.c"
                    INCLUDE_DIRS "." "tasks" "config" "espnow" "devices"
                    REQUIRES driver nvs_flash esp_event esp_netif esp_wifi esp_driver_dac drone-software-common filters
                    )