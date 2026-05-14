idf_component_register(SRCS "main.c" "tasks/controls_receive_task.c" "tasks/log_telemetry.c" "espnow/espnow.c" "config/config.c"
                    INCLUDE_DIRS "." "tasks" "config" "espnow"
                    REQUIRES driver nvs_flash esp_event esp_netif esp_wifi esp_driver_dac drone-software-common
                    )