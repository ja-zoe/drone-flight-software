idf_component_register(SRCS "main.c" "tasks/controls_receive_task.c"
                    INCLUDE_DIRS "." "tasks" "config"
                    REQUIRES driver nvs_flash esp_event esp_netif esp_wifi esp_driver_dac drone-software-common
                    )